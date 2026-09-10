Allows you to define a class in multiple files
Purely used for organization and readability. There is no optimization advantage 
Merged together into one class during compilation
Commonly used in WPF and other tools to write boilerplate code in one file and custom logic in another. If the tool regenerates its file, your custom code is not overwritten.

Partial classes need to have the `partial` keyword in their definition, and they need to be in the same namespace. 

```c#
namespace CompanyApp
{
    // The 'partial' keyword must be used
    public partial class Employee
    {
        public string FirstName { get; set; }
        public string LastName { get; set; }
    }
}

```

```c#
namespace CompanyApp
{
    
    public partial class Employee
    {
        public void DisplayFullName()
        {
            Console.WriteLine($"{FirstName} {LastName}");
        }
    }
}

```