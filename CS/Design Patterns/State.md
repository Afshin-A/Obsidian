The state design pattern is used when designing a finite state machine. 
You're designing something that can be in different states. Based on the current state, it will do different things. 

The naive way to code such a thing, is to use a *switch* and/or *if-else statements*. Which is fine—for small projects. But as the project grows, there will be more and more states; the logic to select a state will become complex. And even then, what happens when we finally switch the current state? Presumably we want to run some code. 

You may end up with code that looks something like this example:
```
class Document is
    field state: string
    // ...
    method publish() is
        switch (state)
            "draft":
                state = "moderation"
                break
            "moderation":
                if (currentUser.role == "admin")
                    state = "published"
                break
            "published":
                // Do nothing.
                break
    // ...
```
Example from [Refactoring Guru](https://refactoring.guru/design-patterns/state)

This is an anti-pattern. 

The solution is that we represent each state as its own class.
All states will all implement an interface, that way we can can use polymorphism. 
```c
interface IState {
	void doThis();
	void doThat();
}

class StateA() : IState {
	void doThis() { /*implementation*/ }
	void doThat() { /*implementation*/ }
}

class StateB() : IState {
	void doThis() { /*implementation*/ }
	void doThat() { /*implementation*/ }
}

...
```

Our state machine class will have a `SwitchState` method and a `currentState` field. It may have some `doThis()` and `doThat()` methods. These will now have a very simple implementation:
```c

class StateMachine {
	private State currentState;
	public void SwitchState(State state) {
		currentState = state;
	}
	public doThis() {
		currentState.doThis();
	}
	public doThat() {
		currentState.doThat();
	}
}
```