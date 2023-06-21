#include <iostream>

using namespace std;

class Node
{
public:
	int Data;
	Node *Next;
	Node *Prev;

public:
	Node(int data)
	{

		Data = data;
		Next = NULL;
		Prev = NULL;
	}
};

class DoublyLinkedList
{
private:
	Node *Head;

public:
	DoublyLinkedList()
	{
		Head = NULL;
	}

	Node *getHead()
	{
		return Head;
	}

	int HeadValue()
	{
		if (Head != NULL)
			return Head->Data;
		else
			return NULL;
	}

	bool isEmpty()
	{
		return Head == NULL;
	}

	void displayList()
	{
		Node *p = Head;
		while (p != NULL)
		{
			cout << p->Data << " -> ";
			p = p->Next;
		}
		cout << "NULL" << endl;
	}

	Node *findNode(int Key)
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

	Node *insertAtHead(int key)
	{
		Node *N = new Node(key);
		if (Head != NULL)
			Head->Prev = N;
		N->Next = Head;

		Head = N;
		return N;
	}

	Node *insertAtEnd(int key)
	{
		Node *N = new Node(key);

		if (Head == NULL)
			Head = N;
		else
		{
			Node *P = Head;
			while (P->Next != NULL)
				P = P->Next;
			P->Next = N;
			N->Prev = P;
		}
		return N;
	}

	int lengthList()
	{
		int count = 0;
		Node *P = Head;
		while (P != NULL)
		{
			P = P->Next;
			count = count + 1;
		}
		return count;
	}

	Node *insertNode(int loc, int key)
	{
		Node *N = new Node(key);
		if (loc <= lengthList())
		{
			Node *p = Head;
			Node *prev;
			for (int i = 0; i <= loc; i++)
				prev = p;
			p = p->Next;
			prev->Next = N;
			N->Prev = prev;
			N->Next = p;
			if (p != NULL)
				p->Prev = N;
		}
		return N;
	}

	bool deleteNode(int key)
	{
		Node *p = Head;
		bool flag = false;
		while (p != NULL)
		{
			if (p->Data == key)
			{
				if (p->Prev != NULL)
					p->Prev->Next = p->Next;
				else
					Head = p->Next;
				if (p->Next != NULL)
					p->Next->Prev = p->Prev;
				flag = true;
			}
			p = p->Next;
		}
		return flag;
	}

	bool update(int newkey, int loc)
	{
		if (loc < lengthList())
		{
			Node *p = Head;
			for (int i = 0; i < loc; i++)
				p = p->Next;
			p->Data = newkey;
		}
	}

	bool deleteFromStart()
	{
		if (Head != NULL)
		{
			Head = Head->Next;
			Head->Prev = NULL;
			return true;
		}
		return false;
	}

	bool deleteFromEnd()
	{
		if (Head != NULL)
		{
			if (lengthList() == 1)
			{
				Head = NULL;
				return true;
			}
			Node *p = Head;
			while (p != NULL)
			{
				if (p->Next == NULL)
				{
					p->Prev->Next = NULL;
					return true;
				}
				p = p->Next;
			}
		}
		return false;
	}
};

int main()
{

	DoublyLinkedList list;
	list.insertAtHead(12);
	list.insertNode(1, 5);
	list.insertAtHead(17);
	list.insertAtEnd(3);
	list.insertAtEnd(0);
	list.insertAtEnd(4);

	list.displayList();

	list.update(9, 6);
	list.displayList();

	return 0;
}
