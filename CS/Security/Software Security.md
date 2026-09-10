Tools to test security of APIs and web servers. They can intercept HTTP requests
- Burp Suite
- OWASP ZAP
- OWASP WebScarab
- and the Firefox plug-in Tamper Data


[IETF](https://en.wikipedia.org/wiki/Internet_Engineering_Task_Force)


```
cach-control: no-cache, no-store, must-revalidate
Expires: -1
```

`No-cache` says that the browser should revalidate the data with every request.
`No-store` says that no part of the request or response should be stored at all in the first place.
`Must-revalidate` says that under no circumstances should stale content be served by the browser
`Expires` tells the browser when the content should expire and thus be requested again from the server.

Care must be taken to ensure that such static content is cached, but any sensitive or user-specific data is never stored.

HSTS - `Strict-Transport-Security` 
```
Strict-Transport-Security: max-age=315
```
This tells the browser to use HTTPS when contacting our server for the next 315 seconds. Only works when connection protocol is HTTPS.


HTTPS offers:
- Confidentiality - no one can see the data
- Integrity - no one can change the data 
- Authenticity - SSL certificates ensure the data is coming from a trustworthy source
>Make sure to force your entire website to HTTPS from the moment you deliver a login page until the user is done logging out!

[check your SSL configuration is Qualys SSL Labs, run by Ivan Ristic. The site offers a free suite of tests to detect any misconfigurations in your server’s SSL setup.](https://www.ssllabs.com/ssltest/)

# Clickjacking
A form of malicious attack where users are tricked into thinking they're clicking on something, while they're actually clicking somewhere else.
`X-Frame-Options` header is used to combat this attack.

# Cross-Site scripting (XSS)
`X-XSS-Protection: 1; mode=block`
Force enables this form of protection against XSS attacks. Only works on IE. Doesn't work all the times, but it helps.

# ReDOS
Regular expression denial of service occurs when validation an input with a regular expression increases exponentially as the input length increases.

Tool for testing regex expressions: https://github.com/jkutner/saferegex?tab=readme-ov-file


Don't depend on input validation alone (specially if validating text boxes) Pair it with query parameterization, encoding, and escaping.


# Authentication
## Techniques
- Don't reinvent the wheel. Design a robust system and reuse it in new projects
- Use CAPTCHA to protect against bots. Use an invisible field. If it's field, a bot probably filled it.



# Man in the middle attack



# Session Fixation
HTTP is stateless. After a user has logged in, we use cookies to store a `sessionid` that keeps users logged in. 
Session fixation happens when attackers get access to that `sessionid` and get complete access to an application on behalf of an authenticated user.
Attackers would get a `sessionid` from the application, embed it in a link, then send it to unsuspecting users, who would then sign in with that same `sessionid`. So, what 