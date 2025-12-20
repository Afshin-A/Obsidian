My Ryzen 7 5800H has 8 cores and 16 threads.
A **core** is an actual, tangible, processing unit on the CPU. With 8 cores, the CPU could execute 8 tasks in parallel. Truly in parallel. That means we don't have to switch between tasks to give the illusion of parallelism.
A **thread** is a sequence of instructions the operating system can manage independently. They are virtual streams of executions that get executed on a core.
In my case, each core could handle 2 threads. Using a process called **Simultaneous Multithreading (SMT)**, the core can switch between executing threads to maximize its utilization. For example, when one thread is waiting for an I/O operation to complete, the core can switch to the other thread. This doesn't mean performance is increased by 2 times. It's more like in the range of 20 to 40% increase.


In summary, cores provide the raw computation power, while threads increase utilization by reducing the idle time of the cores. 

# Producer-Consumer Design Pattern in Multithreaded Applications
A producer thread pushes data onto a *blocking* queue. Consumer threads retrieve data from the queue.
When the producer queue is done, it sends a signal that no more data will be added. Consumers will continue to consume the data until there is nothing left. 
## How this pattern avoids race conditions:
### Synchronization 
By **blocking**, we mean that only 1 thread can access the queue will be blocked, while the rest will be put to sleep by the operating system until it's their turn, and/or until it is safe to access the queue. For example, it is not safe when:
- A consumer thread attempts to retrieve an item when the queue is empty, or 
- The producer thread attempts to put an item in a fixed sized queue when that queue is full, or
- Multiple consuming threads are attempting to access the same item in the queue, although there are ways around this using **fine grained locking**
In this way,  threads don't have to waste resources to constantly check if it's safe to perform an operation, and there will be no race conditions. Instead, the operating system will put them to sleep and wake them up. This is called **synchronization**. 
Synchronization is achieved via practicing thread-safety, which involves using synchronization primitives such as:
- Locks
- Mutex
- Concurrent collections
- etc..

### Mutual Exclusion 
Thread safe data structures have a *locking* mechanism so that when one thread is accessing a resource, no other threads can 




**Deadlocks**—
You can't get a job unless you have experience, and you can't have experience unless you get a job. This is the concept of a deadlock.
In multithreading, deadlocks are a side-effect of the following 4 conditions:
- mutual exclusion - only one thread has access to a resource at a time
- hold and wait - 
- no preemption
- circular wait
- 

this is a situation when two threads 
Thread A is holding resource X
Thread B is holding resource Y

# Atomic Operations
>**Atomic operations** are a sequence of operations that are executed as a single, indivisible unit, meaning they are either completed fully or not at all, with no intermediate state visible to other processes or threads. They are crucial for preventing *data races* in multi-threaded environments by ensuring that shared data is accessed and updated predictably, even when multiple threads try to access it simultaneously.

A **lock/mutex** is a record—a "synchronization primitive"—that holds two things: the calling thread's identity (address, name, etc..) and the status of the thread (whether if it's locked or free). 
The locks have methods for locking and unlocking threads. Threads will call these methods.

If a thread attempts to access a critical section that's locked (already in use by another thread), the **operating system scheduler** places it in a waiting queue, where it goes into a blocked state. When the thread is done, it'll call the unlock method, which frees up the resource and calls upon the operating system to wake up another waiting thread.

**Operating system scheduler**—

A **critical section** the part of code that contains resources shared by multiple threads. This is of special interest to us because we need to take special measures to ensure the typical multithreading issue like race conditions, deadlocks, etc..


Implementing true atomicity is not so simple we could implement it ourselves for reliable, high-performance concurrency. Instead, we have to rely on classes provided by the runtime, such as the `Interlocked` class in C#. They make use of low level OS kernel and hardware instructions to make this possible.

Something like the following is not thread safe because not even variable checking is atomic.
```csharp
bool isLocked = false;
if (!isLocked) // Thread A checks the condition
{
    // A context switch happens here! Thread B now runs.
    isLocked = true; // Thread A tries to set the lock
}
```
That's because these operations get broken down into lower level operations and they're juggled around. The order of instruction we see here is not guaranteed to be preserved by the compiler (which runs at the OS level and creates machine level instructions)

Locking can be done over an entire resource. But it can also be applied over different indices of an array, through what's called **fine-grained locking**.


