#ifndef STUDENTAVLTREE_H
#define STUDENTAVLTREE_H
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
    void insert(const std::string &name, unsigned int id);
    void remove(unsigned int id, bool backtrack = true);
    void removeNthInorder(int n);
    void backtrackAndBalance(std::stack<Student*> parents);

    // Search/traversal
    void searchID(unsigned int id);
    void searchName(const std::string &name);
    std::vector<std::string> inorderTraversal(Student* current);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();

    // utility methods
    unsigned int getSize() const;
    bool isEmpty() const;
    Student* rightRotate(Student *y);
    Student* leftRotate(Student *x);
    int height(Student *s);
    int getBalance(Student *s);
    void printID(unsigned int id);
    void printRelationship(Student *node, const std::string &parentName) {
        if (node == nullptr) return;
        std::cout << "Parent: " << parentName << ", Child: " << node->GetName() << std::endl;
        printRelationship(node->GetLeft(), node->GetName());
        printRelationship(node->GetRight(), node->GetName());
    }

private:
    Student* head;
    unsigned int size;
};

#endif