# Runtime Environment vs Frameworks vs SDK
A runtime environment is where we run our application. It's responsibilities include:
- Memory allocation
- Garbage collection
- Thread execution
- I/O
It knows how to run the application on your machine.
This is exactly what Node.js is. It's powered by its V8 engine.
.NET Runtime is powered by its engine CLR (Common Language Runtime)
The end user (consumer) uses this to run the application on their machine

A framework provides you with utilities and libraries (classes, functions, etc.) that you need for common tasks, so you don't have to re-invent the wheel. It takes care of repetitive tasks under the hood and abstracts them out. That's exactly what Express does.
ASP.NET

SDK provides us the tools to build, run, and test our application. These tools include the .NET CLI, compilers, project templates, dependency mangement tools, etc.. SDK can be configured to use different runtime environments. 


Think about it like building a car:
A factory



Before .NET 5, the .NET ecosystem was a mess of runtimes and partially overlapping APIs, each serving a different environment
So, you had five or six different .NETs, all with subtly incompatible libraries, build systems, and deployment models.
It was confusing because you never knew what library worked with what version of .NET
Then came out .NET 5 and Microsoft merged the runtimes, SDKs, and BCL (Base Class Library) into a single family.