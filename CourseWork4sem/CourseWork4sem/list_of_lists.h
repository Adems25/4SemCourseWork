#ifndef LIST_OF_LISTS_H
#define LIST_OF_LISTS_H

#include "list.h"

using namespace std;

class Adj_List_Elem
{
    List* inf;
    string name;
    Adj_List_Elem* next;

public:

    Adj_List_Elem(string Name, List* Inf)
    {
        next = nullptr;
        inf = Inf;
        name = Name;
    }

    friend class Adj_List;
    friend class OrGraph;

    ~Adj_List_Elem()
    {
        if (inf)
            delete inf;
    }
};

class Adj_List
{
    Adj_List_Elem* head;
    size_t size;

public:

    Adj_List()
    {
        head = nullptr;
        size = 0;
    }

    size_t get_size()
    {
        return size;
    }

    bool create_rib(string from, string to, int weight)
    {
        Adj_List_Elem* F = find(from);
        if (!F)
        {
            List* newList = new List;
            push_back(from, newList);
            F = find(from);
        }

        int index_to = get_index_of(to);
        if (index_to == -1)
        {
            List* newList = new List;
            push_back(to, newList);
            index_to = get_index_of(to);
        }

        ElemL2* rib = F->inf->find_by_inf(index_to);
        if (rib)
            return 0;
        F->inf->push_back(index_to, weight);

        return 1;
    }

    void push_back(string name, List* inf)
    {
        Adj_List_Elem* Cur = head;
        if (Cur)
        {
            while (Cur->next)
                Cur = Cur->next;
            Cur->next = new Adj_List_Elem(name, inf);
        }
        else
            head = new Adj_List_Elem(name, inf);
        size++;
    }

    Adj_List_Elem* find(string name)
    {
        Adj_List_Elem* Cur = head;
        while (Cur)
        {
            if (Cur->name == name)
                return Cur;
            Cur = Cur->next;
        }
        return nullptr;
    }

    Adj_List_Elem* at(size_t index)
    {
        Adj_List_Elem* Cur;
        Cur = head;
        int count = 0;
        while (count != index)
        {
            Cur = Cur->next;
            count++;
        }
        return Cur;
    }

    int get_index_of(string name)
    {
        Adj_List_Elem* Cur = head;
        int index = -1;
        while (Cur)
        {
            index++;
            if (Cur->name == name)
                return index;
            Cur = Cur->next;
        }
        return -1;
    }

    ~Adj_List()
    {
        Adj_List_Elem* Cur = head;
        Adj_List_Elem* next;
        while (Cur)
        {
            next = Cur->next;
            delete Cur;
            Cur = next;
        }
    }
};

#endif
#pragma once
