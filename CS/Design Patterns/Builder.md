```plantuml
@startuml Builder Design Pattern

skinparam groupInheritance 2
hide empty members

Interface RobotPlan {

}

class Robot implements RobotPlan {

}

Interface RobotBuilder {

}

class oldSchoolRobotBuilder implements RobotBuilder {

}

class Engineer {
	- RobotBuilder builder
	+ void createRobot()
	+ Robot deliverRobot()

}

class Client {


}

Engineer <- Client
RobotBuilder <- Engineer 
Robot <- oldSchoolRobotBuilder
Robot <- Client
@enduml
```

The scenario starts with the `Client` wanting a `Robot`.
`Client` uses the `Engineer` to get the `Robot`. The `Engineer` doesn't know how robots are created. It's an intermediary between the `Client` and another object that knows how to make robots–It uses a `RobotBuilder`. The `RobotBuilder` has (knows) a specific `RobotPlan` (robot blue print) and can make it using specific. 

