#include "StudentAVLTree.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

int main()
{
    std::string line, command, name, id;
    int n;
    StudentAVLTree tree;
    std::getline(std::cin, line);
    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        iss >> command;

        if (command == "insert")
        {
            iss >> std::quoted(name) >> id;
            tree.insert(name, id);
        }
        else if (command == "remove")
        {
            iss >> id;
            tree.remove(id);
        }
        else if (command == "search")
        {
            auto firstChar = iss.peek();
            if (firstChar == '\"')
            {
                iss >> std::quoted(name);
                tree.searchName(name);
            }
            else
            {
                iss >> id;
                tree.searchID(id);
            }
        }
        else if (command == "printInorder")
        {
            tree.printInorder();
        }
        else if (command == "printPreorder")
        {
            tree.printPreorder();
        }
        else if (command == "printPostorder")
        {
            tree.printPostorder();
        }
        else if (command == "removeInorder")
        {
            iss >> n;
            tree.removeNthInorder(n);
        }
        else
        {
            std::cout << "unsuccessful" << std::endl;
        }
    }
    return 0;
}