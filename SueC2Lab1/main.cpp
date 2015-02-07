

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
#include <stdexcept>
#include <assert.h>
#include <vector>
#include <math.h>

using namespace std;

//Constants
const int defaultSize = 10; //default size is 10
const int minSize = 0; //min size of array is 0
const int maxSize = 100; //max size of array is 100
const int kDefaultValue = -1; //default value is set to -1

//Reference: http://www.cplusplus.com/forum/windows/88843/
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
    return alphanum[rand() % stringLength]; //character generator and returns a random charater
}

//Helper Functions
//Creates & returns random string to specified length
string generateRandomStringOfLength(int length){
    string myGeneratedString;
    for (int i = 0; i < length; i ++){
        myGeneratedString += genRandomChar();//Puts random string in specified length
    }
    return myGeneratedString; //returns the random string
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

//Deletes the items in array
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
    return this->size; //returns the size fo the array
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
        this->items[index] = value; //writes the value into the item array
        
    }else if(index > this->size-1){
        //cout << "Array is out of bounds, need to resize." << endl;
        //Two Routes can be taken
        //1st -  Use helper function pushItem() to add to end of array
        //this->pushItem(value);  //For the record, this method was a better option.
        //2nd - Adjust the size, then set the item
        this->changeSize(this->size+1); //Increase the size by 1
        this->setItem(value,this->size-1); //Recursive Call, use "this->size-1" in the event that index is n+2 greater than the size of the original size of the array
    }else{
        //Item is not within the bounds of the array
        cerr << "Inserted item is not within the bounds of the array\n";//error statement when item is out of bounds
    }
}

//Gets an item in the array and checks to see if the index is within bounds
template <class Element>
Element SmcArray<Element>::getItem(int index){
    //Check to see if the index can be retrieved
    if(this->checkIndexBounds(index)){
        
        //Write to the array
        return this->items[index]; //writes the value into the item array
        
    }else{
        //Even though this will return the default value the user is prompted with a message indicating that a default value has been returned
        cerr << __PRETTY_FUNCTION__ << "- WARNING: Returning Default Value\n ";//_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
    
        return this->defaultValue; //returns the default value
    }
}

//insert an item to the at the given index of the array
template <class Element>
void SmcArray<Element>::insertItem(Element value, int index, int s){
    
    //extend the array by 1
    //update the size by adding 1 and inserts the value into the array
    
    //Checks that within bounds
    if ((s >= this->size) && s < maxSize){
        
        Element * newArray = new Element[s+1];
        
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
        cerr << "My program is crashing\n"; //Error statement
        throw "array out of bounds exception";
    }
}

