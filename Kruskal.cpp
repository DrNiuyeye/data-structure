#include<iostream>
using namespace std;

struct Edge
{
	int from;    //�ߵ����
	int to;      //�ߵ��յ�
	int weight;     //�ߵ�Ȩ��
};
class spanningTree
{
public:
	spanningTree(int n, int e) :Vnumber(n), Enumber(e) 
	{
		edges = new Edge[Enumber + 1];
	}
	~spanningTree() { delete[]edges; }
	void initial()  //�����
	{
		for (int i = 1; i <= Enumber; i++)
		{
			cin >> edges[i].from >> edges[i].to >> edges[i].weight;
		}
		
	}
	void Sort(int left, int right)//��������
	{
		int i, j;
		i = left;
		j = right;
		Edge index = edges[left];//�����׼�� 
		if (left > right)  //���ź� 
		{
			return;
		}
		else
		{
			while (i != j) //i��jδ����ǰ
			{
				while (i < j && edges[j].weight >= index.weight)  //�������ƶ�j
					j--;
				while (i < j && edges[i].weight <= index.weight)  //�������ƶ�i
					i++;
				if (i < j)  //����i��jָ��Ķ���
				{
					Edge temp = edges[i];
					edges[i] = edges[j];
					edges[j] = temp;
				}
			}
			//��׼ֵ��λ
			Edge temp2 = edges[i];
			edges[i] = edges[left];
			edges[left] = temp2;
		}
		Sort(left, i - 1);//������ߵ���
		Sort(i + 1, right);//�����ұߵ���
	}
	long kruskal();
private:
	Edge* edges;  //�߼�
	int Vnumber;  //������
	int Enumber;  //����
};

int* root;  //���鼯
int* tree_high;
int find(int x) {
	if (x == root[x])
		return x;
	return find(root[x]);  //root[x]�ڴ��x�ĸ��ڵ�
}

//�ϲ�Ԫ��x�� y�����ļ���
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