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
    T& front() { return queue[theFront]; } //������Ԫ��
    void pop() //ɾ��Ԫ��
    {
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

struct lineNode       //�߽��
{
    int adjvertex;    //�߽����
    int weight;       //��Ȩֵ
    lineNode* next;   //ָ����һ���ߵ�ָ��
};

struct vertexNode      //�ڽӱ�����
{
    int data;          //������
    lineNode* firstline;//ָ���һ���ߵ�ָ��   
};

class graph
{
public:
    graph(int n = 0)
    {
        Vnumber = n;
        Enumber = 0;
        aList = new vertexNode[n + 1];
        for (int i = 0; i <= n; i++)   //�ڽӱ����ʼ��
        {
            aList[i].data = i;
            aList[i].firstline = NULL;
        }
    }
    ~graph() { delete[]aList; }
    void insert(int v1, int v2);  //�����v1v2
    void erase(int v1, int v2);   //ɾ����v1v2
    void BFS_order(int v);        //���bfs����
    int bfsorder_len(int v);
    void DFS_order(int v);        //���dfs����
    int dfsorder_len(int v);
    void dfs(int v);              //�����������
    int component();              //������ͨ����
    void min_component();         //���������ͨ��ͼ��С��ı��
    void min_path(int v1, int v2);  //����v1��v2�����·��

private:
    int Vnumber;  //������
    int Enumber;  //����
    vertexNode* aList;   //�ڽӱ�
};

//�����
void graph::insert(int v1, int v2)
{
    //����v1λ���������
    lineNode* newnode = new lineNode;
    newnode->adjvertex = v2;
    lineNode* cur = aList[v1].firstline;  //�ڽӱ���v1����ĵ�һ���߽��
    lineNode* pre = NULL;    //ָ��cur��ǰһ�����
    if (cur == NULL)   //v1û�б�
    {
        aList[v1].firstline = newnode;
        newnode->next = NULL;
    }
    else if (cur->adjvertex > v2)  //v2����v1��һ���ߵĶ���
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
    //����v2Ϊ���������
    lineNode* newnode2 = new lineNode;
    newnode2->adjvertex = v1;
    lineNode* cur2 = aList[v2].firstline;  //�ڽӱ���v2����ĵ�һ���߽��
    lineNode* pre2 = NULL;    //ָ��cur2��ǰһ�����
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
    Enumber++;       //ͼ�ı���+1

}
//ɾ����
void graph::erase(int v1, int v2)
{
    //ɾ����v1v2
    lineNode* cur = aList[v1].firstline;
    lineNode* pre = NULL;
    while (cur != NULL && cur->adjvertex != v2)
    {
        pre = cur;
        cur = cur->next;
    }
    if (cur == NULL)  //û�ҵ��ñ�
    {
        return;
    }
    if (pre != NULL) //ɾ���Ĳ��ǵ�һ����   
    {
        pre->next = cur->next;
    }
    else  //ɾ�����ǵ�һ����
    {
        aList[v1].firstline = cur->next;
    }
    delete cur;

    //ɾ����v2v1
    lineNode* cur2 = aList[v2].firstline;
    lineNode* pre2 = NULL;
    while (cur2 != NULL && cur2->adjvertex != v1)
    {
        pre2 = cur2;
        cur2 = cur2->next;
    }
    if (cur2 == NULL)  //û�ҵ��ñ�
    {
        return;
    }
    if (pre2 != NULL) //ɾ���Ĳ��ǵ�һ����   
    {
        pre2->next = cur2->next;
    }
    else  //ɾ�����ǵ�һ����
    {
        aList[v2].firstline = cur2->next;
    }
    delete cur2;
    Enumber--;      //ͼ�ı���-1
}

bool reach[100000];//������
//���bfs����
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
            if (reach[p->adjvertex])  //�ڽӶ���δ�����
            {
                q.push(p->adjvertex);
                reach[p->adjvertex] = false;  //���Ϊ����
            }
            p = p->next;
        }
    }
    cout << endl;
}
//���dfs����
void graph::DFS_order(int v)
{
    cout << aList[v].data << " ";
    reach[v] = false;  //���Ϊ�ѵ���
    lineNode* p = aList[v].firstline;
    while (p != NULL)
    {
        if (reach[p->adjvertex])  //���ڶ���δ�����
        {
            DFS_order(p->adjvertex);
        }
        p = p->next;
    }
}
//�����������
void graph::dfs(int v)
{
    reach[v] = false;  //���Ϊ�ѵ���
    lineNode* p = aList[v].firstline;
    while (p != NULL)
    {
        if (reach[p->adjvertex])  //���ڶ���δ�����
        {
            dfs(p->adjvertex);
        }
        p = p->next;
    }
}
//������ͨ����
int graph::component()
{
    for (int i = 0; i <= Vnumber; i++)
        reach[i] = true;
    int num = 0;
    for (int i = 1; i <= Vnumber; i++)
    {
        if (reach[i])
        {
            dfs(i);   //���ض���i�ܵ�������ж���
            num++;
        }
    }
    return num;
}
//�����ͨ��ͼ��С��ı��
void graph::min_component()
{
    for (int i = 0; i <= Vnumber; i++)
        reach[i] = true;
    for (int i = 1; i <= Vnumber; i++)
    {
        if (reach[i])
        {
            cout << i << " ";
            dfs(i);   //���ض���i�ܵ�������ж���
        }
    }
    cout << endl;
}

int graph::dfsorder_len(int v)
{
    int len = 1;
    reach[v] = false;  //���Ϊ�ѵ���
    lineNode* p = aList[v].firstline;
    while (p != NULL)
    {
        if (reach[p->adjvertex])  //���ڶ���δ�����
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
            if (reach[p->adjvertex])  //�ڽӶ���δ�����
            {
                q.push(p->adjvertex);
                reach[p->adjvertex] = false;  //���Ϊ����
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
    for (int i = 0; i <= Vnumber; i++)  //��¼��㵽�ö����·������
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
            if (reach[p->adjvertex])  //�ڽӶ���δ�����
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
    cout << g.component() << endl;  //��ͨ������
    g.min_component();  //��ͨ��ͼ��С���
    for (int i = 0; i <= n; i++)
        reach[i] = true;
    cout << g.dfsorder_len(s) << endl;  //dfs���г���
    for (int i = 0; i <= n; i++)
        reach[i] = true;
    g.DFS_order(s);  //dfs����
    cout << endl;
    for (int i = 0; i <= n; i++)
        reach[i] = true;
    cout << g.bfsorder_len(t) << endl;  //bfs���г���
    for (int i = 0; i <= n; i++)
        reach[i] = true;
    g.BFS_order(t);  //bfs����
    for (int i = 0; i <= n; i++)
        reach[i] = true;
    g.min_path(s, t);
    return 0;
}