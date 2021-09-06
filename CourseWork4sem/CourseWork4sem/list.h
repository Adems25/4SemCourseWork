#ifndef LIST_H
#define LIST_H

#include <stdexcept>

using namespace std;

class ElemL2
{
	int inf;
	int key;
	ElemL2* next;
	ElemL2* prev;

public:

	ElemL2(int Inf, int Key)
	{
		next = nullptr;
		prev = nullptr;
		inf = Inf;
		key = Key;
	}

	friend class List;
	friend class Adj_List;
	friend class OrGraph;

	~ElemL2()
	{
		if (next)
			next->prev = prev;
		if (prev)
			prev->next = next;
	}
};

class List
{
	ElemL2* head;
	ElemL2* last;
	size_t size;

public:

	List()
	{
		head = nullptr;
		last = nullptr;
		size = 0;
	}

	bool isEmpty()
	{
		return size == 0;
	}

	size_t get_size()
	{
		return size;
	}

	void push_back(int inf, int key)
	{
		if (!isEmpty())
		{
			last->next = new ElemL2(inf, key);
			last->next->prev = last;
			last = last->next;
		}
		else
		{
			head = new ElemL2(inf, key);
			last = head;
		}
		size += 1;
	}

	void push_front(int inf, int key)
	{
		if (!isEmpty())
		{
			head->prev = new ElemL2(inf, key);
			head->prev->next = head;
			head = head->prev;
		}
		else
		{
			head = new ElemL2(inf, key);
			last = head;
		}
		size += 1;
	}

	void pop_back()
	{
		if (isEmpty())
			throw runtime_error("List is empty\n");
		ElemL2* newLast = last->prev;
		delete last;
		last = newLast;
		if (!newLast)
			head = nullptr;
		size -= 1;
	}

	void pop_front()
	{
		if (isEmpty())
			throw runtime_error("List is empty\n");
		ElemL2* newHead = head->next;
		delete head;
		head = newHead;
		if (!newHead)
			last = nullptr;
		size -= 1;
	}

	ElemL2* at(size_t index)
	{
		if (index >= size)
			return nullptr;
		if (index == 0)
			return head;
		if (index == (size - 1))
			return last;
		int count;
		ElemL2* Cur;
		if ((size / 2) > index)
		{
			Cur = head;
			count = 0;
			while (count != index)
			{
				Cur = Cur->next;
				count++;
			}
		}
		else
		{
			Cur = last;
			count = size - 1;
			while (count != index)
			{
				Cur = Cur->prev;
				count--;
			}
		}
		return Cur;
	}

	ElemL2* find_by_inf(int inf)
	{
		ElemL2* Cur = head;
		while (Cur)
		{
			if (Cur->inf == inf)
				return Cur;
			Cur = Cur->next;
		}
		return nullptr;
	}

	void insert(int inf, int key, size_t index)
	{
		if (index == 0)
			push_front(inf, key);
		else
		{
			try
			{
				ElemL2* Next = at(index);
				ElemL2* Prev = Next->prev;
				ElemL2* Include = new ElemL2(inf, key);
				Prev->next = Include;
				Include->prev = Prev;
				Next->prev = Include;
				Include->next = Next;
				size += 1;
			}
			catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
		}
	}

	void remove(size_t index)
	{
		try
		{
			if (index == 0)
				pop_front();
			else if (index == (size - 1))
				pop_back();
			else
			{
				ElemL2* Exclude = at(index);
				delete Exclude;
				size -= 1;
			}
		}
		catch (runtime_error& exception) { throw runtime_error("List is empty\n"); }
		catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
	}

	void set(int inf, int key, size_t index)
	{
		ElemL2* cur;
		try
		{
			cur = at(index);
			cur->inf = inf;
			cur->key = key;
		}
		catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
	}

	void clear()
	{
		while (!isEmpty())
			pop_front();
	}

	~List()
	{
		clear();
	}
};

#endif
#pragma once
