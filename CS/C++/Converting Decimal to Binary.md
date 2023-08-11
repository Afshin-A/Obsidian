In C++, we can use the `bitset` class to convert integers to binary.

```c++
#include <bitset>
#include <iostream>

int main() {
	char charToConvert = 'c';
	std::bitset<8> binaryNumber(charToConvert);
	std::cout << binaryNumber << std::endl;
}
```

There are 2 ways to initialize `bitset`. The most common way is with an integer. Here, the char is implicitly converted to an integer (its ASCII representation). The `8` in `bitset<8>` from the example above specifies how many bit we'd like to use to represent the binary number.

`bitset` can also be initialized with a string of 0s or 1s.

```c++
	std::bitset<8> binaryNumber2("10100011");
```

# Algorithm (Binary Remainder Method)
We can represent any positive integer using any base besides 10.
The decimal numbers we use daily are base 10. That means we use 10 digits, ranging from 0 to 9, to represent every other number. Mathematically, we can write them as multiples of powers of 10. For example, 345 can be represented like this:
$$
345=3 \times 10^2 + 4 \times 10^1 + 5 \times 10^0
$$
If we divide 345 by 10, we're left with a remainder of 5, the right most digit in 345. That's because every other digit in 345 has a multiple of 10:
$$
\begin{align}
{345 \over 10} & = {3 \times 10^2 \over 10} + {4 \times 10^1 \over 10} + {5 \times 10^0 \over 10} \\
& = 30 + 4+ {5 \over 10}
\end{align}
$$
We can apply the same logic to the quotient 34 and get the next digit:
$$\begin{align}
34 = 3 \times 10^1 + 4 \times 10^0 \\
{34 \over 10} = 3 + {4 \over 10}
\end{align}
$$
We continue while the quotient is greater than 0. During the last iteration, we are left with $3 \times 10^0=3$. Doing one more iteration leaves a quotient of 0 and remainder of 3. So when the quotient is 0, we know we've already extracted the final digit and stop stop the loop. 

We can apply the same logic to convert decimal numbers to binary. We start by writing 345 in base 2:
$$
\begin{align}
345 & = 256 + 89 \\
& = 256 + 64 + 25 \\
& = 256 + 64 + 16 + 9 \\
& = 256 + 64 + 16 + 8 + 1 \\
\end{align}
$$
$$
\begin{align}
345 & = 2^8 + 2^6 + 2^4 + 2^3 + 2^0 \\
& = 1 \times 2^8 + 0 \times 2^7 + 1 \times 2^6 + 0 \times 2^5 + 1 \times 2^4 + 1 \times 2^3 + 0 \times 2^2 + 0 \times 2 ^ 1 + 1 \times 2^0 \\
\end{align}
$$
Already, just by looking at the base 2 if you made it this far, say I love dinosaurs 3 times in a row representation of `345`, we can see it is `101011001` in binary. In our algorithm, we will continuously divide the quotient by 2 and store the remainder. Therefore,
$$\begin{align}
{345 \over 2} & = {1 \times 2^8 + 0 \times 2^7 + 1 \times 2^6 + 0 \times 2^5 + 1 \times 2^4 + 1 \times 2^3 + 0 \times 2^2 + 0 \times 2 ^ 1 + 1 \times 2^0 \over 2} \\
& = \Big(1 \times 2^7 + 0 \times 2^6 + 1 \times 2^5 + 0 \times 2^4 + 1 \times 2^3 + 1 \times 2^2 + 0 \times 2^1 + 0 \times 2 ^ 0\Big)+{1 \over 2} \\
\end{align}
$$
So the remainder 1 will be the right-most digit in the binary form. Just as before, we repeat the process with the quotient to get the next digit, and so on.

Note that we are essentially extracting these digits from right to left. But when we store them in a string, we're storing them from left to right. So we need to reverse the string to get the correct binary number.

```c++
std::string decimalToBinary(int decimal, int base = 2) {
	std::string binary;
	int remainder;
	int quotient = decimal;
	do {
		remainder = quotient % base;
		quotient /= base;
		binary += std::to_string(remainder);
	} while(quotient > 0);
	return std::reverse(binary.begin(), binary.end());
}
```

We can easily extend this function to convert into bases up to hexadecimal since letters (`'A', 'B', ... 'F'`) can be used to represent remainders as large as 15.

```c++
std::string decimalToBinary(int decimal, int base = 2) {
	std::string binary;
	int remainder;
	int quotient = decimal;
	do {
		remainder = quotient % base;
		quotient /= base;
		if (remainder <= 9) {
			binary += std::to_string(remainder);
		}
		else {
			switch (remainder) {
			case(10):
				binary += "A";
				break;
			case(11):
				binary += "B";
				break;
			case(12):
				binary += "C";
				break;
			case(13):
				binary += "D";
				break;
			case(14):
				binary += "E";
				break;
			case(15):
				binary += "F";
				break;
			default:
				throw std::runtime_error("Remainder was greater than 15");
			}
		}
	} while (quotient > 0);
	std::reverse(binary.begin(), binary.end());
	return binary;
}
```


Avoid using the `+=` operator for string concatenation because it will copy create a new string and copy all the elements over, which can be expensive for large strings. It can also lead to [[memory fragmentation]].  Instead, we can use a `stringstream` object, which dynamically manages a buffer that can be converted to a string. We can also use the `std::string::push_back()` method, which avoids the unnecessary creation of intermittent string objects.

We can improve the code by adding input validation, using `stringstream`, and replacing the `switch` statement with a clever way of converting the remainders to their ASCII character representations. 
```c++
#include <sstream>
#include <string>

std::string decimalToBinary(int decimal, int base = 2) {
	if (decimal < 0) {
		throw std::invalid_argument("Decimal value cannot be negative");
	}
	if (base < 2 || base > 16) {
		throw std::invalid_argument("Base cannot be negative or larger than 16");
	}

	std::string binary;
	int remainder;
	int quotient = decimal;
	std::stringstream ss;
	
	do {
		remainder = quotient % base;
		quotient /= base;
		if (remainder <= 9) {
			ss << remainder;
		}
		// if remainder is in {10, 11, ... 15}
		else {
			// if remainder is 10, we want to add A to ss
			// if it's 11, we want to add B, wihch is A+1
			// if it's 12, we want to add B, wihch is A+2
			ss << static_cast<char>('A' + (remainder - 10));
			}
	} while (quotient > 0);

	// convert stringstream to string
	binary = ss.str();
	// reverse the string
	std::reverse(binary.begin(), binary.end());

	return binary;
}
```