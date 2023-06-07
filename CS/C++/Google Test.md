Google Test, also known as gTest or gMock, is a C++ library for unit testing.


There are 3 scenarios when unit testing:
- Success. The test passes. 
- Non-fatal failure. Even though the test fails, the test case continues executing past the failing point until the end of the test case is reached.
```c++
TEST(TestCase, Test1) {
	EXPECT_EQ(1, 2);
	// more code. This will execute regardless
}
```
- Fatal failure. Execution of test case is immediately paused when the test fails and the program flow jumps to the next test case.
```c++
TEST(TestCase, Test2) {
	ASSERT_EQUAL(1, 1);
	// more code. This will not execute if above statement fails.
}
```


More (non-fatal) assertions. There are also fatal versions of these, where `EXPECT` is replaced by `ASSERT`.
```c++
EXPECT_EQ(...) // Expect equal
EXPECT_NE(...) // Expect not equal
EXPECT_LT(...) // Expect less than
EXPECT_LE(...) // Expect less than or equal to
EXPECT_GT(...) // Expect greater than
EXPECT_GE(...) // Expect greater than or equal to
EXPECT_STREQ(...)
EXPECT_STRCASEEQ(...)
EXPECT_STRCASENE(...)
```

We should not have multiple assertions in a single test case. Each test case should have a very specific purpose. In addition, regardless of how many assertions there are in a test case, it will fail as long as a single assertion fails, making it difficult to know exactly which assertion failed.

Tests should be independent of each other, should not rely on external input, and should run in a matter of milliseconds.

Test Fixtures
When writing unit tests, you may find yourself with duplicate code across multiple unit tests. For example, instantiating a class that you need to run tests on. Instead, we can define a test fixture class that automatically instantiates the common code for each test case.

```c++
class Stack {
public:
	void push(int value) { vstack.push_back(value); }
	int pop() {
		if (vstack.size() > 0) {
			int value = vstack.back();
			vstack.pop_back();
			return value;
		}
		else {
			return -1;
		}
	}
	int size() { return vstack.size(); }
private:
	std::vector<int> vstack = {};
};

// Test Fixture: setup for test cases
// We can define this as either a class or a struct
struct stackTest : public testing::Test {
	Stack s1;
	void SetUp() override {
		int value[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		for (auto& val : value) {
			s1.push(val);
		}
	}
	void TearDown() override {}
};

// TEST is now TEST_F 
// It takes the test fixture and test case name as arguments
TEST_F(stackTest, PopTest) {
	int lastPoppedValue = 9;
	while (lastPoppedValue != 1) {
		ASSERT_EQ(s1.pop(), lastPoppedValue--);
	}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

```