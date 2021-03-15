struct sTreeNode
{
	int Data;
	sTreeNode* Left;
	sTreeNode* Right;
};

class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();

private:
	sTreeNode* Root;
	int count;

public:
	void DeleteTree(sTreeNode* Node);
	void Insert(int item);
	int Height(sTreeNode* Node);
	void Print(sTreeNode* Node);
	void Print();
};