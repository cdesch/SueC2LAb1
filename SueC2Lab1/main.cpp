
//
//  main.cpp
//  SueC2Lab1
//
//  Created by cj on 1/29/15.
//  Copyright (c) 2015 KickinEspresso. All rights reserved.
//


//TODO: Does not account for array length of 0

#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
using namespace std;

//Constants
const int defaultSize = 10;
const int minSize = 0;
const int maxSize = 100;
const int kDefaultValue = -1;

//template<class element>
//TODO: We will do this later
class SmcArray{
    
public:
    SmcArray(); // Default Constructor
    SmcArray(int s); //  Constructor with params
    ~SmcArray(); // Deconstructor
    
    int getSize(); // Get size of array
    void pushItem(int value); //inserts item on end of the array
    void setItem(int value, int index); //sets an item  (overwrites) at given index
    int getItem(int index); //retrieves an item at a given index
    void insertItem(int value, int index, int s); //inserts an item at a given index
    void removeItem(int index); // Delete array item
    void replaceItemAt(int index, int value); //replace value at a given index
    void printArray(); // Print Array
    void setDefault(int value); //Sets a default value for out of bounds index expansions via changeSize
    int getDefault(); //Returns the default value
    void changeSize(int newSize); //Changes the array size
    
private:
    int size; // Size of array (elemets)
    int * items;
    int defaultValue;// Default value
    void allocateArray();//Allocates an array of given size
    void copyArrayIncreasedSize(int s); //Copies an array with increased size
    void copyArrayDecreasedSizeby1(int , int); //Decreases the size by 1 and leaves out a specific index;
    bool checkIndexBounds(int index);//Checks the array is within bounds
};

//Default Constructor
SmcArray::SmcArray(){
    //Set the array using the defaults
    this->size = defaultSize;
    
    //Allocate an array of this->size
    this->allocateArray();
    this->defaultValue = kDefaultValue;
}

//Constructor with params
SmcArray::SmcArray(int s){
    this->size = s;
    
    //Allocate an array of this->size
    this->allocateArray();
    this->defaultValue = kDefaultValue;
}

//Deletes the items in aray
SmcArray::~SmcArray(){
    delete [] this->items;
}

//Allocates an array of given size
void SmcArray::allocateArray(){
    //Allocate an array of this->size
    this->items = new int[this->size];
}

//Gets size of the array
int SmcArray::getSize(){
    return this->size;
}

//Add an item to the end of the array
void SmcArray::pushItem(int value){
    
    //Increase the size of array
    this->copyArrayIncreasedSize(this->size + 1);
    
    //Add our new value into the last slot in the array
    this->items[size - 1] = value;
    
}

//sets an item in the array (overwrite)
void SmcArray::setItem(int value, int index){
    
    //Check to see if the index can be written to/if the index is a valid index
    if(this->checkIndexBounds(index)){
        
        //Write to the array
        this->items[index] = value;
        
    }else if(index > this->size-1){
        this->pushItem(value);
    }else{
        //Item is not within the bounds of the array
        //Oh no!! Help
        cerr << "Inserted item is not within the bounds of the array\n";
    }
}

