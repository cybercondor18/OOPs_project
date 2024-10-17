#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <map>
#include <stdexcept>

using namespace std;

// I've Added a bit of exception handling too...
class InvalidBidException : public exception
{
public:
    const char *what() const noexcept override
    {
        return "Invalid bid amount!";
    }
};

// create some more here ...

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
    void log()
    {
    }
    virtual void place_bid() = 0;

    void create_auction()
    {
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

    buyer(string name, string email, string password) : user(name, email, password, "Buyer") {}

    void place_bid(int auctionID, double bidAmount)
    {
        if (bidAmount <= 0)
            throw InvalidBidException();
        cout << "Placed bid of " << bidAmount << " on auction " << auctionID << endl;
    }
};
class auction
{
    string item_name;
    float start_price, curr_bid;
    auction()
    {
        cout << "Enter item name : ";
        cin >> item_name;
        cout << "Enter start price :";
        cin >> start_price;
        cout << "Enter current bid price : ";
        cin >> curr_bid;
    }
    void start_auc()
    {
    }
    void end_auc()
    {
    }
    friend void user::create_auction();
};
class bid
{
    string bidder_name;
    float bid_amount;
    tim t;
    void place_bid()
    {
    }
    void validate_bid()
    {
    }
};
class tim
{
public:
    int hours, min, sec;
    friend class bid;
};
class item
{
    string i_name, description;
    float start_price;
    void get_details(item &t)
    {
        cout << "Item name : " << i_name << endl;
        cout << "Starting price : " << start_price << endl;
        cout << "Description : " << description << endl;
    }
    void update_details(item &t)
    {
        int ch;
        cout << "1.Update item name\n2.Update description\n3.Update starting price\n\n";
        cout << "Choose what to update : ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter new item name : ";
            cin >> i_name;
        case 2:
            cout << "Enter new starting price : ";
            cin >> start_price;
        case 3:
            cout << "Enter new description : ";
            cin >> description;
        default:
            cout << "Choose valid option\n\n";
        }
    }
};
