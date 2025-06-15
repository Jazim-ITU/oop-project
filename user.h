#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
protected:
    int userId;
    string username;
    string email;
    string password;

public:
    User(int id, const string& user, const string& mail, const string& pass);
    virtual ~User() = default;

    virtual bool login(const string& user, const string& pass);
    virtual void updateProfile(const string& newEmail);
    virtual void displayInfo() const = 0; 

    
    int getUserId() const { return userId; }
    string getUsername() const { return username; }
    string getEmail() const { return email; }
};

#endif
