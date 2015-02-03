
//
//  main.cpp
//  SueC2Lab1
//
//  Created by cj on 1/29/15.
//  Copyright (c) 2015 KickinEspresso. All rights reserved.
//

//TODO: Compile instructions for Unix
//TODO: Test cases with assert
//TODO: Test case with his example
//TODO: Does not account for array length of 0

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include <assert.h>
#include <vector>

using namespace std;

//Constants
const int defaultSize = 10;
const int minSize = 0;
const int maxSize = 100;
const int kDefaultValue = -1;



//Curtousey of http://www.cplusplus.com/forum/windows/88843/
//String Sample Context
static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

//Length of the string sample context
int stringLength = sizeof(alphanum) - 1;

// Random Character Generator Function
// returns a random character
char genRandomChar(){
    return alphanum[rand() % stringLength];
}

//Helper Functions
//Creates & returns random string to specified length
string generateRandomStringOfLength(int length){
    string myGeneratedString;
    for (int i = 0; i < length; i ++){
        myGeneratedString += genRandomChar();
    }
    return myGeneratedString;
}

//Class Template of Element for each item
template<class Element>
class SmcArray{
    
public:
    SmcArray(); // Default Constructor
    SmcArray(int s); //  Constructor with params
    ~SmcArray(); // Deconstructor
    
    int getSize(); // Get size of array
    void pushItem(Element value); //inserts item on end of the array
    void setItem(Element value, int index); //sets an item  (overwrites) at given index
    Element getItem(int index); //retrieves an item at a given index - This item can be of Type Element, which can be several different types
    void insertItem(Element value, int index, int s); //inserts an item at a given index
    void removeItem(int index); // Delete array item
    void replaceItemAt(int index, Element value); //replace value at a given index
    void printArray(bool linear); // Print Array
    void setDefault(Element value); //Sets a default value for out of bounds index expansions via changeSize
    Element getDefault(); //Returns the default value
    void changeSize(int newSize); //Changes the array size
    
private:
    int size; // Size of array (elements)
    Element * items; //Array of items of type element
    Element defaultValue;// Default value
    void allocateArray();//Allocates an array of given size
    void copyArrayIncreasedSize(int s); //Copies an array with increased size
    void copyArrayDecreasedSizeby1(int , int); //Decreases the size by 1 and leaves out a specific index;
    bool checkIndexBounds(int index);//Checks the array is within bounds
};

//Default Constructor
template <class Element>
SmcArray<Element>::SmcArray(){
    //Set the array using the defaults
    this->size = defaultSize;
    
    //Allocate an array of this->size
    this->allocateArray();
    this->defaultValue = kDefaultValue;
}

//Constructor with params
template <class Element>
SmcArray<Element>::SmcArray(int s){
    this->size = s;
    
    //Allocate an array of this->size
    this->allocateArray();
    this->defaultValue = kDefaultValue;
}

//Deletes the items in aray
template <class Element>
SmcArray<Element>::~SmcArray(){
    delete [] this->items;
}

//Allocates an array of given size
template <class Element>
void SmcArray<Element>::allocateArray(){
    //Allocate an array of this->size
    this->items = new Element[this->size];
}

//Gets size of the array
template <class Element>
int SmcArray<Element>::getSize(){
    return this->size;
}

//Add an item to the end of the array
template <class Element>
void SmcArray<Element>::pushItem(Element value){

    //Increase the size of array
    this->copyArrayIncreasedSize(this->size + 1);
    
    //Add our new value into the last slot in the array
    this->items[size - 1] = value;
    
}

