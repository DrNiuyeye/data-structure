#include<iostream>
using namespace std;

struct node//节点
{
    long long weight;//权重
    int from, to;//两顶点
};
node edge[5000000];//边数组

//----------------边按权重快速排序过程start--------------------- 
void Sort(node* array, int low, int high)//排序
{
    if (low > high) return;//排好了，不运行了
    int i, j;
    node index;
    index = array[low];//定义基准数 
    i = low;
    j = high;
    while (i < j)
    {
        while (i < j && array[j].weight >= index.weight)
        {
            //从右往左找比基准数小的
            j--;
        }
        if (j > i)
        {
            //交换array[i]和array[j]，并把i右移一位 
            array[i++] = array[j];
        }
        while (i < j && array[i].weight < index.weight)
        {
            //从左往右找比基准数大的
            i++;
        }
        if (j > i)
        {
            //交换array[i]和array[j]，并把j左移一位
            array[j--] = array[i];
        }
    }
    array[i] = index;//基准点归位
    Sort(array, low, i - 1);//递归调用快排比基准点小的元素
    Sort(array, i + 1, high);//递归调用快排比基准点大的元素
}
//---------------边按权重快速排序过程finish---------------------

//--------------父顶点查找压缩，用于检验是否成环start------------- 
int pre[2000000];//记录所有节点的父节点
int find(int x)
{//查找父顶点
    int root = x;
    while (root != pre[root])//该顶点有父顶点
    {
        root = pre[root];//更新root为该点x的父顶点
    }//一直更新到最上方的顶点

    while (x != root)
    {//压缩路径，可以理解为将很高的树压缩成很矮的树，使子节点都指向最上方的顶点
        int temp = pre[x];
        pre[x] = root;
        x = temp;//用于让while停止
    }
    return root;
}
void join(int x, int y)
{//x是y的父顶点，让x的父顶点成为y的父顶点的父顶点，从而实现压缩 
    pre[find(y)] = find(x);
}
//-------------父顶点查找压缩，用于检验是否成环finish------------- 

int main()
{
    long result=0;
    int n, e, k = 0;//k用来记录已连接边的数量
    cin >> n >> e;//输入顶点数和边数 
    for (int i = 1; i <= e; i++)
    {
        cin >> edge[i].from >> edge[i].to >> edge[i].weight;
        int temp = 0;
        if (edge[i].from > edge[i].to)
        {//无向图按照顶点由小到大的顺序存储，如果不符合，则交换一下 
            temp = edge[i].from;
            edge[i].from = edge[i].to;
            edge[i].to = temp;
        }
    }
    for (int i = 1; i <= n; i++) pre[i] = i;//初始化
    Sort(edge, 1, e);//排序
    for (int i = 1; i <= e; i++)
    {//遍历所有的边
        if (k == n - 1) break;//终止条件，选择的边数是顶点数-1 
        if (find(edge[i].from) != find(edge[i].to))
        {//排除成环情况 
            join(edge[i].from, edge[i].to);//合并顶点
            result += edge[i].weight;//累加权值 
            k++;//已连接边数加1 
        }
    }
    cout << result << endl;
    return 0;
}
