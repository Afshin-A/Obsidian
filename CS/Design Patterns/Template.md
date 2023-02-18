> Create a group of subclasses that have to execute a similar group of methods

This pattern includes a "template" method, which serves as an algorithm. An algorithm is nothing but a series of steps used to achieve a certain result. Here, our algorithm is the steps (or methods) to make a sandwich.
The template method is in an abstract class, and has abstract methods left to be implemented by subclasses.
[Refactoring.guru](https://refactoring.guru/design-patterns/template-method) offers a great example of this design pattern in action.
Suppose you're designing a program that can `mine()` data from word `docx` documents. The algorithm is something like this:
```
mineData() {
	openFile()
	extractData()
	parseData()
	analyzeData()
	sendReport()
	closeFile()
}
```
Later as you expand this program to read `.pdf` files, you might discover it involves rewriting much of the same code from the algorithm used for `.docx` files: the only difference between `.pdf` and `.docx` files could be `extractData()` and `parseData()`.

```java
public abstract class ParseFile {
	// The algorithm is not abstract. But it contains abstract methods.
	// It will be inherited by subclasses, which must provide implementation for aforementioned abstract methods.
	// It just works. And makes sense.
	public void mineData(String filePath) {
		if (isFilePathValid(filePath)) {
			openFile();
			extractData();
			parseData();
			analyzeData();
			sendReport();
			closeFile();
		}
	}
	
	public abstract void extractData();
	public abstract void parseData();

	// This method functions the same way for every subclass type. But it can still be overriden should there be need.
	public void openFile() {
		// file opening logic
	}
	public void analyzeData() {
		// data analyze logic. Don't ask me the difference between this method and parseData() ...
	}
	public void sendReport() {
		// sending report logic
	}
	public void closeFile() {
		// file closing logic
	}

	// This method is called a "hook" and serves as a condition in the "template" method, deciding which parts of the algorithm would run and which parts will not. 
	// It can be overriden in subclasses as needed.
	public boolean isFilePathValid(String path) {
		boolean val = true;
		// implement logic
		return val;
	}
}

public class ParseDocxFile() extends ParseFile {
	@Override
	public void extractData() {
		// Logic for extracting data from docx files
	}
	@Override
	public void parseData() {
		// Logic for parsing data from docx files
	}
}

public class ParsePdfFile() extends ParseFile {
	@Override
	public void extractData() {
		// Logic for extracting data from pdf files
	}
	@Override
	public void parseData() {
		// Logic for parsing data from pdf files
	}
}
```