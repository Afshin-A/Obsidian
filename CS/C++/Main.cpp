//#define	ndebug

#include <cassert>
#include <iostream>
#include <string>

namespace project {
	template <typename t>
	size_t size(t array[]);
}

template <typename t>
void print(const t);

int main() {

	//int array[5];
	//
	//size_t initialarraysize = project::size(array);
	//print(initialarraysize);

	//print(strlen("hello world! "));


	//for (int i = 0; i < project::size(array); i++) {
	//    array[i] = 1;
	//}
	
	//
	//for (int i = 0; i < project::size(array); i++) {
	//    std::cout << array[i] << std::endl;
	//}

	const char* stringliteral = "i'm a string literal";

	char charArray[] = { "hi" };
	char* cString = charArray;

	const char* stringLiteral2 = cString;

	charArray[0] = '1';

	print(*charArray);
	print(*cString);
	print(*stringLiteral2);

	int length{ 2,};
	print(length);
}


template <typename t>
size_t project::size(t array[]) {
	if (sizeof(array[0]) > 0) {
		//std::cout << sizeof(array) / sizeof(array[0]) << std::endl;
		return sizeof(array) / sizeof(array[0]);
	}
	return 0;
}

template <typename t>
void print(const t arg) {
	std::cout << arg << std::endl;
}