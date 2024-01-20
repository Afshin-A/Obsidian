Unlike in Java or C++, you can't directly declare protected and private fields in a class. Attributes can be accessed using dot notation.

By convention, protected and private **properties** are preceded by an underscore `_` as a way of communicating with other developers. It is **not** interpreted differently.

# What is a property?
Basically, it's another name for a protected field in a class. We can control how they're accessed, set, and deleted via appropriate methods. We do this using the `@property` [[Python Decorators Vs Java Annotations#Python Decorators|decorator]]:
```python
Class User():
	__init__(self, password):
		self._password = password

	# getter
	@decorator
	def password(self):
		# this should return None because we never set anything for self.password (notice it's different than self._password)
		return self.password

	# setter
	@password.setter
	def password(self, new_password):
		# implement validation logic
		self._password = new_password

	# destructor
	@password.deleter
	def password(self):
		del self._password
```

Python will automatically call these accessors instead:
```python
def run():
	User()
```


More information: https://www.freecodecamp.org/news/python-property-decorator/

#OOP
