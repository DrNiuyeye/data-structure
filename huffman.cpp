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
	bool empty() { return theFront == theBack; }
	T& front() { return queue[theFront]; } //������Ԫ��
	void pop() //ɾ��Ԫ��
	{
		queue[theFront].~T();
		theFront = (theFront + 1) % (arrayLength + 1);
	}
	void push(const T& theElement)
	{
		queue[theBack] = theElement;
		theBack = (theBack + 1) % (arrayLength + 1);
	}
private:
	int theFront;		//��Ԫ��
	int theBack;		//βԪ��
	int arrayLength;	//���г���
	T* queue;			//�洢����
};

template<class T>
class minHeap
{
public:
	minHeap(int Leng = 26)
	{
		Length = Leng + 1;
		heap = new T[Length];
		Size = 0;
	}
	~minHeap() { delete[] heap; }
	T& top() { return heap[1]; }
	void push(const T& theelement);
	void pop();
	void initial(T* theheap, int size);

private:
	T* heap;     //����
	int Length;  //���鳤��
	int Size;    //����Ԫ�ظ���

};

template<class T>
void minHeap<T>::push(const T& theelement)
{
	Size++;
	int curNode = Size;   //�ӵײ������ƶ�
	while (heap[curNode / 2] > theelement && curNode != 1)      //���ڵ���ڲ���Ԫ�ػ򵽴ﶥ��
	{
		heap[curNode] = heap[curNode / 2];         //���ڵ�����
		curNode /= 2;                              //����Ԫ���������ڵ�
	}
	heap[curNode] = theelement;
}

template<class T>
void minHeap<T>::pop()
{
	heap[1].~T();
	T lastelement = heap[Size--];     //ɾ�����һ���ڵ�
	//�ع���
	int curNode = 1;              //���ڵ�
	int nextNode = 2;
	while (nextNode <= Size)
	{
		if (nextNode < Size && heap[nextNode] > heap[nextNode + 1])  //��С�ĺ���
			nextNode++;
		if (lastelement <= heap[nextNode])                          //�ҵ�����λ��
			break;
		heap[curNode] = heap[nextNode];
		curNode = nextNode;                                        //�ƶ�����һ���ж�   
		nextNode *= 2;
	}
	heap[curNode] = lastelement;
}

template<class T>
void minHeap<T>::initial(T* theheap, int size)
{
	delete[]heap;
	heap = theheap;
	Size = size;
	for (int i = Size / 2; i >= 1; i--)          //�����һ���ɺ��ӵĽڵ㿪ʼ���
	{
		T rootelement = heap[i];   //���ڵ��Ԫ��
		int child = 2 * i;         //���ӵ�λ��
		while (child <= Size)
		{
			if (child < Size && heap[child] > heap[child + 1])      //��С�ĺ���
				child++;
			if (rootelement <= heap[child])
				break;
			heap[child / 2] = heap[child];
			child *= 2;
		}
		heap[child / 2] = rootelement;
	}
}

template<class T>
struct binarytreeNode {
	T element;
	binarytreeNode<T>* leftChild;
	binarytreeNode<T>* rightChild;
	binarytreeNode() { leftChild = rightChild = NULL; }
	binarytreeNode(const T& theElement) {
		element = theElement;
		leftChild = rightChild = NULL;
	}
	binarytreeNode(const T& theElement, binarytreeNode<T>* theLeftChild, binarytreeNode<T>* theRightChild) {
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};

//������
template<class T>
class BinaryTree
{
public:
	BinaryTree() { root = NULL; }
	~BinaryTree() {}
	int hufLength(int* weight, int count);
	void makeroot(const T element, BinaryTree<T>& left, BinaryTree<T>& right)    //�����½ڵ���Ϊ���ڵ�
	{
		root = new binarytreeNode<T>(element, left.root, right.root);
	}
private:
	binarytreeNode<T>* root;            //ָ�����ָ��
	int Size;
};

template<class T>
struct huffmanNode
{
	T weight;              //Ȩֵ
	BinaryTree<T>* tree;   //�Ըýڵ�Ϊ���Ķ�����
	operator T() const { return weight; }
};

template<class T>
BinaryTree<T>* makehufTree(T* weight, int n)
{
	huffmanNode<T>* table = new huffmanNode<T>[n + 1];      //һ�鵥�ڵ���
	BinaryTree<int>emptyTree;                               //����
	for (int i = 1; i <= n; i++)
	{               
		table[i].weight = weight[i];
		table[i].tree = new BinaryTree<int>;
		table[i].tree->makeroot(i, emptyTree, emptyTree);       //iΪ�ⲿ�ڵ��ţ��������ȡȨ
	}

	minHeap<huffmanNode<T>> heap;
	heap.initial(table, n);            //��ʼ��ΪС����
	huffmanNode<T> w, x, y;
	BinaryTree<int>* z;
	for (int i = 1; i < n; i++) {
		x = heap.top();               //ȡ��Ȩ��С�������� 
		heap.pop();
		y = heap.top(); 
		heap.pop();
		z = new BinaryTree<int>;
		z->makeroot(0, *x.tree, *y.tree);
		w.weight = x.weight + y.weight;
		w.tree = z;
		heap.push(w);
		delete x.tree;
		delete y.tree;
	}
	return heap.top().tree;          //���ػ�������
}

template<class T>
int BinaryTree<T>::hufLength(int* weight, int count)
{
	Size = 2 * count - 1;
	int sum_len = 0;
	Queue<binarytreeNode<T>*> q(Size);
	binarytreeNode<T>* curNode;
	q.push(root);
	root->element = 0;            //·��(���볤��)
	int temp;
	while (!q.empty())
	{
		curNode = q.front();
		q.pop();
		if (curNode->leftChild != NULL)
		{
			q.push(curNode->leftChild);
			temp = curNode->leftChild->element;                        //ȡ���ڵ���
			curNode->leftChild->element = curNode->element + 1;        //����·��
			if (temp != 0) {                                           //�����ڲ��ڵ�ʱ
				sum_len += weight[temp] * curNode->leftChild->element; //���ݱ���ҵ���Ӧ����(�ܳ���+=Ȩ*·��)
			}
		}
		if (curNode->rightChild != NULL)
		{
			q.push(curNode->rightChild);
			temp = curNode->rightChild->element;
			curNode->rightChild->element = curNode->element + 1;
			if (temp != 0) {
				sum_len += weight[temp] * curNode->leftChild->element;
			}
		}
	}
	return sum_len;
}

int main()
{
	char input[1000000];
	cin >> input;
	int* arr = new int[26];         //��¼Ƶ��
	for (int i = 0; i < 26; i++)
		arr[i] = 0;
	int count = 0;                  //��ͬ��ĸ��Ŀ
	int k = 0;
	while (input[k] != '\0')
	{
		arr[input[k] - 'a']++;      //ͳ����ĸ����Ƶ��
		if (arr[(input[k] - 'a')] == 1)
			count++;
		k++;
	}
	int* weight = new int[count + 1];
	weight[0] = 0;
	int index = 1;
	for (int i = 0; i < 26; i++)
	{
		if (arr[i] != 0)
		{
			weight[index] = arr[i];
			index++;
		}
	}
	BinaryTree<int>* huftree = makehufTree(weight, count);
	cout << huftree->hufLength(weight, count);
	return 0;
}