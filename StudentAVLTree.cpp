#include "StudentAVLTree.h"
#include <iostream>
#include <stack>
#include <queue>

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

void StudentAVLTree::remove(unsigned int id)
{
    Student *current = head, *parent = nullptr;
    std::stack<Student*> parents;

    while (current)
    {
        parents.push(current);
        if (id == current->GetID()) break;
        parent = current;
        if (id < current->GetID()) current = current->GetLeft();
        else current = current->GetRight();
    }
    if (current)
    {
        if (!current->GetRight() && !current->GetLeft())    // no children
        {
            if (!parent) 
            {
                head = nullptr;
            }
            else
            {
                if (parent->GetLeft() == current) parent->SetLeft(nullptr);
                else parent->SetRight(nullptr);
            }
            delete current;
        }
        else if (current->GetRight() || current->GetLeft() && !(current->GetRight() && current->GetLeft())) // one child
        {
            Student *child = (current->GetRight()) ? current->GetRight() : current->GetLeft();
            if (!parent) head = child;
            else if (current == parent->GetRight()) parent->SetRight(child);
            else parent->SetLeft(child);

        }
        else    // two children
        {
            Student* inorderSuccessor = current->GetRight();
            while (inorderSuccessor->GetLeft())
            {
                inorderSuccessor = inorderSuccessor->GetLeft();
            }
            std::string tempName = inorderSuccessor->GetName();
            int tempID = inorderSuccessor->GetID();
            remove(tempID);
            current->SetName(tempName);
            current->SetID(tempID);
        }
        std::cout << "successful" << std::endl;
    }
    else { std::cout << "unsuccessful" << std::endl; }

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


// Search/traversal
void StudentAVLTree::searchID(unsigned int id)
{
    Student* current = head;
    while (current)
    {
        if (current->GetID() == id)
        {
            std::cout << current->GetName() << std::endl;
            return;
        }
        else if (id < current->GetID()) current = current->GetLeft();
        else current = current->GetRight();
    }
    std::cout << "unsuccessful" << std::endl;
}

void StudentAVLTree::searchName(const std::string &name)
{
    std::stack<Student*> students;
    std::queue<int> IDs;
    students.push(head);
    while (!students.empty())
    {
        Student *curr = students.top();
        if (curr->GetName() == name) IDs.push(curr->GetID());
        students.pop();
        if (curr->GetRight()) students.push(curr->GetRight());
        if (curr->GetLeft()) students.push(curr->GetLeft());
    }
    if (IDs.empty()) { std::cout << "unsuccessful" << std::endl; }
    else 
    {
        while (!IDs.empty())
        {
            printID(IDs.front());
            IDs.pop();
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
void StudentAVLTree::printID(unsigned int id)
{
    if (id > 9999999)
    {
        std::cout << id << std::endl;
    }
    else
    {
        std::string s = "";
        for (int i = 0; i < 8; i++)
        {
            if (id / 10 == 0) s = "0" + s;
            else 
            {
                s = std::to_string(id % 10) + s;
                id /= 10;
            }
        }
        std::cout << s << std::endl;
    }
}