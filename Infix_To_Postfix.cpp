#include <iostream>
#include <math.h>
#include <stack>
#include <string>

using namespace std;

int precedence(char c)
{
	if (c == '^')
	{
		return 3;
	}
	else if (c == '*' || c == '/')
	{
		return 2;
	}
	else if (c == '+' || c == '-')
	{
		return 1;
	}
	return 0;
}

bool comparePriorityForPostfix(char a, char b)
{
	if (precedence(a) >= precedence(b))
	{
		return true;
	}
	return false;
}

bool comparePriorityForPrefix(char a, char b)
{
	// a is the top of stack, b is the current character
	if (precedence(a) > precedence(b))
	{
		return true;
	}
	return false;
}

string removeDuplicateSpace(string s)
{
	string result = "";
	for (size_t i = 0; i < s.length(); i++)
	{
		if (s[i] != ' ' || (s[i] == ' ' && s[i + 1] != ' ' && i != s.length() - 1))
		{
			result += s[i];
		}
	}
	return result;
}

bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
	{
		return true;
	}
	return false;
}

string Infix2Postfix(string infix)
{
	string postfix = "";
	stack<char> stack;
	for (size_t i = 0; i < infix.length(); i++)
	{
		if (infix[i] == '(')
		{
			stack.push(infix[i]);
		}
		else if (infix[i] == ')')
		{
			while (!stack.empty() && stack.top() != '(')
			{
				postfix += " ";
				postfix += stack.top();
				stack.pop();
			}
			if (!stack.empty())
			{
				stack.pop();
			}
		}
		else if (isOperator(infix[i]))
		{
			postfix += " "; // This line is to separate each block of number in postfix output by a space
			while (!stack.empty() && comparePriorityForPostfix(stack.top(), infix[i]) == true)
			{
				postfix += stack.top();
				postfix += " ";
				stack.pop();
			}
			stack.push(infix[i]);
		}
		else
		{
			postfix += infix[i];
			/*postfix += " ";*/ // Comment this line to prevent double space between numbers
		}
	}
	while (!stack.empty())
	{
		postfix += " ";
		postfix += stack.top();
		stack.pop();
	}
	postfix = removeDuplicateSpace(postfix);
	return postfix;
}

string Infix2Prefix(string infix)
{
	string prefix = "";
	stack<char> stack;
	for (int i = infix.length() - 1; i >= 0; i--)
	{
		if (infix[i] == ')')
		{
			stack.push(infix[i]);
		}
		else if (infix[i] == '(')
		{
			while (!stack.empty() && stack.top() != ')')
			{
				prefix += " ";
				prefix += stack.top();
				stack.pop();
			}
			if (!stack.empty())
			{
				stack.pop();
			}
		}
		else if (isOperator(infix[i]))
		{
			prefix += " ";
			while (!stack.empty() && comparePriorityForPrefix(stack.top(), infix[i]) == true)
			{
				prefix += stack.top();
				prefix += " ";
				stack.pop();
			}
			stack.push(infix[i]);
		}
		else
		{
			prefix += infix[i];
		}
	}
	while (!stack.empty())
	{
		prefix += " ";
		prefix += stack.top();
		stack.pop();
	}
	reverse(prefix.begin(), prefix.end());
	prefix = removeDuplicateSpace(prefix);
	return prefix;
}

double EvaluatePostfixDouble(string postfix, int& errorHandle)
{
	stack<double> stack;
	for (int i = 0; i < int(postfix.length()); i++)
	{
		if (postfix[i] == ' ')
		{
			continue;
		}
		else if (isOperator(postfix[i]) == true)
		{
			if (stack.empty() == true)
			{
				errorHandle = 2;
				return 0;
			}
			else
			{
				double operand1 = stack.top();
				stack.pop();
				if (stack.empty() == true)
				{
					errorHandle = 2;
					return 0;
				}
				else
				{
					double operand2 = stack.top();
					stack.pop();
					double result = 0;
					switch (postfix[i])
					{
					case '+':
						result = operand2 + operand1;
						break;
					case '-':
						result = operand2 - operand1;
						break;
					case '*':
						result = operand2 * operand1;
						break;
					case '/':
						if (operand1 == 0)
						{
							errorHandle = 1;
							return 0;
						}
						result = operand2 / operand1;
						break;
					case '^':
						result = pow(operand2, operand1);
						break;
					default:
						break;
					}
					stack.push(result);
				}
			}

		}
		else
		{
			double operand = 0;
			while (i < int(postfix.length()) && postfix[i] != ' ')
			{
				operand = operand * 10 + (postfix[i] - '0');
				i++;
			}
			i--;
			stack.push(operand);
		}
	}
	if (stack.empty() == false)
	{
		return stack.top();
	}
	else
	{
		errorHandle = 2;
		return 0;
	}
}

