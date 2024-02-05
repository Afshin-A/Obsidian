After we have gathered extensive information on system requirement from the client, we need to start making a design. At this state, we don't want to prematurely start implementing the system, so we're only talking logical, not physical. Physical comes after the requirements of the system (functional and non-functional) are agreed upon. We want to trace the processes in the system. What does the system do?
A DFD diagram is a simple that shows the flow of data. Typically, data enters the system from an external source (like user input), it is operated on by system modules (classes), passed to other system modules, stored in the system, or sent to another external system. DFD diagrams show a high level view of this. It's similar to a UML diagram or a flowchart, but it only uses 4 symbols, so it's much simpler and only focuses on the information logic. These are two systems used to represent the symbols:
- Source/Sink: these are external to the system
- Process
- Data store
- Data flow
![[Fig07-002.png | 200]]
 
The second system is better because it provides space (the green area) to number processes.

More often than not, a process or task (like getting ready for work) can be broken to sub processes. When we create a DFD, we start with a **context diagram** that has only 1 task. 

~~For future reference, I centered this image by enabling `css` snippets in obsidian settings. There's a `css` file under `Obsidian/.obsidian/snippets`~~

![[Fig07-004.png | center | 300]]

Notice ==the arrows tell us what data is being transferred.== You can have multiple arrows if more than one data is being transferred.


We incrementally evolve our diagram by breaking that task into subtasks, adding more details. This is called **functional decomposition**. The following is called a level 0-diagram. Notice that the processes are numbered 1.**0**, 2.**0**, and so on.
![[Fig07-005.png| center | 400]]

We can create a level 1 diagram by breaking down the processes from the level 0 diagram. We'd number these as 1.1, 1.2, 1.3, and so on. And, if possible, we break 1.1 to 1.1.1, 1.1.2, and so on.

The lowest level data flow diagram is called the primitive DFD.

Make sure the diagrams are consistent (everything matches), not redundant (everything has a unique purpose and nothing overlaps).

Here's another example:
![[Fig07-022.png| center | 600]]

Valacich, J. S., George, J. F., & Hoffer, J. A. (2019). _Modern Systems Analysis and Design_ (9th ed.). Pearson Education (US). [https://bookshelf.vitalsource.com/books/9780135172827](https://bookshelf.vitalsource.com/books/9780135172827)
Chapter 7