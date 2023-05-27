#include <iostream>
#include <string>

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

	Node<T>* SetHead(Node<T>* link) {
		head = link;

		return head;
	}
	Node<T>* GetHead() {
		return head;
	}

	int SetSize(int size) {
		if (size < 0)
			return ErrorValue<T>::GetInt();

		this->size = size;

		return size;
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

	void FillInInsufficientSpace(int size) {
		while (size--) {
			InsertLast(DefaultValue<T>::Get());
		}
	}

	Node<T>* CreateNewNode(T data=DefaultValue<T>::Get()) {
		Node<T>* newNode = new Node<T>;
		newNode->data = data;

		return newNode;
	}

	Node<T>* GetNode(int idx) {
		Node<T>* tmp = GetHead();
		while (--idx) {
			if (tmp->link == NULL)
				break;

			tmp = tmp->link;
		}

		return tmp;
	}

	void ConnectNode(Node<T>* node1, Node<T>* node2) {
		if (node1 == GetHead()) {
			node2->link = GetHead();
			SetHead(node2);
		}
		else {
			node2->link = node1->link;
			node1->link = node2;
		}
	}

	void RemoveNode(Node<T>* prevNode) {
		if (prevNode == GetHead()) {
			Node<T>* removed = GetHead();
			SetHead(GetHead()->link);

			delete removed;
		}
		else {
			Node<T>* removed = prevNode->link;
			prevNode->link = prevNode->link->link;

			delete removed;
		}
	}

public:
	List() {
		head = NULL;

		SetSize(0);
	}

	int GetSize() {
		return size;
	}

	bool IsEmpty() {
		return (GetSize() == 0);
	}

	bool IsIdxValid(int idx) {
		if (idx < 0)
			return false;

		return true;
	}

	T Insert(int idx, T data) {
		if (IsIdxValid(idx) == false)
			return ErrorValue<T>::Get();

		int size = GetSize();

		if (idx > size - 1) {
			int insufficientSpaceSize = idx - size;

			FillInInsufficientSpace(insufficientSpaceSize);
		}

		Node<T>* newNode = CreateNewNode(data);

		if (GetHead() == NULL) {
			InsertFirst(data);

			return DefaultValue<T>::Get();
		}

		Node<T>* tmp = GetNode(idx);

		newNode->link = tmp->link;
		tmp->link = newNode;

		PlusOneToSize();

		return DefaultValue<T>::Get();
	}

	void InsertFirst(T data) {
		Node<T>* newNode = CreateNewNode(data);

		ConnectNode(GetHead(), newNode);

		PlusOneToSize();
	}

	void InsertLast(T data) {
		Node<T>* newNode = CreateNewNode(data);

		if (head == NULL) {
			InsertFirst(data);

			PlusOneToSize();

			return;
		}

		Node<T>* tmp = GetNode(GetSize());

		newNode->link = tmp->link;
		tmp->link = newNode;

		PlusOneToSize();
	}

	T Delete(int idx) {
		if (IsEmpty() == true)
			return ErrorValue<T>::Get();

		if (idx == 0) {
			RemoveNode(GetHead());

			SubtractOneFromTheSize();

			return DefaultValue<T>::Get();
		}

		Node<T>* tmp = GetNode(idx);

		RemoveNode(tmp);

		SubtractOneFromTheSize();

		return DefaultValue<T>::Get();
	}

	void Clear() {
		while (head != NULL) {
			Delete(0);
		}

		SetSize(0);
	}

	void Print() {
		cout << "head->";

		for (; head != NULL; head = head->link) {
			cout << head->data << "->";
		}

		cout << "NULL";
	}
};

int main() {
	List<int> l;

	l.InsertLast(0);
	l.InsertLast(1);
	l.InsertLast(2);

	l.Delete(1);

	l.Print();

	return 0;
}
