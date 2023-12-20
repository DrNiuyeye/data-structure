#include<iostream>
#include<vector>
using namespace std;

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

struct Edge
{
	int from;    //�ߵ����
	int to;      //�ߵ��յ�
	int val;     //�ߵ�Ȩ��
};

struct Min_Edge
{
	int adjvertex;  //����
	int weight;     //Ȩֵ
	Min_Edge() {}
	Min_Edge(int a, int w)
	{
		adjvertex = a;
		weight = w;
	}
	operator int() const { return weight; }
};

bool reach[200000];  //�ж��Ƿ��ѵ����
vector<vector<Edge>> edges(200000);    //��άvector���飬�ڽӱ�

class spanningTree
{
public:
	spanningTree(int n, int e) :Vnumber(n), Enumber(e) {}
	long prime();
private:
	int Vnumber;  //������
	int Enumber;  //����
};

long spanningTree::prime()
{
	long min_result = 0;         //��С������Ȩֵ��
	for (int i = 0; i <= Vnumber; i++)
		reach[i] = false;
	minHeap<Min_Edge> h(Enumber);
	reach[1] = true;           //ѡ���һ������
	for (int i = 0; i < edges[1].size(); i++)  //���붥��1�ڽӵı߼�����С��
	{
		Min_Edge min(edges[1][i].to, edges[1][i].val);     //����1��ÿ���ڽӱ�
		h.push(min);                                       //������С������
	}
	for (int i = 1; i < Vnumber; i++)
	{
		while (reach[h.top().adjvertex])  //�ñ���ѡ
		{
			h.pop();
		}
		//�ҳ�������̱�
		int cur_vertex = h.top().adjvertex;
		reach[cur_vertex] = true;
		min_result += h.top().weight;    //����̱߼���������
		h.pop();
		for (int j = 0; j < edges[cur_vertex].size(); j++)   //���¼��붥��������ڱ߼�����С��
		{ 
			if (!reach[edges[cur_vertex][j].to])
			{
				Min_Edge min(edges[cur_vertex][j].to, edges[cur_vertex][j].val);
				h.push(min);
			}
		}
	}
	return min_result;
}

int main()
{
	int n, e;
	cin >> n >> e;
	spanningTree tree(n, e);
	if (n == 1)
	{
		cout << 0 << endl;
	}
	else
	{
		//�����
		for (int i = 1; i <= e; i++)
		{
			Edge e1, e2;
			cin >> e1.from >> e1.to >> e1.val;
			e2.from = e1.to;
			e2.to = e1.from;
			e2.val = e1.val;
			edges[e1.from].push_back(e1);	
			edges[e2.from].push_back(e2);
		}
		cout << tree.prime() << endl;
	}
	return 0;
}