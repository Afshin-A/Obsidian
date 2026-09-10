Microsoft's .NET is an open-source software development platform/ecosystem that provides everything we need to make and run applications. Everything divides into 3 categories: (==need a better introduction)
- Runtime
- Libraries
- Tools
- programming languages, languages libraries/frameworks, and runtime environments
# Runtime Environment vs Frameworks vs SDK
### Runtime
A **runtime environment** is where we run our application. It sits between your application and the operating system. 
The runtime environment includes:
- Just in time compiler ( #JIT)
- Memory allocation
- Garbage collection
- Threads
- I/O
It knows how to run the application on your machine.
This is exactly what Node.js is. It's powered by its V8 engine.
.NET Runtime is powered by its engine **CLR** (Common Language Runtime)
The end user (consumer) uses this to run the application on their machine


```
Source code -> Compiler -> intermediate language (MSIL) -> .Net runtime -> machine code -> CPU 
```


The compiler creates assemblies, which are either .exe or .dll (dynamic linked library) files.
.NET languages compile to intermediate language. 
.dll files contain IL, metadata, and assembly instructions, that is defined to run on the .net runtime environment.
So you end up with *interoperable assemblies*. That means you can access and use these .dll files from other .NET programming languages. *.NET separates the language from the execution platform*. But just because we can use a .dll created by C# in F# or vice versa, doesn't mean we should, since some concepts don't map across different programming languages. In other words, the common runtime makes languages interoperable; it doesn't make the languages equivalent.

### Libraries
A **framework** provides you with utilities and libraries (pre-written classes, functions, etc.) that you need for common tasks, so you don't have to re-invent the wheel. It takes care of repetitive tasks under the hood and abstracts them out. For example, Express is a framework.

.NET libraries live under namespaces such as:

```
System
System.Collections
System.IO
System.Net.Http
System.Threading
System.Threading.Tasks
```


### Tools
An **SDK** provides us the tools to develop and build applications. These tools include the .NET CLI, compilers, project templates, dependency management tools, package managment tools, etc.. 
The SDK can be configured to use different runtime environments. 

CLI
IDE - Visual Studio.


The C# compiler is called **Roslyn**.
The compiler converts source code (C#, F#, MS Visual Basic) to **Common Intermediate Language (CIL)**, also known as Microsoft IL, or just IL, which is then converted by the .NET Common Language Runtime (CLR) Just-In-Time (JIT) to machine instructions.


**MSBuild** is the underlying build system. It uses XML-based project file schema (.csproj files) that contain instructions/configuration on how to build the application. TypeScript developers should recognize the similarity between configuring the typescript compiler...

**NuGet** is .NET's package management ecosystem.


# Frameworks Built on Top of .NET
### ASP.NET

### Entity Framework (EF) Core
It's an ORM

### UI Frameworks
#### WPF
long-established framework for building **Windows desktop applications** with .net
uses **XAML** to describe the UI
Supports concepts such as:
- XAML
- data binding  
- controls
- graphics
- MVVM

#### WinUI
newer UI technology for **Windows applications**
Also known as Windows App SDK

WinUI is used to build modern windows desktop apps, while WPF is still relevant
#### .NET MAUI
Supports multiple operating systems. Write code once for an app that works on Windows, Android, and Mac


# .NET Components


Before .NET 5, the .NET ecosystem was a mess of runtimes and partially overlapping APIs, each serving a different environment
So, you had five or six different .NETs, all with subtly incompatible libraries, build systems, and deployment models.
It was confusing because you never knew what library worked with what version of .NET
Then came out .NET 5 and Microsoft merged the runtimes, SDKs, and BCL (Base Class Library) into a single family.


# How Just in Time Compiler Fits in .NET
```embed
title: "Just-In-Time (JIT) Compilers Explained"
image: "https://i.ytimg.com/vi/KVvGVPc7QM8/maxresdefault.jpg"
description: "❤️ Get 40% OFF CodeCrafters: https://app.codecrafters.io/join?via=the-coding-gopher💌 Business Inquiries & Partnerships: thecodinggopher@gmail.com👨‍💻 Suppo..."
url: "https://youtu.be/KVvGVPc7QM8"
favicon: ""
aspectRatio: "56.25"
```

compilers - ahead of time compilation, produces an executable in machine language. Optimized and fast. OS loads and prepares the executable and the CPU executes the instructions inside it.
interpreters - read and execute code line by line and produce results. no executables. slow. 

JIT is something between AOT compilers and interpreters. It produces bytecode, which is an intermediate language that runs on a virtual machine.
IL then runs on the .NET CRL virtual machine.
Bytecode is platform independent.
JIT is a component inside the virtual machine that compiles bytecode into machine code while the program is running. It's a smart interpreter. It translates code line by line, but as the program continues, it identifies **hot paths** which are parts of the code that run frequently, like functions. It creates machine code for those parts and stores it in memory and reused. Over time more and more of the program is converted to machine code. 
So it *starts slow but approaches native speeds*, all while allowing developers to write code independent of the system. 
JIT makes **adaptive optimizations** by continuously monitoring the application and making dynamic optimization. It makes guesses and makes optimizations, but if it turns out it was wrong, it backtracks and falls back to interpreting the code, and tries making optimizations again.
.NET uses **RyuJIT** as its JIT.



# MVVM – Model–View–ViewModel
An architectural pattern for building UI applications. It's not exclusive to .NET, however it is standard
Divides the application to three parts. Each 
View - the UI
View model - acts as an intermediary between the UI and the underlying application. It's essentially a model of the View.
Model - data

Without MVVM, we would have to put the application logic in the UI, tightly coupling the two, which is bad practice.



separation of logic from the UI



# .NET Versions

### .NET Framework
The original .NET implementation by Microsoft
Windows only
Still in use today for maintaining older applications
Latest version is 4.8
### .NET Core
Microsoft developed a new implementation of .NET because the original was limited. It added runtime and memory optimizations, dependency injection system, containerization support, and many more. 
Latest version is 3.1

### .NET 10
After .NET Core 3.1, Microsoft dropped the name "Core" and moved up to version 5 (to avoid confusing it with the last version of .NET Framework, which is 4.8). It's now simply called .NET. They released versions 5, 6, all the way to 10.
Microsoft unified all implementations (.NET Framework, .NET Core, Xamarin) starting with .NET 5
That means .NET Framework 4.8 applications are still supported on Windows

### What is .NET Standard?
This is not an implementation of .NET. It's *not a runtime*.
It's a specification for APIs that a standard implementation of .NET must provide.

Anyone can create an implementation of .NET because core parts of the platform are standardized and open-source. 

With different versions of .NET (.NET Framework and .NET Core) diverging, we need a way to make libraries 


Fewer and fewer libraries still support .Net framework


### Version Compatibilities
A DLL compiled against .NET Framework might contain IL just like a DLL compiled for modern .NET, but it can depend on APIs, runtime behavior, or framework components that aren't available in modern .NET.


## Storcad's Explanation
1. .Net Framework is the original set of libraries that C# / VB.Net were written to utilize. The major versions were 1, 2, 3.5, 4.0, and 4.5+. The latest is 4.8.x. It was quite Windows-centric. Several years ago, they restarted with a new set of libraries that had a focus on cross-platform compatibility and named it .Net Core. That went from v1 -> v2 -> v3 -> v3.1. They decided to skip version 4 (to avoid confusion with .Net Framework 4.x) and went from .Net Core 3 to .Net 5 (and then 6, 7, 8, 9, and soon 10).
    
2. There's also ".Net Standard" which was sort of a bridge that allowed for libraries that both .Net 4.x and .Net Core could use.
    
3. tl;dr: it's a bit of a mess.

4. Moving it to .Net 8 would mean that it could use libraries that support .Net Core / .Net. Most libraries in the last ten years are for .Net Core / .Net rather than .Net Framework.
    
5. There's also lots of improvements in the C# language that aren't available in .Net Framework. (.Net Framework is limited to an older version of C#.)


# Visual Studio
F12 takes you to class/method definition
