Long-established framework for building **Windows desktop applications** with .NET.
Supports concepts such as:
- XAML files (to define UI elements)
- Data binding  
- Controls
- Graphics
- [[WPF#MVVM – Model–View–ViewModel|MVVM]]


# MVVM – Model–View–ViewModel
An architectural pattern for building UI applications. It's not exclusive to .NET, however it is standard practice for WPF.

MVVM separates business logic from the UI. It divides the application into three parts: 
- View - the UI
- View model - acts as an intermediary between the UI and the underlying application. It's essentially a model of the View.
- Model - data

Without MVVM, application logic ends up the UI, tightly coupling the two. This is bad practice and should be avoided. 
Similarly, application logic should be reusable; it should not be tailored to one specific view. This is why the view model exists: to bridge the UI to the backend.

Not every view needs a view model, however. 


# Single-Threaded Apartment (STA) Design in .NET WPF
thread affinity and its benefits
A thread gets bound to a specific CPU core
Reduces [[Cache Replacement Policies|cache misses]] and context switching


WPF enforces strict thread affinity. There is only one main UI thread. 
Only the thread that creates a UI element can modify that element.
So other threads, for example created by background tasks, cannot modify UI elements or else WPF will throw an exception
Instead, the background thread must return data to the main thread using a *`Dispatcher`* and UI elements are subsequently updated. 


This solves concurrency problems.

```button
name My Awesome Button
type command
action Copy Obsidian URL for current file
```
