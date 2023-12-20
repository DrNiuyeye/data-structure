#include<iostream>
using namespace std;

template<class T>
class minHeap
{
public:
	minHeap(int Leng)
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
void doubleLength(T*& array, int oldlen, int newlen)     //扩大数组长度
{
	T* temp = new T[newlen];
	for (int i = 0; i < oldlen; i++)
		temp[i] = array[i];
	delete[] array;
	array = temp;
}

template<class T>
void minHeap<T>::push(const T& theelement)
{
	//数组长度不够时扩容
	if (Size == Length - 1)
	{
		doubleLength(heap, Length, Length * 2);
		Length *= 2;
	}
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
	heap = theheap;
	Size = size;
	for (int i = Size / 2; i >= 1; i--)          //从最后一个有孩子的节点开始检查
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

int main()
{
	int m, n, opt;
	cin >> n;
	minHeap<int> Heap(n);
	for (int i = 0; i < n; i++)
	{
		int element;
		cin >> element;
		Heap.push(element);
	}
	cout << Heap.top() << endl;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> opt;
		switch (opt)
		{
		case 1:
			int element;
			cin >> element;
			Heap.push(element);
			cout << Heap.top() << endl;
			break;
		case 2:
			Heap.pop();
			cout << Heap.top() << endl;
			break;
		case 3:
			int num, val;
			cin >> num;
			minHeap<int> h(num);
			for (int i = 0; i < num; i++)
			{
				cin >> val;
				h.push(val);
			}
			for (int i = 0; i < num; i++)
			{
				cout << h.top() << " ";
				h.pop();
			}
			break;
		}
	}
	return 0;
}





