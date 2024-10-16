#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
class user{
    public:
    string name,email,password;
    user(){
        cout<<"Enter name : ";
        cin>>name;
        cout<<"Enter email : ";
        cin>>email;
        cout<<"Enter password : ";
        cin>>password;
    }
    void show_details(){
        cout<<"Name : "<<name<<endl;
        cout<<"Email : "<<email<<endl;
    }
};
class buyer:public user{
    
};
