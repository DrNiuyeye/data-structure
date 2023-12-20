#include<iostream>
using namespace std;
template<class K, class E>
struct pairnode {
	K Key;
	E Value;
	pairnode() : Key(), Value() {}//默认构造函数
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
		table = new pairnode<K, E>*[divisor]; //创建散列表数组
		for (int i = 0; i < divisor; i++)
			table[i] = NULL;
	}
	~hashTable()
	{
		delete[]table;
		table = NULL;
	}
	int search(const K& thekey); //搜索
	int find(const K& thekey); //查找
	void insert(const pairnode<K, E>& thepair);
	int erase(const K& thekey);
private:
	pairnode<K, E>** table; //散列表
	int Size; //数对个数
	int divisor; //散列函数除数
};
template<class K, class E>
int hashTable<K, E>::search(const K& thekey)
{
	int hash = thekey % divisor; //起始桶位置
	int index = hash;
	do
	{
		if (table[index] == NULL || table[index]->Key == thekey) //找到空桶或关键词为 key 的数对
			return index;
		index = (index + 1) % divisor; //进入下一个桶
	} while (index != hash);
	return index; //未找到，返回起始桶
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
	if (table[ind] == NULL) //空桶位置
	{
		table[ind] = new pairnode<K, E>(thepair.Key, thepair.Value);
		Size++;
		cout << ind << endl;
	}
	else if (table[ind]->Key == thepair.Key) //已存在关键字
		cout << "Existed" << endl;
}
template<class K, class E>
int hashTable<K, E>::erase(const K& thekey)
{
	int start = find(thekey);
	int move_num = 0; //移动元素个数
	if (start == -1)
		return -1;
	else
	{
		table[start] = NULL; //将删除的桶置为空
		int delete_pos = start;
		int index = (start + 1) % divisor;
		while (table[index] != NULL && index != start)
		{
			int cur_start = table[index]->Key % divisor; //下一个桶内数对的起始桶
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