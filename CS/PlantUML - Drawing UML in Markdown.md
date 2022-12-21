Standard template from [their website](https://plantuml.com/)
```plantuml
Bob -> Alice : hello 
Alice -> Wonderland: hello 
Wonderland -> next: hello 
next -> Last: hello 
Last -> next: hello 
next -> Wonderland : hello 
Wonderland -> Alice : hello 
Alice -> Bob: hello 
```


Used in SNHU CS 320 Project 1 Fall 2022 
```plantuml
@startuml Service UML Diagram

skinparam groupInheritance 2  
page 2x2  
skinparam pageMargin 10  
skinparam pageExternalColor gray  
skinparam pageBorderColor black  
hide empty members

package services {  
    abstract class Service<T extends ServiceData> {  
        # database: Map<String, T>  
        # validateID(String)
        + add(String, T)  
        + remove(String): T  
        # update(String, T)  
    }  
    class ContactService<Contact> extends Service {  
        + update(String, String, String, String, String)  
        + update(String, Contact)  
    }  
    class TaskService<Task> extends Service {  
        + update(String, String, String)  
        + update(String, Task)  
    }  
    class AppointmentService<Appointment> extends Service {  
  
    }  
}
@enduml
```
