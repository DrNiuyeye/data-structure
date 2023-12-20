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
	int stackTop; //当前栈顶
	int stackLength;  //栈容量
	T* stack; //数组
};

template<class T>
void DoubleLength(T*& a, int oldLength, int newLength) //扩增栈的容量
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
	//取出数字栈前两个数
	b = number.top();   
	number.pop();
	a = number.top();  
	number.pop(); 
	//取出符号栈栈顶的符号
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
	symbol.pop();//将参与运算的符号弹出栈 
}

void compute(string ch)
{
	int length = ch.length();
	arrayStack<double> opnd(length); //操作数栈
	arrayStack<char> optr(length); //操作符栈
	for (int i = 0; i < length; i++) //将表达式字符压入栈
	{
		if (ch[i] == '-' && (ch[i - 1] == '(' || i == 0)) //判断数字是否为负
		{  	//读取到'-'
			i++;
			int number = ch[i] - '0'; //字符转换为整数
			number = -number;
			opnd.push(number);
		}
		else if (ch[i] >= '0' && ch[i] <= '9')
		{   //读到数字
			int number = ch[i] - '0';
			opnd.push(number);
		}
		else
		{   //读到字符
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
				optr.pop();  //删除'('
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