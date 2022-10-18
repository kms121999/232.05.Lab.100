/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *    Our custom implementation of std::list
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        List         : A class that represents a List
 *        ListIterator : An iterator through List
 * Author
 *    <Keaton Smith 4 hours, Philip Marvin 6 hours, Alex Jacob 6 hours>
 ************************************************************************/

#pragma once
#include <cassert>     // for ASSERT
#include <iostream>    // for nullptr
#include <new>         // std::bad_alloc
#include <memory>      // for std::allocator
 
class TestList;        // forward declaration for unit tests
class TestHash;

namespace custom
{

/**************************************************
 * LIST
 * Just like std::list
 **************************************************/
template <typename T>
class list
{
   friend class ::TestList; // give unit tests access to the privates
   friend class ::TestHash;
   friend void swap(list& lhs, list& rhs);
public:  
   // 
   // Construct
   //

   list();
   list(list <T> & rhs);
   list(list <T>&& rhs);
   list(size_t num, const T & t);
   list(size_t num);
   list(const std::initializer_list<T>& il);
   template <class Iterator>
   list(Iterator first, Iterator last);
  ~list() 
   {
   }
  pNew = new list<T>::Node();

  pNew = new list<T>::Node(t);

  pNew = alloc.allocate(1);
  new (void*)pNew T(t);

  // Copy Constructor
  list.copy-constructor(rhs)
  pHead 

   // 
   // Assign
   //

   list <T> & operator = (list &  rhs);
   list <T> & operator = (list && rhs);
   list <T> & operator = (const std::initializer_list<T>& il);

   //
   // Iterator
   //

   class  iterator;
   iterator begin()  { return iterator(); }
   iterator rbegin() { return iterator(); }
   iterator end()    { return iterator(); }

   //
   // Access
   //

   T& front();
   T& back();

   //
   // Insert
   //

   void push_front(const T&  data);
   void push_front(      T&& data);
   void push_back (const T&  data);
   void push_back (      T&& data);
   iterator insert(iterator it, const T& data);
   iterator insert(iterator it, T&& data);

   //
   // Remove
   //

   void pop_back();
   void pop_front();
   void clear();
   iterator erase(const iterator& it);

   // 
   // Status
   //

   bool empty()  const { return true; }
   size_t size() const { return 99;   }


private:
   // nested linked list class
   class Node;

   // member variables
   size_t numElements; // though we could count, it is faster to keep a variable
   Node * pHead;    // pointer to the beginning of the list
   Node * pTail;    // pointer to the ending of the list
};

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <typename T>
class list <T> :: Node
{
public:
   //
   // Construct
   //
   Node()                : pNext(nullptr), pPrev(nullptr), data() {};
   Node(const T &  data) : pNext(nullptr), pPrev(nullptr), data(data) {};
   Node(      T && data) : pNext(nullptr), pPrev(nullptr), data(std::move(data)) {};
   list<int> l6{ 0, 2, 4, 6 };

   //
   // Data
   //

   T data;                 // user data
   Node * pNext;       // pointer to next node
   Node * pPrev;       // pointer to previous node
};

/*************************************************
 * LIST ITERATOR
 * Iterate through a List, non-constant version
 ************************************************/
template <typename T>
class list <T> :: iterator
{
   friend class ::TestList; // give unit tests access to the privates
   friend class ::TestHash;
   template <typename TT>
   friend class custom::list;
public:
   // constructors, destructors, and assignment operator
   iterator() 
   {
      p = nullptr;
   }
   iterator(Node * p) 
   {
      this->p = p;
   }
   iterator(const iterator  & rhs) 
   {
      this->p = rhs.p;
   }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }
   
