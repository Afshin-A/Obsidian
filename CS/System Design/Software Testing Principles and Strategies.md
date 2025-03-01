### Testing Principles
<ul>
<li>Exhaustive testing is not possible. We can't test absolutely everything (because of limited resources and time).</li>
<li>Test the most important features first. Use the associated risk to determine the level of importance.</li>
<li>Defect Claustering. A small number of modules contain the most number of defects. Derived from the 80/20 rule, which states "80% of all outcomes are derived from 20% of causes". </li>
<li>Pesticide Paradox : The same tests will not find new defects. So, we must frequently add and revise test cases to find more defects</li>
<li> Absense of errors is a fallacy. A program can never be bug-free </li>
<li> Testing can only show the presense of defects. It can't prove there are no defects. </li>
<li> Early testing. Testing should start as early as possible in SDLC. The longer you move in the wrong direction, the farther you are from the correct destination. </li>
<li> Testing is context dependent. Different programs should be tested in different ways: an online shopping website will be tested differently than single player video game, for example.</li>
</ul>

### SDLC (Software Development Life Cycle) A.K.A the Waterfall Method
Requirements -> Design -> Build (Implementation) -> Test -> Maintenance

### STLC (Software Testing Life Cycle) and the V-Model
Waterfall method withholds testing until the Testing phase. This is bad practice because we need to test as early as possible. So to combat this, we implement a corresponding testing phase for each phase in the developement cycle.
![[Pasted image 20221116004221.png]]

Requirement analysis - gathering requirements
Functional specification - architecture, database, environmental design
High level design - breaking down the application into modules
Detail design - pseudocode
Coding - the actual coding

#### Levels of testing
##### Unit testing (component testing)
Testing a standalone module (this could be a function, class, or group of classes) to ensure it works.

##### Integration testing
Testing to ensure two or more related modules work well together. Sometimes one of these modules is ready to test before the other necessary modules. Instead of waiting for other developers to finish, we can create a basic mock-up made for the purpose of testing, to mimic the other module. These are called "stub" or "driver". If the module we're testing needs to send data to another module that is not ready yet, we can create a stub. Likewise, a driver is a mock-up module that sends data to the module we're testing.

##### System testing
Testing end-to-end scenarios to ensure the system works as a whole. An end-to-end situation is a real world example where a user interacts with the system normally: Login -> Check balance -> Transfer dosh -> Logout
It also checks for non-functional requirements. 

##### User acceptance testing
The client tests the software to ensure it meets their requirements. Types of user acceptance testing are alpha and beta testings.

##### Other Test Types
###### Sanity/Smoke Testing
If you are a tester working with a developer, make sure to run basic tests to ensure the system health before accepting to do exhaustive testing.

###### Regression Testing
This is performed to ensure that after fixing defects and making changes in one module, the remaining system still functions well. It's to prevent unintended side effects.

###### Black Box Testing
Testing is done without looking at the underlying code or system architecture (structure)



### Iterative Life Cycle (i.e. Agile)
Developement is held in stages, and each stage has a life cycle.




### Testing Case vs. Testing Scenario
A **test scenario** is like a high level category that describes what main functionality of the system needs to be tested in generic terms. An example would be logging into the system.
We can break down testing scenarios into low-leveled, managable **testing cases** that are more specific and detailed. Examples include, "test for user entering valid username and password", "test for user entering invalid username and password", "test for user leaving the fields empty", and so on. 
A test scenario categorizes multiple test cases.
All this information is stored in a **test case specification chart**. In addition to the test scenario and test case columns, we could have pre-conditions for the system before we begin performing a test case, the data used for the test, the expected results from the test, the actual results from the test, the steps taken to conduct the test (so that the tests are reproducable), whether the test has passed or failed.
![[Pasted image 20221116001339.png]]

Traceability: It is good practice to label our test cases as a way of connecting them to a specific functional requirement and to a business requirement, so that in case there are changes to the requirements, we can we can track down and add to/change the test cases. 

Test Basis
How do we come up with tests? Obviously we need to have something to test. This could be the actual Application Under Test (AUT), from our experience, or, most commonly, from documentation. Documentaion is produced during each step of SDLC. We can come up with tests before the program is even written using those documents (such as functional specification documentation)

### Business Requirements vs. Functional Requirements vs. Non-functional Requirements

Functional requirements are about what the system should do.  These come directly from the customers. "The program should do this, and that, etc.."

Non-functional requirements are about how the system should behave. They're usually the byproduct of implementing the functional requirements. For example, "the program should do this in X number of seconds."


