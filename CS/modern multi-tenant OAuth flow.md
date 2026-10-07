---
~
---

Trying to connect to the Instagram API
Add a tester
Generate a token for the tester prompts the user to log in
```
www.instagram.com/accounts/login/?force_authentication=true&next=%2Foauth%2Fauthorize%2F%3Fclient_id%3D1622358879552824%26logger_id%3D14c936c1-2e4e-4d0a-b4d7-877d1702f2ed%26redirect_uri%3Dhttps%253A%252F%252Fdevelopers.facebook.com%252Finstagram%252Ftoken_generator%252Foauth%252F%26response_type%3Dcode%26scope%3Dinstagram_business_basic%252Cinstagram_business_manage_messages%252Cinstagram_business_manage_comments%252Cinstagram_business_content_publish%252Cinstagram_business_manage_insights%26state%3D%257B%2522app_id%2522%253A%25221622358879552824%2522%252C%2522f3_request_id%2522%253A%252214c936c1-2e4e-4d0a-b4d7-877d1702f2ed%2522%252C%2522nonce%2522%253A%25223chHSoJCDAUshEIQ%2522%252C%2522requested_permissions%2522%253A%2522instagram_business_basic%252Cinstagram_business_manage_messages%252Cinstagram_business_manage_comments%252Cinstagram_business_content_publish%252Cinstagram_business_manage_insights%2522%252C%2522user_id%2522%253A%252217841470940121360%2522%257D&request_id=14c936c1-2e4e-4d0a-b4d7-877d1702f2ed
```



It's not a good idea to place a secret access token in the URL of a GET request because browsers and proxy servers cache these.

We're safe to send a request like this from a flask application because it uses HTTPS and is therefore end-to-end encrypted. It never touches a user's browser.
```

```