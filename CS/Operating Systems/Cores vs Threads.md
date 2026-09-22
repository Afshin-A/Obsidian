My Ryzen 7 5800H has 8 cores and 16 threads.
A **core** is an actual, tangible, processing unit on the CPU. With 8 cores, the CPU could execute 8 tasks in parallel—truly in parallel. That means we don't have to switch between tasks quickly in order to give the illusion of parallelism.
A **thread** is a sequence of instructions the operating system can manage independently. Threads are virtual streams of instructions that get executed on a core.
In my case, each core could handle 2 threads. Using a process called **Simultaneous Multithreading (SMT)**, the core can switch between executing threads to maximize its utilization. For example, when one thread is waiting for an I/O operation to complete, the core can switch to the other thread. This doesn't mean performance is increased by 2 times. Actually, it's something in the range of 20 to 40% increase.


In summary, cores provide the raw computation power, while threads increase utilization by reducing the idle time of the cores. 

## What exactly is a thread?
A thread is an **execution context**—an abstract container/environment that contains memory addresses  
Every CPU core has a number of registers that hold important information immediately needed by the CPU. The most important of these are:
- General purpose registers
	- RAX—accumulator, contains the results of an arithmetical or logical operation
	- RBX—base, used for top of a memory stack, to store math results, acts as a [[CPU Registers#RBX|non-volatile]] (callee-saved) register, and for other general data
- Program counter—stores the RAM address for the next CPU instruction to run
- Stack pointer—stores the address of the top of the current running thread's memory stack
At any moment, the collective data stored in these memories are the *context* of a single thread. A thread needs these in order to function. 
When we want to run another thread, we switch the context: we save the current context in a data structure called the **Thread Control Block (TCB)** in RAM, and load the context of the new thread.  


Physically, a thread is a data structure that contains snapshot of the values in CPU registers, in addition to other things (like metadata)




A **process** is an instance of an application.
Threads live inside processes. A process can have multiple threads, but a thread operates in the scope of one process.
This applies to operating systems as well, since they're a type of an application.

## Why are threads expensive to create?


# Producer-Consumer Design Pattern in Multithreaded Applications
A producer thread pushes data onto a *blocking* queue. Consumer threads retrieve data from the queue.
When the producer queue is done, it sends a signal that no more data will be added. Consumers will continue to consume the data until there is nothing left. 
## How this pattern avoids race conditions:
### Synchronization 
The term **blocking** in blocking queue means that only 1 thread can access the queue at time, while the rest will be put to sleep by the operating system until it's their turn, and/or until it is safe to access the queue. For example, it is not safe when:
- A consumer thread attempts to retrieve an item when the queue is empty, or 
- The producer thread attempts to put an item in a fixed sized queue when that queue is full, or
- Multiple consuming threads are attempting to access the same item in the queue, although there are ways around this using **fine grained locking**

In this way, threads don't have to waste resources to constantly check if it's safe to perform an operation. Instead, to avoid race conditions, the operating system will put them to sleep and wake them up. This is called **synchronization**. 
Synchronization is achieved via practicing thread-safety, which involves using synchronization primitives such as:
- Locks
- Mutex
- Concurrent collections
- etc..


> Multiple consumer threads may attempt to access the same queue simultaneously. If the queue is not designed for concurrent access, this can lead to race conditions where two threads try to remove or modify the same item at the same time.
> 
> One way to prevent this is by using synchronization mechanisms such as locks (mutexes). More advanced approaches may use fine-grained locking, lock-free algorithms, or concurrent data structures (like a **blocking queue**) to reduce contention and improve scalability.
> 
> Without synchronization, threads may waste CPU resources by repeatedly checking whether an operation is safe to perform (an anti-pattern known as busy waiting or spinning).
> 
> Instead, synchronization primitives can coordinate access to shared resources. When a thread cannot proceed, the operating system (or runtime scheduler) may block the thread, allowing another thread to run. The blocked thread is later awakened when the required condition becomes true.
> 
> This process of coordinating access to shared resources and ordering operations between threads is called **synchronization**. The operating system acts like a traffic coordinator, navigating threads around system resources to avoid collisions (race conditions).
> 
> Synchronization is typically achieved using thread-safe programming techniques and synchronization primitives such as:
> - Mutexes
> - Locks (often implemented using mutexes)
> - Semaphores
> - Condition variables
> - Read-write locks
> - Barriers
> - Atomic operations
> - Concurrent collections (thread-safe queues, maps, etc.)

### Deadlocks
You can't get a job unless you have experience, and you can't have experience unless you get a job. This is the concept of a **deadlock**.
A similar situation can happen in threads: 
Thread A is holding resource X, but thread B needs it.
Thread B is holding resource Y, but thread A needs it.
Both threads become permanently locked.

#### Avoiding deadlocks
In multithreading, deadlocks are created in all 4 of these conditions occur simultaneously:

- **Mutual exclusion**—only one thread has access to a resource at a time. Thread safe data structures have a *locking* mechanism so that when one thread is accessing a resource, no other threads can 
- **Hold and wait**—a thread is holding a resource, and it's waiting for more resources currently held by other threads.
- **"No preemption"**—this is a rule that an operating system can use for some threads. It makes a running process uninterruptable by the OS kernel. So, for example, an infinite-loop task may lockup the entire system, and OS lacks the authority to pause it. However, it is still commonly used:
	- It preserves data integrity—interruptions mid file writing can corrupt it. 
	- It causes less overhead than context switching 
	- Common in embedded and real-time systems. For example, a microwave only needs to do one important thing on time. It should not be interrupted.
- **Circular wait**—happens when a thread need resources held by the next thread, and so on. The last thread needs resources needed by the first. This creates a metaphorical chain of threads.

Even if one of these conditions is not met, a deadlock becomes impossible. 



# Atomic Operations
>**Atomic operations** are a sequence of operations that are executed as a single, indivisible unit, meaning they are either completed fully or not at all, with no intermediate state visible to other processes or threads. They are crucial for preventing *[[Data Race Vs. Race Condition|data races]]* in multi-threaded environments by ensuring that shared data is accessed and updated predictably, even when multiple threads try to access it simultaneously.



Modern CPUs provide specialized, atomic instructions. An example is `COMPARE_AND_SWAP`

`COMPARE_AND_SWAP`:
1. Read a variable from memory
2. Store a copy of the variable
3. Perform calculations (manipulate data)
4. Check if variable has been untouched by other threads
5. If it untouched, update the variable
6. Else, fail. Try again
Steps 4-6 are atomic. Otherwise, we face the same problem again: how can we make sure another thread didn't change the variable while we were checking it? 

Atomicity cannot be achieved by software alone. It must be physically enforced by the hardware.

So how does a multi-core CPU prevent different cores from reading and data from the same memory RAM address?
- We can lock the memory bus, so that no one (including all other cores on the processor) can access the RAM. This is terrible for performance because we're temporarily locking the entire system.
- The modern approach is **Cache Coherency**. The CPU's cache controller. 

[[RAM Controller, Memory Bus, and Memory Channel]]

#### Locks
A **lock/mutex**—sometimes called a "synchronization primitive"—is a variable in memory that holds the status of the thread: 0 means it's free, 1 means it's locked. It's an abstract concept, and some implementations use a record that also includes the calling thread's identity (address, name, etc..).
~~The locks have methods for locking and unlocking threads. Threads will call these methods.~~
Conceptually, we can think of locks as a guarding mechanism. Threads check the variable to ensure no other threads have control of a resource before making changes, preventing corrupted data
It's like a traffic light at an intersection. It doesn't get passed into any low level system functions. 

#### Operating system scheduler
If a thread attempts to access a critical section that's locked (already in use by another thread), the **operating system scheduler** places it in a waiting queue, where it goes into a blocked state. When the thread is done, it'll call the unlock method, which frees up the resource and calls upon the operating system to wake up another waiting thread.

#### What is a critical section?
A **critical section** the part of code that contains resources shared by multiple threads. This is of special interest to us because we need to take special measures to ensure the typical multithreading issue like race conditions, deadlocks, etc..


Implementing true atomicity is not so simple that we could implement it ourselves for reliable, high-performance concurrency. Instead, we have to rely on tools provided by the runtime environment, such as the `Interlocked` class in C#. They make use of low level OS kernel and hardware instructions to make this possible.

Something like the following is not thread safe because *not even variable checking is atomic*.
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


# Process Vs Thread
A process is "an independent execution environment." It has its own memory space, it is and it is managed by the operating system.
A process has at least 1 thread. Threads can work together and share information as well as access the same data. In C#, a task is an async operation. It is a _promise of a future result_.

```cardlink
url: https://www.youtube.com/shorts/JpD-IKdItRw?feature=share
title: "OS Internals: Processes vs. Threads Memory Layout!"
description: "Process vs thread is one of the most asked systems questions in interviews, and most answers skip the part that actually matters: what the kernel is doing un..."
host: www.youtube.com
favicon: https://www.youtube.com/s/desktop/2e7138bb/img/favicon_32x32.png
image: https://i.ytimg.com/vi/JpD-IKdItRw/hq720.jpg?sqp=-oaymwEdCJUDENAFSFXyq4qpAw8IARUAAIhCcAHAAQbQAQE=&rs=AOn4CLDjIhvKIbdX4oA4DbzO23aAz9qdhg
```



Asynchronous just means that the current block is 


# Coroutines
Standard functions execute from start to end, after which their state is popped from the call stack and execution flow returns to the caller.
A **coroutine** is any function 

cooperative multitasking/cooperative routines
[What are coroutines?](https://www.reddit.com/r/learnprogramming/comments/or0bie/what_are_coroutines/)
## Stackless 


## Stackful 


can the same function be executed by different threads? 
But each thread has its own stack, right? So how is the state of a function represented across multiple stacks on various threads?

does every thread have its own stack?
What sort of threads get their own stack?
Are there any types of threads that don't get their own stack? Protothreads. stackless coroutines (async/await tasks) some GPU threads
