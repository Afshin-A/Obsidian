User logs in
Server creates a session id, stores it in memory or database, and sends it back to the client (browser)
The client stores it as a cookie 
The client sends the session id with each subsequent request
The server checks the session id against the value it has to authenticate the user


# Session Authentication problems
## Cross Site Request Forgery (CSRF)

A user logs in their bank account. With help from social engineering, attackers could send an email with a link to an action in the bank's server, such as transferring money. Because the user is already logged in, the session id sent with the malicious link is valid.

This is less likely to happen because modern web development frameworks include counter measures to this attack.

## Horizontal scaling