double EvaluatePrefixDouble(string prefix, int& errorHandle)
{
	stack<double> stack;
	for (int i = int(prefix.length() - 1); i >= 0; i--)
	{
		if (prefix[i] == ' ')
		{
			continue;
		}
		else if (isOperator(prefix[i]))
		{
			if (stack.empty() == true)
			{
				errorHandle = 2;
				return 0;
			}
			else
			{
				double operand1 = stack.top();
				stack.pop();
				if (stack.empty() == true)
				{
					errorHandle = 2;
					return 0;
				}
				else
				{
					double operand2 = stack.top();
					stack.pop();
					double result = 0;
					switch (prefix[i])
					{
					case '+':
						result = operand1 + operand2;
						break;
					case '-':
						result = operand1 - operand2;
						break;
					case '*':
						result = operand1 * operand2;
						break;
					case '/':
						if (operand2 == 0)
						{
							errorHandle = 1;
							return 0;
						}
						result = operand1 / operand2;
						break;
					case '^':
						result = pow(operand1, operand2);
						break;
					default:
						break;
					}
					stack.push(result);
				}
			}
		}
		else
		{
			double operand = 0;
			int countDigits = 0;
			while (i >= 0 && prefix[i] != ' ')
			{
				operand += (prefix[i] - '0') * pow(10, countDigits);
				i--;
				countDigits++;
			}
			i++;
			stack.push(operand);

		}
	}
	if (stack.empty() == false)
	{
		return stack.top();
	}
	else
	{
		errorHandle = 2;
		return 0;
	}
}

string Double2String(double number)
{
	string str = to_string(number);
	size_t pos = str.find('.');
	if (str[pos + 5] >= '5')
	{
		str[pos + 4] += 1;
	}
	if (pos != string::npos)
	{
		str = str.substr(0, pos + 5);
	}
	for (int i = int(str.length() - 1); i >= 0; i--)
	{
		if (str[i] == '0')
		{
			str.erase(str.length() - 1, 1);
		}
		else
		{
			if (i > 0 && str[i] == '.')
			{
				str.erase(str.length() - 1, 1);
			}
			break;
		}
	}
	return str;
}

bool PrefixOrPostfix(string expression)
{
	if (isOperator(expression[expression.length() - 1]) == true)
	{
		return true;
		// This is a postfix expression
	}
	else
	{
		// Prevent Werror warning by not using else if
		return false;
	}
	//else if (isOperator(expression[0]) == true)
	//{
	//	return false;
	//	// This is a prefix expression
	//}
}

string PostfixPrefixCalculator(string expression, int handleError = 0)
{
	double numResult = 0;

	if (PrefixOrPostfix(expression) == true)
	{
		numResult = EvaluatePostfixDouble(expression, handleError);
	}
	else
	{
		numResult = EvaluatePrefixDouble(expression, handleError);
	}
	if (handleError == 1)
	{
		return "Error: Division by zero";
	}
	else if (handleError == 2)
	{
		return "Error: Stack error";
	}
	return Double2String(numResult);
}

int main()
{
	string list[] = 
	{	
		"1*2*3*4*5*6*7*8/7/6/5/4/3/2/1+2" ,
		"0/5",
		"24/18*(2*1)*9*16+10-26*14+26",
		"7*7+18+28-2+(19-(28+10*19)*28)",
		"2 2 + + +",
		"(4(+3)-2, 4+)(3*2",
		"3..4+2*2",
		"5+2.+2",
		"2 4+3",
		"2 3",
		"1^*3",
		"3--4",
		"1++1",
		"(4()+3)-2",
	};

	for (int i = 0; i < 14; i++)
	{
		string postfix = Infix2Postfix(list[i]);
		cout << PostfixPrefixCalculator(postfix) << endl;
		string prefix = Infix2Prefix(list[i]);
		cout << PostfixPrefixCalculator(prefix) << endl;
		cout << ' ' << endl;
	}

	return 0;	
}