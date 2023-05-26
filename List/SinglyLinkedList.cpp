#define INFINITY 2000000000 // 직접 매크로를 정의해서 쓰는 것보다. C++에서 공식적으로 정의해놓은 리미트를 쓰는 게 좋음 

using namespace std;

template <typename T>
class Node{
public:
	T data;
	
	Node* link;
};

template <typename T>
class List{
private:
	Node<T>* head;
	
	int size;
	
	T infinity;
	
public:
	List(){
		head = NULL;
		
		size = 0;
	}
	
	int Insert(int idx, T data){
		if (idx > size - 1){
			int shortageCnt = idx - size;		
			
			while (shortageCnt--){
				InsertLast(0); // 타입에 따라 다른 기본값을 가질 필요가 있음 
			}
		}
		
		if (idx < 0)
			return INFINITY;
	
		Node<T>* newNode = new Node<T>;
		newNode->data = data;
	
		if (head == NULL){
			newNode->link = head;
			head = newNode;
			
			size++;
			
			return 1;
		}
	
		Node<T>* tmp = head;
		while (--idx){
			if (tmp->link == NULL)
				break;
			
			tmp = tmp->link;
		}
	
		newNode->link = tmp->link;
		tmp->link = newNode;
		
		size++;
		
		return 1;
	}
	
	void InsertFirst(T data){
		Node<T>* newNode = new Node<T>;
		newNode->data = data;
	
		newNode->link = head;
		head = newNode;
		
		size++;
	}
	
	void InsertLast(T data){	
		Node<T>* newNode = new Node<T>;
		newNode->data = data;
	
		if (head == NULL){
			newNode->link = head;
			head = newNode;
			
			size++;
		
			return;
		}
	
		Node<T>* tmp = head;
		for (; tmp->link != NULL; tmp = tmp->link) {}
	
		newNode->link = tmp->link;
		tmp->link = newNode;
		
		size++;
	}
	
	int Delete(int idx){
		if (IsEmpty() == true)
			return INFINITY;
	
		if (idx == 0){
			Node<T>* removed = head;
			head = head->link;
		
			delete removed;
			
			size--;
		
			return 1;
		}
	
		Node<T>* tmp = head;
		while (--idx){
			if (tmp->link == NULL)
				break;
			
			tmp = tmp->link;
		}

		Node<T>* removed = tmp->link;
		tmp->link = tmp->link->link;
	
		delete removed;
		
		size--;
		
		return 1;
	}
	
	void Clear(){
		while (head != NULL){
			Delete(0);
		}
		
		size = 0;
	}
	
	T& operator[](int idx){		
		infinity = INFINITY;
	
		if (idx > size - 1)
			return infinity;
		
		if (idx < 0)
			return infinity;
			
		if (IsEmpty() == true)
			return infinity;
			
	
		Node<T>* tmp = head;
		while (idx--){
			if (tmp->link == NULL)
				break;
			
			tmp = tmp->link;
		}
	
		return tmp->data;	
	}
	
	bool IsEmpty(){
		return (size == 0);
	}
	
	int GetLength(){
		return size;
	}
	
	void Print(){
		cout << "head->";
		
		for (; head != NULL; head = head->link){
			cout << head->data << "->";
		}

		cout << "NULL";
	}
};
