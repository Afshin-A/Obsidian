Also known as cache replacement algorithms.
A **cache miss** occurs when the data the CPU needs is not found in the cache. So the CPU loads it from the RAM memory and stores it in cache for quicker access. As the cache becomes nearly full, we need to oust the least used items and make rooms for new ones. 

There are several algorithms that operate at different levels and depending on the type of cache, system architecture, predicted access patterns.

<iframe width="560" height="315" src="https://www.youtube.com/embed/P_UYI23DddU?si=xP_oLKTRrWwEQm-6" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

# Least Used Algorithm
This is a fairly easy to implement algorithm that's typically implemented at the higher software level, such as in web browser caches or database caches.
It's efficient, but not efficient enough for CPU caches.

It uses a doubly-linked list to order items based on how recently they were accessed. Each node stores an item in the cache. 
The head represents the most recently accessed item and the tail is the least recently item. 
- When the cache becomes full, the tail node is removed. 
- When an item is accessed,
	- If it already exists in the linked list, it is moved up as the new head
	- If it doesn't exist, it gets inserted as the head

In order to instantly look up if an item exists in the list or where it is, we use a hashmap that maps an item to the (address of the) node that represents the item. This way, we can look up items in cache in O(1) time instead of the usual O(n) time complexity for search in linked lists.