   // equals, not equals operator
   bool operator == (const iterator & rhs) const
   {
      if (this->p == rhs.p)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
   bool operator != (const iterator & rhs) const
   {
      if (!(*this == rhs))
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   // dereference operator, fetch a node
   T & operator * ()
   {
      return p->data;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator temp;
      temp = *this;
      ++(*this);
      return temp;
   }

   // prefix increment
   iterator & operator ++ ()
   {
      p = p->pNext;
      return *this;
   }
   
   // postfix decrement
   iterator operator -- (int postfix)
   {
      iterator temp;
      temp = *this;
      --(*this);
      return temp;
   }

   // prefix decrement
   iterator & operator -- ()
   {
      p = p->pPrev;
      return *this;
   } 

   // two friends who need to access p directly
   friend iterator list <T> :: insert(iterator it, const T &  data);
   friend iterator list <T> :: insert(iterator it,       T && data);
   friend iterator list <T> :: erase(const iterator & it);

private:

   typename list <T> :: Node * p;
};

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num, const T & t) 
{
   list<char> l3(4, 'a');
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: ITERATOR constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
template <class Iterator>
list <T> ::list(Iterator first, Iterator last)
{
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: INITIALIZER constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
list <T> ::list(const std::initializer_list<T>& il)
{
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num)
{
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: DEFAULT constructors
 ****************************************/
template <typename T>
list <T> ::list() 
{
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: COPY constructors
 ****************************************/
template <typename T>
list <T> ::list(list& rhs) 
{
   list<char> l4(l3);
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: MOVE constructors
 * Steal the values from the RHS
 ****************************************/
template <typename T>
list <T> ::list(list <T>&& rhs)
{
   list<char> l5(move(l3));
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS 
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (list <T> && rhs)
{
   clear();
   swap(rhs);
   return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
list <T> & list <T> :: operator = (list <T> & rhs)
{
    itRHS = rhs->begin;
    itLHS = begin();
    while (itRHS != rhs->end() && itLHS != end())
    {
        *itLHS = *itRHS;
        ++itRHS;
        ++itLHS;
    }
    if (itRHS != rhs->end());
    {
        while (itRHS != rhs->end())
        {
            push_back(*itRHS);
            ++itRHS;
        }
    }
    elseif(rhs.empty())
    {
        clear();
    }
    elif(itLHS != end())
    {
        p = itLHS->p;
        pTail = p->pPrev;
        pNext = p->pNext;
        while (p != NULL)
        {
            pNext = p->pNext;
            delete p;
            p = pNext;
            --numElements;
            pTail->pNext = NULL;
        }
    }
    return *this;
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (const std::initializer_list<T>& rhs)
{
   return *this;
}

/**********************************************
 * LIST :: CLEAR
 * Remove all the items currently in the linked list
 *     INPUT  :
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
void list <T> :: clear()
{

}

/*********************************************
 * LIST :: PUSH BACK
 * add an item to the end of the list
 *    INPUT  : data to be added to the list
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_back(const T & data)
{

}

template <typename T>
void list <T> ::push_back(T && data)
{

}

/*********************************************
 * LIST :: PUSH FRONT
 * add an item to the head of the list
 *     INPUT  : data to be added to the list
 *     OUTPUT :
 *     COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_front(const T & data)
{

}

template <typename T>
void list <T> ::push_front(T && data)
{

}


/*********************************************
 * LIST :: POP BACK
 * remove an item from the end of the list
 *    INPUT  : 
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_back()
{

}

/*********************************************
 * LIST :: POP FRONT
 * remove an item from the front of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_front()
{

}

/*********************************************
 * LIST :: FRONT
 * retrieves the first element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: front()
{
   return *(new T);
}

/*********************************************
 * LIST :: BACK
 * retrieves the last element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: back()
{
   return *(new T);
}

/******************************************
 * LIST :: REMOVE
 * remove an item from the middle of the list
 *     INPUT  : an iterator to the item being removed
 *     OUTPUT : iterator to the new location 
 *     COST   : O(1)
 ******************************************/
template <typename T>
typename list <T> :: iterator  list <T> :: erase(const list <T> :: iterator & it)
{
   return end();
}

/******************************************
 * LIST :: INSERT
 * add an item to the middle of the list
 *     INPUT  : data to be added to the list
 *              an iterator to the location where it is to be inserted
 *     OUTPUT : iterator to the new item
 *     COST   : O(1)
 ******************************************/
template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
                                                 const T & data) 
{
   return end();
}

template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
   T && data)
{
   return end();
}

/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS
 *********************************************/
template <typename T>
void swap(list <T> & lhs, list <T> & rhs)
{

}


//#endif
}; // namespace custom