//Remove an item at a given index
template <class Element>
void SmcArray<Element>::removeItem(int index){
    //Remove 1 item from the array
    //Decrease the size of the array
    if (index < 0 || index >=size) cout << "The index of the item to be removed is out of range." << endl; //Error statement
    else{
        for (int i = index; i < this->size-1; i++) //starts the loop where the item is removed and goes to one less than original array size
            items[i] = items[i+1]; //sets the values after the item is deleted
        this->size = size-1; //reduces the size of the array by 1
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

//Copies an array in an increased size array
template <class Element>
void SmcArray<Element>::copyArrayIncreasedSize(int s){
    //check to see if new size is within the minSize And MaxSize
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
        cerr << "My program is crashing\n"; //Error statement
        throw "Array out of bounds exception";
    }
}

//Copy array into a new array when it is decreased by one item
template <class Element>
void SmcArray<Element>::copyArrayDecreasedSizeby1(int s, int index){
    //Notes:
    //if ( i != index) --> copy it ... else --> (if it does equal index... keeps going.)
    //Check to see if new size is within the minSize And MaxSize
    //check if the new size is greater than the existing size
    
    if (this->checkIndexBounds(index)){ //check to see if index is within bounds
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
        this->items = newArray;  //Copy items to new point for array newArray
        this->size = s;
        
    }else{
        cerr << __PRETTY_FUNCTION__ << "My program is crashing\n"; //_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
        throw "Array out of bounds exception";
    }
}

//Checks if the index is within the bounds of the array
template <class Element>
bool SmcArray<Element>::checkIndexBounds(int index){
    if(index >= minSize && index < this->size){ //checks if the index is greater than or equal to the minimum size and less than size of the array
        return true; //if yes then return true
    }else{
        return false; //if no then return false
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

//Changes the size of the array
template <class Element>
void SmcArray<Element>::changeSize(int newSize){
    //Check to make sure there is a default value
    //if(this->defaultValue == NULL){
    if (/* DISABLES CODE */ (false)) {
        cerr << __PRETTY_FUNCTION__ << " a default value has not been set\n";////_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
    }
    
    //First check to make sure the new size is within the bounds of the system
    if(newSize > minSize && newSize < maxSize){
        
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

//Testing
//Test Case One tests adding items to the array using integers
void testCaseOne(){
    
    cout << __PRETTY_FUNCTION__ << endl;
    
    int myArraySize = 8; //sets array size to 8
    //Create an INSTANCE OBJECT of our class
    SmcArray<int>* testArray = new SmcArray<int>(myArraySize);
    // Add values to our array
    for (int i = 0; i < testArray->getSize(); i++){
        testArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << "//////////////////////////////////////////////////////////////////////////////////////" << endl;
    
    cout << "//===============" << endl;
    cout << "//== Test Case 1.1: Insert into Array with data type INT" << endl;
    cout << "//== Array before performing operation: ";
    
    testArray->printArray(true); //print original array
    
    //Items to be added to the array.
    testArray->pushItem(55);
    testArray->pushItem(12);
    testArray->pushItem(43);
    testArray->pushItem(21);
    testArray->pushItem(-21);
    testArray->setItem(88, 44);
    
    cout << "//== Test Case 1.1: Insert into Array with data type INT" << endl;
    cout << "//== Results 1.1: ";
    testArray->printArray(true); //print array with added integers
    
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
    cout << __PRETTY_FUNCTION__ << " - Test 1.1 Completed Successfully" << endl; //_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
    cout << endl;
}

void testCaseOneFloat(){ //Test Case One tests adding items to the array using floats
    
    int myArraySize = 8; //set array size to 8
    //Create an INSTANCE OBJECT of our class
    SmcArray<float>* testArray = new SmcArray<float>(myArraySize);
    // Add values to our array
    for (int i = 0; i < testArray->getSize(); i++){
        testArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << "//== Test Case 1.2: Insert into Array with data type FLOAT" << endl;
    cout << "//== Array before performing operation: ";
    testArray->printArray(true); // prints original array with floats
    
    //Items to be added to the array.
    testArray->pushItem(.25);
    testArray->pushItem(12);
    testArray->pushItem(1.01);
    testArray->pushItem(21);
    testArray->pushItem(-21.2);
    testArray->setItem(88, 44);
    
    cout << "//== Test Case 1.2: Insert into Array with data type FLOAT" << endl;
    cout << "//== Results 1.2: ";
    testArray->printArray(true); //print array with adding floats
    
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
    
    for(int i = 0; i < testArray->getSize(); i++){ //assert to check and debug
        assert(testArray->getItem(i) == resultArray->getItem(i));
    }
    cout << __PRETTY_FUNCTION__ << " - Test 1.2 Completed Successfully" << endl; //_PRETTY_FUNCTION helps with debugging by identifying the name of where error is located
}

//Test Case One tests adding items to the array using double
void testCaseOneDouble(){
    
    cout << endl;
    
    int myArraySize = 8; //set array size to 8
    //Create an INSTANCE OBJECT of our class
    SmcArray<double>* testArray = new SmcArray<double>(myArraySize);
    // Add values to our array
    for (int i = 0; i < testArray->getSize(); i++){
        testArray->setItem(i,i);
    }
    
    //Prints what is in my array
    cout << "//== Test Case 1.3: Insert into Array with data type DOUBLE" << endl;
    cout << "//== Array before performing operation: ";
    testArray->printArray(true); //print original array
    
    //Items to be added to the array.
    testArray->pushItem(.25);
    testArray->pushItem(12);
    testArray->pushItem(1.01123);
    testArray->pushItem(21);
    testArray->pushItem(-21.2);
    testArray->setItem(88, 44);
    
    cout << "//== Test Case 1.3: Insert into Array with data type DOUBLE" << endl;
    cout << "//== Results 1.3: ";
    testArray->printArray(true); //prints array with new DOUBLE
    
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
    resultArray->setItem(1.01123,10);
    resultArray->setItem(21, 11);
    resultArray->setItem(-21.2, 12);
    resultArray->setItem(88, 13);
    
    for(int i = 0;i < testArray->getSize(); i++){ //assert and debug
        assert(testArray->getItem(i) == resultArray->getItem(i));
    }
    
    cout << __PRETTY_FUNCTION__ << " - Test 1.3 Completed Successfully" << endl;
}

//Test Case One tests adding items to the array using string
void testCaseOneString(){
    
    //cout << __PRETTY_FUNCTION__ << endl;
    cout << endl;
    int myArraySize = 8; //set array size to 8
    
    //Setup test data
    vector <string> testData;
    for (int i = 0; i < myArraySize+6; i++){ //generates random strings to store in array
        testData.push_back(generateRandomStringOfLength(i+1));
    }
    
    //Create an INSTANCE OBJECT of our class
    SmcArray<string>* testArray = new SmcArray<string>(myArraySize);
    // Add values to our array
    for (int i = 0; i < testArray->getSize(); i++){
        testArray->setItem(testData.at(i),i);
    }
    
    //Prints what is in my array
    cout << "//== Test Case 1.4: Insert into Array with data type STRING" << endl;
    cout << "//== Array before performing operation: ";
    testArray->printArray(true); //prints original array
    
    //Items to be added to the array.
    for (int i = 8; i < myArraySize+6; i++){
        testArray->pushItem(testData.at(i));
    }
    cout << "//== Test Case 1.4: Insert into Array with data type STRING" << endl;
    cout << "//== Results 1.4: ";
    testArray->printArray(true); //prints array with added strings
    
    //Assertion of correctness
    SmcArray<string>* resultArray = new SmcArray<string>(myArraySize+6);
    for (int i = 0; i < myArraySize+6; i++){
        string temp = testData.at(i);
        resultArray->setItem(temp, i);
    }
    
    for(int i = 0;i < testArray->getSize(); i++){ //assertion of correctness
        assert(testArray->getItem(i) == resultArray->getItem(i));
    }
    cout << __PRETTY_FUNCTION__ << " - Test 1.4 Completed Successfully" << endl;
}

//Test Case One tests adding items to the array using char
void testCaseOneChar(){
    
    cout << endl;
    int myArraySize = 8; //set array size to 8
    
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
    cout << "//== Test Case 1.5: Insert into Array with data type CHAR" << endl;
    cout << "//== Array before performing operation: ";
    testArray->printArray(true); //prints original array
    
    //Items to be added to the array.
    for (int i = 8; i < myArraySize+6; i++){
        testArray->pushItem(testData.at(i));
    }
    cout << "//== Test Case 1.5: Insert into Array with data type CHAR" << endl;
    cout << "//== Results 1.5: ";
    testArray->printArray(true); //prints array with added char items
    
    //Assertion of correctness
    SmcArray<char>* resultArray = new SmcArray<char>(myArraySize+6);
    for (int i = 0; i < myArraySize+6; i++){
        char temp = testData.at(i);
        resultArray->setItem(temp, i);
    }
    
    for(int i = 0;i < testArray->getSize(); i++){
        assert(testArray->getItem(i) == resultArray->getItem(i));
    }
    cout << __PRETTY_FUNCTION__ << " - Test 1.5 Completed Successfully" << endl;
    cout << "//===============" << endl ;
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
    cout << "Prints out the array with changed size when new array is larger than orginal array. Default value is set to " << myArray->getDefault() << endl;
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

//TestData
//ExpectedTestResults

//This test case validates the functionality of the printArray() function
template <typename Element>
void testPrintArray(typename SmcArray<Element>::SmcArray* smcArray){
    //Prints the array
    smcArray->printArray(true);
}

//This test case validates the functionality of the setItem() function
template <typename Element>
void testSetItem(typename SmcArray<Element>::SmcArray* smcArray, Element testData ){
    //Prints the array
    cout << "Prints out the array before performing an operation: ";
    smcArray->printArray(true);
    
    //Test setting an item into the array
    cout << "Sets an item at given index. Result is: ";
    smcArray->setItem(testData, 5);
    smcArray->printArray(true);
    
    //Test setting an item outside the bounds of the array
    cout << "***Test for setting an item outside array bounds then resizing array before inserting item in array***\n";//error statement when item is out of bounds
    smcArray->setItem(testData, smcArray->getSize() + 15);
    cout << "Sets an item at given index. Result is: ";
    smcArray->printArray(true);
    cout << "===================" << endl;
}

//This test case validates the functionality of the Change Size function
template <typename Element>
void testChangeSize(typename SmcArray<Element>::SmcArray* smcArray, Element defaultValue ){
    
    //Set the default value for printing the array
    smcArray->setDefault(defaultValue);
    
    //Prints what is in my array.
    cout << "Prints out the array before performing an operation: ";
    smcArray->printArray(true);
    
    //Prints array with changed size.
    smcArray->changeSize(5);
    cout << "Prints out the array with changed size when new array is a smaller array: ";
    smcArray->printArray(true);
    
   
    
    //Prints array with changed size.
    cout << "Prints out the array with changed size when new array is a larger array. Default value is set to " << smcArray->getDefault() << ": " << endl;
    smcArray->changeSize(15);
    smcArray->printArray(true);
    cout << endl << "===================" << endl;
}

//This test case validates the functionality of the Insert function
template <typename Element>
void testInsertItem(typename SmcArray<Element>::SmcArray* smcArray, Element testData ){
    //Prints the array before operation
    cout << "Prints out the array before performing an operation: ";
    smcArray->printArray(true);
    
    //Prints array with inserted item
    smcArray->insertItem(testData, 4, smcArray->getSize());
    cout << "Prints out the array with inserted item: ";
    smcArray->printArray(true);
    cout << "===================" << endl;
}

template <typename Element>
void testRemoveItem(typename SmcArray<Element>::SmcArray* smcArray, Element testData ){
    
    //Prints the array
    cout << "Prints out the array before performing an operation: ";
    smcArray->printArray(true);
    
    //Test removing an item from the array
    smcArray->removeItem(7);
    cout << "Removing item from array. Result is: ";
    smcArray->printArray(true);
    
    //Test removing an item from the array
    smcArray->removeItem(0);
    cout << "Removing item from array. Result is: ";
    smcArray->printArray(true);
    
    cout << "===================" <<endl;
}

//This test validates the test case provided
void testProvidedTestCase(){
    SmcArray<int>* Xvals = new SmcArray<int>(10);
    SmcArray<double>* Yvals = new SmcArray<double>();
    cout << "Validates the test case provided in Assignment 1" << endl;
    //Print statemete that gives the size of x
    cout << "size is " << Xvals->getSize() << "\n";
    
    //Loops and calculates y with x varrying
    for (int i = 0; i < 30; i += 1){
        int x = i*3+1;
        double y = sin(M_PI/x); //M_PI is a constant in the math.h library
        Xvals->setItem(x, i);
        Yvals->setItem(y, i);
    }
    //Print statement that gives the x value
    cout << "size is " << Xvals->getSize() << "\n";
    
    for (int i = 0; i <= Xvals->getSize(); i += 1)
        cout << i << ": x = " << Xvals->getItem(i) << ", sin(pi/x) = " << Yvals->getItem(i) << "\n";
}

int main(int argc, const char * argv[]){
    
    int testArraySize = 8; //Setting test array size
    
    //Sets integer values fin array or the various operations
    SmcArray<int>* intTestArray = new SmcArray<int>(testArraySize);
    // Add values to our array
    for (int i = 0; i < intTestArray->getSize(); i++){
        intTestArray->setItem(i,i);
    }
    int intTestData = 92; //Sets integer test data
    int intTestData2 = -88; //Sets another integer test data
    
    //Sets double values in array for the various operations
    SmcArray<double>* doubleTestArray = new SmcArray<double>(testArraySize);
    // Add values to our array
    for (int i = 0; i < doubleTestArray->getSize(); i++){
        doubleTestArray->setItem(i + 0.1,i);
    }
    double doubleTestData = 77.02; //Sets double test data
    double doubleTestData2 = 44.57; //Sets another double test data
    
    //Sets float values in array for the various operations
    SmcArray<float>*  floatTestArray = new SmcArray<float>(testArraySize);
    // Add values to our array
    for (int i = 0; i < floatTestArray->getSize(); i++){
        floatTestArray->setItem(i + 0.2,i);
    }
    float floatTestData = 555.555; //Sets float test data
    float floatTestData2 = -345.6; //Sets another float test data
    
    //Sets string values in array for the various operations
    SmcArray<string>* stringTestArray = new SmcArray<string>(testArraySize);
    // Add values to our array
    for (int i = 0; i < stringTestArray->getSize(); i++){
        stringTestArray->setItem(generateRandomStringOfLength(i+1), i);
    }
    string stringTestData = "MyTestString"; // Sets string test data
    string stringTestData2 = "ItWorks"; // Sets another string test data
    
    //Sets char values in array for the various operations
    SmcArray<char>* charTestArray = new SmcArray<char>(testArraySize);
    // Add values to our array
    for (int i = 0; i < charTestArray->getSize(); i++){
        charTestArray->setItem(genRandomChar(), i);
    }
    char charTestData = 't'; // Sets char test data
    char charTestData2 = 'z'; // Sets another char test data
    
    cout << "//////////////////////////////////////////////////////////////////////////////////////" << endl;
    //Testing Print Array for integer, double, float, string and char
    cout << "===================" << endl;
    cout << "Testing the print function for integers, double, floats, string, and char:" << endl;
    testPrintArray<int>(intTestArray);
    testPrintArray<double>(doubleTestArray);
    testPrintArray<float>(floatTestArray);
    testPrintArray<string>(stringTestArray);
    testPrintArray<char>(charTestArray);
    cout << "===================" << endl;
    
    //Testing Set Item Array for integer, double, float, string and char
    cout << "+++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+ Testing the Set operation         +" << endl;
    cout << "+++++++++++++++++++++++++++++++++++++" << endl;
    testSetItem<int>(intTestArray, intTestData);
    testSetItem<double>(doubleTestArray, doubleTestData);
    testSetItem<float>(floatTestArray, floatTestData);
    testSetItem<string>(stringTestArray, stringTestData);
    testSetItem<char>(charTestArray, charTestData);
    
    //Testing Change Size Array for integer, double, float, string and char
    cout << "+++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+ Testing the Change Size operation +" << endl;
    cout << "+++++++++++++++++++++++++++++++++++++" << endl;

    
    
    testChangeSize<int>(intTestArray, -9);
    testChangeSize<double>(doubleTestArray, -10);
    testChangeSize<float>(floatTestArray, -2.212);
    testChangeSize<string>(stringTestArray, "Default String");
    testChangeSize<char>(charTestArray, 't');
     
    
    //Testing Insert Item in Array for integer, double, float, string and char
    cout << "+++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+ Testing the Insert operation      +" << endl;
    cout << "+++++++++++++++++++++++++++++++++++++" << endl;
    testInsertItem<int>(intTestArray, intTestData2);
    testInsertItem<double>(doubleTestArray, doubleTestData2);
    testInsertItem<float>(floatTestArray, floatTestData2);
    testInsertItem<string>(stringTestArray, stringTestData2);
    testInsertItem<char>(charTestArray, charTestData2);
    
    
    //Testing Remove Item in Array for integer, double, float, string and char
    cout << "+++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+ Testing the Remove operation      +" << endl;
    cout << "+++++++++++++++++++++++++++++++++++++" << endl;
    testRemoveItem<int>(intTestArray, intTestData);
    testRemoveItem<double>(doubleTestArray, doubleTestData);
    testRemoveItem<float>(floatTestArray, floatTestData);
    testRemoveItem<string>(stringTestArray, stringTestData);
    testRemoveItem<char>(charTestArray, charTestData);
    
    //Test Case Provided in the Assignment
    cout << "+++++++++++++++++++++++++++++++++++" << endl;
    cout << "+ Validating the Case Provided    +" << endl;
    cout << "+++++++++++++++++++++++++++++++++++" << endl;
    testProvidedTestCase();
    
    //Calling Test Case 1 for debugging purposes
    /*
     testCaseOne(); //Test Case One tests adding items to the array
     testCaseOneFloat();
     testCaseOneDouble();
     testCaseOneString();
     testCaseOneChar();
     */
    
    //Release Resources
    intTestArray->~SmcArray();
    doubleTestArray->~SmcArray();
    floatTestArray->~SmcArray();
    stringTestArray->~SmcArray();
    charTestArray->~SmcArray();
    
    cout << "===================" << endl;
    cout << "//////////////////////////////////////////////////////////////////////////////////////" << endl;
    return 0;
}
