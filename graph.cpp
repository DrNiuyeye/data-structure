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
    inline bool empty() { return theFront == theBack; }
    T& front() { return queue[theFront]; } //返回首元素
    void pop() //删除元素
    {
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

struct lineNode       //边结点
{
    int adjvertex;    //边结点编号
    int weight;       //边权值
    lineNode* next;   //指向下一条边的指针
};

struct vertexNode      //邻接表顶点结点
{
    int data;          //顶点编号
    lineNode* firstline;//指向第一条边的指针   
};

class graph
{
public:
    graph(int n = 0)
    {
        Vnumber = n;
        Enumber = 0;
        aList = new vertexNode[n + 1];
        for (int i = 0; i <= n; i++)   //邻接表顶点初始化
        {
            aList[i].data = i;
            aList[i].firstline = NULL;
        }
    }
    ~graph() { delete[]aList; }
    void insert(int v1, int v2);  //插入边v1v2
    void erase(int v1, int v2);   //删除边v1v2
    void BFS_order(int v);        //输出bfs序列
    int bfsorder_len(int v);
    void DFS_order(int v);        //输出dfs序列
    int dfsorder_len(int v);
    void dfs(int v);              //深度优先搜素
    int component();              //计算连通分量
    void min_component();         //升序输出连通子图最小点的编号
    void min_path(int v1, int v2);  //计算v1到v2的最短路径

private:
    int Vnumber;  //顶点数
    int Enumber;  //边数
    vertexNode* aList;   //邻接表
};

//插入边
void graph::insert(int v1, int v2)
{
    //更新v1位顶点的链表
    lineNode* newnode = new lineNode;
    newnode->adjvertex = v2;
    lineNode* cur = aList[v1].firstline;  //邻接表内v1顶点的第一个边结点
    lineNode* pre = NULL;    //指向cur的前一个结点
    if (cur == NULL)   //v1没有边
    {
        aList[v1].firstline = newnode;
        newnode->next = NULL;
    }
    else if (cur->adjvertex > v2)  //v2大于v1第一条边的顶点
    {
        newnode->next = aList[v1].firstline;
        aList[v1].firstline = newnode;
    }
    else
    {
        while (cur != NULL && cur->adjvertex < v2)
        {
            pre = cur;
            cur = cur->next;
        }
        if (cur == NULL)
        {
            pre->next = newnode;
            newnode->next = NULL;
        }
        else
        {
            newnode->next = pre->next;
            pre->next = newnode;
        }
    }
    //更新v2为顶点的链表
    lineNode* newnode2 = new lineNode;
    newnode2->adjvertex = v1;
    lineNode* cur2 = aList[v2].firstline;  //邻接表内v2顶点的第一个边结点
    lineNode* pre2 = NULL;    //指向cur2的前一个结点
    if (cur2 == NULL)   
    {
        aList[v2].firstline = newnode2;
        newnode2->next = NULL;
    }
    else if (cur2->adjvertex > v1) 
    {
        newnode2->next = aList[v2].firstline;
        aList[v2].firstline = newnode2;
    }
    else
    {
        while (cur2 != NULL && cur2->adjvertex < v1)
        {
            pre2 = cur2;
            cur2 = cur2->next;
        }
        if (cur2 == NULL)
        {
            pre2->next = newnode2;
            newnode2->next = NULL;
        }
        else
        {
            newnode2->next = pre2->next;
            pre2->next = newnode2;
        }
    }
    Enumber++;       //图的边数+1

}
//删除边
void graph::erase(int v1, int v2)
{
    //删除边v1v2
    lineNode* cur = aList[v1].firstline;
    lineNode* pre = NULL;
    while (cur != NULL && cur->adjvertex != v2)
    {
        pre = cur;
        cur = cur->next;
    }
    if (cur == NULL)  //没找到该边
    {
        return;
    }
    if (pre != NULL) //删除的不是第一条边   
    {
        pre->next = cur->next;
    }
    else  //删除的是第一条边
    {
        aList[v1].firstline = cur->next;
    }
    delete cur;

    //删除边v2v1
    lineNode* cur2 = aList[v2].firstline;
    lineNode* pre2 = NULL;
    while (cur2 != NULL && cur2->adjvertex != v1)
    {
        pre2 = cur2;
        cur2 = cur2->next;
    }
    if (cur2 == NULL)  //没找到该边
    {
        return;
    }
    if (pre2 != NULL) //删除的不是第一条边   
    {
        pre2->next = cur2->next;
    }
    else  //删除的是第一条边
    {
        aList[v2].firstline = cur2->next;
    }
    delete cur2;
    Enumber--;      //图的边数-1
}

bool reach[100000];//到达标记
//输出bfs序列
void graph::BFS_order(int v)
{
    Queue<int> q(Vnumber);
    q.push(v);
    reach[v] = false;
    while (!q.empty())
    {
        cout << aList[q.front()].data << " ";
        int w = q.front();
        q.pop();
        lineNode* p = aList[w].firstline;
        while (p != NULL)
        {
            if (reach[p->adjvertex])  //邻接顶点未到达过
            {
                q.push(p->adjvertex);
                reach[p->adjvertex] = false;  //标记为到达
            }
            p = p->next;
        }
    }
    cout << endl;
}
//输出dfs序列
void graph::DFS_order(int v)
{
    cout << aList[v].data << " ";
    reach[v] = false;  //标记为已到达
    lineNode* p = aList[v].firstline;
    while (p != NULL)
    {
        if (reach[p->adjvertex])  //相邻顶点未到达过
        {
            DFS_order(p->adjvertex);
        }
        p = p->next;
    }
}
//深度优先搜素
void graph::dfs(int v)
{
    reach[v] = false;  //标记为已到达
    lineNode* p = aList[v].firstline;
    while (p != NULL)
    {
        if (reach[p->adjvertex])  //相邻顶点未到达过
        {
            dfs(p->adjvertex);
        }
        p = p->next;
    }
}
//计算连通分量
int graph::component()
{
    for (int i = 0; i <= Vnumber; i++)
        reach[i] = true;
    int num = 0;
    for (int i = 1; i <= Vnumber; i++)
    {
        if (reach[i])
        {
            dfs(i);   //搜素顶点i能到达的所有顶点
            num++;
        }
    }
    return num;
}
//输出连通子图最小点的编号
void graph::min_component()
{
    for (int i = 0; i <= Vnumber; i++)
        reach[i] = true;
    for (int i = 1; i <= Vnumber; i++)
    {
        if (reach[i])
        {
            cout << i << " ";
            dfs(i);   //搜素顶点i能到达的所有顶点
        }
    }
    cout << endl;
}

int graph::dfsorder_len(int v)
{
    int len = 1;
    reach[v] = false;  //标记为已到达
    lineNode* p = aList[v].firstline;
    while (p != NULL)
    {
        if (reach[p->adjvertex])  //相邻顶点未到达过
        {
            len += dfsorder_len(p->adjvertex);
        }
        p = p->next;
    }
    return len;
}

int graph::bfsorder_len(int v)
{
    int len = 0;
    Queue<int> q(Vnumber);
    q.push(v);
    reach[v] = false;
    while (!q.empty())
    {
        len++;
        int w = q.front();
        q.pop();
        lineNode* p = aList[w].firstline;
        while (p != NULL)
        {
            if (reach[p->adjvertex])  //邻接顶点未到达过
            {
                q.push(p->adjvertex);
                reach[p->adjvertex] = false;  //标记为到达
            }
            p = p->next;
        }
    }
    return len; 
}

void graph::min_path(int v1, int v2)
{
    Queue<int> q(Vnumber);
    int* path=new int[Vnumber+1];
    for (int i = 0; i <= Vnumber; i++)  //记录起点到该顶点的路径长度
        path[i] = 0;
    q.push(v1);
    reach[v1] = false;
    while (!q.empty())
    {
        int w = q.front();
        q.pop();
        lineNode* p = aList[w].firstline;
        while (p != NULL)
        {
            if (reach[p->adjvertex])  //邻接顶点未到达过
            {
                if (p->adjvertex == v2)
                {
                    cout << path[w] + 1 << endl;
                    return;
                }
                path[p->adjvertex] = path[w] + 1;
                q.push(p->adjvertex);
                reach[p->adjvertex] = false;
            }
            p = p->next;
        }
    }
    delete[]path;
    cout << -1 << endl;
}

int main()
{
    int n, m, s, t, opt;
    int v1, v2;
    cin >> n >> m >> s >> t;
    graph g(n);
    for (int i = 0; i < m; i++)
    {
        cin >> opt;
        if (opt == 0)
        {
            cin >> v1 >> v2;
            g.insert(v1, v2);
        }
        else if (opt == 1)
        {
            cin >> v1 >> v2;
            g.erase(v1, v2);
        }
    }
    cout << g.component() << endl;  //连通分量数
    g.min_component();  //连通子图最小编号
    for (int i = 0; i <= n; i++)
        reach[i] = true;
    cout << g.dfsorder_len(s) << endl;  //dfs序列长度
    for (int i = 0; i <= n; i++)
        reach[i] = true;
    g.DFS_order(s);  //dfs序列
    cout << endl;
    for (int i = 0; i <= n; i++)
        reach[i] = true;
    cout << g.bfsorder_len(t) << endl;  //bfs序列长度
    for (int i = 0; i <= n; i++)
        reach[i] = true;
    g.BFS_order(t);  //bfs序列
    for (int i = 0; i <= n; i++)
        reach[i] = true;
    g.min_path(s, t);
    return 0;
}