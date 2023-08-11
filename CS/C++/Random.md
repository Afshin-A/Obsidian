## Pseudo-Random

```c++
#include <ctime>
#include <cassert>
#include <cstdlib>
int getPseudoRandomNumber(int min, int max) {
	// max should be greater than min
	assert(max > min);
	// Setting the seed for the rand() function
	std::srand(std::time(nullptr)); 
	
	return (std::rand() % (max - min)) + min;
}
```

## True Random
