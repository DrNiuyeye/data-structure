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
	T* heap;     //����
	int Length;  //���鳤��
	int Size;    //����Ԫ�ظ���

};

template<class T>
void doubleLength(T*& array, int oldlen, int newlen)     //�������鳤��
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
	//���鳤�Ȳ���ʱ����
	if (Size == Length - 1)
	{
		doubleLength(heap, Length, Length * 2);
		Length *= 2;
	}
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
	heap = theheap;
	Size = size;
	for (int i = Size / 2; i >= 1; i--)          //�����һ���к��ӵĽڵ㿪ʼ���
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





