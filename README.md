# Enhanced_Malloc

	This program deals with creating your own malloc and free function. We malloc by using an array as
our “memory” and have a linked list that contains the memEntry structs. Everytime we call the malloc
function we set space from the array and return a void* pointer back to the user. Our malloc function
also takes care of merging nodes that are empty to prove a larger amount of memory back to the user.
	The free function checks the nodes for the void*p that was passed and changes the free variable
back to being free instead of being not free. The free function does not delete the node or remove its
link because although its free, the malloc function will traverse through it to find the free space. If that
space is too small it will try to reach the end where there may be a possibility or free unallocated
memory.
