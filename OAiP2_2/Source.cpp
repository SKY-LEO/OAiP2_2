#include <iostream>
#include <ctime>

using namespace std;

struct Stack
{
	int number;
	Stack* next;
};

Stack* pushStack(Stack* begin, int number);
Stack* viewStack(Stack* begin);
Stack* individualTask1(Stack*& begin, Stack*& max);
Stack* individualTask2(Stack*& begin, int& max_number);
void deleteStack(Stack*& begin);
void fillStack(Stack*& begin, bool is_random = false);
bool isCorrectTask(Stack*& begin, Stack*& max, int& max_number);
int popStack(Stack*& begin);
int correctInputInt();

int main()
{
	Stack* begin = NULL, * max = NULL, * new_stack = NULL;
	int max_number;
	while (true)
	{
		int code;
		do
		{
			cout << "\n Create - 1\n Add - 2\n Individual task_variant1 - 3\n Individual task_variant2 - 4\n View Stack - 5\n Delete Stack - 6\n EXIT - 0\n";
			code = correctInputInt();
		} while (code < 0 || code > 6);
		switch (code)
		{
		case 1:
		case 2:
			if (code == 1 && begin != NULL)
			{
				cout << "Delete previous Stack" << endl;
				deleteStack(begin);
			}
			do
			{
				cout << "How you want to fill Stack? \n By random - 1\n By keyboard - 2\n";
				code = correctInputInt();
			} while (code < 1 || code > 2);
			switch (code)
			{
			case 1: fillStack(begin, true);
				continue;
			case 2: fillStack(begin);
				continue;
			}
			break;
		case 3:
		case 4:
			if (isCorrectTask(begin, max, max_number))
			{
				if (code == 3)
				{
					new_stack = individualTask1(begin, max);
				}
				else
				{
					new_stack = individualTask2(begin, max_number);
				}
				cout << "New Stack:" << endl;
				viewStack(new_stack);
				cout << "Old Stack:" << endl;
				viewStack(begin);
			}
			else
			{
				cout << "Bad Stack, nothing interesting!" << endl;
			}
			break;
		case 5: viewStack(begin);
			break;
		case 6:
			if (begin) deleteStack(begin);
			if (new_stack) deleteStack(new_stack);
			break;
		case 0:
			cout << "Safe exit..." << endl;
			if (begin) deleteStack(begin);
			if (new_stack) deleteStack(new_stack);
			system("pause");
			return 0;
		}
	}
}

void fillStack(Stack*& begin, bool is_random)
{
	int n, number;
	do
	{
		cout << "How many?" << endl;
		n = correctInputInt();
	} while (n < 1);
	if (is_random)
	{
		int min, max;
		srand(time(NULL));
		cout << "What range? Enter min:" << endl;
		min = correctInputInt();
		cout << "Enter max:" << endl;
		max = correctInputInt();
		if (min > max)
		{
			cout << "Min > Max, swap them!" << endl;
			int temp;
			temp =  min;
			min = max;
			max = temp;
		}
		for (int i = 0; i < n; i++)
		{
			number = rand() % (max - min + 1) + min;
			begin = pushStack(begin, number);
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			cout << "Enter number: " << endl;
			number = correctInputInt();
			begin = pushStack(begin, number);
		}
	}
}

Stack* individualTask1(Stack*& begin, Stack*& max)
{
	Stack* new_stack = NULL;
	Stack* temp = begin->next;
	int variable;
	while (temp != max)
	{
		variable = popStack(temp);
		new_stack = pushStack(new_stack, variable);
	}
	begin->next = max;
	return new_stack;
}

Stack* individualTask2(Stack*& begin, int& max_number)
{
	Stack* new_stack = NULL;
	Stack* temp = begin->next;
	int variable;
	while (temp->number < max_number)
	{
		variable = popStack(temp);
		new_stack = pushStack(new_stack, variable);
	}
	begin->next = temp;
	return new_stack;
}

bool isCorrectTask(Stack*& begin, Stack*& max, int& max_number)
{
	if (begin == NULL)
	{
		return false;
	}
	Stack* temp = begin->next;
	max = begin;
	int i = 0;
	while (temp)
	{
		if (max->number < temp->number)
		{
			max = temp;
		}
		temp = temp->next;
		i++;
	}
	max_number = max->number;
	cout << "MAX " << max_number << endl;
	if (max == begin || max == begin->next || i < 3)
	{
		return false;
	}
	else
	{
		return true;
	}
}

Stack* pushStack(Stack* begin, int number)
{
	Stack* temp = new Stack;
	temp->number = number;
	temp->next = begin;
	return temp;
}

int popStack(Stack*& begin)//по адресу
{
	int out;
	out = begin->number;
	begin = begin->next;
	return out;
}

Stack* viewStack(Stack* begin)
{
	if (begin)
	{
		cout << begin->number << '\t';
		begin = begin->next;
		return viewStack(begin);
	}
	cout << endl;
	return begin;	
}

void deleteStack(Stack*& begin)//по адресу
{
	while (begin)
	{
		begin = begin->next;
	}
	cout << "Stack deleted successfully" << endl;
}

int correctInputInt()
{
	int a;
	while (true)
	{
		cin >> a;
		if (cin.get() == '\n') {
			break;
		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error, please write INT numbers!\n" << "Try again!" << endl;
		}
	}
	return a;
}



