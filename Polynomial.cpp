//  file name -- Polynomial.cpp
//  This file is the implementaion file for the
//  Polynomial class.

#include <stddef.h>                   // for NULL
#include <iostream>                   // for input/output
#include "Polynomial.h"               // for Polynomial class
using namespace std;

Polynomial::Polynomial()
           : List<double>()
{
}  // constructor

Polynomial::Polynomial(const Polynomial &source)
           :List<double>(source)
{
}


int Polynomial::getOrder()
{   
   return length() - 1;
}


Polynomial& Polynomial::operator+(Polynomial &other)
{
   Polynomial *resultant = new Polynomial;
   int index = 1;
   int otherIndex = 1;

   resetList();
   other.resetList();

   if (getOrder() > other.getOrder())
   {
      add(other, resultant, other.length(), index);

      while (index <= length())
      {
         resultant -> insertAfter(retrieve());
         advance();
         ++index;
      }
   }
   else if (getOrder() < other.getOrder())
   {
      add(other, resultant, length(), otherIndex);

      while (otherIndex <= other.length())
      {
         resultant -> insertAfter(other.retrieve());
         other.advance();
         ++otherIndex;
      }
   }
   else
   {
      add(other, resultant, length(), index);
   }

   return *resultant;
}


Polynomial& Polynomial::operator-(Polynomial &other)
{
    Polynomial *resultant = new Polynomial;
   int index = 1;
   int otherIndex = 1;

   resetList();
   other.resetList();

   if (getOrder() > other.getOrder())
   {
      subtract(other, resultant, other.length(), index);

      while (index <= length())
      {
         resultant -> insertAfter(retrieve());
         advance();
         ++index;
      }
   }
   else if (getOrder() < other.getOrder())
   {
      subtract(other, resultant, length(), otherIndex);

      while (otherIndex <= other.length())
      {
         resultant -> insertAfter(changeSign(other));
         other.advance();
         ++otherIndex;
      }
   }
   else
   {
      subtract(other, resultant, length(), index);
   }

   return *resultant;
}


int Polynomial::operator==(Polynomial &other)
{
   bool isEqual = true;
   int index = 1, otherIndex = 1;

   resetList();
   other.resetList();
   while (index <= length()
          && otherIndex <= other.length()
          && isEqual)
   {
      if (retrieve() != other.retrieve())
         isEqual = false;

      
      advance();
      other.advance();
      ++index;
      ++otherIndex;
   }

   if (isEqual)
      return 1;
   else
      return 0;
}


Polynomial& Polynomial::operator=(Polynomial &other)
{
   makeEmpty();
   other.resetList();
   for (int i = 1; i <= other.length(); ++i)
   {
      insertAfter(other.retrieve());
      other.advance();
   }
}


void Polynomial::display()
{
   resetList();
   
   for (int i = 1; i <= length(); ++i)
   {
      if (retrieve() != 0)
      {
         if (i == 1)
         {
            cout << retrieve();
         }
         else if (i == 2)
         {
            cout << showpos
                 << retrieve()
                 << "*x";
         }
         else
         {
            cout << showpos
                 << retrieve();
            cout << noshowpos
                 << "*x**"
                 << i - 1;
         }
      }
      advance();
   }
   cout << endl << endl;
}


void Polynomial::add(Polynomial& object, Polynomial *sum, int upperBound, int& index)
{   
   for (int i = 1; i  <= upperBound; ++i)
   {
      sum -> insertAfter(retrieve() + object.retrieve());

      advance();
      object.advance();
      ++index;
   }
}


void Polynomial::subtract(Polynomial& object, Polynomial *diff, int upperBound, int& index)
{
   for (int i = 1; i  <= upperBound; ++i)
   {
      diff -> insertAfter(retrieve() + changeSign(object));

      advance();
      object.advance();
      ++index;
   }
}



int Polynomial::changeSign(Polynomial& object)
{
   return (object.retrieve() * (-1));
}

