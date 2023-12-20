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

struct Edge
{
	int from;    //边的起点
	int to;      //边的终点
	int val;     //边的权重
};

struct Min_Edge
{
	int adjvertex;  //顶点
	int weight;     //权值
	Min_Edge() {}
	Min_Edge(int a, int w)
	{
		adjvertex = a;
		weight = w;
	}
	operator int() const { return weight; }
};

bool reach[200000];  //判断是否已到达过
vector<vector<Edge>> edges(200000);    //二维vector数组，邻接表

class spanningTree
{
public:
	spanningTree(int n, int e) :Vnumber(n), Enumber(e) {}
	long prime();
private:
	int Vnumber;  //顶点数
	int Enumber;  //边数
};

long spanningTree::prime()
{
	long min_result = 0;         //最小生成树权值和
	for (int i = 0; i <= Vnumber; i++)
		reach[i] = false;
	minHeap<Min_Edge> h(Enumber);
	reach[1] = true;           //选择第一个顶点
	for (int i = 0; i < edges[1].size(); i++)  //将与顶点1邻接的边加入最小堆
	{
		Min_Edge min(edges[1][i].to, edges[1][i].val);     //顶点1的每条邻接边
		h.push(min);                                       //放入最小堆排序
	}
	for (int i = 1; i < Vnumber; i++)
	{
		while (reach[h.top().adjvertex])  //该边已选
		{
			h.pop();
		}
		//找出堆内最短边
		int cur_vertex = h.top().adjvertex;
		reach[cur_vertex] = true;
		min_result += h.top().weight;    //将最短边加入生成树
		h.pop();
		for (int j = 0; j < edges[cur_vertex].size(); j++)   //将新加入顶点的所有邻边加入最小堆
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
		//输入边
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