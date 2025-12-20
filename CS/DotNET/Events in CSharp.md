Events are based on the [[Observer|observer design pattern]]
## Theory
**Observers** *subscribe* to a **subject** (or **observable**). When a change occurs in some value of interest in the observable, all the observers get notified. 
Observers can register an **event handler** (basically a function) **delegate**  so the observable would call that function when an event is triggered. 
An event is associated with change in the state of the observer. It could be anything from an asynchronous operation changing to a user clicking a button and changing a value.
C# heavily abstracts all this using the `event` keyword. The keyword `event` modifies a delegate. It's essentially a wrapper for a delegate type,
### What are Delegates?
A **delegate** is a type that represents a function signature. It is not just a pointer. Rather, it is a type. Any functions that has that signature is a match and can be represented by this type. We could assign a function to the delegate, then invoke the delegate to call the function.

Delegate types used in events are:
- `Action` is used when no data is sent from the observable ==(in other words, when the event handler registered does not have an argument.)==
- `Action<A, B, C, ...>`—used if we wanted to send multiple values, but *this is an anti-pattern*. We're defining the signature that all callback methods must follow. If we change the delegate, then all the methods must also be changed to conform to the signature. 
- `Action<CustomObject>`—We could also use a custom class that stores all the values we want to pass: 
- *The standard is to use `EventHandler` with `EventArgs`*. This offers a consistent event handler signature that is strongly typed, has debugging support, and is compatible with other libraries.
`EventHandler` is a delegate type that takes in two things:
- An object of type `object`  that represents the sender (observable)
- An `EventArgs` object representing the data sent from the observable
`EventArgs` is mostly an empty class. It is simply used as a convention. It is a legacy class that was mandatory before .NET 4.5. *It is recommended to use* it because many libraries still use it as a convention.
```cs
public class ScoreChangedEventArgs : EventArgs
{
    public int NewScore { get; }
    public int OldScore { get; }        // added later
    public bool WasCritical { get; }    // added later
}

...
public class Player
{
	private int _score;
	public event EventHandler<ScoreChangedEventArgs> OnScoreChange;
	public void AddScore(int amount)
	{
	        _score += amount;
	        ScoreChanged?.Invoke(this, new ScoreChangedEventArgs(_score));
	}
}
```


Event data is passed as an object of type `EventArgs` (which comes from the `System` namespace). We may define a custom class that extends this class.

### Events are thread-safe
Subscribing/unsubscribing to events is an [[Cores vs Threads#Atomic Operations|atomic operation]] and therefore thread-safe.

### Always watchout for null events
Internally, events store a linked list of delegate references. The event is considered `null` when it does not have any delegates: 
- Before it has any subscribers
- After all subscribers unsubscribe
That's why we need to use the null-conditional operator:
```cs
Died?.Invoke();
```
If `Died` is null, the method that follows up `.Invoke()` (and any other follow up methods that are chained), won't get called.
Otherwise we get a null reference exception.

## Examples
### Simple `Action` Event - No data sent
Here's an example of a simple event with no data or handler:
```cs
public class Player
{
	// This is the Observable
	public event Action Died;
	public void Kill() {
		Console.WriteLine("You Died");
		// Trigger the event
		Died?.Invoke();
	}
}
public class Main
{
	public static void Main(string[] args) 
	{
		var player = new Player();
		// Register the event with a delegate
		player.Died += () => Console.WriteLine("");
		// Trigger the event
		player.Kill();
		
		player
	}
}
```

### `EventHandler` and `EventArgs`
```cs
public class ScoreChangedEventArgs : EventArgs
{
    public int NewScore { get; }
    public ScoreChangedEventArgs(int newScore)
    {
        NewScore = newScore;
    }
}

public class Player
{
    public event EventHandler<ScoreChangedEventArgs> ScoreChanged;
    private int _score;
    public void AddScore(int amount)
    {
        _score += amount;
        ScoreChanged?.Invoke(this, new ScoreChangedEventArgs(_score));
    }
}

player.ScoreChanged += (sender, args) =>
{
    Console.WriteLine($"Player score is now: {args.NewScore}");
};
```
As you can see, one advantage of using `EventHandler` is that we get access to `sender`, a reference to the observable that invoked the event. In other words, observers know who the observable is.
 