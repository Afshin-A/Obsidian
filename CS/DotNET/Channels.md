Channels are used to implement the producer-consumer pattern in a multi-stage pipeline.
They are :
- Thread-safe
- Support synchronous and asynchronous operations 
- Much faster due to better performance
- They handle **backpressure**
- 

**Backpressure**
>A feedback mechanism where a slow consumer signals an upstream producer to slow down or stop sending data, preventing overload, data loss, and system crashes


We have to keep in mind that async/await adds overhead (via state machine, continuations); they're best for I/O and network operations—most of the time they do nothing but wait for a completion signal.
So you might think it makes better sense to use `BlockingCollection` with multithreading for CPU bound tasks, since async/await offer no benefit for CPU-bound tasks. 
BUT, channels cover every scenario: 
- For pure CPU-bound pipelines, channels can be used with synchronous functions.
```cs
// bounded channel used for enforcing backpresure
var channel = Channel.CreateUnbounded<int>(100);
// Producer thread - fire and forget
var producerTask = Task.Run(() =>
{
    for (int i = 0; i < 1000; i++)
    {
        channel.Writer.TryWrite(i);
    }
    channel.Writer.Complete();
});

// 4 consumers (CPU-bound)
var consumerTasks = Enumerable
	.Range(0, 4)
	.Select(
		_ => Task.Run(() => {
			while (channel.Reader.TryRead(out var item))
				ProcessItem(item); // CPU work
		}
		); // end of Task.Run
	); // end of .Select

// Wait until tasks are complete to avoid memory leaks 
await producerTask;
await Task.WhenAll(consumerTasks);
```
- For I/O bound pipelines, channels can be used with async/await. And it works great.
```cs
var channel = Channel.CreateUnbounded<int>();
var writer = channel.Writer;
var reader = channel.Reader;

_ = Task.Run(async () =>
{
    for (int i = 0; i < 100; i++)
    {
        await writer.WriteAsync(i);
        await Task.Delay(10);
    }

    writer.Complete();
});

for (int c = 0; c < 3; c++)
{
    _ = Task.Run(async () =>
    {
        await foreach (var item in reader.ReadAllAsync())
        {
            Console.WriteLine($"Consumer {c} processed: {item}");
        }
    });
}
```
- If the pipeline has different type of stages (I/O or CPU bound), channels are once again great for this scenario.

Channels cover every scenario.

Channels are easier to work with as we don't have to 
- manually set up `BlockingCollection`s, 
- manually signal completion (of adding items) from the producer, 
- manually check if there are more elements


