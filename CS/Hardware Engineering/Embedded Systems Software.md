# Bit field
## Commonly used in C libraries to select options 
Example:
```c
#define TS_BUF_LENGTH 30 
// define options
#define LOG_TIME  0X01 //0b00000001
#define LOG_DATE  0X02 //0b00000010
#define LOG_USER  0X04 //0b00000100
#define LOG_COUNT 0X08 //0b00001000
#define LOG_ALL   0XFF //0b11111111
#define FULL_TIME 0X01 //0b00000011

void logMessage(FILE* fp, char* message, uint_8 option) {
	static uint64_t logCount = 0;
	time_t timeVal;
	char timeStamp[TS_BUF_LENGTH];
	char dateStamp[TS_BUF_LENGTH];
	
	// ...
	
	if (option & LOG_COUNT)
		fprintf(fp, "%lli, ", ++logCount);
	if (option & LOG_DATE)
		fprintf(fp, "%s, ", dateStamp);
	if (option & LOG_TIME)
		fprintf(fp, "%s, ", timeStamp);
	if (option & LOG_USER)
		fprintf(fp, "%s, ", getLogin());
		
	fprintf(fp, "%s\n", message);
}

int main() {
	logMessage(stdout, "Error", LOG_ALL); // All ifs will return true
}
```
[Source: Jacob Sorber (YouTube) Bit Fields in C. What are they, and how do I use them?](https://youtu.be/aMAM5vL7wTs)

## Save memory
?

# Paper
Embedded systems are equipped with limited memory and processing power. Therefore, as programmers, in addition to writing code that is bug-free and easy to read and maintain, we must take extra care to write code that efficiently utilizes system resources. For embedded C we must follow best coding practices in areas such as bit manipulation, volatile, memory utilization, cross compiling, state machines, variable scope, and stack management. We will also address common pitfalls to avoid. 

bit manipulation gives programmers low level access to alter data at the bit level, which is 
we can combine bitwise operations to create masks, which allow us to set or get specific bits from a number. 
