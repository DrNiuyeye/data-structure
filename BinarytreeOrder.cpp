#include<iostream>
using namespace std;


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
	void setRoot(treeNode<T>* p, int n) 
	{ 
		root = p;
		Size = n;
	}
	void preOrder(treeNode<T>* p);
	void postOrder();              //�������
	treeNode<T>* get() { return root; }
	treeNode<T>* buildTree(int* pre, int* in, int pre_start, int pre_end, int in_start, int in_end);     //����������
private:
	treeNode<T>* root; //ָ�����ָ��
	int Size;

};

template<class T>
void BinaryTree<T>::postOrder()
{
	treeNode<T>** table = new treeNode<T>*[Size];
	for (int i = 0; i < Size; i++)
		table[i] = NULL;
	int top = -1;
	treeNode<T>* cur;                 //��ǰ�ڵ�
	treeNode<T>* last = NULL;         //��һ�����ʵĽڵ�
	table[++top] = root;
	while (top >= 0)
	{
		cur = table[top];
		if ((cur->leftChild == NULL && cur->rightChild == NULL) || (last != NULL && (last == cur->leftChild || last == cur->rightChild)))
		{
			visit(cur);              //��ǰ�ڵ�û���ӽ������ӽڵ㶼�����ʹ� 
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
void BinaryTree<T>::preOrder(treeNode<T>* p)
{
	if (p != NULL)
	{
		visit(p);  //���ʸ��ڵ�
		preOrder(p->leftChild);  //����������
		preOrder(p->rightChild);  //����������
	}
}

template<class T>
treeNode<T>* BinaryTree<T>::buildTree(int* pre, int* in, int pre_start, int pre_end, int in_start, int in_end)
{
	if (pre_start > pre_end)
		return NULL;
	int root_pos = -1;
	for (int i = in_start; i <= in_end; i++)   //�������Ҹ�����������е�λ��
	{
		if (pre[pre_start] == in[i])
		{
			root_pos = i;
			break;
		}
	}

	int left_num = root_pos - in_start;    //�������ڵ���
	treeNode<T>* node = new treeNode<T>(pre[pre_start]);     //�������ڵ�
	node->leftChild = buildTree(pre, in, pre_start + 1, pre_start + left_num, in_start, root_pos - 1);
	node->rightChild = buildTree(pre, in, pre_start + left_num + 1, pre_end, root_pos + 1, in_end);
	return node;
}

int main()
{
	int n;
	cin >> n;
	int* pre = new int[n];
	int* in = new int[n];
	for (int i = 0; i < n; i++)
		cin >> pre[i];
	for (int i = 0; i < n; i++)
		cin >> in[i];
	BinaryTree<int> tree;
	treeNode<int>* Root = tree.buildTree(pre, in, 0, n - 1, 0, n - 1);
	tree.setRoot(Root, n);
	tree.postOrder();
	return 0;
}

