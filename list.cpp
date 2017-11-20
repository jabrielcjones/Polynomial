//  file name -- list.cpp
//  This file is the implementaion file for the doubly linked List class.

#include <stddef.h>                       // for NULL
#include <iostream>                       // for input/output
//#include "list.h"
using namespace std;


template <class ItemType>
List<ItemType>::List()
//  purpose -- initialize the list object
//  precondition -- none
//  postcondition -- size set to zero, use head to create a dummy
//                  node, and set both head and current point to the
//                  dummy node
{
   size = 0;
   head = new Node<ItemType>;
   head -> next_link = head;
   head -> back_link = head;
   current = head;
}  // constructor


template <class ItemType>
List<ItemType>::List(const List<ItemType>& source)
//  purpose -- copy the content of source to create a new List object.
//  precondition -- none
//  postcondition -- deep copy is performed to produce a copy of source.
{
   ItemType item;
   Node<ItemType> *temp;

   size = 0;
   head = new Node<ItemType>;
   head -> next_link = head;
   head -> back_link = head;
   current = head;

   temp = source.head -> next_link;
   for (int k = 1; k <= source.size; k++)
   {
      item = temp -> data;
      insertAfter(item);
      temp = temp -> next_link;
   } // for all nodes in source
}  // copy constructor


template <class ItemType>
List<ItemType>::~List()
//  purpose -- deallocate the spaces used to hold the list of nodes
//  precondition -- none
//  postcondition -- if list is not empty, the list nodes are freed
//                  from the heap.
{
   makeEmpty();
}  // end destructor


template <class ItemType>
void List<ItemType>::makeEmpty()
//  purpose -- deallocate the spaces used to hold the list of nodes
//  precondition -- none
//  postcondition -- if list is not empty, the list nodes are freed
//                  from the heap.
{
   Node<ItemType> *ptr;

   while (size != 0)
   {
      //cout << size << endl;
      ptr = head -> next_link;
      head -> next_link = ptr -> next_link;
      ptr -> next_link -> back_link = ptr -> back_link;
      delete ptr;
      size --;
   }  // while
   current = head;
}  // end makeEmpty


template <class ItemType>
int List<ItemType>::isFull() const
//  purpose -- check to see if any more space can be allocated for a
//             new node.
//  precondition -- none
//  postcondition -- if there is no more space available in the heap,
//                   1 is returned; otherwise 0 is returned.
{
   Node<ItemType> *ptr;

   ptr = new Node<ItemType>;
   if (ptr == NULL)
   {
      return 1;
   }
   else
   {
      delete ptr;
      return 0;
   }  // else
}  // end isFull


template <class ItemType>
int List<ItemType>::isEmpty() const
//  purpose -- check to see if the list is empty
//  precondition -- none
//  postcondition -- if list is empty, 1 is returned; otherwise 0 is
//                  returned.
{
   return (size == 0);
}  // end isEmpty


template <class ItemType>
int List<ItemType>::length() const
//  purpose -- return the length of the list.
//  precondition -- none
//  postcondition -- returns the number of nodes in the list.
{
   return size;
}  // end length


template <class ItemType>
void List<ItemType>::insertBefore(const ItemType &item)
//  purpose -- inset a new node before the current node.
//  precondition -- none.
//  postcondition -- the item is inserted before the current node of the
//                  list and the the size of the list is incremented
//                  by 1.
{
   Node<ItemType> *new_node;

   new_node = new Node<ItemType>;
   new_node -> data = item;
   new_node -> next_link = current;
   new_node -> back_link = current -> back_link;
   current -> back_link -> next_link = new_node;
   current -> back_link = new_node;
   current = new_node;
   size ++;
}  // end insertBefore


template <class ItemType>
void List<ItemType>::insertAfter(const ItemType &item)
//  purpose -- insert item to the list.
//  precondition -- none of the list nodes contains the same key value
//                  as that in item.
//  postcondition -- the item is inserted after the current node of the
//                  list and the the size of the list is incremented
//                  by 1.
{
   Node<ItemType> *new_node;

   new_node = new Node<ItemType>;
   new_node -> data = item;
   new_node -> back_link = current;
   new_node -> next_link = current -> next_link;
   current -> next_link -> back_link = new_node;
   current -> next_link = new_node;
   current = new_node;
   size ++;
}  // end insertAfter


template <class ItemType>
void List<ItemType>::insertItem(const ItemType &item)
//  purpose -- insert item to the list.
//  precondition -- none of the list nodes contains the same key value
//                  as that in item.
//  postcondition -- the item is inserted the beginning of the list
//                  and the the size of the list is incremented by 1.
{
   Node<ItemType> *new_node;

   new_node = new Node<ItemType>;
   new_node -> data = item;
   new_node -> next_link = head -> next_link;
   new_node -> back_link = head -> next_link -> back_link;
   head -> next_link -> back_link = new_node;
   head -> next_link = new_node;
   resetList();
   size ++;
}  // end insertItem


template <class ItemType>
void List<ItemType>::deleteItem(const ItemType &item)
//  purpose -- delete a node from the list
//  precondition --  list is not empty.
//  postcondition -- the current node is removed from the list and size of list is
//                   decremented by 1.
{
   if (!isEmpty())
   {
      current -> next_link -> back_link = current -> back_link;
      current -> back_link -> next_link = current -> next_link;
      Node<ItemType> *temp = current;
      current = temp -> next_link;
      temp -> next_link = NULL;
      temp -> back_link = NULL;
      delete temp;
   }
}  // end deleteItem


template <class ItemType>
void List<ItemType>::resetList()
//  purpose -- reset the current pointer so that it points to the
//             beginning of the list.
//  precondition -- none
//  postcondition -- holds the address of the first node if list is not
//                   empty; otherwise, it holds NULL value.
{
   current = head -> next_link;
}  // end resetList


template <class ItemType>
void List<ItemType>::bottom()
//  purpose -- reset the current pointer so that it points to the end
//             of the list.
//  precondition -- none
//  postcondition -- holds the address of the first node if list is not
//                  empty; otherwise, it holds NULL value.
{
   current = head -> back_link;
}  // end bottom


template <class ItemType>
void List<ItemType>::advance()
//  purpose -- advance the current pointer to next node.
//  precondition -- current pointer holds the address of a node.
//  postcondition -- advance the current pointer to the next node.
{
   if (current != head -> back_link)
      current = current -> next_link;
   else
      current = head -> next_link;
}  // end advance


template <class ItemType>
void List<ItemType>::moveback()
//  purpose -- move the current pointer to previous node.
//  precondition -- current pointer holds the address of a node.
//  postcondition -- move the current pointer to the previous node.
{
   if (current != head -> next_link)
      current = current -> back_link;
   else
      current = head -> back_link;
}  // end moveback


template <class ItemType>
ItemType List<ItemType>::retrieve()
//  purpose -- retrieve the current node data from the list.
//  precondition -- current pointer does not point to the last node of
//                  the list.
//  postcondition -- the data of the node pointed to by the
//                  current pointer is retrieved and copied to item.
{
   return (current -> data);
}  // end retrieve