//gets an item in the array and checks to see if the index is within bounds
int SmcArray::getItem(int index){
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
void SmcArray::insertItem(int value, int index, int s){
    
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
void SmcArray::removeItem(int index){
    
    //Remove 1 item from the array
    //Decrease the size of the array
    if (index <0 || index >=size) cout << "The index of the item to be removed is out of range." << endl;
    else{
        for (int i = index; i < this->size -1; i++)
            items[i] = items[i+1];
        this->size = size-1;
    }
}

//Replaces a value at a given index
void SmcArray::replaceItemAt(int index, int value){
    
    if (index <0 || index >=size) cout << "The index of the item to be removed is out of range." << endl;
    else{
        for (int i = index; i < this->size; i++)
            if (int i = index) items[i] = value;
    }
}

//Prints the array
void SmcArray::printArray(){
    //Prints what is in my array
    //loop through an print each item
    for (int i=0; i < this->size; i++){
        cout << "Index is: " << i << " Array value is: " << this->items[i] << endl;
    }
    cout << endl;
}

void SmcArray::copyArrayIncreasedSize(int s){
    //original array 'this->items'
    //create a new array
    
    //TODO: refactor and rename this to change size
    
    //Check to see if new size is within the minSize And MaxSize
    //check if the new size is greater than the existing size
    if ((s > this->size) && s < maxSize){
        
        int * newArray = new int[s];
        
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

void SmcArray::copyArrayDecreasedSizeby1(int s, int index){
    //TODO:
    //if ( i != index) --> copy it ... else --> (if it does equal index... keeps going.)
    //Check to see if new size is within the minSize And MaxSize
    //check if the new size is greater than the existing size
    
    if (this->checkIndexBounds(index)){
        
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
        this->items = newArray;
        this->size = s;
        
    }else{
        cerr << __PRETTY_FUNCTION__ << " Oh no! My program is crashing\n";////_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
        throw "array out of bounds exception";
    }
}


//Checks if the index is within the bounds of the array
bool SmcArray::checkIndexBounds(int index){
    if(index >= minSize && index < this->size){
        return true;
    }else{
        return false;
    }
}

//Sets a default value for out of bounds index expansions via changeSize
void SmcArray:: setDefault(int value){
    this->defaultValue = value;
}
//Returns the default value
int SmcArray::getDefault(){
    return this->defaultValue;
}

void SmcArray::changeSize(int newSize){
    //Check to make sure there is a default value
    //TODO: Come back to this issue when we get started with TYPES
    //if(this->defaultValue == NULL){
    if (/* DISABLES CODE */ (false)) {
        cerr << __PRETTY_FUNCTION__ << " a default value has not been set\n";////_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
    }
    
    //First check to make sure the new size is within the bounds of the system
    if(newSize > minSize && newSize < maxSize){
        
        int * newArray = new int[newSize];
        
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
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray* myArray = new SmcArray(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray();
    
    //Items to be added to the array.
    myArray->pushItem(55);
    myArray->pushItem(12);
    myArray->pushItem(43);
    myArray->pushItem(21);
    myArray->pushItem(-21);
    
    myArray->setItem(88, 44);
    
    cout << "Prints out the array with added items." << endl;
    myArray->printArray();
}

//Test Case Two tests changing size to the array
void testCaseTwo(){
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray* myArray = new SmcArray(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array.
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray();
    
    //Push items
    myArray->pushItem(55);
    myArray->pushItem(12);
    myArray->pushItem(43);
    myArray->pushItem(21);
    myArray->pushItem(-21);
    
    //Prints what is in new array with added items.
    cout << "Prints out the array with push items" << endl;
    myArray->printArray();
    
    //Prints array with changed size.
    myArray->changeSize(5);
    cout << "Prints out the array with changed size when new array is smaller than original array." << endl;
    myArray->printArray();
    
    //Prints array with changed size.
    cout << "Prints out the array with changed size when new array is larger than orginal array. Default value is set to -1." << endl;
    myArray->changeSize(10);
    myArray->printArray();
    
}

//Test Case Three tests inserting an item at a given index
void testCaseThree(){
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray* myArray = new SmcArray(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray();
    
    
    //Prints array with inserted item
    myArray->insertItem(55, 3, myArray->getSize());
    cout << "Prints out the array with inserted item." << endl;
    myArray->printArray();
    
    //Prints what is in my array
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray();
    
    
    //Prints array with inserted item
    myArray->insertItem(-10, 6, myArray->getSize());
    cout << "Prints out the array with inserted item." << endl;
    myArray->printArray();
    
}

//Test Case Four tests removing an item at a given index
void testCaseFour(){
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray* myArray = new SmcArray(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray();
    
    //Removes an item
    myArray->removeItem(3);
    cout << "The array with item removed." << endl;
    //Prints the array with item removed
    myArray->printArray();
    
    
    //Prints what is in my array
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray();
    
    // Removes an item
    myArray->removeItem(0);
    cout << "The array with item removed." << endl;
    //Prints the array with item removed
    myArray->printArray();
    
}

//Test Case Five tests replacing a value at a given index
void testCaseFive(){
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray* myArray = new SmcArray(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << "Prints out the array before performing an operation." << endl;
    myArray->printArray();
    
    //Replace Item at given index
    myArray->replaceItemAt(5, 253);
    cout << "An item's value in the array is replaced at given index." << endl;
    //Prints the array with value replaced at given index
    myArray->printArray();
    
}

int main(int argc, const char * argv[])
{
    //Calling Test cases
    testCaseOne(); //Test Case One tests adding items to the array
    testCaseTwo(); //Test Case Two tests changing size to the array
    testCaseThree(); //Test Case Three tests inserting an item at a given index
    testCaseFour(); //Test Case Four tests removing an item at a given index
    testCaseFive(); //Test Case Five tests replacing a value at a given index
    return 0;
}