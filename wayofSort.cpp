#include <iostream>
using namespace std;
template<class T>
class Sort {
private:
	T* data;
	int num;

public:
	Sort(int n) {  //构造函数
		num = n;
		data = new T[num];
	}
	~Sort() {
		delete[]data;
	}
	void Setarray() {
		for (int i = 0; i < num; i++) {
			cin >> data[i];
		}
	}
	void swap(T& a, T& b);
	void Show() {
		for (int i = 0; i < num; i++) {
			cout << data[i] << " ";
		}
	}
	void bubbleSort();
	void insertSort();
	void selectSort();
	void rankSort();
};

template<class T>
void Sort<T>::swap(T& a, T& b) {  //交换位置
	T tem = a;
	a = b;
	b = tem;
}

template<class T>
void Sort<T>::bubbleSort() {  //及时终止的冒泡排序
	bool sorted = false;
	for (int i = 0; !sorted && i < num - 1; i++)  //内部循环未出现交换则终止排序
	{
		sorted = true;//未比较前设为已排序
		for (int j = 0; j < num - i - 1; j++) {
			if (data[j] > data[j + 1])
			{
				swap(data[j], data[j + 1]);
				sorted = false;
			}
		}
	}
}

template<class T>
void Sort<T>::insertSort() {  //插入排序
	int j;
	for (int i = 1; i < num; i++) {  //从数组第二位开始选择数字插入
		T tem = data[i];
		for (j = i - 1; j >= 0 && tem < data[j]; j--)  //要插入的数小于有序列中的数
			data[j + 1] = data[j];  ///后移
		data[j + 1] = tem;
	}

}

template<class T>
void Sort<T>::selectSort() {  //及时终止的选择排序
	bool sorted = false;
	for (int i = num; !sorted && i > 1; i--) {
		int indexMax = 0;
		sorted = true;  //未比较前设为已排序
		for (int j = 1; j < i; j++) {  //查找最大元素
			if (data[indexMax] <= data[j])  //两两比较
				indexMax = j;
			else
				sorted = false;  //无序
		}
		swap(data[indexMax], data[i - 1]);
	}
}

template<class T>
void Sort<T>::rankSort() {
	int* rank = new int[num];
	T* arr = new T[num];
	for (int i = 0; i < num; i++)
		rank[i] = 0;
	int index;
	//计算名次
	for (index = num - 1; index > 0; index--) {  //取一个数与比较
		for (int j = index - 1; j >= 0; j--) {
			if (data[j] <= data[index])
				rank[index]++;  //固定数位次+1
			else
				rank[j]++;  //被比较数位次+1
		}
	}
	for (int i = 0; i < num; i++)  //排序放入辅助数组
		arr[rank[i]] = data[i];
	for (int k = 0; k < num; k++)
		data[k] = arr[k];
	delete[]rank;
	delete[]arr;
}

int main() {
	int n;
	cin >> n;
	Sort<int> s(n);
	s.Setarray();
	s.bubbleSort();
	s.Show();
	return 0;
}