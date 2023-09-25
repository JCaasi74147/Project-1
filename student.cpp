#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;

class Student
{
public:
    Student() : name(""), ID(0), left(nullptr), right(nullptr) {};
    Student(string name, unsigned int id) : name(name), ID(id), left(nullptr), right(nullptr) {};
    Student(string name, unsigned int id, Student *left, Student *right) : name(name), ID(id), left(left), right(right) {};
    ~Student()
    {
        left = nullptr;
        right = nullptr;
    }
private:
    string name;
    unsigned int ID;
    Student *left;
    Student *right;
};

#endif