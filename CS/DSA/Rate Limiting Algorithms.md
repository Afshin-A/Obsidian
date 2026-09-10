Limiting user messages in a Discord server using two rate limiting strategies of sliding window and leaky bucket.
# Sliding Window
In general, this algorithm is used to answer a specific question: how many events happened during a specific window of time?
This is applied to count API calls, errors in an application, 


Can precisely enforce a rule like:
> No more than 5 messages in a 10 second window

We keep track of user messages using a map:
```python
user_messages = {
	user_id: deque(...)
}
```
Messages are already ordered by the time they're sent. 
When a new message is sent, it gets appended to the deque. We loop through the deque from the start and pop left any messages that are too old. The messages left is how many messages this user has sent over the allowed window. If it surpasses the allowed threshold, we time out the user.
```python
WINDOW = 10
THRESHOLD = 20
history = user_messages[user_id]

now = time.time()

history.append(now)

while history and history[0] < now - WINDOW:
	history.popleft()

if len(history) > THRESHOLD:
	timeout(user_id)

```

If the rule is no more than 5 messages in 10 seconds, then the moment a user sends a 6th message, we can identify a spammer. Which means we don't need any more than 6 entries in the deque. 

One more note about memory management in the sliding window method.
As a user sends more messages, we start from the beginning of that user's deque and clean messages outside of the time window of interest. But when a user stops sending messages, their old and expired messages would stay in the deque. So we need to way to actively remove them.

We could use a `last_seen` entry in the map. 
```python
user_state = {
    user_id: {
        "messages": deque(),
        "last_seen": now
    }
}
```
We'll update the `last_seen` entry whenever a new message is sent. Then, every hour or so, we query  and delete the inactive from the dictionary. 
```python
if now - state.last_seen > 1 hour:
    delete user
```

We can also use an **expiring cache** with a TTL. Many cache libraries like **Redis** support this.
Lastly, we can use a heap that stores a tuple of `(expiration_date, user_id)` to frequently keep popping expired dictionary elements:
```python
while heap[0][0] <= now:
	delete user_messages[heap.heappop()]
```

How would you apply the sliding window to other applications?
# Leaky Bucket / Token Bucket
Suppose max tokens allowed for a user is 10 and the token regen is 1 token/s 
When `t=0s`, user A sends 10 messages. Now they're out of tokens and have to wait 1s to send another message. 1 message/s becomes the average frequency they're allowed in the long term.
But suppose user A waits until `t=9s` to send another 9 messages. So in 9 seconds, user A has sent 19 messages. 
The leaky bucket doesn't have the exactness of the [[Rate Limiting Algorithms#Sliding Window|sliding window]] because it doesn't users' store message history. It only stores the time stamp of the last message sent and the number of tokens a user has left. When It does arithmetic to find if a user has any tokens left. 


$$
\Large
\text{tokens =
}\min\Large(\text{max tokens}, \underbrace{{\lfloor\text{now}-\text{last message time}\rfloor}\times \text{refill rate}+\text{tokens}}_{\text{Net tokens gained since last message was sent}}\Large)

$$
We don't ever want the user to have more than the maximum allowed number of tokens, so we use the $\min$ function to lower the count of tokens if it's ever than max allowed.

Here's the logic for allowing or timing out a user in code
```python
tokens = min(
    max_tokens,
    tokens + (now - last_refill_time) * refill_rate
)

last_refill_time = now
if tokens >= 1:
    tokens -= 1
    allow()
else:
    reject()
```

