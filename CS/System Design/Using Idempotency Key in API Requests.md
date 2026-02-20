Imagine a customer makes a purchase and a network outage occurs. Their browser could keep repeating the request until it goes through. Or the user could keep refreshing. Or is sending the request via an API link. Or, a malicious [[Relay Attacks|relay attack.]]  
Idempotency keys are there to make sure requests stay **idempotent**. 

# Idempotency
A request is idempotent if you make it multiple times and it has the same effect.
For example, 
- *HTTP GET is idempotent* because a read request returns the same data each time without having any other effect.
- *HTTP PUT is idempotent* because the same PUT request (used for updating a resource on a server) just updates the same resource.
- *POST is **not** idempotent*. A POST request (used for sending data to the server and/or creating a resource) can potentially cause different effects—at least, not without some logic to prevent duplicate requests. Back to the payment example, how do we make sure that a request is not a duplicate so we don't charge the customer multiple times? Furthermore, what if the customer really did mean to buy the same thing twice?

We need a clear way to distinguish from requests. This is referred to as **idempotency key**, and it can really be anything, as long as it's unique for each request. A *request id* immediately comes to mind. The key is typically consisted of three parts as a measure to ensure it is globally unique across all server URLs and other users:
- `user-id`
- `request-endpoint`
- `request-id`

```
user-id_request-endpoint-url_request-id
```

We need to store idempotency-key and its response body using a dictionary. A unique key gets mapped to a response body.

**HOWEVER**, It is possible we receive a different request (different body) that uses a repeat idempotency key, either through client error, malicious attacks, or just by sheer chance (because request ids are randomly generated). To counter this, we also need store the hash of the request body in the response.
```json
{ 
	"request_hash": "a1b2c3d4...", // SHA-256 of the incoming request body/params 
	"status": "COMPLETED", // or "IN_PROGRESS"
	"response_payload": { // The result we want to replay 
		"id": 999, 
		"status": "paid", 
		"amount": 5000
	}, 
	"response_code": 200,
	 "expiry": 1715629000 // TTL (Time to Live) 
}
```

When a request first comes in, we first check in the database:
1. If the idempotency key already exists, and the hash of the incoming request matches what we stored in the value (saved response), we can safely detect a duplicated request and  just return the previously saved response to the user, without having to process the request again.
2. If the idempotency key exists and the hash of the incoming request does not match the the hash stored in the value, then this is an error. It means there was either request tampering or there was some sort of error due to attempting to use the same idempotency key for different requests. So we return an error.
3. If a key-value pair doesn't exist, we process the request, return a response to the user, then create a key-value pair in the database.


How long do we need to keep these in the database? It depends on the nature of the application. Typically anywhere between 24 to 48 hours is enough. However, it could be as low as 10 minutes. We just need to see what makes sense for the nature of our application.

IF using dynamoDB or Redis, use TTL (time-to-live) to automatically remove items after a certain time

We also need to be careful when using a load-balancer and Redis. If we're using something like Docker containers to run our application, and each container gets its own Redis instance, then we can't really share data between our instances and duplicate requests could still slip by. So instead we need to use a centralized database that all instances of our application have access to.