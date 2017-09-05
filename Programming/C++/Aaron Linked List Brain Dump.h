

template<class T>
class LinkedList
{
public:

	class Node
	{
	public:
		T value;
		Node *next = nullptr;
		Node *prev = nullptr;
	};
	
	class Iterator
	{
	public:
	
		Iterator(Node *n);
	
		T& operator * (){
			return n->value;
		}
		
		void operator ++ () {
			n = n->next;
		}
		
		void operator -- () {
			n = n->prev;
		}
		
		bool operator == (const Iterator *rhs){
			return n == rhs->n;
		}
		
		bool operator != (const Iterator *rhs){
			return n != rhs->n;
		}
		
		Node *GetNode() {  return n; }
		
	private:
	
		Node *n;
	};

public:

	LinkedList();
	~LinkedList();
	
	void PushBack(const T &value);
	void PushFront(const T &value);
	
	// removes the item and returns the value that was stored
	T PopBack()
	{
		assert( end == nullptr && "cant pop from an empty collection" );
		
		T value = end->value;
		end = end->prev;
		delete end->next;
		end->next = nullptr;
		
		return value;
	}; 
	T PopFront(); // removes the item and returns the value that was stored
	
	T& Front(); // returns the value at the beginning of the list
	T& Back();  // returns the value at the end of the list
	
	
	Iterator Begin()
	{
		return Iterator(start);
	};
	
	Iterator End()
	{
		return Iterator(nullptr);
	};
	
	bool IsEmpty();
	
	Iterator FindFirstValue(const T& value)
	{
		for(auto iter = Begin(); iter != End(); iter++ )
		{
			if( *iter == value )
				return iter;
		}
		
		return End();
	}
	
	void Insert(Iterator loc, const T &value)
	{
		if(loc == End())
		{
			PushBack(value);
			return;
		}
		
		Node *n = new Node();
		n->value = value;
		
		Node* ln = loc->GetNode();
		ln->prev->next = n;
		n->prev = ln->prev;
		
		ln->prev = n;
		n->next = ln;
	}

protected:

	Node *start = nullptr;
	Node *end = nullptr;

private:
};


bool test1()
{
	// do some things
	
	// return if successfull result.
};


int main(int argc, char **argv)
{
	LinkedList<int> myList;
	myList.PushBack(10);
	myList.PushBack(20);
	myList.PushBack(30);
	myList.PushBack(40);
	myList.PushBack(40);
	
	
	auto iter = myList.FindFirstValue(30);
	myList.Insert(iter, 32);
	
}