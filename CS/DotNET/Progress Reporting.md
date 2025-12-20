- Only one consumer
- There can be multiple producers
- Thread-safe and synchronization

We provide the producer with a callback; subsequent calls trigger this callback

`IProgress` is designed to show progress on a UI, such as GUI or console applications.
`IProgress` is very useful for GUI applications because because UI frameworks, such as such as WPF and WinForms, as well as older frameworks, are not thread-safe, and have only one thread that is dedicated for rendering the UI. 
`IProgress` automatically moves the callback to the correct UI.

**SynchronizationContext** is the policy that defines where code must run. For example, where continuations and event callbacks run. 

Console apps and .NET generic host applications don't have a UI context. Continuations run on a thread from the threadpool.

### Example usage
```cs
public async Task DownloadFileAsync(string url, IProgress<int> progress)
{
    for (int i = 0; i <= 100; i++)
    {
        await Task.Delay(50); // simulate work
        progress?.Report(i);
    }
}

var progress = new Progress<int>(percent => Console.WriteLine(percent));
await DownloadFileAsync("url", progress);
```



