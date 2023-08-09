## XOR Logic
Let's consider the concept of exclusive or with an example.
1. You must have a bachelors degree or 2 years of experience to be eligible for a promotion.
2. You can take $20 or this mystery box.

It is pretty obvious that in case 1, there wouldn't be an issue if you have both a bachelors degree and 2 years of experience. Translating this to logic, `true OR true` gives `true`.
In case 2, you can either take the $20 OR the mystery box, but not both. In other words, both cannot be `true`. Thus, `true OR true` is false. This is an example of the exclusive OR (XOR). 
The XOR operation evaluates to `true` only if exactly one of the operands is `true`.

An important property of XOR is that it's commutative:
$$
A \oplus B = B \oplus A
$$

XOR is also symmetric. In other words:
$$
\begin{align}
(A \oplus B ) \oplus B & = A \\
(B \oplus A ) \oplus A & = B \\
\end{align}
$$

## How does XOR Encryption Work?
To start, we need something to encrypt, like a word, and an encryption key. Each letter in the word can be converted to binary numbers that represent that letter according to the character encoding (like ASCII). The encryption key should be random and as long as the word we're encrypting. 
Then, we perform the XOR operation on the word and key. For example, to encrypt the letter `F`, we find that its ASCII value is 70, which in binary is 01000110. We also need a key: 11010101. I just randomly pressed 0s and 1s on my keyboard 8 times! To do XOR by hand, we just need to remember that 1 means `true` and 0 `false`, and follow the rules from [[streams#XOR]]. We do this for every bit and get:
$$
\begin{align}
& 0 \ 1 \ 0 \ 0 \ 0 \ 1 \ 1 \ 0 \\
& 1 \ 1 \ 0 \ 1 \ 0 \ 1 \ 0 \ 1 \\
\hline
& 1 \ 0 \ 0 \ 1 \ 0 \ 0 \ 1 \ 1 \\
\end{align}
$$
We then loop around the remaining letters in the word and do the same thing (using the same key)

## How to Decrypt
Recall that $A \oplus B$ is symmetric. If $A$ is the word and $B$ the key, then $A \oplus B$ is the encrypted word. If we take the XOR of the encrypted word and the key, we get back the original word, because
$$
(A \oplus B ) \oplus B = A
$$
In other words, since we're doing the same operation, we only need one algorithm to encrypt as well as decrypt.

## Implementing XOR in C++

```c++
std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
  // get lengths now instead of calling the function every time.
  // this would have most likely been inlined by the compiler, but design for perfomance.
  const auto key_length = key.length();
  const auto source_length = source.length();

  // assert that our input data is good
  assert(key_length > 0);
  assert(source_length > 0);

  std::string output = source;

  // loop through the source string char by char
  for (size_t i = 0; i < source_length; ++i) {
    // transform each character based on an xor of the key modded constrained to key length using a mod
      output[i] = source[i] ^ key[i % key_length];
  }

  // our output length must equal our source length
  assert(output.length() == source_length);

  // return the transformed string
  return output;
}
```