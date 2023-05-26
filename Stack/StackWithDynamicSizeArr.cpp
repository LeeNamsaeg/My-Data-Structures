#include <cstdlib>

#define INFINITY 2000000000

using namespace std;

template <typename T>
class Stack{
private:	
	T* datas;
	
	int size;
	
	int top;
	
public:
	Stack(){
		size = 0;
		
		top = -1;
	}
	
	int Push(T data){
		if (IsFull() == true){
			datas = (T*)realloc(datas, sizeof(T) * size);
		}
		
		datas[++top] = data;
	}
	
	T Pop(){
		if (IsEmpty() == true)
			return INFINITY;
		
		return (datas[top--]);
	}
	
	bool IsEmpty(){
		return (top == -1);
	}
	
	bool IsFull(){
		return (top == size - 1);
	}
	
	void Clear(){
		top = -1;
	}
};
