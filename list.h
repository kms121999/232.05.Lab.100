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
 *    <Keaton Smith 6 hours, Philip Marvin 6 hours, Alex Jacob 8 hours>
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
     clear();
   }

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
   iterator begin()  { return iterator(pHead); }
   iterator rbegin() { return iterator(pTail); }
   iterator end()    { return iterator(nullptr); }

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

   bool empty()  const { return (pHead == nullptr); }
   size_t size() const { return numElements; }


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
   numElements = num;
   pHead = pTail = nullptr;

   if (num)
   {
       pHead = new Node(t);
       Node* pPrevious = pHead;
       Node* pNew = pHead;
       pHead->pPrev = nullptr;
       for (size_t i = 1; i < num; i++)
       {
           pNew = new Node(t);
           pNew->pPrev = pPrevious;
           pNew->pPrev->pNext = pNew;
           pPrevious = pNew;
       }
       pNew->pNext = nullptr;
       pTail = pNew;
   }
}

/*****************************************
 * LIST :: ITERATOR constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
template <class Iterator>
list <T> ::list(Iterator first, Iterator last)
{
   numElements = 0;
   pHead = pTail = nullptr;

   if (first)
   {
      pHead = new Node(*first);
      Node* pNew = pHead;
      Node* pPrevious = pHead;
      ++numElements;
      ++first;

      for (auto it = first; it != last; ++it)
      {
         pNew = new Node(*it);
         pPrevious->pNext = pNew;
         pNew->pPrev = pPrevious;
         pPrevious = pNew;
         ++numElements;
      }

      pTail = pNew;
   }
}

/*****************************************
 * LIST :: INITIALIZER constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
list <T> ::list(const std::initializer_list<T>& il)
{
   numElements = il.size();
   pHead = pTail = nullptr;

   auto first = il.begin();

   if (first)
   {
      pHead = new Node(*first);
      Node* pNew = pHead;
      Node* pPrevious = pHead;
      ++first;

      for (auto it = first; it != il.end(); ++it)
      {
         pNew = new Node(*it);
         pPrevious->pNext = pNew;
         pNew->pPrev = pPrevious;
         pPrevious = pNew;
      }

      pTail = pNew;
   }
}

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num)
{
    numElements = num;
    pHead = pTail = nullptr;

    if (num)
    {
        pHead = new Node();
        Node* pPrevious = pHead;
        Node* pNew = pHead;
        pHead->pPrev = nullptr;
        for (size_t i = 1; i < num; i++)
        {
            pNew = new Node();
            pNew->pPrev = pPrevious;
            pNew->pPrev->pNext = pNew;
            pPrevious = pNew;
        }
        pNew->pNext = nullptr;
        pTail = pNew;
    }
}

/*****************************************
 * LIST :: DEFAULT constructors
 ****************************************/
template <typename T>
list <T> ::list() 
{
    pHead = nullptr;
    pTail = nullptr;
    numElements = 0;
}

/*****************************************
 * LIST :: COPY constructors
 ****************************************/
template <typename T>
list <T> ::list(list& rhs) 
{
    pHead = nullptr;
    pTail = nullptr;
    numElements = 0;

    for (auto it = rhs.begin(); it != rhs.end(); ++it)
    {
        push_back(*it);
    }
}

/*****************************************
 * LIST :: MOVE constructors
 * Steal the values from the RHS
 ****************************************/
