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

