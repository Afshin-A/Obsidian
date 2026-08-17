They are distinct problems.
You can have a data race without a race condition, and a race condition without a data race.
Data race happens in the Hardware / Memory level, while race condition happens in the application / logic level.

> A **data race** occurs when 2 instructions from different threads access the same memory location, at least one of these accesses is a write and there is no synchronization that is mandating any particular order among these accesses.