//sets an item in the array (overwrite)
template <class Element>
void SmcArray<Element>::setItem(Element value, int index){
    
    //Check to see if the index can be written to/if the index is a valid index
    if(this->checkIndexBounds(index)){
        
        //Write to the array
        this->items[index] = value;
        
    }else if(index > this->size-1){
        
        //Two Routes can be taken
        //1st -  Use helper function pushItem() to add to end of array
        //this->pushItem(value);  //For the record, this method was a better option.
        //2nd - Adjust the size, then set the item
        this->changeSize(this->size+1); //Increase the size by 1
        this->setItem(value,this->size-1); //Recursive Call, use "this->size-1" in the event that index is n+2 greater than the size of the original size of the array
    }else{
        //Item is not within the bounds of the array
        //Oh no!! Help
        cerr << "Inserted item is not within the bounds of the array\n";
    }
}

//gets an item in the array and checks to see if the index is within bounds
template <class Element>
Element SmcArray<Element>::getItem(int index){
    //Check to see if the index can be retrieved
    if(this->checkIndexBounds(index)){
        
        //Write to the array
        return this->items[index];
        
    }else{
        //Even though this will return the default value the user is prompted with a message indicating that a default value has been returned
        cerr << __PRETTY_FUNCTION__ << ": Returning Default Value\n ";//_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
        
        //TODO: setting with type
        return this->defaultValue;
    }
}

//insert an item to the at the given index of the array
template <class Element>
void SmcArray<Element>::insertItem(Element value, int index, int s){
    
    //extend the array by 1
    //update the size by adding 1 and inserts the value into the array
    
    //Checks that within bounds
    if ((s >= this->size) && s < maxSize){
        
        int * newArray = new int[s+1];
        
        //Copy array that is increased by 1 at given index from the original array into the new array
        if (index < 0 || index >= size+1) cout << "The index of the item to be removed is out of range." << endl;
        else{
            //sets the values in array before the inserted value
            for (int i = 0; i <= index; i++) newArray[i] = items[i];
            
            //inserts the value after the given index
            if (int i = index+1) newArray[i] = value;
            
            //sets the values in the array after the inserted value
            for (int i = index+1; i <= this->size; i++) newArray[i+1]=items[i];
        }
        
        //Deallocate old memory
        delete [] this->items;
        
        //Copy to new pointer
        this->items = newArray;
        this->size = s+1;
        
    }else{
        cerr << "Oh no! My program is crashing\n"; //Error statement
        throw "array out of bounds exception";
    }
}

//Remove an item at a given index
template <class Element>
void SmcArray<Element>::removeItem(int index){
    
    //Remove 1 item from the array
    //Decrease the size of the array
    if (index < 0 || index >=size) cout << "The index of the item to be removed is out of range." << endl;
    else{
        for (int i = index; i < this->size -1; i++)
            items[i] = items[i+1];
        this->size = size-1;
    }
}

//Replaces a value at a given index
template <class Element>
void SmcArray<Element>::replaceItemAt(int index, Element value){
    
    if (index < 0 || index >=size) cout << "The index of the item to be removed is out of range." << endl;
    else{
        for (int i = index; i < this->size; i++)
            if (int i = index) items[i] = value;
    }
}

//Prints the array
template <class Element>
void SmcArray<Element>::printArray(bool linear){
    
    if(linear){
        for (int i=0; i < this->size; i++){
            cout << this->items[i] << " ";
        }
    }else{
        //Prints what is in my array
        //loop through an print each item
        for (int i=0; i < this->size; i++){
            cout << "Index is: " << i << " Array value is: " << this->items[i] << endl;
        }
    }
   
    cout << endl;
}
//TODO: Comments
template <class Element>
void SmcArray<Element>::copyArrayIncreasedSize(int s){
    //original array 'this->items'
    //create a new array
    
    //TODO: refactor and rename this to change size
    
    //Check to see if new size is within the minSize And MaxSize
    //check if the new size is greater than the existing size
    if ((s > this->size) && s < maxSize){
        
        Element * newArray = new Element[s];
        
        //Copy everything from the original array into the new array
        for (int i = 0; i < this->size; i++){
            newArray[i] = this->items[i];
        }
        
        //Deallocate old memory
        delete [] this->items;
        
        //Copy to new pointer
        this->items = newArray;
        this->size = s;
        
    }else{
        cerr << "Oh no! My program is crashing\n";
        throw "array out of bounds exception";
    }
}
//TODO: Comments
template <class Element>
void SmcArray<Element>::copyArrayDecreasedSizeby1(int s, int index){
    //TODO:
    //if ( i != index) --> copy it ... else --> (if it does equal index... keeps going.)
    //Check to see if new size is within the minSize And MaxSize
    //check if the new size is greater than the existing size
    
    if (this->checkIndexBounds(index)){
        
        //TODO: Comments
        int * newArray = new int[s];
        
        //Copy array that is decreased by 1 at given index from the original array into the new array
        for (int i = 0; i < s; i++){
            if(i != index){
                newArray[i] = this->items[i];
            }
        }
        
        //Deallocate old memory
        delete [] this->items;
        
        //Copy to new pointer
        this->items = newArray;  ///TODO: Comment
        this->size = s;
        
    }else{
        cerr << __PRETTY_FUNCTION__ << " Oh no! My program is crashing\n";////_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
        throw "array out of bounds exception";
    }
}


