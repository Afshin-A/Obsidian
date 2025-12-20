# Event Loop



## Timers

Available from the `timers` module in node.js, there functions are available globally to set callback executions at certain times. Examples of built in timers are:
- `setTimeout(callback, delay, [...args]);` executes `callback` with the given `args` after the given `delay` in milliseconds 
- `setInterval(callback, delay, [...args]);`
- `setImmediate(callback, [...args]);`
Each of these return an object representing the timer. It can be fed to an associated function to cancel the timer:
- `clearTimeout(timeoutObject);`
- `clearInterval(intervalObject)`;
- `clearImmediate(immediateObject)`;
