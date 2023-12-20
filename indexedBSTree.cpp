#include<iostream>
using namespace std;
template<class T>
struct binarytreeNode {
	T element;
	int LeftSize; //左子树节点个数
	binarytreeNode<T>* leftChild; //左子树
	binarytreeNode<T>* rightChild; //右子树
	binarytreeNode() { leftChild = rightChild = NULL; }
	binarytreeNode(const T& theElement) {
		element = theElement;
		LeftSize = 0;
		leftChild = rightChild = NULL;
	}
	binarytreeNode(const T& theElement, binarytreeNode<T>* theLeftChild, binarytreeNode<T>*
		theRightChild, int leftSize)
	{
		element = theElement;
		LeftSize = leftSize;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};
template <class T>
class indexedBSTree //索引二叉搜索树
{
public:
	indexedBSTree()
	{
		root = NULL;
		Size = 0;
	}
	int insert(const T& theElement); //插入函数
	int find(const T& theElement); //查找函数
	int erase(const T& theElement); //删除函数
	int find_order(int order); //按名次搜索函数
	int erase_order(int order); //按名次删除函数
private:
	binarytreeNode<T>* root;
	int Size;
};
//插入函数
template <class T>
int indexedBSTree<T>::insert(const T& theElement)
{
	binarytreeNode<T>* curNode = root; //当前节点
	binarytreeNode<T>* preNode = NULL; //父节点
	int sum = 0; //比较的元素值的异或和
	while (curNode != NULL)
	{
		preNode = curNode;
		if (theElement < curNode->element) //插入的元素小
		{
			sum ^= curNode->element;
			curNode = curNode->leftChild;
		}
		else if (theElement > curNode->element) //插入的元素大
		{
			sum ^= curNode->element;
			curNode = curNode->rightChild;
		}
		else if (theElement == curNode->element) //相等
		{
			return 0;
		}
	}
	binarytreeNode<T>* newNode = new binarytreeNode<T>(theElement);
	if (preNode != NULL)
	{
		if (theElement > preNode->element) //插入元素比父节点大
			preNode->rightChild = newNode; //放在右孩子
		else if (theElement < preNode->element) //插入元素比父节点小
			preNode->leftChild = newNode; //放在左孩子
	}
	else //空树则作为根节点
	{
		root = newNode;
	}
	Size++;
	//重新遍历二叉树，更新索引(LeftSize)
	curNode = root;
	while (curNode->element != theElement) //按插入元素经过的路线走
	{
		if (curNode->element < theElement)
		{
			curNode = curNode->rightChild;
		}
		else if (curNode->element > theElement)
		{
			curNode->LeftSize++;
			curNode = curNode->leftChild;
		}
	}
	return sum;
}
//查找函数
template <class T>
int indexedBSTree<T>::find(const T& theElement)
{
	binarytreeNode<T>* curNode = root;
	int sum = 0; //异或和
	while (curNode != NULL && curNode->element != theElement)
	{
		sum ^= curNode->element;
		if (theElement < curNode->element)
		{
			curNode = curNode->leftChild;
		}
		else if (theElement > curNode->element)
		{
			curNode = curNode->rightChild;
		}
	}
	if (curNode == NULL)
		return 0;
	else
	{
		sum ^= curNode->element;
		return sum;
	}
}
//删除函数
template <class T>
int indexedBSTree<T>::erase(const T& theElement)
{
	binarytreeNode<T>* curNode = root; //要删除的节点
	binarytreeNode<T>* preNode = NULL; //要删除节点的父节点
	int sum = 0;
	while (curNode != NULL && curNode->element != theElement)
	{
		sum ^= curNode->element;
		preNode = curNode;
		if (theElement < curNode->element)
		{
			curNode = curNode->leftChild;
		}
		else if (theElement > curNode->element)
		{
			curNode = curNode->rightChild;
		}
	}
	if (curNode == NULL) //未找到
	{
		return 0;
	}
	sum ^= curNode->element; //找到后
	//重新遍历二叉树，更新索引(LeftSize)
	curNode = root;
	while (curNode != NULL && curNode->element != theElement)
	{
		if (theElement > curNode->element)
		{
			curNode = curNode->rightChild;
		}
		else if (theElement < curNode->element)
		{
			curNode->LeftSize--;
			curNode = curNode->leftChild;
		}
	}
	//要删除的节点有两个孩子
	if (curNode->leftChild != NULL && curNode->rightChild != NULL)
	{
		binarytreeNode<T>* replace = curNode->rightChild; //用来替换要删除节点的元素
		binarytreeNode<T>* pre = curNode;
		while (replace->leftChild != NULL) //替换元素为右子树的最小元素
		{
			replace->LeftSize--;
			pre = replace; //最小元素父节点的位置
			replace = replace->leftChild;
		}
		binarytreeNode<T>* temp = new binarytreeNode<T>(replace->element, curNode->leftChild,
			curNode->rightChild, curNode->LeftSize); //创建一个新节点作为替换节点
		if (preNode == NULL) //要删除的为根节点
			root = temp;
		else if (curNode == preNode->leftChild) //更新要删除节点的父节点的孩子指针
			preNode->leftChild = temp;
		else
			preNode->rightChild = temp;
		if (pre == curNode) //替换元素的父节点就是要删除节点
			preNode = temp;
		else
			preNode = pre;
		delete curNode; //释放删除节点的内存
		curNode = replace;
	}
	//要删除的节点只有一个孩子
	binarytreeNode<T>* p;
	if (curNode->leftChild != NULL)
		p = curNode->leftChild;
	else
		p = curNode->rightChild;
	if (curNode == root) //删除节点为根节点
		root = p;
	else
	{
		if (curNode == preNode->leftChild) //删除的是左孩子
			preNode->leftChild = p;
		else //删除的是右孩子
			preNode->rightChild = p;
	}
	Size--;
	delete curNode; //若没有孩子直接删除
	return sum;
}
//按名次查找函数
template <class T>
int indexedBSTree<T>::find_order(int order)
{
	order = order - 1;
	binarytreeNode<T>* curNode = root;
	int sum = 0;
	while (curNode != NULL)
	{
		sum ^= curNode->element;
		if (curNode->LeftSize > order) //查找元素在左子树
		{
			curNode = curNode->leftChild;
		}
		else if (curNode->LeftSize < order) //查找元素在右子树
		{
			order = order - curNode->LeftSize - 1;
			curNode = curNode->rightChild;
		}
		else
		{
			return sum;
		}
	}
	return 0;
}
//按名次删除函数
template <class T>
int indexedBSTree<T>::erase_order(int order)
{
	order = order - 1;
	binarytreeNode<T>* curNode = root;
	binarytreeNode<T>* preNode = NULL;
	int sum = 0;
	while (curNode != NULL && curNode->LeftSize != order)
	{
		sum ^= curNode->element;
		preNode = curNode;
		if (curNode->LeftSize > order)
		{
			curNode = curNode->leftChild;
		}
		else if (curNode->LeftSize < order)
		{
			order = order - curNode->LeftSize - 1;
			curNode = curNode->rightChild;
		}
	}
	if (curNode == NULL) //未找到
		return 0;
	sum ^= curNode->element;
	int theElement = curNode->element;
	//重新遍历二叉树，更新索引(LeftSize)
	curNode = root;
	while (curNode != NULL && curNode->element != theElement)
	{
		if (curNode->element < theElement)
		{
			curNode = curNode->rightChild;
		}
		else if (curNode->element > theElement)
		{
			curNode->LeftSize--;
			curNode = curNode->leftChild;
		}
	}
	//要删除的节点有两个孩子
	if (curNode->leftChild != NULL && curNode->rightChild != NULL)
	{
		binarytreeNode<T>* replace = curNode->rightChild; //用来替换要删除节点的元素
		binarytreeNode<T>* pre = curNode;
		while (replace->leftChild != NULL) //替换元素为右子树的最小元素
		{
			replace->LeftSize--;
			pre = replace; //最小元素父节点的位置
			replace = replace->leftChild;
		}
		binarytreeNode<T>* temp = new binarytreeNode<T>(replace->element, curNode->leftChild,
			curNode->rightChild, curNode->LeftSize); //创建一个新节点作为替换节点
		if (preNode == NULL) //要删除的为根节点
			root = temp;
		else if (curNode == preNode->leftChild) //更新要删除节点的父节点的孩子指针
			preNode->leftChild = temp;
		else
			preNode->rightChild = temp;
		if (pre == curNode) //替换元素的父节点就是要删除节点
			preNode = temp;
		else
			preNode = pre;
		delete curNode; //释放删除节点的内存
		curNode = replace;
	}
	//要删除的节点只有一个孩子
	binarytreeNode<T>* p;
	if (curNode->leftChild != NULL)
		p = curNode->leftChild;
	else
		p = curNode->rightChild;
	if (curNode == root) //删除节点为根节点
		root = p;
	else
	{
		if (curNode == preNode->leftChild) //删除的是左孩子
			preNode->leftChild = p;
		else //删除的是右孩子
			preNode->rightChild = p;
	}
	Size--;
	delete curNode; //若没有孩子直接删除
	return sum;
}
int main()
{
	ios::sync_with_stdio(false);
	indexedBSTree<int> tree;
	int m, a, b;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		switch (a)
		{
		case 0:
			cout << tree.insert(b) << endl;
			break;
		case 1:
			cout << tree.find(b) << endl;
			break;
		case 2:
			cout << tree.erase(b) << endl;
			break;
		case 3:
			cout << tree.find_order(b) << endl;
			break;
		case 4:
			cout << tree.erase_order(b) << endl;
			break;
		}
	}
	return 0;
}