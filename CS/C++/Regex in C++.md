```c++
#include<regex>
int main() {
	const char* rule = "[a-zA-Z0-9]";
	std::regex pattern(rule);
	//regex_search returns true if a substring of the string matches the rule.
	if (std::regex_search(input, pattern)) {
		//...
	}
	//regex_match returns false if the entire string does NOT match the rule
	if (std::regex_match(input, pattern)) {
		//...
	}
}
```