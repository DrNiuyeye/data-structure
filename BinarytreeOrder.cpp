#include<iostream>
using namespace std;


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
	void setRoot(treeNode<T>* p, int n) 
	{ 
		root = p;
		Size = n;
	}
	void preOrder(treeNode<T>* p);
	void postOrder();              //后序遍历
	treeNode<T>* get() { return root; }
	treeNode<T>* buildTree(int* pre, int* in, int pre_start, int pre_end, int in_start, int in_end);     //构建二叉树
private:
	treeNode<T>* root; //指向根的指针
	int Size;

};

template<class T>
void BinaryTree<T>::postOrder()
{
	treeNode<T>** table = new treeNode<T>*[Size];
	for (int i = 0; i < Size; i++)
		table[i] = NULL;
	int top = -1;
	treeNode<T>* cur;                 //当前节点
	treeNode<T>* last = NULL;         //上一个访问的节点
	table[++top] = root;
	while (top >= 0)
	{
		cur = table[top];
		if ((cur->leftChild == NULL && cur->rightChild == NULL) || (last != NULL && (last == cur->leftChild || last == cur->rightChild)))
		{
			visit(cur);              //当前节点没有子结点或者子节点都被访问过 
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
		visit(p);  //访问根节点
		preOrder(p->leftChild);  //访问左子树
		preOrder(p->rightChild);  //访问右子树
	}
}

template<class T>
treeNode<T>* BinaryTree<T>::buildTree(int* pre, int* in, int pre_start, int pre_end, int in_start, int in_end)
{
	if (pre_start > pre_end)
		return NULL;
	int root_pos = -1;
	for (int i = in_start; i <= in_end; i++)   //遍历查找根在中序遍历中的位置
	{
		if (pre[pre_start] == in[i])
		{
			root_pos = i;
			break;
		}
	}

	int left_num = root_pos - in_start;    //左子树节点数
	treeNode<T>* node = new treeNode<T>(pre[pre_start]);     //创建根节点
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