Locks are assigned over a critical block. Threads call methods on a lock.

This example uses [[Faster Modulo Using the Bitwise 'And' Operation (&)]] 
```csharp
using System;
using System.Threading;

// Thread-safe array with fine-grained locking
public class FineGrainedArray<T>
{
    private readonly T[] _items;
    private readonly ReaderWriterLockSlim[] _locks;
    private const int NumLocks = 16; // Power of 2
    private const int LockMask = NumLocks - 1;

    public FineGrainedArray(int size)
    {
        _items = new T[size];
        
        // One ReaderWriterLockSlim per bucket
        _locks = new ReaderWriterLockSlim[NumLocks];
        for (int i = 0; i < NumLocks; i++)
        {
            _locks[i] = new ReaderWriterLockSlim(LockRecursionPolicy.NoRecursion);
        }
    }

    // Hash function: use index itself (or hash it if needed)
    private int GetLockIndex(int index)
    {
        // For array indices: just use the index
        // For keys (like in dict), use: key.GetHashCode()
        uint hash = (uint)index;
        return (int)(hash & LockMask); // Fast: & (16-1) = & 15
    }

    public T Read(int index)
    {
        if (index < 0 || index >= _items.Length)
            throw new IndexOutOfRangeException();

        int lockIndex = GetLockIndex(index);
        _locks[lockIndex].EnterReadLock();
        try
        {
            return _items[index];
        }
        finally
        {
            _locks[lockIndex].ExitReadLock();
        }
    }

    public void Write(int index, T value)
    {
        if (index < 0 || index >= _items.Length)
            throw new IndexOutOfRangeException();

        int lockIndex = GetLockIndex(index);
        _locks[lockIndex].EnterWriteLock();
        try
        {
            _items[index] = value;
        }
        finally
        {
            _locks[lockIndex].ExitWriteLock();
        }
    }
}
```

The `ReaderWriterLockSlim` class allows multiple threads to read an index but only one thread to write 

Use case: 
```csharp
 Parallel.Invoke(
            () => Console.WriteLine($"Read[10] = {array.Read(10)}"),
            () => Console.WriteLine($"Read[26] = {array.Read(26)}"),
            () => array.Write(26, 999) // This blocks only lock for index 26
        );
```



# Asynchronous vs Multi-Threaded Applications
I/O operations are typically asynchronous. An operation that would typically hold up the main application thread is handed off to the OS, which hands it off to the controller of the disk drive. It is this controller that actually draws the data from the disk, not another CPU thread. When it's complete, the OS will briefly create a thread just to do a callback on the original thread, telling it the results are ready.

More accurately, the compiler creates a state machine for the async method. The await keywords become yield points in this state machine. 
The code that follows the yield points is called the continuation callback. This is the callback 

The application thread resumes. When the other thread is done, the result is returned and ready to be used  
<iframe width="560" height="315" src="https://www.youtube.com/embed/0vFgKr5bjWI?si=xu0uhV3ekCdL0c6_" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
https://youtu.be/0vFgKr5bjWI



>An "I/O bound" process is one where the time it takes to complete is primarily limited by input/output (I/O) operations (such as reading from or writing to a disk, or network communication) rather than by CPU computations.

*Async is not for CPU bound work.* It does not make sense for CPU bound work. It is designed to yield execution until something external happens.

Async/await is used to avoid blocking the calling thread while we wait for an async operation to complete. 
Async methods are appropriate for
- a drive driver to finish reading a file,
- a network request to complete,
- or until the OS receives an exit signal
- or even a timer to run out 


In C#, A `Task` is awaitable. It is a _promise of a future result_.

`Task.Run()` is different, however. Given a function (more specifically a delegate, which is a function pointer in C#), it will assign that function to a thread from the thread pool.



 Process Vs Thread
 A process is "an independent execution environment." It has its own memory space, it is and it is managed by the operating system.
 A process has at least 1 thread. Threads can work together and share information as well as access the same data.
 In C#, a task is an async operation. It is a _promise of a future result_.

Asynchronous just means that the current block is 






I see.
Although I'm disappointed, I'm thankful to have had the opportunity to speak with you and learn about your company. 
I'd love to keep in touch and connect with you professionally on Linked In. If there are any openings in the future, I would love to interview again and visit the company site



