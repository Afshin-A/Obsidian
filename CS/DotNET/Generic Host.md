**Generic Host** provides the infrastructure/framework to build and manage any type of application (hence why it's called generic), complete with support for:
- dependency injection, 
- logging, 
- lifetime management, 
- hosted services (which are background tasks), 
- as well as providing various means to configure the application (including environmental variables, JSON files, etc.).
It is *a generic version of ASP.NET*, Microsoft's framework for building web applications. 


You can build things like **worker services** and console applications with Generic Host.
A worker service is a kind of app build on top of Generic Host. It is made for long-term apps that run in the background. Microsoft provides us a template to build this kind of app via the `BackgroundService` abstract class, which makes creating a hosted service (a process that runs on the host) easier. All we have to do is override the `ExecuteAsync` method. In this method, we define what the application should do in the background

First, we need to configure the generic host framework. 
We use a builder of type `IHostBuilder` to create and configure the generic host.
There is a `Host` class that contains static helper methods such as `.CreateDefaultBuilder()` and `.CreateApplicationBuilder()` to create an `IHostBuilder` object.

Several methods are usually chained together, each configuring a different aspect of the application:
 - `.ConfigureAppConfiguration()`
 - `.ConfigureLogging()`
 - `.ConfigureServices()` - This builds the DI container. The host will know how to create and inject services
At the end, we call the `.Build()` method, then `.RunAsync()` to start the app asynchronously, so that way we don't block the main thread.
These methods take a callback lambda in order to configure the host. 
```cs
await Host.CreateDefaultBuilder(args)
                .ConfigureAppConfiguration((hostingContext, config) => { /* ... */})
                .ConfigureLogging(logging => { /* ... */ })
                .ConfigureServices((hostContext, services) => { /* ... */ })
                .Build().
                .RunAsync();
```
What we see here is the perfect example of the [[Builder|builder design pattern]], where configuration methods are chained one after another.
This way of configuring the host with an object of type `IHostBuilder` is referred to as the *callback approach*. 

While the callback approach is still relevant, there is a newer/prettier/easier way to configure the host. And that is by using a builder of type `HostApplicationBuilder`: 
```cs
public class SomeServiceWorker : BackgroundService
{
    protected override async Task ExecuteAsync(CancellationToken ct) { /* ... */}
}

HostApplicationBuilder builder = Host.CreateApplicationBuilder(args);
builder.Services.AddHostedService<SomeServiceWorker>();
await builder.Build().RunAsync();
```
By the way, if you're wondering what `CancellationToken` is, it is a mechanism we can use to detect when a [[POSIX]] signal interrupt (SIGINT, Ctrl+C) is received in order to gracefully shutdown the application. 
For `BackgroundService` worker services, we do it like this:
```cs
if (ct.IsCancellationRequested) return;
```
This actually calls `IHostedService.StopAsync()` under the hood, since `BackgroundService` implements the `IHostedService` interface.
`BackgroundService` abstracts away the details of creating a worker service. But if we wanted to manually create a worker service, we would have to use the `IHostedService` type and define `.StopAsync()` ourselves. 
As you can see, it's much easier to do in a `BackgroundService` object with simple `if` statements.

- Hosted services - background tasks within the framework


	A **host** is an object that encapsulates an app's resources and lifetime functionality,
Host implements the `IHost` interface


## `IHostedService` vs `BackgroundService`
### `IHostedService` 
This interface allows us to define startup and shutdown logic for our apps by implementing the `StartAsync` and `StopAsync` methods
### `BackgroundService` 
abstract class inherits from `IHostedService` and provides the `ExecuteAsync` method.
#### TLDR
For simpler background tasks, use `BackgroundService`. If you want to fine tune the task, use `IHostedService`

## More on Worker Services (AKA Workers)
DI container knows how to create *hosted services*. It manages them when a worker asks for them on demand. We don't have to write `new ExampleService()`.
### Hosted Services
*Hosted services* are helpers to the workers. They're lightweight, have short lives compared to the workers, and do not automatically get executed—only as needed, such as when injected as a dependency into a worker service. We have to manually inject them in a worker or another service's constructor.
A *worker service is a type of a hosted service*, but with logic for startup and shutdown. It's created as a singleton service and lasts for the duration of the hosting system. Worker services are meant for long term tasks that run in the background.

Basically, a system hosts processes. Generic host provides the infrastructure to create and manage the processes. 

- Workers may use an infinite loop to run continuously. 
	- For example, you can have a *polling loop* that keeps checking if there was a change to some input, or a loop that keeps listening to incoming requests or data. 
- But that's not always the case. 
	- The worker can simply not have a loop. 

*You can also have multiple workers instead of one giant worker.* Each worker gets its own instance and runs independently of the others; they get their own lifecycle and dependencies. Scenarios where this becomes useful include:
- Separation of concerns - each worker does its own work
- Different frequencies - worker 1 might need to run once every minute, worker 2 once every hour, and worker 3 runs indefinitely. 
- Pipeline - a worker does 
Workers run as Tasks on a thread from the [[Cores vs Threads|Threadpool]]. They run *concurrently*, not necessarily parallel to each other. 
Here's what concurrent means: Tasks are running on the same time. But how the CPU manages that can be done in two different ways:
- Either tasks are running on the same CPU core, and the CPU switches between them really fast to give the illusion that they are happening at the same time, or,
- Tasks are running on different CPU threads. This is true parallelism 
The *Threadpool* is a collection of ready made threads provided by the .NET framework, ready to be assigned some work to do. This is to avoid overhead by creating and destroying threads, as well as resource management. 

Async tasks are a promise of future work. All we know is that the calling thread isn't blocked. The details of *how the work is done is abstracted from us*. The work in question could be:
1. Performed over the network, 
2. On an I/O controller (I/O bound work)
3. or there could be no work being done at all, just waiting for a signal,
4. For CPU bound work (*not recommended*)
5. on a different thread via`Task.Run(() => {})`
The first 3 is what async/await is really intended for, as opposed to CPU bound work in case 4, but you could still do that, even though it just adds the overhead of creating a state machine and making pointless callbacks (for continuation); it would be far more efficient to just use a separate from the threadpool, as shown in case 5.

The point is, how non-blocking async works is done is abstracted from us. Similarly, in generic host framework, how the services run is abstracted from us. It could be on different threads, it could be asynchronously, it could be switching really fast on the same CPU core, on different cores, they could be put to sleep by the OS scheduler. They don't even always stay on the same thread (since continuation resumes on a different thread from the threadpool). The point is, all we care about is that the services run concurrently. The details are abstracted from us by the framework, .NET runtime environment, and the operating system.

Type `IServiceCollection` stores information/instructions about how to initialize services and workers which are registered during the configuration of the host. Later, when we build the host, this information is used in order to build the DI container.
Type `HostBuilderContext` contains the environment and configuration associated with the host.

Type `IServiceProvider` resolves the dependencies of the services, and constructs the object/service (a service is represented by an object, so don't let the terminology confuse you). *It allows us to retrieve service objects after they've been registered.*

Type `IServiceScope` defines and keeps track of the **scope** of an object, i.e. how long it lives for in the DI container before it is disposed of. And there are 3 different scopes:
- Singleton - the object is created once and lives throughout the entire lifecycle of the app
- Scoped - the object is is created once throughout a custom scope. For example, object is created for an HTTP request and is disposed of once the request is processed.
- Transient - the object is created every time it is requested. 
It's basically a temporary box that holds services belonging to one operation/request.

`IServiceProvider` uses `IServiceScope` to define and keep track of the service scopes.

So all together, these 3 are used in the DI container like this:
- `IServiceCollection`—list of instructions that map services to their lifetime scopes and factories that create them
- `IServiceProvider`—creates and manages service instances
- ` IServiceScpe`—controls lifetime and automatic disposal of scoped services

Registering services
```cs
services.AddSingleton(Channel.CreateUnbounded<ProgressUpdate>());
// register IProgress<ProgressUpdate> that writes to the channel
services.AddSingleton<IProgress<ProgressUpdate>>(provider =>
{
	provider.
	 // retrieve the channel from the service provider
	var channel = provider.GetRequiredService<Channel<ProgressUpdate>>();
	// return an IProgress implementation that writes to the channel
	return new Progress<ProgressUpdate>(update => {
		channel.Writer.TryWrite(update);
	});
});
services.AddHostedService<UIService>();
services.Configure<UQOptions>(hostContext.Configuration); // bind configuration key-values to UQOptions
services.AddTransient<DirectoryScanner>();
```