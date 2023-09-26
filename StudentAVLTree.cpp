#include "StudentAVLTree.h"
#include <iostream>
#include <stack>

void StudentAVLTree::insert(const std::string& name, unsigned int id) 
{
    Student *toAdd = new Student(name, id);
    if (head == nullptr) 
    {
        head = toAdd;
        return;
    }

    Student *current = head, *parent = nullptr;
    std::stack<Student*> parents;

    while (current)
    {
        parent = current;
        parents.push(current);
        if (*current < *toAdd) current = current->GetRight();
        else if (*current > *toAdd) current = current->GetLeft();
        else 
        {
            delete toAdd;
            std::cout << "unsuccessful" << std::endl;
            return;
        }
    }
    if (*parent < *toAdd) parent->SetRight(toAdd);
    else parent->SetLeft(toAdd);
    std::cout << "successful" << std::endl;

    backtrackAndBalance(parents);
}

void StudentAVLTree::backtrackAndBalance(std::stack<Student*> parents)
{
    while (!parents.empty())
    {
        Student *current = parents.top();
        parents.pop();
        Student *parentOfCurrent = parents.empty() ? nullptr : parents.top();
        Student *newRoot = nullptr;
        int balance = StudentAVLTree::getBalance(current);
        if (balance > 1)    // tree is left heavy
        {
            Student *left = current->GetLeft();
            int leftBalance = StudentAVLTree::getBalance(left);
            if (leftBalance < 0) left = leftRotate(left);
            newRoot = rightRotate(current);
        }
        else if (balance < -1)  // tree is right heavy
        {
            Student *right = current->GetRight();
            int rightBalance = StudentAVLTree::getBalance(right);
            if (rightBalance > 0) right = rightRotate(right);
            newRoot = leftRotate(current);
        }

        if (newRoot)
        {
            if (parentOfCurrent)
            {
                if (parentOfCurrent->GetLeft() == current) parentOfCurrent->SetLeft(newRoot);
                else parentOfCurrent->SetRight(newRoot);
            }
            else head = newRoot;
        }
    }
}

// Utility methods
Student* StudentAVLTree::rightRotate(Student *y)
{
    Student* x = y->GetLeft();
    Student* temp = x->GetRight();
    x->SetRight(y);
    y->SetLeft(temp);
    return x;
}
Student* StudentAVLTree::leftRotate(Student *x)
{
    Student* y = x->GetRight();
    Student* temp = y->GetLeft();
    y->SetLeft(x);
    x->SetRight(temp);
    return y;
}
int StudentAVLTree::height(Student *s)
{
    if (!s) return -1;
    if (!(s->GetLeft()) && !(s->GetRight())) return 0;
    return std::max(height(s->GetLeft()), height(s->GetRight())) + 1;
}
int StudentAVLTree::getBalance(Student *s)
{
    return height(s->GetLeft()) - height(s->GetRight());
}