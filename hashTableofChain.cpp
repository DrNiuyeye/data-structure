#include<iostream>
using namespace std;
template<class K, class E>
struct pairnode {
	K Key;
	E Value;
	pairnode() : Key(), Value() {}//默认构造函数
	pairnode(const K& key, const E& val) : Key(key), Value(val) {}
};
template <class K, class E>
struct chainNode //链表节点定义
{
	pairnode<K, E> element; //数据域
	chainNode<K, E>* next; //指针域
	//节点构造函数
	chainNode(pairnode<K, E>& thepair) :element(thepair) {}
	chainNode(pairnode<K, E>& thepair, chainNode<K, E>* thenext) :element(thepair) { next = thenext; }
};
template<class K, class E>
class sortedChain //链表类
{
public:
	sortedChain()
	{
		firstNode = NULL;
		Size = 0;
	}
	~sortedChain()
	{
		while (firstNode != NULL)
		{
			chainNode<K, E>* next = firstNode->next;
			delete firstNode;
			firstNode = next;
		}
	}
	pairnode<K, E>* find(const K& thekey);
	int Length() { return Size; }
	int insert(pairnode<K, E>& thepair);
	void erase(const K& thekey);
protected:
	chainNode<K, E>* firstNode;//指向链表第一个节点的指针
	int Size; //链表内节点数
};
template<class K, class E>
pairnode<K, E>* sortedChain<K, E>::find(const K& thekey)
{
	chainNode<K, E>* curNode = firstNode;
	while (curNode != NULL && curNode->element.Key != thekey) //寻找链表内关键字符合的数对
	{
		curNode = curNode->next;
	}
	if (curNode != NULL && curNode->element.Key == thekey)
		return &curNode->element; //返回指向数对的指针
	else
		return NULL;
}
template<class K, class E>
int sortedChain<K, E>::insert(pairnode<K, E>& thepair)
{
	chainNode<K, E>* curNode = firstNode, * preNode = NULL;
	while (curNode != NULL && curNode->element.Key < thepair.Key) //寻找插入位置
	{
		preNode = curNode;
		curNode = curNode->next;
	}
	if (curNode != NULL && curNode->element.Key == thepair.Key) //已存在关键字
	{
		cout << "Existed" << endl;
		return -1;
	}
	chainNode<K, E>* newNode = new chainNode<K, E>(thepair, curNode); //创建新节点，同时与后一节点连
	接
		if (preNode == NULL) //头节点插入
			firstNode = newNode;
		else
			preNode->next = newNode; //与前一节点连接
	Size++;
	return 0;
}
template<class K, class E>
void sortedChain<K, E>::erase(const K& thekey)
{
	chainNode<K, E>* curNode = firstNode, * preNode = NULL;
	while (curNode != NULL && curNode->element.Key < thekey)
	{
		preNode = curNode;
		curNode = curNode->next;
	}
	if (curNode != NULL && curNode->element.Key == thekey) //找到要删除的数对
	{
		if (preNode == NULL) //删除头节点
			firstNode = curNode->next;
		else
			preNode->next = curNode->next;
		delete curNode; //释放节点内存
		Size--;
		cout << Size << endl;
	}
	else //未找到
		cout << "Delete Failed" << endl;
}
template<class K, class E>
class hashChains
{
public:
	hashChains(int dis)
	{
		divisor = dis;
		Size = 0;
		table = new sortedChain<K, E>[divisor];
	}
	~hashChains() { delete[] table; }
	void find(const K& thekey) //查找
	{
		int index = thekey % divisor; //起始桶
		pairnode<K, E>* temp = table[index].find(thekey);
		if (temp != NULL)
			cout << table[index].Length() << endl;
		else
			cout << "Not Found" << endl;
	}
	void insert(pairnode<K, E>& thepair) //插入
	{
		int index = thepair.Key % divisor;
		int flag = table[index].insert(thepair);
		if (flag == 0) //插入成功
			Size++;
	}
	void erase(const K& thekey) //删除
	{
		int index = thekey % divisor;
		table[index].erase(thekey);
	}
private:
	sortedChain<K, E>* table; //散列表数组
	int divisor; //除数
	int Size; //散列表数对个数
};
int main()
{
	int D, m, opt, x;
	cin >> D >> m;
	hashChains<int, int> hc(D);
	pairnode<int, int> p;
	for (int i = 0; i < m; i++)
	{
		cin >> opt >> x;
		switch (opt)
		{
		case 0:
			p.Key = x;
			p.Value = x;
			hc.insert(p);
			break;
		case 1:
			hc.find(x);
			break;
		case 2:
			hc.erase(x);
			break;
		}
	}
	return 0;
}