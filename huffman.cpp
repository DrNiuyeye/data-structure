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
	T& front() { return queue[theFront]; } //返回首元素
	void pop() //删除元素
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
	int theFront;		//首元素
	int theBack;		//尾元素
	int arrayLength;	//队列长度
	T* queue;			//存储数组
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
	T* heap;     //数组
	int Length;  //数组长度
	int Size;    //堆内元素个数

};

template<class T>
void minHeap<T>::push(const T& theelement)
{
	Size++;
	int curNode = Size;   //从底部向上移动
	while (heap[curNode / 2] > theelement && curNode != 1)      //父节点大于插入元素或到达顶部
	{
		heap[curNode] = heap[curNode / 2];         //父节点下移
		curNode /= 2;                              //插入元素移至父节点
	}
	heap[curNode] = theelement;
}

template<class T>
void minHeap<T>::pop()
{
	heap[1].~T();
	T lastelement = heap[Size--];     //删除最后一个节点
	//重构堆
	int curNode = 1;              //根节点
	int nextNode = 2;
	while (nextNode <= Size)
	{
		if (nextNode < Size && heap[nextNode] > heap[nextNode + 1])  //更小的孩子
			nextNode++;
		if (lastelement <= heap[nextNode])                          //找到合适位置
			break;
		heap[curNode] = heap[nextNode];
		curNode = nextNode;                                        //移动至下一层判断   
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
	for (int i = Size / 2; i >= 1; i--)          //从最后一个由孩子的节点开始检查
	{
		T rootelement = heap[i];   //父节点的元素
		int child = 2 * i;         //左孩子的位置
		while (child <= Size)
		{
			if (child < Size && heap[child] > heap[child + 1])      //更小的孩子
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

//二叉树
template<class T>
class BinaryTree
{
public:
	BinaryTree() { root = NULL; }
	~BinaryTree() {}
	int hufLength(int* weight, int count);
	void makeroot(const T element, BinaryTree<T>& left, BinaryTree<T>& right)    //创建新节点作为根节点
	{
		root = new binarytreeNode<T>(element, left.root, right.root);
	}
private:
	binarytreeNode<T>* root;            //指向根的指针
	int Size;
};

template<class T>
struct huffmanNode
{
	T weight;              //权值
	BinaryTree<T>* tree;   //以该节点为根的二叉树
	operator T() const { return weight; }
};

template<class T>
BinaryTree<T>* makehufTree(T* weight, int n)
{
	huffmanNode<T>* table = new huffmanNode<T>[n + 1];      //一组单节点树
	BinaryTree<int>emptyTree;                               //空树
	for (int i = 1; i <= n; i++)
	{               
		table[i].weight = weight[i];
		table[i].tree = new BinaryTree<int>;
		table[i].tree->makeroot(i, emptyTree, emptyTree);       //i为外部节点编号，方便后面取权
	}

	minHeap<huffmanNode<T>> heap;
	heap.initial(table, n);            //初始化为小根堆
	huffmanNode<T> w, x, y;
	BinaryTree<int>* z;
	for (int i = 1; i < n; i++) {
		x = heap.top();               //取出权最小的两棵树 
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
	return heap.top().tree;          //返回霍夫曼树
}

template<class T>
int BinaryTree<T>::hufLength(int* weight, int count)
{
	Size = 2 * count - 1;
	int sum_len = 0;
	Queue<binarytreeNode<T>*> q(Size);
	binarytreeNode<T>* curNode;
	q.push(root);
	root->element = 0;            //路长(编码长度)
	int temp;
	while (!q.empty())
	{
		curNode = q.front();
		q.pop();
		if (curNode->leftChild != NULL)
		{
			q.push(curNode->leftChild);
			temp = curNode->leftChild->element;                        //取出节点编号
			curNode->leftChild->element = curNode->element + 1;        //计算路长
			if (temp != 0) {                                           //不是内部节点时
				sum_len += weight[temp] * curNode->leftChild->element; //根据编号找到对应长度(总长度+=权*路长)
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
	int* arr = new int[26];         //记录频率
	for (int i = 0; i < 26; i++)
		arr[i] = 0;
	int count = 0;                  //不同字母数目
	int k = 0;
	while (input[k] != '\0')
	{
		arr[input[k] - 'a']++;      //统计字母出现频率
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