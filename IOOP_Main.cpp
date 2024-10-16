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
   void log(){

    }
    void place_bid(){

    }
    void create_auction(){
        
    }
    void show_details(){
        cout<<"Name : "<<name<<endl;
        cout<<"Email : "<<email<<endl;
    }
};

int user::userCount = 18007;
class buyer : public user
{
public:
    string list;
};
class auction{
    string item_name;
    float start_price, curr_bid;
    auction(){
        cout<<"Enter item name : ";
        cin>>item_name;
        cout<<"Enter start price :";
        cin>>start_price;
        cout<<"Enter current bid price : ";
        cin>>curr_bid;
    }
    void start_auc(){

    }
    void end_auc(){

    }
    friend void user::create_auction();
};
