The JetBrains Python IDE, PyCharm, uses a document-generating software called **Sphinx**.
Sphinx supports markup language.
Examples from

![test](/home/afshin/PycharmProjects/LearningMongoDB/learn_json.py)

```
"""  
| This module explores how to work with JSON in python.  
| We must first import the **json** package; it contains several essential methods:  
+ `json.load()` loads a json object from a given file, and saves it as a python dictionary  
+ `json.loads()` takes in a string representing a JSON object and returns a python dictionary. The "s" in `loads()` means `string`.  
+ `json.dump()` takes in a python dictionary, converts it to json, then writes (dumps) it into a file  
+ `json.dumps()` takes in a python dictionary and converts to a properly formatted json object (as a string)  
"""  


def load_json_from_file(file_path):  
    """  
    `json.load()` example: takes in a file obj and returns the json content as a python dictionary    :param file_path: path to file from which json object will be extracted from    :return:  
    """
```

