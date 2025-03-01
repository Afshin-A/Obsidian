
## Raw Strings
In python, the prefix `r` to a string, such as `r'He\l\lo world!'` treats characters literally as they are. In other words, the backslash `\` isn't treated as an escaping character. This is useful for regex because `\` plays an important role in expressions, and we wouldn't have to escape the `\` itself.

## Capturing groups
A capturing group is used to group and organize searching patterns. They return a backreference, which is a pointer to whatever text that is matched by the capturing group. 
```
([\"\'])((?:images|dummy)\/[\w/-]+\.\w{3,4})\1
```
In the above, `([\"\'])` is a capturing group. Notice the `\1` at the end. This means that whatever that is found by the capturing group (either `'` or `"`) at the start should also be present at the end. 

Capturing groups add overhead and make regex slower. So if we know that we don't need backreferences, we can use a non-capturing group instead.
```
((?:images|dummy)
```
This is just like a capturing group, but without the backreferences.

# `re.sub()`


Scenario: We want to go through an html file and replace all static links with dynamic ones. For example in
```html
<form action="#" class="search-form">
	<input type="text" placeholder="Search...">
	<button type="submit"><img src="images/icon-search.png" alt=""></button>
</form>
```
` src="images/icon-search.png"` needs to be `src="{{ url_for('static', filename="images/icon-search.png"')}}`

For this, we can use the `sub` method from the `re` module (used for regex).
```python
def replace_image_paths(text): 
	# Regex to match file paths like "images/icon-phone.png" 
	pattern = r'(["\'])((?:images|css|js)/[\w/-]+\.\w{3,4})\1' 
	# Replace the matched pattern with {{url_for('static', filename='path') }}
	replaced_text = re.sub(
		pattern, 
		r"\1{{ url_for('static', filename='\2') }}\1",
		text) 
	return replaced_text
```
The backreferences in the replacement text refer to the capture groups from the regex pattern.