`std::cin()` considers all whitespace characters as delimiter. Thus, it stops recording input upon encountering whitespace characters, such as a space. We may consider using the `std::cin.getline()` function which, by default, treats the new line character (`\n`) as a delimiter. In addition to a character array variable, `std::cin.getline()` can optionally take the maximum number of input characters we want to take in, and a custom delimiter as arguments:
```C++
std::cin.getline(char[], int, char);
```

The number of input characters as set by `std::setw()` also includes the null point terminator (`\0`). Thus, the actual number of readable characters in an array will be its length minus 1.

## `fstream`
`fstream`, `ifstream`, `ofstream` all extend a common interface. `fstream` does both input and output streams. `ifstream` specializes input file stream, and `ofstream` does output.

There are several ways to gather input from a file using the `ifstream` class.
```c++
std::ifstream inputStream("filename.txt");
char ch;
while (std::inputStream.get(ch)) {
	std::cout << ch;
}
```
The loop above prints the contents of the text file character by character. `std::ifstream::get()` returns 1 (evaluated as `true`) if successful, or 0 (`false`) in case of a fail.

```c++
std::string input;
while (std::getline(inputStream, input, '\n')) {
	std::cout << input << std::endl;
}
```
**Note**: `std::getline()` returns a reference to an `istream` object. The `istream` class overrides the `bool()` operator such that an `istream` object is evaluated to `true` if the operation completes error free, and `false` if there are errors. This makes it possible to use `std::getline(inputStream, input)` directly in a `while` loop condition.

```c++
std::string input2;
while (inputStream >> input2) {
	std::cout << input2 << std::flush;
}
```

Recall that for streams (including `iostream`) `std::fstream::operator>>()` (which is what is actually called when we write `inputStream>>input2`) returns a "stream" object, which as we explained above, can be evaluated to a Boolean.

Here's a function that reads and returns contents of a file
```c++
std::string read_file(const std::string& filename)
{
  std::string file_text = "John Q. Smith\nThis is my test string";
  std::string nextLine;
  std::fstream fileReader;
  try {
      fileReader.open(filename);
      if (fileReader.is_open()) {
          while (std::getline(fileReader, nextLine)) {
              file_text += nextLine;
          }
          fileReader.close();
      }
      else {
          throw std::runtime_error("Could not open file " + filename);
      }
  }
  catch (std::exception& e) {
      std::cout << e.what() << std::endl;
  }

  return file_text;
}
```