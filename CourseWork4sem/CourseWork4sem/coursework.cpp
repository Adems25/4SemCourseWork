#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <limits>
#include "list_of_lists.h"

using namespace std;

class OrGraph
{
    class Iterator
    {
        class Stack
        {
            struct Elem
            {
                Adj_List_Elem* inf;
                Elem* next;
            };

            Elem* head;

        public:

            Stack()
            {
                head = nullptr;
            }

            bool contains(Adj_List_Elem* E)
            {
                Elem* Cur = head;
                while (Cur)
                {
                    if (Cur->inf == E)
                        return true;
                    Cur = Cur->next;
                }
                return false;
            }

            bool is_empty()
            {
                return (!head);
            }

            void push(Adj_List_Elem* Push)
            {
                Elem* New = new Elem;
                New->inf = Push;
                New->next = head;
                head = New;
            }

            Adj_List_Elem* pop()
            {
                if (!head)
                    return nullptr;
                Elem* nextHead = head->next;
                Adj_List_Elem* ans = head->inf;
                delete head;
                head = nextHead;
                return ans;
            }

            int get_min_rib(Adj_List_Elem* E, Adj_List* list)
            {
                int min_rib = INT_MAX;
                int temp;
                Adj_List_Elem* AdjL_Elem_Cur = E;
                Adj_List_Elem* AdjL_Elem_Prev;
                Elem* Stack_Cur = head;

                while (Stack_Cur)
                {
                    AdjL_Elem_Prev = Stack_Cur->inf;

                    temp = AdjL_Elem_Prev->inf->find_by_inf(list->get_index_of(AdjL_Elem_Cur->name))->key;
                    if (temp < min_rib)
                        min_rib = temp;

                    AdjL_Elem_Cur = AdjL_Elem_Prev;
                    Stack_Cur = Stack_Cur->next;
                }
                return min_rib;
            }

            void clear()
            {
                while (head)
                    pop();
            }

            ~Stack()
            {
                clear();
            }
        };

        Stack* Path;
        Stack* Visited;
        Adj_List_Elem* Cur;
        Adj_List* list;

    public:

        Iterator(Adj_List_Elem* Beg, Adj_List* adj_list)
        {
            Cur = Beg;
            list = adj_list;
            Path = new Stack;
            Visited = new Stack;
            Visited->push(Cur);
        }

        Adj_List_Elem* get_cur()
        {
            return Cur;
        }

        void prev(int dec)
        {
            //step back, rib between cur and prev will decrease by int dec, opposite rib will decrease by it
            Adj_List_Elem* Prev = Path->pop();
            int cur_index = list->get_index_of(Cur->name);
            int prev_index = list->get_index_of(Prev->name);

            ElemL2* rib = Prev->inf->find_by_inf(cur_index);
            ElemL2* opposite_rib = Cur->inf->find_by_inf(prev_index);
            rib->key -= dec;
            opposite_rib->key += dec;

            Cur = Prev;
        }

        void next()
        {
            ElemL2* Cur2 = Cur->inf->at(0);
            int max_rib = 0;
            while (Cur2)
            {
                if (!Visited->contains(list->at(Cur2->inf)))
                {
                    if (max_rib < Cur2->key)
                        max_rib = Cur2->key;
                }
                Cur2 = Cur2->next;
            }

            Cur2 = Cur->inf->at(0);
            while (Cur2)
            {
                if (!Visited->contains(list->at(Cur2->inf)) && Cur2->key == max_rib)
                    break;
                Cur2 = Cur2->next;
            }

            Path->push(Cur);
            Cur = list->at(Cur2->inf);
            Visited->push(Cur);
        }

        bool has_next()
        {
            ElemL2* Cur2 = Cur->inf->at(0);
            while (Cur2)
            {
                if (Cur2->key > 0)
                {
                    if (!Visited->contains(list->at(Cur2->inf)))
                        return true;
                }
                Cur2 = Cur2->next;
            }
            return false;
        }

        bool has_prev()
        {
            return (!Path->is_empty());
        }

        int to_beg()
        {
            int dec = Path->get_min_rib(Cur, list);
            while (has_prev())
                prev(dec);
            Visited->clear();
            Visited->push(Cur);
            if (dec == INT_MAX)
                return 0;
            return dec;
        }

        ~Iterator()
        {
            delete Path;
            delete Visited;
        }
    };

    Adj_List* adj_list;

    bool crt_rib(string name1, string name2, string rib)
    {
        if (rib.empty() || name2.empty())
            return 0;

        int weight;
        try { weight = stoi(rib); }
        catch (exception) { return 0; }
        if (weight < 0)
            return 0;

        bool ret = adj_list->create_rib(name1, name2, weight);
        if (ret)
            ret = adj_list->create_rib(name2, name1, 0);
        return ret;
    }

    bool string_working(ifstream* input)
    {
        string cur;
        getline(*input, cur);
        if (cur.empty())
            return 0;

        size_t p1 = 0, p2 = 0;
        string name1, name2, rib;

        for (int i = 0; i < cur.length(); i++)
        {
            if (cur[i] == ';')
            {
                if (p1 == 0)
                    p1 = i;
                else if (p2 == 0)
                    p2 = i;
                else
                    return 0;
            }
        }
        if (p1 == 0 || p2 == 0)
            return 0;

        rib = cur.substr(p2 + 1);
        cur.erase(p2);
        name2 = cur.substr(p1 + 1);
        cur.erase(p1);
        name1 = cur;

        if (!crt_rib(name1, name2, rib))
            return 0;
        return 1;
    }

    void input(string filename)
    {
        ifstream input;
        input.open(filename);
        if (!input.is_open())
            throw runtime_error("Could not open file " + filename);
        while (!input.eof())
        {
            if (!string_working(&input))
            {
                input.close();
                delete adj_list;
                throw invalid_argument("Incorrect input");
            }
        }
        input.close();
    }

public:

    OrGraph(string filename)
    {
        adj_list = new Adj_List;
        input(filename);
        if ((!adj_list->find("T") || (!adj_list->find("S"))))
            throw invalid_argument("Graph must contain S- and T- elements");
    }

    int get_max_flow()
    {
        int max_flow = 0;
        Adj_List_Elem* Cur = adj_list->find("S");
        Iterator* I = new Iterator(Cur, adj_list);

        while (I->has_next())//while there are ways from "S"
        {
            Cur = I->get_cur();
            while (Cur->name != "T")//until we came to stock
            {
                if (I->has_next())//there is further way
                {
                    I->next();
                    Cur = I->get_cur();
                }
                else//dead end
                {
                    while (!I->has_next() && I->has_prev())//until getting another way or coming back to "S"
                        I->prev(0);//step back
                    Cur = I->get_cur();
                    if (Cur->name == "S" && !I->has_next())//coming back to "S", no way further
                    {
                        delete I;
                        return max_flow;
                    }
                }
            }
            max_flow += I->to_beg();//return to the source
        }
        delete I;
        return max_flow;
    }

    ~OrGraph()
    {
        delete adj_list;
    }
};

int main()
{
    string filename;
    cout << "Enter name of file:\n";
    getline(cin, filename);
    try
    {
        OrGraph G(filename);
        cout << "Max flow is " << G.get_max_flow() << endl;
    }
    catch (exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
}
