#include<iostream>
using namespace std;
template<class T>
class Queue
{
public:
	Queue(int Length)
	{
		arrayLength = Length;
		queue = new T[arrayLength + 1];
		theFront = 0;
		theBack = 0;
	}
	~Queue() { delete[] queue; }
	inline bool empty() { return theFront == theBack; }
	inline bool full() { return theFront == (theBack + 1) % (arrayLength + 1); }
	T& front() { return queue[theFront]; } //返回首元素
	void pop() //删除元素
	{
		theFront = (theFront + 1) % (arrayLength + 1);
	}
	void push(const T& theElement)
	{
		if (!full())
		{
			queue[theBack] = theElement;
			theBack = (theBack + 1) % (arrayLength + 1);
		}
	}
private:
	int theFront; //首元素
	int theBack; //尾元素
	int arrayLength; //队列长度
	T* queue; //存储数组
};
//树节点
template<class T>
struct treeNode
{
	T element;
	treeNode<T>* leftChild; //左子树
	treeNode<T>* rightChild; //右子树
	treeNode() { leftChild = rightChild = NULL; } //默认构造函数
	treeNode(const T& theelement) //构造函数
	{
		element = theelement;
		leftChild = rightChild = NULL;
	}
	treeNode(const T& theelement, treeNode<T>* left, treeNode<T>* right)
	{
		element = theelement;
		leftChild = left;
		rightChild = right;
	}
};
//二叉树
template<class T>
class BinaryTree
{
public:
	BinaryTree() { root = NULL; Size = 0; }
	~BinaryTree() {}
	inline void visit(treeNode<T>* p) { cout << p->element << " "; } //输出节点数据域
	treeNode<T>* getRoot() { return root; }
	void preOrder(treeNode<T>* p); //前序遍历
	void inOrder(); //中序遍历
	void postOrder(); //后序遍历
	void levelOrder(); //层次遍历
	treeNode<T>* find(int m); //查找编号为 m 的节点
	void origin(const int& n); //初始化二叉树
	int height(treeNode<T>* p); //计算二叉树高度
	int nodeNum(treeNode<T>* p); //计算节点数
private:
	treeNode<T>* root; //指向根的指针
	treeNode<T>** Nodetable; //存放指向节点的指针
	int Size;
};
template<class T>
void BinaryTree<T>::preOrder(treeNode<T>* p)
{
	if (p != NULL)
	{
		visit(p); //访问根节点
		preOrder(p->leftChild); //访问左子树
		preOrder(p->rightChild); //访问右子树
	}
}
template<class T>
void BinaryTree<T>::inOrder()
{
	treeNode<T>** table = new treeNode<T>*[Size];
	for (int i = 0; i < Size; i++)
		table[i] = NULL;
	int top = -1;
	treeNode<T>* node = root;
	while (top >= 0 || node != NULL) //数组不为空
	{
		while (node != NULL) //左节点放入数组
		{
			table[++top] = node;
			node = node->leftChild;
		}
		if (top >= 0) //数组内有节点
		{
			node = table[top];
			visit(node);
			table[top--] = NULL;
			node = node->rightChild;
		}
	}
	delete[] table;
}
template<class T>
void BinaryTree<T>::postOrder()
{
	treeNode<T>** table = new treeNode<T>*[Size];
	for (int i = 0; i < Size; i++)
		table[i] = NULL;
	int top = -1;
	treeNode<T>* cur; //当前节点
	treeNode<T>* last = NULL; //上一个访问的节点
	table[++top] = root;
	while (top >= 0)
	{
		cur = table[top];
		if ((cur->leftChild == NULL && cur->rightChild == NULL) || (last != NULL && (last ==
			cur->leftChild || last == cur->rightChild)))
		{
			visit(cur); //当前节点没有子结点或者子节点都被访问过
			table[top--] = NULL;
			last = cur;
		}
		else
		{
			if (cur->rightChild != NULL)
				table[++top] = cur->rightChild;
			if (cur->leftChild != NULL)
				table[++top] = cur->leftChild;
		}
	}
	delete[] table;
}
template<class T>
void BinaryTree<T>::levelOrder()
{
	Queue<treeNode<T>*> table(Size);
	treeNode<T>* node = root;
	while (node != NULL)
	{
		visit(node);
		if (node->leftChild != NULL) //放入左节点
			table.push(node->leftChild);
		if (node->rightChild != NULL) //放入右节点
			table.push(node->rightChild);
		if (table.empty())
			break;
		node = table.front();
		table.pop();
	}
}
template<class T>
treeNode<T>* BinaryTree<T>::find(int m)
{
	return Nodetable[m];
}
template<class T>
void BinaryTree<T>::origin(const int& n)
{
	Size = n;
	Nodetable = new treeNode<T>*[Size + 1];
	root = new treeNode<T>(1); //创建根节点
	for (int i = 0; i <= Size; i++)
		Nodetable[i] = NULL;
	Nodetable[1] = root;
	treeNode<T>* temp = NULL;
	int a, b;
	for (int i = 1; i <= n; i++)
	{
		cin >> a >> b;
		temp = Nodetable[i];
		if (temp != NULL)
		{
			if (a != -1)
			{
				temp->leftChild = new treeNode<T>(a);
				Nodetable[a] = temp->leftChild;
			}
			if (b != -1)
			{
				temp->rightChild = new treeNode<T>(b);
				Nodetable[b] = temp->rightChild;
			}
		}
	}
}
template<class T>
int BinaryTree<T>::height(treeNode<T>* p)
{
	if (!p) //空树
		return 0;
	int hl = height(p->leftChild);
	int hr = height(p->rightChild);
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}
template<class T>
int BinaryTree<T>::nodeNum(treeNode<T>* p)
{
	int num = 0;
	if (p != NULL)
	{
		num = nodeNum(p->leftChild) + nodeNum(p->rightChild) + 1; //左子树节点+右子树节点+根
	}
	return num;
}
int main()
{
	int n, a, b;
	cin >> n;
	BinaryTree<int> tree;
	treeNode<int>* temp = NULL;
	tree.origin(n);
	tree.preOrder(tree.getRoot());
	cout << endl;
	tree.inOrder();
	cout << endl;
	tree.postOrder();
	cout << endl;
	tree.levelOrder();
	cout << endl;
	int* node_num = new int[n + 1];
	int* ht = new int[n + 1];
	for (int i = 1; i <= n; i++)
	{
		temp = tree.find(i);
		node_num[i] = tree.nodeNum(temp);
		ht[i] = tree.height(temp);
	}
	for (int j = 1; j <= n; j++)
		cout << node_num[j] << " ";
	cout << endl;
	for (int k = 1; k <= n; k++)
		cout << ht[k] << " ";
	delete[] node_num;
	delete[] ht;
	return 0;
}