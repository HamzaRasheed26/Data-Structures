#include <iostream>

using namespace std;

class Node
{
public:
	int Data;
	Node *Next;

public:
	Node(int data)
	{

		Data = data;
		Next = NULL;
	}
};

class LinkedList
{
private:
	Node *Head;

public:
	LinkedList()
	{
		Head = NULL;
	}

	void print()
	{
		Node *p = Head;
		while (p != NULL)
		{
			cout << p->Data << " -> ";
			p = p->Next;
		}
		cout << "NULL" << endl;
	}

	Node *Search(int Key)
	{
		Node *p = Head;
		while (p != NULL)
		{
			if (p->Data == Key)
				return p;
			p = p->Next;
		}
		return NULL;
	}

	void insertHead(int key)
	{
		Node *N = new Node(key);
		if (Head != NULL)
			N->Next = Head;
		Head = N;
	}

	void insertTail(int key)
	{
		Node *N = new Node(key);
		Node *P = Head;
		while (P->Next != NULL)
			P = P->Next;
		P->Next = N;
	}

	int lengthList()
	{
		int count = 0;
		Node *P = Head;
		while (P->Next != NULL)
		{
			P = P->Next;
			count = count + 1;
		}
		return count;
	}

	void insert(int key, int loc)
	{
		if (loc <= lengthList())
		{
			Node *N = new Node(key);
			Node *p = Head;
			Node *prev;
			for (int i = 0; i < loc; i++)
			{
				prev = p;
				p = p->Next;
			}
			prev->Next = N;
			N->Next = p;
		}
	}

	Node *deleteNode(int key)
	{
		Node *p = Head;
		Node *prev;
		while (p != NULL)
		{
			if (p->Data == key)
				prev->Next = p->Next;
			cout << p->Data << endl;
			return p;
			p = p->Next;
			prev->Next = p;
		}
		return NULL;
	}

	bool update(int newkey, int loc)
	{
		if (loc <= lengthList())
		{
			Node *p = Head;
			for (int i = 0; i < loc; i++)
				p = p->Next;
			p->Data = newkey;
		}
	}
};

int main()
{

	LinkedList list;
	list.insertHead(12);
	list.insertTail(23);
	list.insertHead(3);
	list.insertTail(87);
	cout << "length " << list.lengthList() << endl;
	list.print();
	list.insert(5, 3);
	list.print();

	return 0;
}
