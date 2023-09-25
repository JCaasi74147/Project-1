#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;

class Student
{
public:
    // Constructors and destructor
    Student() : name(""), ID(0), left(nullptr), right(nullptr) {};
    Student(string name, unsigned int id) : name(name), ID(id), left(nullptr), right(nullptr) {};
    Student(string name, unsigned int id, Student *left, Student *right) : name(name), ID(id), left(left), right(right) {};
    ~Student()
    {
        left = nullptr;
        right = nullptr;
    }
    // Getters and setters
    string GetName() const { return name; }
    unsigned int GetID() const { return ID; }
    Student* GetLeft() const { return left; }
    Student* GetRight() const { return right; }
    void SetName(const string &n)  { name = n; }
    void SetID(unsigned int id) { ID = id; }
    Student& SetLeft(Student* left) { this->left = left; return *this; }    // return *this so we can method chain children pointers
    Student& SetRight(Student* right) {this->right = right; return *this; }

    // Operator overloading for comparisons
    bool operator==(const Student &other) const { return ID == other.ID; }
    bool operator!=(const Student &other) const { return ID != other.ID; }
    bool operator<(const Student &other) const { return ID < other.ID; }
    bool operator>(const Student &other) const { return ID > other.ID; }

private:
    string name;
    unsigned int ID;
    Student *left;
    Student *right;
};

#endif