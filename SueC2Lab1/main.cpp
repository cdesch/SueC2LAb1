//
//  main.cpp
//  SueC2Lab1
//
//  Created by cj on 1/29/15.
//  Copyright (c) 2015 KickinEspresso. All rights reserved.
//


#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

//Constants
const int defaultSize = 10;
const int minSize = 0;
const int maxSize = 100;

//template<class element>
//TODO: We will do this later
class SmcArray{
    
public:
    SmcArray(); // Default Constructor
    SmcArray(int s); //  Constructor with params
    ~SmcArray(); // Deconstructor
    
    
    int getSize(); // Get size of array
    void setSize(int s); // Set size of array
    //TODO: changeSize : TODO later
    void clear(); // Clear array

    void pushItem(int value); //inserts item on end of the array
    void setItem(int value, int index); //sets an item  (overwrites) at given index
    int getItem(int index); //retrieves an item at a given index
    void insertItem(int value, int index); //inserts an item at a given index
    void removeItem(int index); // Delete array item
    void printArray(); // Print Array
    void setDefault(); //Sets a default value for out of bounds index expansions via changeSize //TODO: we will do this later
    
private:
    int size; // Size of array (elemets)
    int * items;
    int default_value;
    void allocateArray();
    void copyArrayIncreasedSize(int s);
    void copyArrayDecreasedSizeby1(int index); //Decreases the size by 1 and leaves out a specific index;
    bool checkIndexBounds(int index);
};

//Default Constructor
SmcArray::SmcArray(){
    //Set the array using the defaults
    this->size = defaultSize;

    //Allocate an array of this->size
    this->allocateArray();
}

//Constructor with params
SmcArray::SmcArray(int s){
    this->size = s;

    //Allocate an array of this->size
    this->allocateArray();
}

SmcArray::~SmcArray(){
     delete [] this->items;
}

void SmcArray::allocateArray(){
    //Allocate an array of this->size
    this->items = new int[this->size];
}

int SmcArray::getSize(){
    
    return this->size;
}
void SmcArray::setSize(int s){
    
    //Check for bounds
    //if(s < minSize || s > maxSize)
    //TODO: we will do this later.
    
}
void SmcArray::clear(){
    
    //Remove all the value array
    //TODO: We will do this later
    
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
        throw "Illegal Index exception";
    }
}

//TODO: Add Comments
int SmcArray::getItem(int index){
    //Check to see if the index can be retrieved
    if(this->checkIndexBounds(index)){
        
        //Write to the array
        return this->items[index];
        
    }else{
        //Oh no!! God Help
        cerr << "Inserted item is not within the bounds of the array\n";
        throw "Illegal Index exception";
    }
}

//insert an item to the somewhere in the array
void SmcArray::insertItem(int value, int index){
    
    //extend the array by 1
    
    //update the size by adding 1
    
    //insert the value into the array

    //TODO:
    
}

//Remove an item at a given index
void SmcArray::removeItem(int index){
    
    //TODO: Remove 1 item from the array
}

//Prints the array
void SmcArray::printArray(){
    
    //loop through an print each item
    //TODO: Print the array
    
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


void copyArrayDecreasedSizeby1(int index){
    //TODO:
    //if ( i != index) --> copy it ... else --> (if it does equal index... keeps going.)
}


//Checks if the index is within the bounds of the array
//TODO: Does not account for array length of 0
bool SmcArray::checkIndexBounds(int index){
    if(index >= minSize && index < this->size ){
        return true;
    }else{
        return false;
    }
}

//TODO: testing we will do this later
//  insertings, removing items
// default settings... what about negatives?


int main(int argc, const char * argv[])
{
    
    int myArraySize = 8;
    //Create an INSTANCE OBJECT of our class
    SmcArray* myArray = new SmcArray(myArraySize);
    // Add values to our array
    for (int i = 0; i < myArray->getSize(); i++){
        myArray->setItem(i,i);
    }
    
    //Prints what is in my array
    for (int i = 0; i < myArray->getSize(); i++){
        cout << myArray->getItem(i) << endl;
    }
    
    myArray->pushItem(55);
    myArray->pushItem(12);
    myArray->pushItem(43);
    myArray->pushItem(21);
    myArray->pushItem(-21);
    
    //Prints what is in my array
    for (int i = 0; i < myArray->getSize(); i++){
        cout << myArray->getItem(i) << endl;
    }
    
    myArray->setItem(88, 44);
    //Prints what is in my array
    for (int i = 0; i < myArray->getSize(); i++){
        cout << myArray->getItem(i) << endl;
    }
    
    return 0;
}
