#define MAX 200

class CStack
{
public:
	int top;
	int* stack;

public:
	CStack();
	~CStack();
	void push(int x);
	int pop();
	bool isEmpty();
	bool isFull();
	void print();
	int getTop();
	int size();
};