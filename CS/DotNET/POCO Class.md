Plain old c# object
A class that stores data and does not have dependencies on any external frameworks.
I first encountered this acronym while learning about the [[DOT NET Generic Host|.NET generic host framework]].
We can bind configuration that is fed into the application (via env variables, config files, command line args, etc.) to the fields of a class, therefore getting modular access to the configuration anywhere in the application via the dependency injection system.

```c#
await Host.CreateDefaultBuilder(args)
.ConfigureServices((hostContext, services) => 
{
services.Configure<UQOptions>(hostContext.Configuration);
})
.Build()
.RunAsync(); 
```