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
		"""This method is the equivalent of the java .toString() method"""
		return f"Student {self._name} has id: {self._id}"
	
```