# SplayTreeLab

## 🔖 Background Information
In a Map interface, items are stored as key-value pairs. I should be able to create a new key-value pair, retrieve the value associated with a key, and delete a key-value pair. This might look something like:

```
Map map = new Map();
map.insert("someKey", "someValue"); // This should save the key-value pair in the map
map.get("someKey");                 // This should return the value "someValue"
map.delete("someKey")               // This should delete the key-value pair in the map
```
There are many different ways to implement a map, all with their own advantages and disadvantages. We are going to focus on tree maps in this lab.

A TreeMap is an implementation of the Map interface, where the key-value pairs are stored in a binary search tree. The pairs are arranged in the tree by the alphabetical ordering of the keys (Swiniarski et al., 2023). Of course, we want our binary search tree to have some balancing structure so that queries are as efficient as possible. A splay tree is a nice choice when we expect our users to favor the insertion and retrieval of a few specific keys more than others.

## 🎯 Problem Statement
Implement a TreeMap data structure from scratch using a SplayTree under the hood to store key-value pairs.

## ✅ Acceptance Criteria
Your TreeMap data structure should have the following methods:

- insert(string key, string value) - Inserts a key-value pair into the map.
- get(string key) - Returns the value associated with a given key. If the key does not exist, return an empty string or some default value of your choice.
- delete(string key) - Deletes the key-value pair associated with a given key. If the key does not exist, you may return an error message or perform no action.

## 📋 Dev Notes
Let’s take a moment to try to break down this problem into manageable bite-sized chunks. If we tried to implement everything all at once, we would probably get overwhelmed.

Here is how I might break down this lab:

- Implement a generic BinarySearchTree data structure without any special balancing. You should be able to insert, retrieve, and delete elements from the tree.
- Rename your BinarySearchTree data structure to SplayTree and add the splaying operations.
- Implement a KeyValuePair class that stores a string key and a string value. You might want to create getters and setters for those two attributes.
- Overload the comparison operations on the KeyValuePair class. When you compare two KeyValuePair objects using >, <, >=, <=, or ==, it should compare the keys of the objects and assess their alphabetical ordering.
- Create a TreeMap class. In the constructor, have it create a SplayTree<KeyValuePair> object and save it to a private variable.
- Write the insert method on TreeMap which takes a string key and a string value as arguments. It should build a KeyValuePair object using the arguments and insert it into the SplayTree<KeyValuePair> object.
- Write the get method on TreeMap which takes a string key as its argument. It should search the SplayTree<KeyValuePair> object for the key and return its corresponding value.
- Write the delete method on TreeMap which takes a string key as its argument. It should search the SplayTree<KeyValuePair> object for the key and delete the entry.

## 🖥️ Example Output
I might expect to see the TreeMap class used like this:

```
#include <iostream>
 
int main() {
  TreeMap map;
 
  // Insert a number of key-value pairs into the tree map
  map.insert("keyOne", "valueOne");
  map.insert("keyTwo", "valueTwo");
  map.insert("keyThree", "valueThree");
 
  // Prints out valueOne
  std::cout << map.get("keyOne");
 
  // Prints out valueThree
  std::cout << map.get("keyThree");
 
  // Prints out an empty string or some default value of your choice
  std::cout << map.get("keyDoesNotExist");
 
  // Deletes the key-value pair from the tree map
  std::cout << map.delete("keyOne");
}
```


## 📝 Thought Provoking Questions
- Suppose a user inserts a few hundred million items into your TreeMap as a storage structure. After that, you determine that 90% of their queries involve retrieving the value for one specific key and the remaining 10% of the queries involve retrieving the values for other random keys. Describe the expected performance of your TreeMap data structure in this case.
- Suppose a user inserts a few hundred million items into your TreeMap as a storage structure. After that, you determine that there is no discernable pattern in how they retrieve values. It is equally likely that any key-value pair will be accessed. Describe the expected performance of your TreeMap data structure in this case.

## 💼 Add-Ons For the Portfolio
N/A

## 🔗 Useful Links
Java Project Template

## 📘 Works Cited
Swiniarski, S., Chermsirivatana, T., Kapoor, S., Thompson, K., & Diaz, C. (2023). Java | TreeMap. In Codecademy. https://www.codecademy.com/resources/docs/java/treemap
