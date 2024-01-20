
```
{% with messages = get_flashed_messages(with_categories=true) %}  
	{% if messages %}  
		{% for message in messages %}  
			<p>{{ message }}</p>  
		{% endfor %}  
	{% endif %}  
{% endwith %}
```
This block demonstrates the difference between the `{% %}` and `{{ }}` in Jinga.
You can see that language constructs and keywords such as `with`, `if`, and `for` go inside `{% %}` tags whereas variables are used in `{{ }}`.
