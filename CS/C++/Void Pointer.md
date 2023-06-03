These allow you to store the address of any variable types. But you cannot dereference them without first casting the void pointer to a specific 
```c++
void testFunction(void* ptr, char type) {
	switch (type):
		case 'i':
			std::cout << *((int*)ptr) << std::endl;
			break;
		case 'c':
			std::cout << *((char*)ptr) << std::endl;
			break;
}

int main() {
	int num = 1;
	testFunction(&num);
}
```