//Checks if the index is within the bounds of the array
template <class Element>
bool SmcArray<Element>::checkIndexBounds(int index){
    if(index >= minSize && index < this->size){
        return true;
    }else{
        return false;
    }
}

//Sets a default value for out of bounds index expansions via changeSize
template <class Element>
void SmcArray<Element>::setDefault(Element value){
    this->defaultValue = value;
}
//Returns the default value
template <class Element>
Element SmcArray<Element>::getDefault(){
    return this->defaultValue;
}

//TODO: Comments
template <class Element>
void SmcArray<Element>::changeSize(int newSize){
    //Check to make sure there is a default value
    //TODO: Come back to this issue when we get started with TYPES
    //if(this->defaultValue == NULL){
    if (/* DISABLES CODE */ (false)) {
        cerr << __PRETTY_FUNCTION__ << " a default value has not been set\n";////_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
    }
    
    //First check to make sure the new size is within the bounds of the system
    if(newSize > minSize && newSize < maxSize){
        
        
        //TODO: Comment
        Element * newArray = new Element[newSize];
        
        //Copy array that is decreased by 1 at given index from the original array into the new array
        for (int i = 0; i < newSize; i++){
            //if expanding the array  (10 -> 15), check to see if the current position is going to be outside
            //of the index of the original items array. If it is use the default value
            if(i >= this->size){
                newArray[i] = defaultValue;
            }else{
                newArray[i] = this->items[i];
            }
        }
        
        //Deallocate old memory
        delete [] this->items;
        
        //Copy to new pointer
        this->items = newArray;
        this->size = newSize;
        
    }else{
        cerr << __PRETTY_FUNCTION__ << " Size changed to a illegal size\n"; //_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
    }
}



//TODO: testing we will do this later
//  insertings, removing items
// default settings... what about negatives?

