#define INFINITY 2000000000

#define MAX_STACK_SIZE 100

template <typename T>
class Stack{
private:	
	T datas[MAX_STACK_SIZE];
	
	int top;
	
public:
	Stack(){
		top = -1;
	}
	
	int Push(T data){
		if (IsFull() == true)		
			return INFINITY;
		
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
		return (top == MAX_STACK_SIZE - 1);
	}
	
	void Clear(){
		top = -1;
	}
};
