JCA - Java Cryptography Architecture
JCE - Java Cryptography Extension

Secure Sockets Layer (SSL) - cryptographic protocol
Transport Layer Security (TLS) is the modern version of SSL. The two acronyms are often used interchangeably.

## The certificate system
A server adopts a certificate that is signed by a certificate authority (CA). When a client connects, the server would send the certificate over, and the client assesses wether it is signed by an authority it trusts. If it is, then a connection is established.
The clients (browser, SDK, or Java applications) store a list of CAs it trusts,

While we may not have to worry about low level details of TLS if we are writing code behind a web server or client that handles it for us, we cannot trust the said server and client because they may form connections regardless of veracity of certificates. So always test the system with bad or expired certificates.

## Using TLS in Java
JSSE (Java Secure Socket Extension).
A socket is a virtual channel that is used for communication between a client and a server.

```java
import javax.net.ssl.*;

...
SocketFactory sf = SSLSocketFactory.getDefault();
Socket socket = sf.createSocket(host, port);

```

The `SocketFactory` class uses the [[Factory|Factory design pattern.]]

You can manually set the `socket` to use the latest TLS versions:
```java
socket.setEnabledProtocols({"TLSv1.1", "TLSv1.2"});
```

## Cipher Suites
Combination of algorithms used by TLS for security in sockets

### How to Read Cipher Suit Names



### Forward Secrecy 
Forward secrecy uses ephemeral session keys for each communication to prevent decrypting past communication messages, even if a server's private keys are leaked to attackers. Use cipherr suites with `ECDHE` or `DHE`. Warning: these suites may not be supported by all systems.
**If both parties don't support a cipher suit, then the connection will fail.**


### How to setup cipher suites
```java
String[] ciphers = {
	"TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA",
	"TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA"
};

socket.setEnabledCipherSuites(ciphers);
```

