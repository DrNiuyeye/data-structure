#include <iostream>
using namespace std;
template<class T>
class Sort {
private:
	T* data;
	int num;

public:
	Sort(int n) {  //���캯��
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
void Sort<T>::swap(T& a, T& b) {  //����λ��
	T tem = a;
	a = b;
	b = tem;
}

template<class T>
void Sort<T>::bubbleSort() {  //��ʱ��ֹ��ð������
	bool sorted = false;
	for (int i = 0; !sorted && i < num - 1; i++)  //�ڲ�ѭ��δ���ֽ�������ֹ����
	{
		sorted = true;//δ�Ƚ�ǰ��Ϊ������
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
void Sort<T>::insertSort() {  //��������
	int j;
	for (int i = 1; i < num; i++) {  //������ڶ�λ��ʼѡ�����ֲ���
		T tem = data[i];
		for (j = i - 1; j >= 0 && tem < data[j]; j--)  //Ҫ�������С���������е���
			data[j + 1] = data[j];  ///����
		data[j + 1] = tem;
	}

}

template<class T>
void Sort<T>::selectSort() {  //��ʱ��ֹ��ѡ������
	bool sorted = false;
	for (int i = num; !sorted && i > 1; i--) {
		int indexMax = 0;
		sorted = true;  //δ�Ƚ�ǰ��Ϊ������
		for (int j = 1; j < i; j++) {  //�������Ԫ��
			if (data[indexMax] <= data[j])  //�����Ƚ�
				indexMax = j;
			else
				sorted = false;  //����
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
	//��������
	for (index = num - 1; index > 0; index--) {  //ȡһ������Ƚ�
		for (int j = index - 1; j >= 0; j--) {
			if (data[j] <= data[index])
				rank[index]++;  //�̶���λ��+1
			else
				rank[j]++;  //���Ƚ���λ��+1
		}
	}
	for (int i = 0; i < num; i++)  //������븨������
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