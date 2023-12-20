#include<iostream>
using namespace std;

struct Edge
{
	int from;    //边的起点
	int to;      //边的终点
	int weight;     //边的权重
};
class spanningTree
{
public:
	spanningTree(int n, int e) :Vnumber(n), Enumber(e) 
	{
		edges = new Edge[Enumber + 1];
	}
	~spanningTree() { delete[]edges; }
	void initial()  //输入边
	{
		for (int i = 1; i <= Enumber; i++)
		{
			cin >> edges[i].from >> edges[i].to >> edges[i].weight;
		}
		
	}
	void Sort(int left, int right)//快速排序
	{
		int i, j;
		i = left;
		j = right;
		Edge index = edges[left];//定义基准数 
		if (left > right)  //已排好 
		{
			return;
		}
		else
		{
			while (i != j) //i与j未相遇前
			{
				while (i < j && edges[j].weight >= index.weight)  //先向左移动j
					j--;
				while (i < j && edges[i].weight <= index.weight)  //再向右移动i
					i++;
				if (i < j)  //交换i和j指向的对象
				{
					Edge temp = edges[i];
					edges[i] = edges[j];
					edges[j] = temp;
				}
			}
			//基准值归位
			Edge temp2 = edges[i];
			edges[i] = edges[left];
			edges[left] = temp2;
		}
		Sort(left, i - 1);//快排左边的数
		Sort(i + 1, right);//跨拍右边的数
	}
	long kruskal();
private:
	Edge* edges;  //边集
	int Vnumber;  //顶点数
	int Enumber;  //边数
};

int* root;  //并查集
int* tree_high;
int find(int x) {
	if (x == root[x])
		return x;
	return find(root[x]);  //root[x]内存放x的父节点
}

//合并元素x， y所处的集合
void Unite(int x, int y) 
{
	int root_x = find(x);
	int root_y = find(y);
	if (tree_high[root_x] <= tree_high[root_y])
	{
		root[root_x] = root_y;
	}
	else
	{
		root[root_y] = root_x;
	}
	if (tree_high[root_x] == tree_high[root_y] && root_x != root_y)
		tree_high[root_y]++;
}

long spanningTree::kruskal()
{
	long min_result = 0;
	int k = 0;
	for (int i = 1; i <= Enumber; i++)
	{
		if (find(edges[i].from) != find(edges[i].to))
		{
			Unite(edges[i].from, edges[i].to);
			min_result += edges[i].weight;
			k++;
		}
		if (k == Vnumber - 1)
			break;
	}
	return min_result;
}

int main()
{
	int n, e;
	cin >> n >> e;
	spanningTree tree(n, e);
	root = new int[n + 1];
	tree_high = new int[n + 1];
	for (int i = 1; i <= n; i++)
	{
		root[i] = i;
		tree_high[i] = 1;
	}
	tree.initial();
	tree.Sort(1, e);
	cout << tree.kruskal() << endl;
	delete[] root;
	delete[]tree_high;
	return 0;

}