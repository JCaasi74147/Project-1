#ifndef STUDENTAVLTREE_H
#define STUDENTAVLTREE_H
#include "Student.h"
#include <stack>

class StudentAVLTree
{
public:
    // Constructors
    StudentAVLTree() : head(nullptr), size(0) {};
    StudentAVLTree(Student* head) : head(head), size(1) {};
    StudentAVLTree(Student* head, unsigned int size) : head(head), size(size) {};

    // Modifications
    void insert(const std::string &name, unsigned int id);
    void remove(unsigned int id);
    void removeInorder(int n);
    void backtrackAndBalance(std::stack<Student*> parents);

    // Search/traversal
    void searchID(unsigned int id);
    void searchName(const std::string &name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    int findHeight();

    // utility methods
    unsigned int getSize() const;
    bool isEmpty() const;
    Student* rightRotate(Student *y);
    Student* leftRotate(Student *x);
    int height(Student *s);
    int getBalance(Student *s);

private:
    Student* head;
    unsigned int size;
};

#endif