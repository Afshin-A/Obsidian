Asymmetric Encryption
This uses a pair of independent keys: a public key, and a private key. Only the private key can be used to decrypt a message encrypted by the public key, and vice versa.
For example, when transmitting a message, the other party will use my public key to encrypt it. I will use my private key to decrypt. Because the private key is secret, only I can decrypt the message.

If I use my privae key to encrypt a message, then anyone can use the public key to decrypt the message. What is the point of it, then?
Since only my public key can decrypt the message, then we can be sure the message was encrypted using my private key, hence the message must from me.

We can combine these two ideas to make sure 
- No one else can read the message
- The message was from the right person
First, we encrypt the message with our private key. Then we encrypt the message with your public key.
The other party will have have to go backwards: first they will have to decrypt the message using their private key first, then our public key.
If the outcome message doesn't make sense, something must have gone wrong. Either the message was not encrypted using my private key