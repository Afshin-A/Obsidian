This is an [[Cryptography in Python#Asymmetric Encryption|asymmetric algorithm]].
Two parties share public components of a key, then use the private parts to create a key no one else has access to. In an end-to-end encryption, this is done before every message is sent.

A Symmetric is needed to perform cryptographic operations.

combine public variables with private ones to create a key both parties can derive.


First, Alice and Bob must agree on two mathematical parameters, `g` and `a`. These are available public for all to see, including attackers.
`g` is called the generator, a relatively small prime number, and `n` is a large prime number (often `2,000` bits long, sometimes `4,000`).

Next, Alice and Bob both come up with their own private keys.
Next, Alice and Bob use `g` to create public keys. Now, this operation involves modular arithmetic and is irreversible. I.e. private keys cannot be calculated from public keys.

Then, Alice will use Bob's public key and use her private key and derive a secret key. This key is also derived by Bob when he uses his private key with Alice's public key.
This key can then be used for cryptographic purposes.

`n` cannot be too large otherwise the procedure becomes less efficient.
`a` is a random number such that:
$$\begin{align}
1 < a < n \\
\text{public\_key}_{\text{alice}}=g^a \mod n
\end{align}
$$
Similarly,
$$\begin{align}
1 < b < n \\
\text{public\_key}_{\text{bob}}=g^b \mod n
\end{align}
$$

# Fermat's Little Theorem
