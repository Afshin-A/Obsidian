Python's `datetime` introduces 3 classes that are used to represent, store, and perform time calculations. These classes are divided to 2 categories: naive and aware. Naive classes are used for simple operations and don't involve time zones. Aware classes take time zones into considerations. We utilize the `pytz` for time zones.

## `datetime.date`
Naive class for simple date functions
```python
import daytime

my_dob = datetime.date(1997, 7, 5)
today = datetime.date.today()
my_dob.weekday()  # returns an int 0-6, where 0 is Monday and 6 Sunday
my_dob.isoweekday()  # 1 is Monday
```

## `datetime.timedelta`
The `timedelta` class is useful for performing mathematical operations on date items.
```python
my_age = today - my_dob  # my_age is a timedelta object
my_age.total_seconds()
delta_t = datetime.timedelta(days=3, hours=24)
future_date = today + delta_t  # future_date is a date object
```

## `datetime.time`
A naive class that lets us work with and represent hours, minutes, seconds, and microseconds. But it does not have attributes from the date class (such as year, month, etc.). Does not include time zones.
```python
time = datetime.time(9, 30, 45, 500)
```

## `datetime.datetime`
This is a combination of the `date` and `time` classes.
```python
dt = datetime.datetime(2023, 12, 30, 11, 39) # seconds and microseconds were omitted here and will be set to 0 by default.

dt.time()
print(dt.year)
print(dt.second)

dt = datetime.datetime(2023, 12, 30, 11, 39, tzinfo=pytz.UTC)

```

## Three ways to get the current time
Returns the date and time in local time zone of the system on which the code is running. But it doesn't actually include information about the time zone (when you print it, for example).
```python
current_time = datetime.datetime.today()
```

In the following, we can optionally supply the time zone as an argument.
```python
import pytz
# When no time zone is given, the now() method works identical to today()
current_time = datetime.datetime.now()
# UTC (formerly known as GMT--Greenwich Mean Time) is the standard time zone 
current_time = datetime.datetime.now(tz=pytz.UTC)
current_time = datetime.datetime.now(tz=pytz.timezone('US/Central'))
```


For the sake of consistency, a **globally used application should store times in the standard format and convert to the users' local time whenever necessary.**
Consider a scenario where a system is using the `now()` method to log information. The system administrator is located in a different time zone, so their times are not the same. If the admin logs information, it will be added in his time zone and confuse everyone else.
```python
current_time_utc = datetime.datetime.utcnow()  # Returns the current time in UTC, but doesn't include the time zone.
print(current_time_utc)  # prints 2023-12-30 18:37:57.664859
```
To add the time zone, we can use the `replace()` method. This method can be used to change any aspect of a datetime object (such as year, month, etc..), including the time zone. Note that, in the case of replacing time zone, it just simply changes it.
```python
current_time_utc_w_timezone = current_time_utc.replace(tzinfo=pytz.UTC)
print(current_time_utc_w_timezone)  # prints 2023-12-30 18:37:57.664859+00:00
```

## Time zones in `pytz`
We can print a list of all the time zones supported by the `pytz` module:
```python
for tz in pytz.all_timezones:
	print(tz)
```

## Converting between time zones
```python
datetime.datetime.utcnow().astimezone(tz=pytz.timezone('US/Central'))
```


## Formatting times
`strftime()` formats how a `datetime` object is displayed. Additionally, the output is a string.
Check the documentation of the method for more formatting keywords.
```python
date_time_str = datetime.datetime.utcnow().strftime('%A, %B %d, %Y')
print(date_time_str)  # prints Saturday, December 30, 2023

# converting back to datetime
date_time = datetime.datetime.strptime(date_time_str, '%A, %B %d, %Y')
```
