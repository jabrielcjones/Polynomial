// filename -- driver.cpp
// Client file for the Polynomial class

#include <iostream>
#include <fstream>
#include "Polynomial.h"

using namespace std;

// ================ CONSTANTS ================= //
const int NAMESIZE = 100;

// ================ FUNCTION PROTOTYPES ======= //
   /** Reads in the name of the file and opens it if its valid.
   * @param inFile an ifstream object.
   * @pre none.
   * @post file is opened.
   */
   void openFile(ifstream&);

   /** Performs necessary operations on the data from a file.
    * @param inFile an ifstream object.
    * @param resultant a pointer of the Polynomial type.
    * @pre none.
    * @post all data from file has been read.
    */
   void processData(ifstream&, Polynomial*);
   
   /** Adds two Polynomial objects.
    * @param aPolynomial a Polynomial object.
    * @param bPolynomial a Polynomial object.
    * @param resultant a Polynomial object.
    * @pre none.
    * @post Two Polynomial objects are added and stored.
    */
   void add(Polynomial*, Polynomial*, Polynomial*);
   
    /** Subtracts two Polynomial objects.
    * @param aPolynomial a Polynomial object.
    * @param bPolynomial a Polynomial object.
    * @param resultant a Polynomial object.
    * @pre none.
    * @post Two Polynomial objects are subtracted and stored.
    */
   void subtract(Polynomial*, Polynomial*, Polynomial*);

   /** Reads a polynomial from a file.
    * @param inFile an ifstream object.
    * @param polynomial a Polynomial object.
    * @pre none.
    * @post Polynomial is read from the file.
    */
   void getPolynomial(ifstream&, Polynomial*);
   
    /** Displays a Polynomial object.
    * @param polynomialPtr a pointer of the Polynomial type.
    * @pre none.
    * @post a Polynomial object is ouputed.
    */
   void displayPolynomial(Polynomial*);


int main()
{
   ifstream inFile;
   Polynomial *resultant = new Polynomial;

   openFile(inFile);
   processData(inFile, resultant);
   
   return 0;
}



void openFile(ifstream& inFile)
{
   char file_name[NAMESIZE];

   do
   {
      cout << "Please enter file name:"<< endl;
      cin  >> file_name;
      inFile.open(file_name);

      if(!inFile)
      {
         cout << file_name
              << " could not be opened."
              << endl;
      }
   }while(!inFile);
}  // end of openFile function


void processData(ifstream& inFile, Polynomial *resultant)
{
   char           operation;
   int            temp;
   Polynomial*    aPolynomial = new Polynomial;
   Polynomial*    bPolynomial = new Polynomial;

   /** Get Operation */
   inFile >> operation;
   
   while (!inFile.eof())
   {

      /** First Polynomial */
      getPolynomial(inFile, aPolynomial);

      /** Second Polynomial */
      getPolynomial(inFile, bPolynomial);

      /** Perform Operation */
      if (operation == '+')
      {
         add(aPolynomial, bPolynomial, resultant);
      }
      else if (operation == '-')
      {
         subtract(aPolynomial, bPolynomial, resultant);
      }
      else
      {
         cout << "Invalid Operation." << endl;
      }

      /** Output Resultant */
      displayPolynomial(resultant);

      aPolynomial -> makeEmpty();
      bPolynomial -> makeEmpty();
      
      /** Get Operation */
      inFile >> operation;
   }
}


void add(Polynomial* aPolynomial, Polynomial* bPolynomial, Polynomial* resultant)
{
   *resultant = *aPolynomial + *bPolynomial;
}


void subtract(Polynomial* aPolynomial, Polynomial* bPolynomial, Polynomial* resultant)
{
   *resultant = *aPolynomial - *bPolynomial;
}


void getPolynomial(ifstream& inFile, Polynomial *polynomial)
{
   int   temp;
   bool  isNumLeft = true;
   
   inFile >> temp;
   polynomial -> insertItem(temp);
   
   while (isNumLeft)
   {
      if(inFile.peek() == '|')
      {
         inFile.ignore(1);
         inFile >> temp;
         polynomial -> insertAfter(temp);
      }
      else
      {
         isNumLeft = false;
      }
   }
}


void displayPolynomial(Polynomial* polynomial)
{
   polynomial -> display();
}
