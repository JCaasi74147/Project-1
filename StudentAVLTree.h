#pragma once
#include "Student.h"
#include <stack>
#include <vector>
#include <iostream>

class StudentAVLTree
{
public:
    // Constructors
    StudentAVLTree() : head(nullptr), size(0) {};
    StudentAVLTree(Student* h) : head(h), size(1) {};
    StudentAVLTree(Student* h, unsigned int s) : head(h), size(s) {};

    // Modifications
    void insert(const std::string &name, const std::string &stringID);
    void remove(const std::string &stringID, bool backtrack = true);
    void removeNthInorder(int n);
    void backtrackAndBalance(std::stack<Student*> parents);

    // Search/traversal
    void searchID(std::string stringID);
    void searchName(const std::string &name);
    std::vector<std::string> inorderTraversal(Student* current);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();

    // utility methods
    int getSize() { return size; }
    int IDConversion(const std::string &stringID);
    std::string itos(int ID);
    Student* rightRotate(Student *y);
    Student* leftRotate(Student *x);
    int height(Student *s);
    int getBalance(Student *s);
    void printID(unsigned int id);
    bool isTreeBalanced();
    bool isBalanced(Student* node);
    Student* head;
    bool isValidName(const std::string& name);
private:
    int size;
};
