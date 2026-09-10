The allowed character set in URLs is defined by **the Internet Engineering Task Force (IETF)** through a formal technical specification known as a **Request for Comments (RFC)**. 
The IETF is an open international community of network designers that develop, propose, and publish internet standards.
RFCs are used by various groups (aside from IETF) to propose new ideas, technical specifications, or changes to internet standards, and invite the public to review and collaborate.

Yes, there are far more than 4,000 documents; there are currently over 10,000 published RFCs, of which only about 160 to 180 are accepted. Combined together, they form about 90 **Internet Standards**.

**RFC 3986** defines the generic syntax for Uniform Resource Identifiers (URIs) and URLs across the internet, things like the protocol naming system (`http:`), queries (`?key=value`),  allowed characters (`A-Z`, `a-z`, `-`,`_`,`.`.`~`), and reserved characters (`:`,`/`,`?`,  etc.).

# Why is character encoding necessary?
Because a URL may contain a character outside of the allowed set defined by RFC 3986. All other characters must be converted to something that can be understood. For example, spaces get converted to either `%20` or `+`.

==As developers, we should always use libraries built inside the programming language to guarantee accuracy. ==
For example, in JavaScript, we use the function `encodeURIComponent()` to safely encode a string for use as a query parameter or path segment in a URL 
