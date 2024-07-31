```python
# Returns an unambiguous string representation of object  
def __repr__(self):  
return f'User(first_name={self.first_name}, last_name={self.last_name}, email={self.email}, phone={self.phone}, dob={self.dob}, message={self.message})'  
  
# Returns a user-friendly string representation of object  
def __str__(self):  
return f'\nFirst Name:\t{self.first_name}\nLast Name:\t{self.last_name}\nDate of Birth:\t{self.dob}\nEmail:\t{self.email}\nPhone Number:\t{self.phone}\nMessage:\t{self.message}'
```

General rule of thumb is that you should be able to execute what's returned by the `__repr__` method in [[eval]].
