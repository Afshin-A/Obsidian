# Behavioral Diagrams
Dynamic

## Use Case Diagram
<iframe width="560" height="315" src="https://www.youtube.com/embed/zid-MVo7M-E?si=pBLmCV7iOry9Pgcx" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>


## Activity Diagram
Behavior diagram - a simple way to describe the logic of the system (i.e. what must happen in the system)

## Sequence Diagram
<iframe width="560" height="315" src="https://www.youtube.com/embed/pCK6prSq8aw?si=6oUnV-qwvFXxTqNX" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

# Structural Diagrams
Static


## Class Diagram


In this scenario, both of the given activity and sequence UML diagrams describe the logic of when a user withdraws cash from an ATM machine. First, the user enters the pin associated with their banking card. If the pin is incorrect, the user is denied access. Upon entering a valid pin, the user is prompted to enter the amount they wish to retrieve in cash. Another check ensures the amount is available in the user's balance. If so, cash is dispensed. In either case, next, the ATM machine generates and prints a receipt. Throughout this scenario, the sequence diagram shows that information from the user, including as their pin and amount requested, is being passed back and forth.   
These diagrams are valid, albeit very simplistic, representation of the flow in an ATM system. In reality, ATM machines have additional functionalities to dispensing cash, including depositing cash to your account and checking your account balance. As such, we can improve the diagrams by adding the ability to deposit cash. Furthermore, the system could benefit from additional security checks. For instance, what should happen if there is not enough cash available in the ATM to accommodate the user's requested amount? These deficiencies are addressed in the following, improved, UML activity diagram of an ATM machine system:

