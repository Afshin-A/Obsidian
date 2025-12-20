
`IConfiguration`

all settings from various sources (setting files, env variables, command line args, etc.) go into `IConfiguration`

For the command line source, it is possible to allow different flags to translate to the same configuration using what's called switch mapping. In the following example, any time .NET sees a `--root` or `-d` flag, the value gets saved under the `UQ:Roots` key instead

These options go through a hierarchy, which we can define ourselves:
```c#
await Host.CreateDefaultBuilder(args)
	.ConfigureAppConfiguration((hostingContext, config) =>
	{
		var switchMappings = new()
		{ 
			{ "--root", "UQ:Roots" }, 
			{ "-d", "UQ:Roots" },
		}
	
		config.SetBasePath(Directory.GetCurrentDirectory())
		.AddJsonFile("appsettings.json", optional: true, reloadOnChange: true)
		.AddJsonFile($"appsettings.{hostingContext.HostingEnvironment.EnvironmentName}.json", optional: true, reloadOnChange: true)
		.AddEnvironmentVariables()
		.AddCommandLine(args, switchMappings);
```

So now we have a way to save and retrieve configurations, but it's not safe to use raw configurations in our code. 
Instead, we bind these configurations to a type safe, structured options class. We will then need to register a service that an which we'll then use this as a service, so it can be injected in our registered services


```c#
...
.ConfigureServices((hostContext, services) =>
{
	services.Configure<UQOptions>(hostContext.Configuration);
	...
})
.Build()
.RunAsync()
```

The challenge here is what we want to map configurations to a list in our options class

This is possible if we run a command like:
```
dotnet run -- --Roots:0 c:/ --Roots:1 d:/  
```
But that's cumbersome for the user to have to type out.
Instead, we want a simple command like this:
```
dotnet run -- dir1 dir2 dir3 [options...]
```
