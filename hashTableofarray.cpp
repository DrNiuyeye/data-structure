#include<iostream>
using namespace std;
template<class K, class E>
struct pairnode {
	K Key;
	E Value;
	pairnode() : Key(), Value() {}//Ĭ�Ϲ��캯��
	pairnode(const K& key, const E& val) : Key(key), Value(val) {}
};
template<class K, class E>
class hashTable
{
public:
	hashTable(int dis)
	{
		divisor = dis;
		Size = 0;
		table = new pairnode<K, E>*[divisor]; //����ɢ�б�����
		for (int i = 0; i < divisor; i++)
			table[i] = NULL;
	}
	~hashTable()
	{
		delete[]table;
		table = NULL;
	}
	int search(const K& thekey); //����
	int find(const K& thekey); //����
	void insert(const pairnode<K, E>& thepair);
	int erase(const K& thekey);
private:
	pairnode<K, E>** table; //ɢ�б�
	int Size; //���Ը���
	int divisor; //ɢ�к�������
};
template<class K, class E>
int hashTable<K, E>::search(const K& thekey)
{
	int hash = thekey % divisor; //��ʼͰλ��
	int index = hash;
	do
	{
		if (table[index] == NULL || table[index]->Key == thekey) //�ҵ���Ͱ��ؼ���Ϊ key ������
			return index;
		index = (index + 1) % divisor; //������һ��Ͱ
	} while (index != hash);
	return index; //δ�ҵ���������ʼͰ
}
template<class K, class E>
int hashTable<K, E>::find(const K& thekey)
{
	int i = search(thekey);
	if (table[i] == NULL || table[i]->Key != thekey)
		return -1;
	return i;
}
template<class K, class E>
void hashTable<K, E>::insert(const pairnode<K, E>& thepair)
{
	int ind = search(thepair.Key);
	if (table[ind] == NULL) //��Ͱλ��
	{
		table[ind] = new pairnode<K, E>(thepair.Key, thepair.Value);
		Size++;
		cout << ind << endl;
	}
	else if (table[ind]->Key == thepair.Key) //�Ѵ��ڹؼ���
		cout << "Existed" << endl;
}
template<class K, class E>
int hashTable<K, E>::erase(const K& thekey)
{
	int start = find(thekey);
	int move_num = 0; //�ƶ�Ԫ�ظ���
	if (start == -1)
		return -1;
	else
	{
		table[start] = NULL; //��ɾ����Ͱ��Ϊ��
		int delete_pos = start;
		int index = (start + 1) % divisor;
		while (table[index] != NULL && index != start)
		{
			int cur_start = table[index]->Key % divisor; //��һ��Ͱ�����Ե���ʼͰ
			if (cur_start != index && ((cur_start <= delete_pos && index > delete_pos) || ((cur_start >
				index) && (delete_pos < index || delete_pos >= cur_start))))
			{
				table[delete_pos] = table[index];
				table[index] = NULL;
				delete_pos = index;
				move_num++;
			}
			index = (index + 1) % divisor;
		}
		return move_num;
	}
}
int main() {
	int D, m, opt, x;
	cin >> D >> m;
	pairnode<int, int> node;
	hashTable<int, int> ht(D);
	for (int i = 0; i < m; i++)
	{
		cin >> opt >> x;
		switch (opt)
		{
		case 0:
			node.Key = x;
			node.Value = x;
			ht.insert(node);
			break;
		case 1:
			cout << ht.find(x) << endl;
			break;
		case 2:
			int flag = ht.erase(x);
			if (flag == -1)
				cout << "Not Found" << endl;
			else
				cout << flag << endl;
			break;
		}
	}
	return 0;
}