//Test Case One tests adding items to the array
void testCaseOne(){

    cout << __PRETTY_FUNCTION__ << endl;
    
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray<int>* testArray = new SmcArray<int>(myArraySize);
    // Add values to our array
    for (int i = 0; i < testArray->getSize(); i++){
        testArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << __PRETTY_FUNCTION__ << " - Prints out the array before performing an operation." << endl;
    testArray->printArray(true);
    
    //Items to be added to the array.
    testArray->pushItem(55);
    testArray->pushItem(12);
    testArray->pushItem(43);
    testArray->pushItem(21);
    testArray->pushItem(-21);
    testArray->setItem(88, 44);
    cout << __PRETTY_FUNCTION__ << " - Prints out the array with added items." << endl;
    
    testArray->printArray(true);
    
    //Assertion of correctness
    SmcArray<int>* resultArray = new SmcArray<int>(myArraySize+6);
    resultArray->setItem(0, 0);
    resultArray->setItem(1, 1);
    resultArray->setItem(2, 2);
    resultArray->setItem(3, 3);
    resultArray->setItem(4, 4);
    resultArray->setItem(5, 5);
    resultArray->setItem(6, 6);
    resultArray->setItem(7, 7);
    resultArray->setItem(55, 8);
    resultArray->setItem(12, 9);
    resultArray->setItem(43, 10);
    resultArray->setItem(21, 11);
    resultArray->setItem(-21, 12);
    resultArray->setItem(88, 13);
    
    for(int i = 0;i < testArray->getSize(); i++){
        assert(testArray->getItem(i) == resultArray->getItem(i));
    }
    
    cout << __PRETTY_FUNCTION__ << " - Test Completed Successfully" << endl;
    
}

void testCaseOneFloat(){
    
    cout << __PRETTY_FUNCTION__ << endl;
    
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray<float>* testArray = new SmcArray<float>(myArraySize);
    // Add values to our array
    for (int i = 0; i < testArray->getSize(); i++){
        testArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << __PRETTY_FUNCTION__ << " - Prints out the array before performing an operation." << endl;
    testArray->printArray(true);
    
    //Items to be added to the array.
    testArray->pushItem(.25);
    testArray->pushItem(12);
    testArray->pushItem(1.01);
    testArray->pushItem(21);
    testArray->pushItem(-21.2);
    testArray->setItem(88, 44);
    cout << __PRETTY_FUNCTION__ << " - Prints out the array with added items." << endl;
    
    testArray->printArray(true);
    
    //Assertion of correctness
    SmcArray<float>* resultArray = new SmcArray<float>(myArraySize+6);
    resultArray->setItem(0, 0);
    resultArray->setItem(1, 1);
    resultArray->setItem(2, 2);
    resultArray->setItem(3, 3);
    resultArray->setItem(4, 4);
    resultArray->setItem(5, 5);
    resultArray->setItem(6, 6);
    resultArray->setItem(7, 7);
    resultArray->setItem(0.25, 8);
    resultArray->setItem(12, 9);
    resultArray->setItem(1.01, 10);
    resultArray->setItem(21, 11);
    resultArray->setItem(-21.2, 12);
    resultArray->setItem(88, 13);
    
    for(int i = 0; i < testArray->getSize(); i++){
        //cout << __PRETTY_FUNCTION__ << " - Test Array Item: " << testArray->getItem(i) << " - Result Array Item: " <<resultArray->getItem(i) << endl;
        assert(testArray->getItem(i) == resultArray->getItem(i));
        /*
        if(){
            cerr << __PRETTY_FUNCTION__ << " - Test Array Item: " << testArray->getItem(i) << " - Result Array Item: " <<resultArray->getItem(i) << endl;
        }
         */
    }
    
    cout << __PRETTY_FUNCTION__ << " - Test Completed Successfully" << endl;
    
}


void testCaseOneDouble(){
    
    cout << __PRETTY_FUNCTION__ << endl;
    
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray<double>* testArray = new SmcArray<double>(myArraySize);
    // Add values to our array
    for (int i = 0; i < testArray->getSize(); i++){
        testArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << __PRETTY_FUNCTION__ << " - Prints out the array before performing an operation." << endl;
    testArray->printArray(true);
    
    //Items to be added to the array.
    testArray->pushItem(.25);
    testArray->pushItem(12);
    testArray->pushItem(1.01);
    testArray->pushItem(21);
    testArray->pushItem(-21.2);
    testArray->setItem(88, 44);
    cout << __PRETTY_FUNCTION__ << " - Prints out the array with added items." << endl;
    
    testArray->printArray(true);
    
    //Assertion of correctness
    SmcArray<double>* resultArray = new SmcArray<double>(myArraySize+6);
    resultArray->setItem(0, 0);
    resultArray->setItem(1, 1);
    resultArray->setItem(2, 2);
    resultArray->setItem(3, 3);
    resultArray->setItem(4, 4);
    resultArray->setItem(5, 5);
    resultArray->setItem(6, 6);
    resultArray->setItem(7, 7);
    resultArray->setItem(0.25, 8);
    resultArray->setItem(12, 9);
    resultArray->setItem(1.01, 10);
    resultArray->setItem(21, 11);
    resultArray->setItem(-21.2, 12);
    resultArray->setItem(88, 13);
    
    for(int i = 0;i < testArray->getSize(); i++){
        //cout << __PRETTY_FUNCTION__ << " - Test Array Item: " << testArray->getItem(i) << " - Result Array Item: " <<resultArray->getItem(i) << endl;
        assert(testArray->getItem(i) == resultArray->getItem(i));
        /*
         if(){
         cerr << __PRETTY_FUNCTION__ << " - Test Array Item: " << testArray->getItem(i) << " - Result Array Item: " <<resultArray->getItem(i) << endl;
         }
         */
    }
    
    cout << __PRETTY_FUNCTION__ << " - Test Completed Successfully" << endl;
    
}



void testCaseOneString(){
    
    cout << __PRETTY_FUNCTION__ << endl;
    int myArraySize = 8;
    
    //Setup test data
    vector <string> testData;
    for (int i = 0; i < myArraySize+6; i++){
        testData.push_back(generateRandomStringOfLength(i+1));
    }
    
    //Create an INSTANCE OBJECT of our class
    SmcArray<string>* testArray = new SmcArray<string>(myArraySize);
    // Add values to our array
    for (int i = 0; i < testArray->getSize(); i++){
        testArray->setItem(testData.at(i),i);
    }
    
    //Prints what is in my array
    cout << __PRETTY_FUNCTION__ << " - Prints out the array before performing an operation." << endl;
    testArray->printArray(true);
    
    //Items to be added to the array.
    for (int i = 8; i < myArraySize+6; i++){
        testArray->pushItem(testData.at(i));
    }
    cout << __PRETTY_FUNCTION__ << " - Prints out the array with added items." << endl;
    
    testArray->printArray(true);
    
    //Assertion of correctness
    SmcArray<string>* resultArray = new SmcArray<string>(myArraySize+6);
    for (int i = 0; i < myArraySize+6; i++){
        string temp = testData.at(i);
        resultArray->setItem(temp, i);
    }
    
    for(int i = 0;i < testArray->getSize(); i++){
        //cout << __PRETTY_FUNCTION__ << " - Test Array Item: " << testArray->getItem(i) << " - Result Array Item: " <<resultArray->getItem(i) << endl;
        assert(testArray->getItem(i) == resultArray->getItem(i));
        /*
         if(){
         cerr << __PRETTY_FUNCTION__ << " - Test Array Item: " << testArray->getItem(i) << " - Result Array Item: " <<resultArray->getItem(i) << endl;
         }
         */
    }
    
    cout << __PRETTY_FUNCTION__ << " - Test Completed Successfully" << endl;
    
}

void testCaseOneChar(){
    
    cout << __PRETTY_FUNCTION__ << endl;
    int myArraySize = 8;
    
    //Setup test data
    vector <char> testData;
    for(int i = 0; i < myArraySize + 6; i++){
        testData.push_back(genRandomChar());
    }
    
    //Create an INSTANCE OBJECT of our class
    SmcArray<char>* testArray = new SmcArray<char>(myArraySize);
    // Add values to our array
    for (int i = 0; i < testArray->getSize(); i++){
        testArray->setItem(testData.at(i),i);
    }
    
    //Prints what is in my array
    cout << __PRETTY_FUNCTION__ << " - Prints out the array before performing an operation." << endl;
    testArray->printArray(true);
    
    //Items to be added to the array.
    for (int i = 8; i < myArraySize+6; i++){
        testArray->pushItem(testData.at(i));
    }
    cout << __PRETTY_FUNCTION__ << " - Prints out the array with added items." << endl;
    
    testArray->printArray(true);
    
    //Assertion of correctness
    SmcArray<char>* resultArray = new SmcArray<char>(myArraySize+6);
    for (int i = 0; i < myArraySize+6; i++){
        char temp = testData.at(i);
        resultArray->setItem(temp, i);
    }

    
    for(int i = 0;i < testArray->getSize(); i++){
        //cout << __PRETTY_FUNCTION__ << " - Test Array Item: " << testArray->getItem(i) << " - Result Array Item: " <<resultArray->getItem(i) << endl;
        assert(testArray->getItem(i) == resultArray->getItem(i));
        /*
         if(){
         cerr << __PRETTY_FUNCTION__ << " - Test Array Item: " << testArray->getItem(i) << " - Result Array Item: " <<resultArray->getItem(i) << endl;
         }
         */
    }
    
    cout << __PRETTY_FUNCTION__ << " - Test Completed Successfully" << endl;
    
}


//Test Case Two tests changing size to the array
void testCaseTwo(){
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray<int>* myArray = new SmcArray<int>(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array.
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray(true);
    
    //Push items
    myArray->pushItem(55);
    myArray->pushItem(12);
    myArray->pushItem(43);
    myArray->pushItem(21);
    myArray->pushItem(-21);

    //Prints what is in new array with added items.
    cout << "Prints out the array with push items" << endl;
    myArray->printArray(true);
    
    //Prints array with changed size.
    myArray->changeSize(5);
    cout << "Prints out the array with changed size when new array is smaller than original array." << endl;
    myArray->printArray(true);
    
    //Prints array with changed size.
    cout << "Prints out the array with changed size when new array is larger than orginal array. Default value is set to -1." << endl;
    myArray->changeSize(10);
    myArray->printArray(true);
    
}

//Test Case Three tests inserting an item at a given index
void testCaseThree(){
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray<int>* myArray = new SmcArray<int>(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray(true);
    
    
    //Prints array with inserted item
    myArray->insertItem(55, 3, myArray->getSize());
    cout << "Prints out the array with inserted item." << endl;
    myArray->printArray(true);
    
    //Prints what is in my array
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray(true);
    
    
    //Prints array with inserted item
    myArray->insertItem(-10, 6, myArray->getSize());
    cout << "Prints out the array with inserted item." << endl;
    myArray->printArray(true);
    
}

//Test Case Four tests removing an item at a given index
void testCaseFour(){
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray<int>* myArray = new SmcArray<int>(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray(true);
    
    //Removes an item
    myArray->removeItem(3);
    cout << "The array with item removed." << endl;
    //Prints the array with item removed
    myArray->printArray(true);
    
    
    //Prints what is in my array
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray(true);
    
    // Removes an item
    myArray->removeItem(0);
    cout << "The array with item removed." << endl;
    //Prints the array with item removed
    myArray->printArray(true);
    
}

//Test Case Five tests replacing a value at a given index
void testCaseFive(){
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray<int>* myArray = new SmcArray<int>(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray(true);
    
    //Replace Item at given index
    myArray->replaceItemAt(5, 253);
    cout << "An item's value in the array is replaced at given index." << endl;
    //Prints the array with value replaced at given index
    myArray->printArray(true);
}

//TestData
//ExpectedTestResults

int main(int argc, const char * argv[]){
    //Calling Test cases
    testCaseOne(); //Test Case One tests adding items to the array
    testCaseOneFloat();
    testCaseOneDouble();
    testCaseOneString();
    testCaseOneChar();
    testCaseTwo(); //Test Case Two tests changing size to the array
    testCaseThree(); //Test Case Three tests inserting an item at a given index
    testCaseFour(); //Test Case Four tests removing an item at a given index
    testCaseFive(); //Test Case Five tests replacing a value at a given index
    return 0;
}

////////////////


//===============
//== Test Case 1: Insert into Array with data type INT
//== Result 1
//== Test Case 1: Insert into Array with data type DOUBLE
//== Results 2
//== Test Case 1: Complete
//===============
//== Test Case 2: Insert into Array with data type INT
//== Result 1
//== Test Case 2: Complete

/*
 
 Assignment 1 - Flexible Resizable Array
 
 Create a class that implements a safe resizable array, which can
 contain data of any single type. It should be easy and convenient
 to use.
 
 + Use templates so that the data stored in the arrays can be of any type.
 
 + Provide a "default" (no parameter) constructor that sets the array to
 some reasonable default initial size.
 
 + Provide another constructor with one int parameter that allows the
 programmer to specify the original size.
 
 so these would all be possible declarations:
 
 { Array<int> A;
 Array<string> B, C;
 Array<double> D(100);
 
 + Provide a destructor that ensures all heap memory is released when
 an Array object is destroyed.
 
 + Provide set and get methods that allow the programmer to put data into
 and take data from an Array object, e.g.
 
 cout << B.get(3)     is like     cout << B[3]
 D.set(i, x*y)        is like     D[i] = x*y
 
 + Make sure your set and get methods check that the index used (3 and i
 in the above examples) are properly in range.
 
 + Provide a change_size(int newsize) method that changes the size of the
 array, preserving as much of the original data as possible, and carefully
 recycling any heap memory that is no longer needed.
 
 + Make your set method automatically use the change_size method if ever
 the index used is too big.
 
 + Provide a get_size() method that returns the current size of the array.
 
 + Provide a set_default method that makes the Array object remember a
 special default value. Whenever the get method is used with an index
 that is out of bounds, it should return the default value (if one has
 been set) instead of reporting an error.
 
 + Test it.
 
 Here is a dull example
 
 { Array<int> Xvals(10);
 Array<double> Yvals;
 
 cout << "size is " << Xvals.get_size() << "\n";
 
 for (int i = 0; i < 30; i += 1)
 { int x = i*3+1;
 double y = sin(pi/x);
 Xvals.set(i, x);
 Yvals.set(i, y); }
 
 cout << "size is " << Xvals.get_size() << "\n";
 
 for (int i = 0; i <= Xvals.get_size(); i += 1)
 cout << i << ": x = " << Xvals.get(i) << ", sin(pi/x) = " << Yvals.get(i) << "\n"; }
 
 It should produce output a lot like this (not necessarily identical)
 
 size is 10
 size is 30
 0: x = 1, sin(pi/x) = 1.22461e-16
 1: x = 4, sin(pi/x) = 0.707107
 2: x = 7, sin(pi/x) = 0.433884
 3: x = 10, sin(pi/x) = 0.309017
 4: x = 13, sin(pi/x) = 0.239316
 5: x = 16, sin(pi/x) = 0.19509
 6: x = 19, sin(pi/x) = 0.164595
 7: x = 22, sin(pi/x) = 0.142315
 8: x = 25, sin(pi/x) = 0.125333
 9: x = 28, sin(pi/x) = 0.111964
 10: x = 31, sin(pi/x) = 0.101168
 11: x = 34, sin(pi/x) = 0.0922684
 12: x = 37, sin(pi/x) = 0.0848059
 13: x = 40, sin(pi/x) = 0.0784591
 14: x = 43, sin(pi/x) = 0.0729953
 15: x = 46, sin(pi/x) = 0.0682424
 16: x = 49, sin(pi/x) = 0.0640702
 17: x = 52, sin(pi/x) = 0.0603785
 18: x = 55, sin(pi/x) = 0.0570888
 19: x = 58, sin(pi/x) = 0.0541389
 20: x = 61, sin(pi/x) = 0.0514788
 21: x = 64, sin(pi/x) = 0.0490677
 22: x = 67, sin(pi/x) = 0.0468723
 23: x = 70, sin(pi/x) = 0.0448648
 24: x = 73, sin(pi/x) = 0.0430222
 25: x = 76, sin(pi/x) = 0.041325
 26: x = 79, sin(pi/x) = 0.0397565
 27: x = 82, sin(pi/x) = 0.0383027
 28: x = 85, sin(pi/x) = 0.0369515
 29: x = 88, sin(pi/x) = 0.0356923
 Error - index out of bounds.
*/