#include "Student.h"
#include "StudentAVLTree.h"
#include <string>
#include <iostream>

int main()
{
    StudentAVLTree tree;
    tree.insert("hey", 99999999);
    tree.insert("why", 809);
    tree.insert("when", 6581484);
    tree.insert("okay", 1);
    tree.insert("lol", 3);
    tree.insert("rey", 69000000);
    tree.searchID(6581484);
    return 0;
}