#include<iostream>
using namespace std;
template<class K, class E>
struct pairnode {
	K Key;
	E Value;
	pairnode() : Key(), Value() {}//Ĭ�Ϲ��캯��
	pairnode(const K& key, const E& val) : Key(key), Value(val) {}
};
template <class K, class E>
struct chainNode //����ڵ㶨��
{
	pairnode<K, E> element; //������
	chainNode<K, E>* next; //ָ����
	//�ڵ㹹�캯��
	chainNode(pairnode<K, E>& thepair) :element(thepair) {}
	chainNode(pairnode<K, E>& thepair, chainNode<K, E>* thenext) :element(thepair) { next = thenext; }
};
template<class K, class E>
class sortedChain //������
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
	chainNode<K, E>* firstNode;//ָ�������һ���ڵ��ָ��
	int Size; //�����ڽڵ���
};
template<class K, class E>
pairnode<K, E>* sortedChain<K, E>::find(const K& thekey)
{
	chainNode<K, E>* curNode = firstNode;
	while (curNode != NULL && curNode->element.Key != thekey) //Ѱ�������ڹؼ��ַ��ϵ�����
	{
		curNode = curNode->next;
	}
	if (curNode != NULL && curNode->element.Key == thekey)
		return &curNode->element; //����ָ�����Ե�ָ��
	else
		return NULL;
}
template<class K, class E>
int sortedChain<K, E>::insert(pairnode<K, E>& thepair)
{
	chainNode<K, E>* curNode = firstNode, * preNode = NULL;
	while (curNode != NULL && curNode->element.Key < thepair.Key) //Ѱ�Ҳ���λ��
	{
		preNode = curNode;
		curNode = curNode->next;
	}
	if (curNode != NULL && curNode->element.Key == thepair.Key) //�Ѵ��ڹؼ���
	{
		cout << "Existed" << endl;
		return -1;
	}
	chainNode<K, E>* newNode = new chainNode<K, E>(thepair, curNode); //�����½ڵ㣬ͬʱ���һ�ڵ���
	��
		if (preNode == NULL) //ͷ�ڵ����
			firstNode = newNode;
		else
			preNode->next = newNode; //��ǰһ�ڵ�����
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
	if (curNode != NULL && curNode->element.Key == thekey) //�ҵ�Ҫɾ��������
	{
		if (preNode == NULL) //ɾ��ͷ�ڵ�
			firstNode = curNode->next;
		else
			preNode->next = curNode->next;
		delete curNode; //�ͷŽڵ��ڴ�
		Size--;
		cout << Size << endl;
	}
	else //δ�ҵ�
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
	void find(const K& thekey) //����
	{
		int index = thekey % divisor; //��ʼͰ
		pairnode<K, E>* temp = table[index].find(thekey);
		if (temp != NULL)
			cout << table[index].Length() << endl;
		else
			cout << "Not Found" << endl;
	}
	void insert(pairnode<K, E>& thepair) //����
	{
		int index = thepair.Key % divisor;
		int flag = table[index].insert(thepair);
		if (flag == 0) //����ɹ�
			Size++;
	}
	void erase(const K& thekey) //ɾ��
	{
		int index = thekey % divisor;
		table[index].erase(thekey);
	}
private:
	sortedChain<K, E>* table; //ɢ�б�����
	int divisor; //����
	int Size; //ɢ�б����Ը���
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