### Testing Techniques
#### Equivalence Partitioning
Suppose our program asks the user to enter how many copies of a document to print. The program can print anywhere between 1 to 10 copies. We can, for example, partition the range of possible inputs from the user into: negative, zero, 1 to 10, above 10, above 100. Obviously we can't create a test case for every single possible entry. Instead, we can create a test case for a range of values (because all values in a range would produce the same result).

#### Decision making table (cause-effect table)
If instead of literal values 

#### State Transition Diagram
A diagram that shows how the state of a program changes based on what decisions are taken, allowing the  testers to see what paths the program could take, and consequently what to test. This is drawn by using circles (that represent states) and arrows (which represent transitions). Above the arrows you would write the events that cause the transition to occur from one state to another.

It is also possible to to summarize a stage transition with a table, where you have states on the columns and events on the rows.
![[Pasted image 20221116183809.png]]
So state S1 after "Correct Password" would result in state S6 (which means access, for example).

#### Use Case Testing
<a href="https://youtu.be/zid-MVo7M-E">Use case diagram</a>

A use case diagram summarizes a system by providing a high level overview of its functions (modules). It shows actors and use cases (how actors could potentially interact with the system)

<a href="https://upload.wikimedia.org/wikipedia/commons/thumb/1/1d/Use_case_restaurant_model.svg/800px-Use_case_restaurant_model.svg.png"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/1d/Use_case_restaurant_model.svg/800px-Use_case_restaurant_model.svg.png" width="300" height="300" /></a>

Use case diagrams could show us examples of how the users interact with our system, and what we have to test.

#### Static Testing
Static testing is analyzing a system/program without executing it. An example is reviewing documentation to make sure there are no errors that could result in disaster in the later stages of developement.

#### Work product
It could by anything produced during developement, including documentation (like design documents and system requirement specifications), code, test plans.

General Review process in a team: 
1. Planning: author hands the work product to the manager, who would overview and suggest any quick fixes needed, then sets up a meeting (time and place) for the  team to get together and review the work product.
2. Kick-off: The reviewers study the material and prepare for the meeting.
3. Review meeting: The reviewers gather together and discuss/make suggestions.
4. Rework: The author incorporates the agreed upon changes into his/her work.
5. Follow up: the revised work is passed back to the participants to ensure all changes are incorporated.

### Test Plan Vs. Test Case



### Test Driven Development
In this type of development, we first create test cases from user stories. The user story would indicate what exactly is expected from the program when given some input data.
Then, we would iteratively create and edit code until it passes the test.


### CI CD (Continuous Integration / Continuous Development) pipeline
From CS-320 M8 weekly post:
Software testing automation techniques, such as CD/CI, improve efficiency by providing swift feedback to the developers. The process roughly works as follows: developers submit their work to an online server that runs a framework (like CircleCI). The new build is then bombarded with a variety of pre-written tests, including unit tests, integration tests, and end-to-end system tests. Finally, feedback: changes are either integrated into the system upon successful test results, or are rejected and the developers are provided with feedback (error logs).
This method eliminates many redundant tests, allowing the QA team to focus on the more important and subtle tasks concerning the non-functional requirements of the system, like performing security tests, integration and end-to-end system testing. As a result, the production cycle shortens and software with higher quality is delivered faster.
Following this process, the line between quality engineers and software developers is dissipating. The roles of testers and developers intertwines, with each role performing more duties traditionally defined for the other. As technology enhances and new AIs are developed, soon there might no longer be a need for software testers, or developers. The rise of robots is imminent!
The pros of software automation (hitherto described) outweigh the cons. Since automated testing would perform the bulk of testing, the tests should be designed and reviewed extra carefully avoid false results.


Need -> Feature -> Requirements (Specification)
Software elicitation -> Modeling -> analysis -> design -> implementation
Meet with the customer, get the requirements, elaborate on those requirements and make plans, come up with architecture and how to build the system, code the system, test the system, release and provide support.

Simultaneously to project developement, testing can begin 
Analysis -> Test planning (test plan document) -> Test design


#### Testing Mindset
When testing, your goal shouldn't be to prove there are no defects. In that aim, you may be tempted to write easy test. Instead, your goal should be to show defects. 


#### Best Practices for Testing:
1. Keep it simple. 
2. Don't waste time testing trivial methods like setters and getters
3. Give test cases meaningful names and make use of JUnit's `@DisplayName` annotation
4. Single responsibility principle: a test case should test only 1 system requirement
5. 