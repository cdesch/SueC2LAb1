
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
    void printArray(); // Print Array
    void setDefault(int value); //Sets a default value for out of bounds index expansions via changeSize
    int getDefault(); //Returns the default value
    void changeSize(int newSize); //Changes the array size
    
private:
    int size; // Size of array (elemets)
    int * items;
    int defaultValue;
    void allocateArray();
    void copyArrayIncreasedSize(int s);
    void copyArrayDecreasedSizeby1(int , int); //Decreases the size by 1 and leaves out a specific index;
    bool checkIndexBounds(int index);
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

//
SmcArray::~SmcArray(){
    delete [] this->items;
}

//
void SmcArray::allocateArray(){
    //Allocate an array of this->size
    this->items = new int[this->size];
}

//
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
        //Oh no!! God Help
        cerr << "Inserted item is not within the bounds of the array\n";
    }
}

//TODO: Add Comments
//gets an item in the array and checks to see if the index is within bounds
int SmcArray::getItem(int index){
    //Check to see if the index can be retrieved
    if(this->checkIndexBounds(index)){
        
        //Write to the array
        return this->items[index];
        
    }else{

        //Even though this will return the default value the user is prompted with a message indicating that a default value has been returned
        cerr << __PRETTY_FUNCTION__ << ": Returning Default Value\n ";

        //TODO: setting with type
        return this->defaultValue;
    }
}

//insert an item to the somewhere in the array
void SmcArray::insertItem(int value, int index, int s){
    
    //extend the array by 1
    
    //update the size by adding 1
    
    //insert the value into the array
    
    int j=0;
    
    if ((s > this->size) && s < maxSize){
        
        int * newArray = new int[s];
        
        //Copy array that is decreased by 1 at given index from the original array into the new array
        for (int i = 0; i < this->size+1; i++){
            j=j+1;
            if(i == index){
                j = j + 1;
                newArray[j]=value;
            }
            newArray[j] = this->items[i];
        }
        
        //Deallocate old memory
        delete [] this->items;
        
        //Copy to new pointer
        this->items = newArray;
        this->size = s+1;
        
    }else{
        cerr << "Oh no! My program is crashing\n";
        throw "array out of bounds exception";
    }
    
}

//Remove an item at a given index
void SmcArray::removeItem(int index){
    
    //TODO: Remove 1 item from the array
    //Decrease the size of the array
    this->copyArrayDecreasedSizeby1(this->size-1, index);
}

//Prints the array
void SmcArray::printArray(){
    
    //loop through an print each item
    for (int i=0; i < this->size; i++){
        cout << "Index is: " << i << " Array value is: " << this->items[i] << endl;
    }
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
        cerr << __PRETTY_FUNCTION__ << " Oh no! My program is crashing\n";
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
        cerr << __PRETTY_FUNCTION__ << " a default value has not been set\n";
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
        cerr << __PRETTY_FUNCTION__ << " Size changed to a illegal size\n";
    }
}

//TODO: testing we will do this later
//  insertings, removing items
// default settings... what about negatives?

void testCaseOne(){
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray* myArray = new SmcArray(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array
    myArray->printArray();
    
    myArray->pushItem(55);
    myArray->pushItem(12);
    myArray->pushItem(43);
    myArray->pushItem(21);
    myArray->pushItem(-21);
    
    myArray->setItem(88, 44);
    
    
    //Prints what is in my array
    myArray->printArray();
}


void testCaseTwo(){
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray* myArray = new SmcArray(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array
    myArray->printArray();
    //Push items
    myArray->pushItem(55);
    myArray->pushItem(12);
    myArray->pushItem(43);
    myArray->pushItem(21);
    myArray->pushItem(-21);
    
    //Prints what is in my array
    myArray->printArray();
    myArray->changeSize(5);
    myArray->printArray();
    myArray->changeSize(10);
    myArray->printArray();
                    
}

void testCaseThree(){
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray* myArray = new SmcArray(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array
    myArray->printArray();
    //Push items
    myArray->pushItem(55);
    myArray->pushItem(12);
    myArray->pushItem(43);
    myArray->pushItem(21);
    myArray->pushItem(-21);
    
    //Prints what is in my array
    myArray->printArray();

}

int main(int argc, const char * argv[])
{
    
    //testCaseOne();
    //testCaseTwo();
    testCaseThree();
    return 0;
}