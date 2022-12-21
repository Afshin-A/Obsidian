One downside to this design pattern is the number of small classes.

```plantuml
@startuml
skinparam groupInheritance 2
hide empty members

interface Command {
	+ void execute()
}

abstract class DeviceCommand implements Command {
	# Device device
	+ DeviceCommand()
	+ DeviceCommand(Device device)
}

class TurnDeviceOn extends DeviceCommand {
	+ void execute()
}

class TurnDeviceOff extends DeviceCommand {
	+ void execute()
}

interface Device {
	+ void turnOn()
	+ void turnOff()
}

class Television implements Device {
	+ void turnOn()
	+ void turnOff()
}

class Microwave implements Device {
	+ void turnOn()
	+ void turnOff()
}

Device –– DeviceCommand

@enduml
```

```java
class Client {
	public static void main(String[] args) {
		Device tv = new Television();
		new TurnDeviceOn(tv).execute();
	}
}
```

