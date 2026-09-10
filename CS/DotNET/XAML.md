Heavily used in [[Understanding .NET#WPF|WPF]]
Developed by Microsoft, used to define user interfaces and initialize objects.
UI elements are created in this file via tags, then linked to a companion code file like `.xaml.cs` via [[Partial Class|partial classes]]
Allows for *direct object mapping*, where it connects data from UI elements to corresponding data sources (e.g. class variables)
In other words, every XML tag maps directly to a concrete .NET class instance; every attribute maps directly to a property on that class.