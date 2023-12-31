#pragma once
#include <string>

class Student
{
public:
    // Constructors and destructor
    Student() : name(""), ID(0), left(nullptr), right(nullptr) {};
    Student(std::string n, unsigned int id) : name(n), ID(id), left(nullptr), right(nullptr) {};
    Student(std::string n, unsigned int id, Student *l, Student *r) : name(n), ID(id), left(l), right(r) {};
    ~Student()
    {
        left = nullptr;
        right = nullptr;
    }
    // Getters and setters
    std::string GetName() const { return name; }
    int GetID() const { return ID; }
    Student* GetLeft() const { return left; }
    Student* GetRight() const { return right; }
    void SetName(const std::string &n)  { name = n; }
    void SetID(unsigned int id) { ID = id; }
    Student& SetLeft(Student* l) { this->left = l; return *this; }    // return *this for method-chaining children pointers
    Student& SetRight(Student* r) {this->right = r; return *this; }

    // Operator overloading for comparisons
    bool operator==(const Student &other) const { return ID == other.ID; }
    bool operator!=(const Student &other) const { return ID != other.ID; }
    bool operator<(const Student &other) const { return ID < other.ID; }
    bool operator>(const Student &other) const { return ID > other.ID; }

private:
    std::string name;
    unsigned int ID;
    Student *left;
    Student *right;
};