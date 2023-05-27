#include <limits>
#include <initializer_list>

using namespace std;

template <typename T>
class ErrorValue {
public:
	static T Get() {
		return numeric_limits<T>::max();
	}

	static int GetInt() {
		return numeric_limits<int>::max();
	}
};

template<typename T>
class DefaultValue {
public:
	static T Get() {
		return T();
	}

	static int GetInt() {
		return int();
	}
};

template <typename T>
class Node {
public:
	T data;

	Node* link;
};

template <typename T>
class List {
private:
	Node<T>* head;

	int size;

	T SetHead(Node<T>* link) {
		if (head == link)
			return ErrorValue<T>::Get();

		head = link;
	}

	inline Node<T>* GetHead() {
		return head;
	}

	int SetSize(int size) {
		if (size < 0)
			return ErrorValue<T>::GetInt();

		this->size = size;

		return this->size;
	}

	int PlusOneToSize() {
		size++;

		return size;
	}

	int SubtractOneFromTheSize() {
		if (size <= 0)
			return ErrorValue<T>::GetInt();

		size--;

		return size;
	}

	Node<T>* CreateNewNode(T data = DefaultValue<T>::Get()) {
		Node<T>* newNode = new Node<T>;
		newNode->data = data;

		return newNode;
	}

	Node<T>* GetNode(int idx) {
		Node<T>* tmp = GetHead();
		while (idx--) {
			if (tmp->link == NULL)
				break;

			tmp = tmp->link;
		}

		return tmp;
	}

	T ConnectNodetoHead(Node<T>* node) {
		if (node == NULL)
			return ErrorValue<T>::Get();

		node->link = GetHead();
		SetHead(node);
	}

	T ConnectNodeToNode(Node<T>* node1, Node<T>* node2) {
		if (node1 == NULL || node2 == NULL)
			return ErrorValue<T>::Get();

		node2->link = node1->link;
		node1->link = node2;
	}

	void FillInInsufficientSpace(int insufficientSpaceSize) {
		while (insufficientSpaceSize--) {
			InsertLast(DefaultValue<T>::Get());
		}
	}

	T RemoveNodeFromHead() {
		if (GetHead() == NULL)
			return ErrorValue<T>::Get();

		Node<T>* removed = GetHead();
		SetHead(GetHead()->link);

		delete removed;
	}

	T RemoveNodeFromNode(Node<T>* prevNode) {
		if (prevNode == NULL)
			return ErrorValue<T>::Get();

		Node<T>* removed = prevNode->link;
		prevNode->link = prevNode->link->link;

		delete removed;
	}

	inline bool IsIdxValid(int idx) {
		return (idx >= 0);
	}

public:
	List() {
		head = NULL;

		SetSize(0);
	}

	inline int GetSize() {
		return size;
	}

	inline bool IsEmpty() {
		return (GetSize() == 0);
	}

	T Insert(int idx, T data) {
		if (IsIdxValid(idx) == false)
			return ErrorValue<T>::Get();

		if (idx > GetSize() - 1) {
			int insufficientSpaceSize = idx - GetSize();

			FillInInsufficientSpace(insufficientSpaceSize);
		}

		Node<T>* newNode = CreateNewNode(data);

		if (GetSize() == 0) {
			ConnectNodetoHead(newNode);
		}
		else {
			Node<T>* node = GetNode(idx);
			ConnectNodeToNode(node, newNode);
		}

		PlusOneToSize();

		return DefaultValue<T>::Get();
	}

	void InsertFirst(T data) {
		Node<T>* newNode = CreateNewNode(data);

		ConnectNodetoHead(newNode);

		PlusOneToSize();
	}

	void InsertLast(T data) {
		Node<T>* newNode = CreateNewNode(data);

		if (GetSize() == 0) {
			ConnectNodetoHead(newNode);
		}
		else {
			Node<T>* node = GetNode(GetSize() - 1);
			ConnectNodeToNode(node, newNode);
		}

		PlusOneToSize();
	}

	T Delete(int idx) {
		if (IsIdxValid(idx) == false)
			return ErrorValue<T>::Get();

		if (IsEmpty() == true)
			return ErrorValue<T>::Get();

		if (idx == 0) {
			RemoveNodeFromHead();
		}
		else {
			Node<T>* prevNode = GetNode(idx - 1);
			RemoveNodeFromNode(prevNode);
		}

		SubtractOneFromTheSize();

		return DefaultValue<T>::Get();
	}

	void Clear() {
		while (GetSize() != 0) {
			Delete(0);
		}
	}

	void Print() {
		cout << '\n';

		cout << "size: " << GetSize() << '\n';

		cout << "head->";

		Node<T>* tmp = GetHead();
		for (; tmp != NULL; tmp = tmp->link) {
			cout << tmp->data << "->";
		}

		cout << "NULL";

		cout << '\n';
	}
};
