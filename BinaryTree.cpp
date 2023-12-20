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
	T& front() { return queue[theFront]; } //������Ԫ��
	void pop() //ɾ��Ԫ��
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
	int theFront; //��Ԫ��
	int theBack; //βԪ��
	int arrayLength; //���г���
	T* queue; //�洢����
};
//���ڵ�
template<class T>
struct treeNode
{
	T element;
	treeNode<T>* leftChild; //������
	treeNode<T>* rightChild; //������
	treeNode() { leftChild = rightChild = NULL; } //Ĭ�Ϲ��캯��
	treeNode(const T& theelement) //���캯��
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
//������
template<class T>
class BinaryTree
{
public:
	BinaryTree() { root = NULL; Size = 0; }
	~BinaryTree() {}
	inline void visit(treeNode<T>* p) { cout << p->element << " "; } //����ڵ�������
	treeNode<T>* getRoot() { return root; }
	void preOrder(treeNode<T>* p); //ǰ�����
	void inOrder(); //�������
	void postOrder(); //�������
	void levelOrder(); //��α���
	treeNode<T>* find(int m); //���ұ��Ϊ m �Ľڵ�
	void origin(const int& n); //��ʼ��������
	int height(treeNode<T>* p); //����������߶�
	int nodeNum(treeNode<T>* p); //����ڵ���
private:
	treeNode<T>* root; //ָ�����ָ��
	treeNode<T>** Nodetable; //���ָ��ڵ��ָ��
	int Size;
};
template<class T>
void BinaryTree<T>::preOrder(treeNode<T>* p)
{
	if (p != NULL)
	{
		visit(p); //���ʸ��ڵ�
		preOrder(p->leftChild); //����������
		preOrder(p->rightChild); //����������
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
	while (top >= 0 || node != NULL) //���鲻Ϊ��
	{
		while (node != NULL) //��ڵ��������
		{
			table[++top] = node;
			node = node->leftChild;
		}
		if (top >= 0) //�������нڵ�
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
	treeNode<T>* cur; //��ǰ�ڵ�
	treeNode<T>* last = NULL; //��һ�����ʵĽڵ�
	table[++top] = root;
	while (top >= 0)
	{
		cur = table[top];
		if ((cur->leftChild == NULL && cur->rightChild == NULL) || (last != NULL && (last ==
			cur->leftChild || last == cur->rightChild)))
		{
			visit(cur); //��ǰ�ڵ�û���ӽ������ӽڵ㶼�����ʹ�
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
		if (node->leftChild != NULL) //������ڵ�
			table.push(node->leftChild);
		if (node->rightChild != NULL) //�����ҽڵ�
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
	root = new treeNode<T>(1); //�������ڵ�
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
	if (!p) //����
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
		num = nodeNum(p->leftChild) + nodeNum(p->rightChild) + 1; //�������ڵ�+�������ڵ�+��
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