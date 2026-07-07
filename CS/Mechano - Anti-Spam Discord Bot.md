A common scam that is currently happening on Discord communities, is that a compromised account pings a popular role in every channel of the server. It's usually followed by a message about crypto or a popular streamer. Seeing that Discord's auto mod and 3rd party moderation bots have been unable to stop these attacks, I've decided to implement my own solution. Introducing: Mechano—A discord bot designed to stop Discord spam. 

<!-- ![](https://media.discordapp.net/attachments/941556065806471219/1514098852976922654/Mechano.gif?ex=6a32b3b1&is=6a316231&hm=20aba0bc10e5815b0757931696424418c2fa046bbba8fea5bf0011ee22c64b62&) -->

We establish a WebSocket connection to the Discord API and listen in for all messages sent in the server.
Bot listens to the `MessageCreate` events
We implement the Producer-Consumer pattern in order to process user messages in order and prevent influx and server overrun. The `MessageCreate` event handler is the producer: it pushes incoming message payloads into a thread-safe queue. We then have multiple background workers analyzing messages to detect spam.

We use the sliding window rate limiting algorithm to detect if a user surpasses their allowed message quota. 
For each user, we create a `userID` $\to$ `deque[(userMessage, messageTime)]` entry in a thread-safe dictionary.

We use a double-ended queue data structure to leftpop and append in `O(1)` time, making it the most efficient approach.
When a new message is sent, it is added to the end of the deque. 
Older messages are pruned out of the deque. 

HTTP PATCH request updates existing resource, unlike PUT which entirely replaces 
We patch the user into timeout mode

