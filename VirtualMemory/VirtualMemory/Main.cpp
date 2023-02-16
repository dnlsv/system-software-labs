#include <iostream>
#include<windows.h>

int const SIZE_15KB = 15 * 1024;

using namespace std;

struct Node
{
	void* p;
	Node* next;
};

struct Queue
{
	int size;
	Node* first;
	Node* last;
};

void creation(Queue* queue)
{
	queue->first = new Node;
	queue->first->next = NULL;
	queue->last = queue->first;
	queue->size = 0;
}

bool isEmpty(Queue* queue)
{
	if (queue->first == queue->last) 
		return true;
	else 
		return false;
}

void* top(Queue* queue)
{
	return queue->first->next->p;
}

void add(Queue* queue)
{
	queue->last->next = new Node;
	queue->last = queue->last->next;
	queue->last->p = VirtualAlloc(NULL, SIZE_15KB, MEM_COMMIT, PAGE_READONLY);
	queue->last->next = NULL;
	queue->size++;
	cout << "\n������� ��������\n";
}

bool cleanMemory(Node* q)
{
	return VirtualFree(q->p, 0, MEM_RELEASE);
}

void Delete(Queue* queue)
{
	Node* temp;
	temp = queue->first;
	queue->first = queue->first->next;
	queue->size--;
	cleanMemory(temp);
	delete(temp);
	cout << "\n������� ������\n";
}

int size(Queue* queue)
{
	return queue->size;
}

void cleanAll(Queue* queue)
{
	Node* h;
	for (h = queue->first->next; h != NULL; h = h->next)
		VirtualFree(h->p, 0, MEM_RELEASE);
}

void view(Queue* queue)
{
	Node* h;
	cout << endl <<"�������:" << endl << endl;
	for (h = queue->first->next; h != NULL; h = h->next)
	{
		cout << h->p << endl;
	}
	cout << endl;

}

void duplicate(Queue* queue)
{
	void* w;
	w = queue->last->p;
	queue->last->next = new Node;
	queue->last = queue->last->next;
	queue->last->p = w;
	queue->last->next = NULL;
	queue->size++;
	cout << "\n������� �������������\n";
}

void main()
{
	setlocale(LC_ALL, "Rus");
	Queue queue;
	creation(&queue);
	char number;
	do
	{
		cout << "1. ���������, ������� �����/�� �����\n";
		cout << "2. �������� ������� � ����� �������\n";
		cout << "3. ������� ������� �� ������ �������\n";
		cout << "4. ����������� ������ �������\n";
		cout << "5. �������������� ����� �������\n";
		cout << "6. ����������� ��� �������� �������\n";
		cout << "0. �����\n\n";
		cout << "����� ������� > "; cin >> number;
		switch (number)
		{
		case '1':
			if (isEmpty(&queue))
				cout << "\n������� �����\n\n";
			else
				cout << "\n������� �� �����\n\n";
			break;
		case '2': 
			add(&queue);
			view(&queue);
			break;
		case '3':
			if (isEmpty(&queue))
				cout << endl << "������� �����\n\n";
			else
			{
				Delete(&queue);
				view(&queue);
			}
			break;
		case '4':
			if (isEmpty(&queue))
				cout << "\n������� �����\n\n";
			else
				cout << "\n������ �������: " << top(&queue) << "\n\n";
			break;
		case '5':
			if (isEmpty(&queue))
				cout << "\n������� �����\n\n";
			else
			{
				duplicate(&queue);
				view(&queue);
			}
			break;
		case '6':
			if (isEmpty(&queue))
				cout << "\n������� �����\n\n";
			else
				view(&queue);
			break;
		case '0':
			cleanAll(&queue);
			break;
		default: cout << endl << "������� �� ����������\n\n";
			break;
		}
	} while (number != '0');

	system("pause");
}