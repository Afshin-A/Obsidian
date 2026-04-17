Struct is a value type. It's passed by value. It is stored in the [[Stack vs. Heap in System Memory#Stack|stack]]
Class is a reference type. It's passed by reference. It's stored in the [[Stack vs. Heap in System Memory#Heap|heap]].

Record is basically a class but with a few twists:
- Equality comparison is based on the fields, just like a Struct
- It's immutable by default without having to manually set the setter to private, like we would in a class. This makes it perfect to represent data in transfer requests in HTTP requests, for example. 


### References
<iframe width="560" height="315" src="https://www.youtube.com/embed/HAybBV-A1Gg?si=J1pc6rZ3jzWXvAF5" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>
