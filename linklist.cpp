// Harold Justin Windham
// LinkList Cheesecake
// COP 3330
// Dr Gaitros

#include <iostream>
#include "linklist.h"
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// ***************************************************************************
// * Function influenced by Dr. Gaitros' class videos and office hours.      *
// * Default constructor to set up primary linklist                          *
// ***************************************************************************

LinkList::LinkList()
{
    head = new PieCake_struct();
    tail = new PieCake_struct();
    head->lname = "";
    tail->lname = "ZZZZZZZZZZZZZZZZZZZZZZZZZ";
    head->next = tail;
    head->prev = nullptr;
    tail->next = nullptr;
    tail->prev = head;
    current = nullptr;
    count = 0;
}

// ***************************************************************************
// * Destructor function to set back to 0                                    *
// ***************************************************************************

LinkList::~LinkList()
{
    while (head)
    {
        current = head;
        head = head->next;
        delete current;
    }
    head = tail = current = nullptr;
    count = 0;

}

// ***************************************************************************
// * Function to return an empty status while count equals 0                 *
// ***************************************************************************

bool LinkList::Empty()
{
    return count == 0;
}

// ***************************************************************************
// * Returns size of linklist by count                                       *
// ***************************************************************************

int LinkList::Size()
{
    return count;
}

// ***************************************************************************
// * Searches id number in occupied node                                     *
// ***************************************************************************

bool LinkList::Find(const int idnumber)
{
    current = nullptr;
    if (Empty())
        return false;
    current = head;
    while (current != nullptr)
    {
        if (current->id == idnumber)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// ***************************************************************************
// * Inserts by adding node with iterator                                    *
// ***************************************************************************

void LinkList::Insert(PieCake_struct *p)
{
    PieCake_struct *tempCurrent;
    tempCurrent = head;

    if (count == 0)
    {
        p->prev = nullptr;
        head = tail = p;
    }
    else if (tempCurrent->lname >= p->lname)
    {
        p->next = tempCurrent;
        p->next->prev = p;
        head = p;
    }

    else
    {
        while (tempCurrent->next != NULL &&
               tempCurrent->next->lname < p->lname)
            tempCurrent = tempCurrent->next;

        p->next = tempCurrent->next;

        if (tempCurrent->next != NULL)
            p->next->prev = p;

        tempCurrent->next = p;
        p->prev = tempCurrent;
    }
    count++;
}

// ***************************************************************************
// * Delete or clear out linked list                                         *
// ***************************************************************************

bool LinkList::Delete()
{
    if (current == nullptr)
        return false;

    if (current == head)
    {
        head = current->next;
        head->prev = nullptr;
    }
    else if (current == tail)
    {
        tail = current->prev;
        tail->next = nullptr;
    }
    else
    {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    count--;
    delete current;
    return true;
}

// ***************************************************************************
// * Print function prints out the list using the List() function            *
// ***************************************************************************

void LinkList::Print()
{
    cout << "****** The CheeseCake Survey ******" << endl;
    cout << "Id First Name MI Last Name Sex Pie/Cake" << endl;
    cout << "-- ----- ---- -- ---- ---- --- --------" << endl;
    List();
    cout << "Total Surveyed: " << count << endl;
    cout << "People who thought Cheesecake was Pie: " << CountPie() << endl;
    cout << "People who thought Cheesecake was Cake: " << CountCake() << endl;
}

// ***************************************************************************
// * List function generates list of people by their attributes.             *
// ***************************************************************************

void LinkList::List()
{
    PieCake_struct *t;
    t = head;
    while (t != nullptr)
    {
        string gender = "";
        string cakeOrPie = "";
        if (t->sex == 'M')
            gender = "Male";
        else if (t->sex == 'F')
            gender = "Female";
        else if (t->sex == 'O')
            gender = "Other";

        if (t->pORc == 'C')
            cakeOrPie = "Cake";
        else
            cakeOrPie = "Pie";

        cout << t->id << setw(2) << "  " << t->fname << setw(15) << "    ";
        cout << t->mi << setw(4) << "  " << t->lname << "    " << setw(15) << gender << "  ";
        cout << cakeOrPie << endl;
        t = t->next;
    }
}

// ***************************************************************************
// * Returns number of people that picked pie                                *
// ***************************************************************************

int LinkList::CountPie()
{
    PieCake_struct *t;
    t = head;
    int pieCount = 0;
    while (t != nullptr)
    {
        if (t->pORc == 'P')
            pieCount++;

        t = t->next;
    }

    return pieCount;
}

// ***************************************************************************
// * Returns number of people that picked cake                               *
// ***************************************************************************

int LinkList::CountCake()
{
    PieCake_struct *t;
    t = head;
    int cakeCount = 0;
    while (t != nullptr)
    {
        if (t->pORc == 'C')
            cakeCount++;

        t = t->next;
    }

    return cakeCount;
}
