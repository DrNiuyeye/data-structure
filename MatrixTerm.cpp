#include<iostream>
using namespace std;

struct node//�ڵ�
{
    long long weight;//Ȩ��
    int from, to;//������
};
node edge[5000000];//������

//----------------�߰�Ȩ�ؿ����������start--------------------- 
void Sort(node* array, int low, int high)//����
{
    if (low > high) return;//�ź��ˣ���������
    int i, j;
    node index;
    index = array[low];//�����׼�� 
    i = low;
    j = high;
    while (i < j)
    {
        while (i < j && array[j].weight >= index.weight)
        {
            //���������ұȻ�׼��С��
            j--;
        }
        if (j > i)
        {
            //����array[i]��array[j]������i����һλ 
            array[i++] = array[j];
        }
        while (i < j && array[i].weight < index.weight)
        {
            //���������ұȻ�׼�����
            i++;
        }
        if (j > i)
        {
            //����array[i]��array[j]������j����һλ
            array[j--] = array[i];
        }
    }
    array[i] = index;//��׼���λ
    Sort(array, low, i - 1);//�ݹ���ÿ��űȻ�׼��С��Ԫ��
    Sort(array, i + 1, high);//�ݹ���ÿ��űȻ�׼����Ԫ��
}
//---------------�߰�Ȩ�ؿ����������finish---------------------

//--------------���������ѹ�������ڼ����Ƿ�ɻ�start------------- 
int pre[2000000];//��¼���нڵ�ĸ��ڵ�
int find(int x)
{//���Ҹ�����
    int root = x;
    while (root != pre[root])//�ö����и�����
    {
        root = pre[root];//����rootΪ�õ�x�ĸ�����
    }//һֱ���µ����Ϸ��Ķ���

    while (x != root)
    {//ѹ��·�����������Ϊ���ܸߵ���ѹ���ɺܰ�������ʹ�ӽڵ㶼ָ�����Ϸ��Ķ���
        int temp = pre[x];
        pre[x] = root;
        x = temp;//������whileֹͣ
    }
    return root;
}
void join(int x, int y)
{//x��y�ĸ����㣬��x�ĸ������Ϊy�ĸ�����ĸ����㣬�Ӷ�ʵ��ѹ�� 
    pre[find(y)] = find(x);
}
//-------------���������ѹ�������ڼ����Ƿ�ɻ�finish------------- 

int main()
{
    long result=0;
    int n, e, k = 0;//k������¼�����ӱߵ�����
    cin >> n >> e;//���붥�����ͱ��� 
    for (int i = 1; i <= e; i++)
    {
        cin >> edge[i].from >> edge[i].to >> edge[i].weight;
        int temp = 0;
        if (edge[i].from > edge[i].to)
        {//����ͼ���ն�����С�����˳��洢����������ϣ��򽻻�һ�� 
            temp = edge[i].from;
            edge[i].from = edge[i].to;
            edge[i].to = temp;
        }
    }
    for (int i = 1; i <= n; i++) pre[i] = i;//��ʼ��
    Sort(edge, 1, e);//����
    for (int i = 1; i <= e; i++)
    {//�������еı�
        if (k == n - 1) break;//��ֹ������ѡ��ı����Ƕ�����-1 
        if (find(edge[i].from) != find(edge[i].to))
        {//�ų��ɻ���� 
            join(edge[i].from, edge[i].to);//�ϲ�����
            result += edge[i].weight;//�ۼ�Ȩֵ 
            k++;//�����ӱ�����1 
        }
    }
    cout << result << endl;
    return 0;
}
