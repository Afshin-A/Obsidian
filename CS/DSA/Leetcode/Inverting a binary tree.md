Given a binary tree, return its mirror image. AFAIK there's really no point in doing this aside from testing someone's knowledge of recursion and trees. 

To solve it, we use a post order search and at each iteration, we swap the left child tree with the right child tree (subtree).

```python
def mirror(root):
	if root == None:
		return
	mirror(root.left)
	mirror(root.right)

	root.left, root.right = root.right, root.left
```