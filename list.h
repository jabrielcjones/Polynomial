//  file name -- list.h
//  This file contains the doubly linked list class declaration.

#ifndef list_class_
#define list_class_

template <class ItemType>
class Node
{
   public:
      ItemType data;
      Node *back_link;
      Node *next_link;
};  // end Node

template<class ItemType>
class List
{
   private:
     int size;
     Node<ItemType> *head;
     Node<ItemType> *current;

   public:
     List();
     List(const List<ItemType>&);
     ~List();
     void makeEmpty();
     int isEmpty() const;
     int isFull() const;
     int length() const;
     void insertBefore(const ItemType &);
     void insertAfter(const ItemType &);
     void insertItem(const ItemType &);
     void deleteItem(const ItemType &);
     void resetList();
     void bottom();
     void advance();
     void moveback();
     ItemType retrieve();
};  // class List

#include "list.cpp"

#endif
