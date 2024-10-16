#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class user
{
public:
    string name, email, password, role; // role is used only when object is of inherited class.
    int userID;
    static int userCount;

    user()
    {
        cout << "Enter name : ";
        cin >> name;
        cout << "Enter email : ";
        cin >> email;
        cout << "Enter password : ";
        cin >> password;
        userID = ++userCount;
    }
    user(string name, string email, string password, string role) : name(name), email(email), password(password), role(role)
    {
        userID = userCount++;
    }
    void show_details()
    {
        cout << "Name : " << name << endl;
        cout << "Email : " << email << endl;
    }
};

int user::userCount = 18007;
class buyer : public user
{
public:
    string list;
};
