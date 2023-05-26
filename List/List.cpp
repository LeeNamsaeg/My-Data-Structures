#include <limits>
#include <string>

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
	
	T Insert(int idx, T data){
		if (idx > size - 1){
			int shortageCnt = idx - size;
			
			while (shortageCnt--){
				InsertLast(0); // T 형에 맞게 바꿔야 함 
			}
		}
		
		if (idx < 0)
			return numeric_limits<T>::max();
	
		Node<T>* newNode = new Node<T>;
		newNode->data = data;
	
		if (head == NULL){
			newNode->link = head;
			head = newNode;
			
			size++;
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
	
	T Delete(int idx){
		if (IsEmpty() == true)
			return numeric_limits<T>::max();
	
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
		infinity = numeric_limits<T>::max();
	
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