template <typename T>
list <T> ::list(list <T>&& rhs)
{
   pHead = rhs.pHead;
   pTail = rhs.pTail;
   numElements = rhs.numElements;
   
   rhs.pHead = nullptr;
   rhs.pTail = nullptr;
   rhs.numElements = 0;
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
   swap(*this, rhs);
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
    iterator itRHS = rhs.begin();
    iterator itLHS = begin();
    while (itRHS != rhs.end() && itLHS != end())
    {
        *itLHS = *itRHS;
        ++itRHS;
        ++itLHS;
    }
    if (itRHS != rhs.end())
    {
        while (itRHS != rhs.end())
        {
            push_back(*itRHS);
            ++itRHS;
        }
    }
    else if (rhs.empty())
    {
        clear();
    }
    else if (itLHS != end())
    {
        Node* p = itLHS.p;
        pTail = p->pPrev;
        Node* pNext = p->pNext;
        while (p != NULL)
        {
            pNext = p->pNext;
            delete p;
            p = pNext;
            --numElements;
        }
        pTail->pNext = nullptr;

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
    auto itRHS = rhs.begin();
    iterator itLHS = begin();
    while (itRHS != rhs.end() && itLHS != end())
    {
        *itLHS = *itRHS;
        ++itRHS;
        ++itLHS;
    }
    if (itRHS != rhs.end())
    {
        while (itRHS != rhs.end())
        {
            push_back(*itRHS);
            ++itRHS;
        }
    }
    else if (rhs.size()==0)
    {
        clear();
    }
    else if (itLHS != end())
    {
        Node* p = itLHS.p;
        pTail = p->pPrev;
        Node* pNext = p->pNext;
        while (p != NULL)
        {
            pNext = p->pNext;
            delete p;
            p = pNext;
            --numElements;
        }
        pTail->pNext = nullptr;

    }
   return *this;
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
   Node* p = pHead;
   Node* pNext = nullptr;

   while (p)
   {
      pNext = p->pNext;
      delete p;
      p = pNext;
   }

   pHead = pTail = nullptr;
   numElements = 0;
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
   Node* pNew = new Node(data);
   pNew->pPrev = pTail;
   if (pTail)
   {
      pTail->pNext = pNew;
   }
   else
   {
      pHead = pNew;
   }
   pTail = pNew;
   numElements += 1;
}

template <typename T>
void list <T> ::push_back(T && data)
{
   Node* pNew = new Node(std::move(data));
   pNew->pPrev = pTail;
   if (pTail)
   {
      pTail->pNext = pNew;
   }
   else
   {
      pHead = pNew;
   }
   pTail = pNew;
   numElements += 1;
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
   Node* pNew = new Node(data);
   pNew->pNext = pHead;
      if (pHead)
      {
         pHead->pPrev = pNew;
      }
      else
      {
         pTail = pNew;
      }
   pHead = pNew;
   numElements += 1;
}

template <typename T>
void list <T> ::push_front(T && data)
{
   Node* pNew = new Node(std::move(data));
   pNew->pNext = pHead;
   if (pHead)
   {
      pHead->pPrev = pNew;
   }
   else
   {
      pTail = pNew;
   }
   pHead = pNew;
   numElements += 1;
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
   erase(rbegin());
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
   erase(begin());
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
   if (not empty())
   {
      return pHead->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
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
   if (not empty())
   {
      return pTail->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
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
   iterator itNext = end();

   if (not it.p) return itNext;

   if (it.p->pNext) 
   {
      it.p->pNext->pPrev = it.p->pPrev;
      itNext = it.p->pNext;
   }
   else
   {
      pTail = pTail->pPrev;
   }

   if (it.p->pPrev)
   {
      it.p->pPrev->pNext = it.p->pNext;
   }
   else
   {
      pHead = pHead->pNext;
   }

   delete it.p;
   numElements--;

   return itNext;
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
   Node* pNew = new Node(data);
   if (empty())
   {
      pHead = pTail = pNew;
      numElements = 1;
      return begin();
   }
   else if (it == end())
   {
      pTail->pNext = pNew;
      pNew->pPrev = pTail;
      pTail = pNew;
      numElements++;
      return iterator(pNew);
   }
   else
   {
      pNew->pPrev = it.p->pPrev;
      pNew->pNext = it.p;
      if (pNew->pPrev)
      {
         pNew->pPrev->pNext = pNew;
      }
      else
      {
         pHead = pNew;
      }

      if (pNew->pNext)
      {
         pNew->pNext->pPrev = pNew;
      }
      else
      {
         pTail = pNew;
      }
      numElements++;
      return iterator(pNew);
   }
}

template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
   T && data)
{
   Node* pNew = new Node(std::move(data));
   if (empty())
   {
      pHead = pTail = pNew;
      numElements = 1;
      return begin();
   }
   else if (it == end())
   {
      pTail->pNext = pNew;
      pNew->pPrev = pTail;
      pTail = pNew;
      numElements++;
      return iterator(pNew);
   }
   else
   {
      pNew->pPrev = it.p->pPrev;
      pNew->pNext = it.p;
      if (pNew->pPrev)
      {
         pNew->pPrev->pNext = pNew;
      }
      else
      {
         pHead = pNew;
      }

      if (pNew->pNext)
      {
         pNew->pNext->pPrev = pNew;
      }
      else
      {
         pTail = pNew;
      }
      numElements++;
      return iterator(pNew);
   }
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
   std::swap(lhs.pHead, rhs.pHead);
   std::swap(lhs.pTail, rhs.pTail);
   std::swap(lhs.numElements, rhs.numElements);
}


//#endif
}; // namespace custom
