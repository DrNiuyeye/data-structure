#include<iostream>
using namespace std;
template<class T>
struct binarytreeNode {
	T element;
	int LeftSize; //�������ڵ����
	binarytreeNode<T>* leftChild; //������
	binarytreeNode<T>* rightChild; //������
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
class indexedBSTree //��������������
{
public:
	indexedBSTree()
	{
		root = NULL;
		Size = 0;
	}
	int insert(const T& theElement); //���뺯��
	int find(const T& theElement); //���Һ���
	int erase(const T& theElement); //ɾ������
	int find_order(int order); //��������������
	int erase_order(int order); //������ɾ������
private:
	binarytreeNode<T>* root;
	int Size;
};
//���뺯��
template <class T>
int indexedBSTree<T>::insert(const T& theElement)
{
	binarytreeNode<T>* curNode = root; //��ǰ�ڵ�
	binarytreeNode<T>* preNode = NULL; //���ڵ�
	int sum = 0; //�Ƚϵ�Ԫ��ֵ������
	while (curNode != NULL)
	{
		preNode = curNode;
		if (theElement < curNode->element) //�����Ԫ��С
		{
			sum ^= curNode->element;
			curNode = curNode->leftChild;
		}
		else if (theElement > curNode->element) //�����Ԫ�ش�
		{
			sum ^= curNode->element;
			curNode = curNode->rightChild;
		}
		else if (theElement == curNode->element) //���
		{
			return 0;
		}
	}
	binarytreeNode<T>* newNode = new binarytreeNode<T>(theElement);
	if (preNode != NULL)
	{
		if (theElement > preNode->element) //����Ԫ�رȸ��ڵ��
			preNode->rightChild = newNode; //�����Һ���
		else if (theElement < preNode->element) //����Ԫ�رȸ��ڵ�С
			preNode->leftChild = newNode; //��������
	}
	else //��������Ϊ���ڵ�
	{
		root = newNode;
	}
	Size++;
	//���±�������������������(LeftSize)
	curNode = root;
	while (curNode->element != theElement) //������Ԫ�ؾ�����·����
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
//���Һ���
template <class T>
int indexedBSTree<T>::find(const T& theElement)
{
	binarytreeNode<T>* curNode = root;
	int sum = 0; //����
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
//ɾ������
template <class T>
int indexedBSTree<T>::erase(const T& theElement)
{
	binarytreeNode<T>* curNode = root; //Ҫɾ���Ľڵ�
	binarytreeNode<T>* preNode = NULL; //Ҫɾ���ڵ�ĸ��ڵ�
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
	if (curNode == NULL) //δ�ҵ�
	{
		return 0;
	}
	sum ^= curNode->element; //�ҵ���
	//���±�������������������(LeftSize)
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
	//Ҫɾ���Ľڵ�����������
	if (curNode->leftChild != NULL && curNode->rightChild != NULL)
	{
		binarytreeNode<T>* replace = curNode->rightChild; //�����滻Ҫɾ���ڵ��Ԫ��
		binarytreeNode<T>* pre = curNode;
		while (replace->leftChild != NULL) //�滻Ԫ��Ϊ����������СԪ��
		{
			replace->LeftSize--;
			pre = replace; //��СԪ�ظ��ڵ��λ��
			replace = replace->leftChild;
		}
		binarytreeNode<T>* temp = new binarytreeNode<T>(replace->element, curNode->leftChild,
			curNode->rightChild, curNode->LeftSize); //����һ���½ڵ���Ϊ�滻�ڵ�
		if (preNode == NULL) //Ҫɾ����Ϊ���ڵ�
			root = temp;
		else if (curNode == preNode->leftChild) //����Ҫɾ���ڵ�ĸ��ڵ�ĺ���ָ��
			preNode->leftChild = temp;
		else
			preNode->rightChild = temp;
		if (pre == curNode) //�滻Ԫ�صĸ��ڵ����Ҫɾ���ڵ�
			preNode = temp;
		else
			preNode = pre;
		delete curNode; //�ͷ�ɾ���ڵ���ڴ�
		curNode = replace;
	}
	//Ҫɾ���Ľڵ�ֻ��һ������
	binarytreeNode<T>* p;
	if (curNode->leftChild != NULL)
		p = curNode->leftChild;
	else
		p = curNode->rightChild;
	if (curNode == root) //ɾ���ڵ�Ϊ���ڵ�
		root = p;
	else
	{
		if (curNode == preNode->leftChild) //ɾ����������
			preNode->leftChild = p;
		else //ɾ�������Һ���
			preNode->rightChild = p;
	}
	Size--;
	delete curNode; //��û�к���ֱ��ɾ��
	return sum;
}
//�����β��Һ���
template <class T>
int indexedBSTree<T>::find_order(int order)
{
	order = order - 1;
	binarytreeNode<T>* curNode = root;
	int sum = 0;
	while (curNode != NULL)
	{
		sum ^= curNode->element;
		if (curNode->LeftSize > order) //����Ԫ����������
		{
			curNode = curNode->leftChild;
		}
		else if (curNode->LeftSize < order) //����Ԫ����������
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
//������ɾ������
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
	if (curNode == NULL) //δ�ҵ�
		return 0;
	sum ^= curNode->element;
	int theElement = curNode->element;
	//���±�������������������(LeftSize)
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
	//Ҫɾ���Ľڵ�����������
	if (curNode->leftChild != NULL && curNode->rightChild != NULL)
	{
		binarytreeNode<T>* replace = curNode->rightChild; //�����滻Ҫɾ���ڵ��Ԫ��
		binarytreeNode<T>* pre = curNode;
		while (replace->leftChild != NULL) //�滻Ԫ��Ϊ����������СԪ��
		{
			replace->LeftSize--;
			pre = replace; //��СԪ�ظ��ڵ��λ��
			replace = replace->leftChild;
		}
		binarytreeNode<T>* temp = new binarytreeNode<T>(replace->element, curNode->leftChild,
			curNode->rightChild, curNode->LeftSize); //����һ���½ڵ���Ϊ�滻�ڵ�
		if (preNode == NULL) //Ҫɾ����Ϊ���ڵ�
			root = temp;
		else if (curNode == preNode->leftChild) //����Ҫɾ���ڵ�ĸ��ڵ�ĺ���ָ��
			preNode->leftChild = temp;
		else
			preNode->rightChild = temp;
		if (pre == curNode) //�滻Ԫ�صĸ��ڵ����Ҫɾ���ڵ�
			preNode = temp;
		else
			preNode = pre;
		delete curNode; //�ͷ�ɾ���ڵ���ڴ�
		curNode = replace;
	}
	//Ҫɾ���Ľڵ�ֻ��һ������
	binarytreeNode<T>* p;
	if (curNode->leftChild != NULL)
		p = curNode->leftChild;
	else
		p = curNode->rightChild;
	if (curNode == root) //ɾ���ڵ�Ϊ���ڵ�
		root = p;
	else
	{
		if (curNode == preNode->leftChild) //ɾ����������
			preNode->leftChild = p;
		else //ɾ�������Һ���
			preNode->rightChild = p;
	}
	Size--;
	delete curNode; //��û�к���ֱ��ɾ��
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