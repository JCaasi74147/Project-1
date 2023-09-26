#include "StudentAVLTree.h"
#include <iostream>

void StudentAVLTree::insert(const std::string& name, unsigned int id) 
{
    Student *toAdd = new Student(name, id);
    if (head == nullptr) 
    {
        head = toAdd;
        return;
    }

    Student *current = head, *parent = nullptr;

    while (current)
    {
        parent = current;
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
    return;
}
