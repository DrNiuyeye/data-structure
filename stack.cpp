#include<iostream>
#include<iomanip>
using namespace std;

template<class T>
class arrayStack
{
public:
	arrayStack(int length)
	{
		stackLength = length;
		stack = new T[stackLength];
		stackTop = -1;
	}
	~arrayStack() { delete[] stack; }
	bool empty() { return stackTop == -1; }
	int size() const { return stackTop + 1; }
	T& top() { return stack[stackTop]; }
	void pop();
	void push(const T& theElement);


private:
	int stackTop; //��ǰջ��
	int stackLength;  //ջ����
	T* stack; //����
};

template<class T>
void DoubleLength(T*& a, int oldLength, int newLength) //����ջ������
{
	T* temp = new T[newLength];
	for (int i = 0; i < oldLength; i++)
		temp[i] = a[i];
	delete[] a;
	a = temp;
}

template<class T>
void arrayStack<T>::pop()
{
	stack[stackTop].~T();
	stackTop--;
}

template<class T>
void arrayStack<T>::push(const T& theElement)
{
	if (stackTop == stackLength - 1)
	{
		DoubleLength(stack, stackLength, 2 * stackLength);
		stackLength *= 2;
	}
	stackTop++;
	stack[stackTop] = theElement;
}

int priority(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '(':
		return 0;
	};
}

void operate(arrayStack<double>& number, arrayStack<char>& symbol)
{
	double a, b;
	//ȡ������ջǰ������
	b = number.top();   
	number.pop();
	a = number.top();  
	number.pop(); 
	//ȡ������ջջ���ķ���
	switch (symbol.top())
	{
	case '+':
		number.push(a + b);
		break;
	case '-': 
		number.push(a - b);
		break;
	case '*':
		number.push(a * b);
		break;
	case '/': 
		number.push(a / b);
		break;
	}
	symbol.pop();//����������ķ��ŵ���ջ 
}

void compute(string ch)
{
	int length = ch.length();
	arrayStack<double> opnd(length); //������ջ
	arrayStack<char> optr(length); //������ջ
	for (int i = 0; i < length; i++) //�����ʽ�ַ�ѹ��ջ
	{
		if (ch[i] == '-' && (ch[i - 1] == '(' || i == 0)) //�ж������Ƿ�Ϊ��
		{  	//��ȡ��'-'
			i++;
			int number = ch[i] - '0'; //�ַ�ת��Ϊ����
			number = -number;
			opnd.push(number);
		}
		else if (ch[i] >= '0' && ch[i] <= '9')
		{   //��������
			int number = ch[i] - '0';
			opnd.push(number);
		}
		else
		{   //�����ַ�
			switch (ch[i])
			{
			case '(':
				optr.push(ch[i]);
				break;
			case '+':
			case '-':
			case '*':
			case '/':
				while(!optr.empty() && (priority(ch[i]) <= priority(optr.top())))
					operate(opnd, optr);
				optr.push(ch[i]);
				break;
			case ')':
				while (optr.top() != '(')
				{
					operate(opnd, optr);
				}
				optr.pop();  //ɾ��'('
				break;
			}
		}
	}
	while (!optr.empty())
	{
		operate(opnd, optr);
	}
	cout << fixed << setprecision(2) << opnd.top() << endl;
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		compute(s);
	}
	return 0;
}