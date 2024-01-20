#OOP
dunder (\_\_) methods 

Instance variables and functions are marked by the `self` keyword:
```python
class Student():
	"""This is class description"""


	def __init__(self, name, id):
		"""This is the constructor"""
		# convention for naming private, instance variables is
		self._name = name
		self._id = id

	def __str__(self):
		"""This method is the equivalent of the java .toString() method
		It returns a userfriendly, readable, string representation of the object"""
		return f"Student {self._name} has id: {self._id}"
		
	def __repr__(self):
		"""This method is similar to __str__ (it returns a string), but it should unambigously return what this object is, so that when it's put inside the eval method, it would get executed."""
		return f"Student(name='{self.name}, id='{self.id}')
```