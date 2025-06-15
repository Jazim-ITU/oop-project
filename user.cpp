#include "User.h"
using namespace std;

User::User(int id, const string& user, const string& mail, const string& pass)
    : userId(id), username(user), email(mail), password(pass) {
}

bool User::login(const string& user, const string& pass) {
    return (username == user && password == pass);
}

void User::updateProfile(const string& newEmail) {
    email = newEmail;
    cout << "Profile updated successfully!" << endl;
}
