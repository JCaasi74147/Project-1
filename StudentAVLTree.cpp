#include "StudentAVLTree.h"
#include <iostream>
#include <stack>
#include <queue>
#include <iostream>
#include <functional>

void StudentAVLTree::insert(const std::string& name, unsigned int id)
{
    Student* toAdd = new Student(name, id);

    Student* current = head, * parent = head;
    std::stack<Student*> parents = {};

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
    if (current == parent && !parent) {
        head = toAdd;
        parents.push(head); 
    }
    else if (*parent < *toAdd) {
        parent->SetRight(toAdd);
        parents.push(toAdd);
    }
    else {
        parent->SetLeft(toAdd);
        parents.push(toAdd); 
    }
    StudentAVLTree::backtrackAndBalance(parents);

    StudentAVLTree::backtrackAndBalance(parents);
    std::cout << "successful" << std::endl;
    size++;
}

void StudentAVLTree::remove(unsigned int id, bool backtrack)
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
        else if ((current->GetRight() || current->GetLeft()) && (!(current->GetRight() && current->GetLeft()))) // one child
        {
            Student *child = (current->GetRight()) ? current->GetRight() : current->GetLeft();
            if (!parent) head = child;
            else if (current == parent->GetRight()) parent->SetRight(child);
            else parent->SetLeft(child);
            delete current;
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
            remove(tempID, false);
            current->SetName(tempName);
            current->SetID(tempID);
        }
        parents.pop();
        if (backtrack) { std::cout << "successful" << std::endl; }
        size--;
    }
    else { std::cout << "unsuccessful" << std::endl; return;  }

    if (backtrack) StudentAVLTree::backtrackAndBalance(parents);
}

void StudentAVLTree::removeNthInorder(int n) {
    std::stack<Student*> parents;
    n++;

    // Helper function to find N-th node and its parent
    std::function<Student* (Student*, int&)> findNthInorder;
    findNthInorder = [&](Student* root, int& n) -> Student* {
        if (!root) return nullptr;
        parents.push(root);
        Student* left = findNthInorder(root->GetLeft(), n);
        if (left) return left;
        if (--n == 0) return root;
        return findNthInorder(root->GetRight(), n);
    };

    Student* nodeToRemove = findNthInorder(head, n);
    if (!nodeToRemove) {
        std::cout << "unsuccessful" << std::endl;
        return;
    }
    remove(nodeToRemove->GetID());
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
            if (leftBalance < 0) current->SetLeft(leftRotate(left));
            newRoot = rightRotate(current);
        }
        else if (balance < -1)  // tree is right heavy
        {
            Student *right = current->GetRight();
            int rightBalance = StudentAVLTree::getBalance(right);
            if (rightBalance > 0) current->SetRight(rightRotate(right));
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
    if (head) students.push(head);
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

std::vector<std::string> StudentAVLTree::inorderTraversal(Student* current) {
    std::vector<std::string> names;
    if (current == nullptr) return names;
    
    auto left_names = inorderTraversal(current->GetLeft());
    names.insert(names.end(), left_names.begin(), left_names.end());
    
    names.push_back(current->GetName());
    
    auto right_names = inorderTraversal(current->GetRight());
    names.insert(names.end(), right_names.begin(), right_names.end());
    
    return names;
}

void StudentAVLTree::printInorder() {
    std::vector<std::string> names = inorderTraversal(head);
    for (size_t i = 0; i < names.size(); ++i) 
    {
        std::cout << names[i];
        if (i < names.size() - 1) 
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void StudentAVLTree::printPreorder() 
{
    if (!head) return;
    std::stack<Student*> stk;
    stk.push(head);
    std::string output = "";
    while (!stk.empty())
    {
        Student* current = stk.top();
        stk.pop();
        output += current->GetName() + ", ";

        if (current->GetRight()) stk.push(current->GetRight());
        if (current->GetLeft()) stk.push(current->GetLeft());
    }
    if (output.length() > 0) output = output.substr(0, output.length() - 2);

    std::cout << output << std::endl;
};
void StudentAVLTree::printPostorder()
{
    if (!head) return;

    std::stack<Student*> stk1, stk2;
    stk1.push(head);
    std::string output = "";

    while (!stk1.empty())
    {
        Student* current = stk1.top();
        stk1.pop();
        stk2.push(current);

        if (current->GetLeft()) stk1.push(current->GetLeft());
        if (current->GetRight()) stk1.push(current->GetRight());
    }

    while (!stk2.empty())
    {
        Student* current = stk2.top();
        stk2.pop();
        output += current->GetName() + ", ";
    }

    if (output.length() > 0) output = output.substr(0, output.length() - 2);
    std::cout << output << std::endl;
}

void StudentAVLTree::printLevelCount()
{
    if (!head)
    {
        std::cout << "0" << std::endl;
    }
    std::cout << height(head) << std::endl;
}

// Utility methods
unsigned int getSize() {return 1; };
bool isEmpty() {return false; };
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
    return 1 + std::max(height(s->GetLeft()), height(s->GetRight()));
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