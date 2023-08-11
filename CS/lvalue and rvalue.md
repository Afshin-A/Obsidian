```c++
// pop_front, erase, size can be added here
template <typename T>
class LinkedList {
private:
    class Node {
        T data;
        Node* pNext;
        // LinkedList class methods need
        // to access Node information
        friend class LinkedList;
    };
    // Create a new Node
    Node* MakeNode(T data) {
        Node* pNewNode = new Node;
        pNewNode->data = data;
        pNewNode->pNext = nullptr;
        return pNewNode;
    }

    // Return by reference so that it can be used in
    // left hand side of the assignment expression

	// WHY IS THIS POSSIBLE?
    Node*& GetHeadNode() {
        return head;
    }
    static Node* head;

public:
    LinkedList<T>() noexcept {
        // caution: static members can't be
        // initialized by initializer list
        head = nullptr;
    }
    void push_back(T data) {
        Node* pTemp = MakeNode(data);
        if (!GetHeadNode()) {
		    // WHY IS THIS POSSIBLE?
            GetHeadNode() = pTemp;
        }
		// ...
    }
```