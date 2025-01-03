#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <cstring>
#include <map>
#include <stdexcept>
#include <sstream>
#include<conio.h>
#include <regex>
#define max 500

using namespace std;

class admin;
class jobseeker;
class job;
class application;
class education;
class employer;
class experience;
class job_preferences;
class company_profile;

vector <employer> emp_list;
vector <jobseeker> jobseek_list;
vector <job> job_list;
vector <admin> admin_list; 

bool isValidEmail(const string& email) {
    const regex emailPattern(R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))");
    return regex_match(email, emailPattern);
}
bool isValidPassword(const string& password) {
    if (password.length() < 8) {
        cout << "Password must be at least 8 characters long." << endl;
        return false;
    }
    bool hasUppercase = false, hasLowercase = false, hasDigit = false, hasSpecialChar = false;
    string specialChars = "!@#$%^&*()-_=+[{]}|;:',<.>/?";
    for (char ch : password) {
        if (isupper(ch)) hasUppercase = true;
        else if (islower(ch)) hasLowercase = true;
        else if (isdigit(ch)) hasDigit = true;
        else if (specialChars.find(ch) != string::npos) hasSpecialChar = true;
    }
    if (!hasUppercase) cout << "Password must include at least one uppercase letter." << endl;
    if (!hasLowercase) cout << "Password must include at least one lowercase letter." << endl;
    if (!hasDigit) cout << "Password must include at least one number." << endl;
    if (!hasSpecialChar) cout << "Password must include at least one special character." << endl;
    return hasUppercase && hasLowercase && hasDigit && hasSpecialChar;
}
class user{
    public:
    string name,email,password,user_type;
    user(){
        name=" ";
        email=" ";
        password=" ";
        user_type=" ";
    }
    void register_user(){
        int ch;
        cout<<"\nEnter name : ";
        cin.ignore(); 
        getline(cin,this->name);
        em:cout<<"Enter email : ";
        cin>>this->email;
        if(!isValidEmail(email)){
            cout<<"\n*** Please enter valid email id ***\n\n";
            goto em;
        }
        pass:cout<<"Enter password : ";
        cin>>this->password;
        if (!isValidPassword(password)) {
           cout << "\n\n*** Password is invalid. ***\n\n" << endl;
           goto pass;
        } 
    }
    void update_profile(){
        int ch;
        string input;
        a : cout<<"\n1.Name\t2.Email\t3.Password\n\n";
        cout<<"Enter choice : ";
        cin>>input;
        try{
            stringstream ss(input);
            if (!(ss >> ch) || !(ss.eof())) {
                throw invalid_argument("Input must be an integer.\n");
            }
            switch(ch){
                case 1:
                    cout<<"Enter new name : ";
                    cin.ignore(); 
                    getline(cin,name);
                    break;
                case 2:
                    cout<<"Enter new email : ";
                    cin>>email;
                    break;
                case 3:
                    cout<<"Enter new password : ";
                    cin>>password;
                    break;
                default :
                    cout<<"\nEnter valid choice\n";
                    goto a;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Invalid Argument: " << e.what() << endl;
            goto a;
        }
    }
    virtual void view_profile(){
        cout<<"\nName : "<<name<<endl;
        cout<<"Email : "<<email<<endl;
    }
};
class experience{
    public:
    string job_title,company_name,duration;
    experience(){
        job_title=" ";
        company_name=" ";
        duration=" ";
    }
    void create_exp(){
        cout<<"\nEnter job title : ";
        cin.ignore(); 
        getline(cin,job_title);
        cout<<"Enter company name : ";
        getline(cin,company_name);
        cout<<"Enter job duration : ";
        getline(cin,duration);
        return;
    }
};
class education{
    public:
    string name_of_grade,institute;
    int year_dur;
    education(){
        name_of_grade=" ";
        institute=" ";
        year_dur=0;
    }
    void create_edc(){
        cout<<"\nEnter name of qualification : ";
        cin.ignore(); 
        getline(cin,name_of_grade);
        cout<<"Enter institute or place from where you complete qualification : ";
        getline(cin,institute);
        cout<<"Enter year of completion : ";
        cin>>year_dur;
    }
};
enum status{hired,rejected,pending,shortlisted};
class application{
    public:
    string appl_resume,cover_letter,input;
    long long appl_id;
    status appl_st;
    job *job_ref;
    jobseeker *applicant;
    application();
    void view_appl_details();
    void update_appl_status(){
        int ch;
        c : cout<<"\n1.Hired\t2.Rejected\t3.Pending\t4.Shortlisted\n\n";
        cout<<"Enter updated status : ";
        cin>>input;
        try{
            stringstream ss(input);
            if (!(ss >> ch) || !(ss.eof())) {
                throw invalid_argument("Input must be an integer.\n");
            }
            switch(ch){
                case 1:
                    this->appl_st=hired;
                    break;
                case 2:
                    this->appl_st=rejected;
                    break;
                case 3:
                    this->appl_st=pending;
                    break;
                case 4:
                    this->appl_st=shortlisted;
                    break;
                default:
                    cout<<"\nEnter valid option"<<endl;
                    goto c;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "\nInvalid Argument: " << e.what() << endl;
            goto c;
        }
        return;
    }
    void view_appl_status(){
        cout<<"Application status : "<<this->appl_st<<endl;
    }
    void withdraw_application(){

    }
    void saveApplication();
};
long long application_id=1000000;
class job{
    public:
    static long long jobid;
    string job_title,job_type;
    long long job_id;
    employer *job_emp;
    string job_descr;
    vector <string> requirements;
    float salary;
    string job_location;
    vector <application> appl_list;
    job();
    void view_details();
    void view_compt_details();
    void create_job(string jb_title, string description, vector<string> req, float sal, string location, string jb_type);
    void update_job_details();
    void close_job(){

    }
    void saveToCSV_jobs();
};
long long job:: jobid=9000000;
class jobseeker:public user{
    public:
    string resume;
    vector <experience> exp_list;
    vector <education> edu_list;
    vector <string> skills;
    vector <job> applied_jobs;
    vector <application> app_list;
    job_preferences *job_prefr;
    jobseeker();
    void create_new_jobseeker();
    int jbs_login();
    void view_profile_jbs();
    void apply_for_job(job &jb, string job_resume,string cover_ltr=NULL);
    void update_resume(string new_resume){
        this->resume=new_resume;
        return;
    }
    void view_applied_jobs();
    void update_skills();
    void search_jobs();
    void update_experiences();
    void track_application_status();
    void logout(){
        return;
    }
    void saveProfile() {
        fstream outFile;
        outFile.open("jobseekers.txt", ios::app); 
        if (outFile.is_open()) {
            int currentPos = outFile.tellg();
            outFile << name << ",";
            outFile.seekp(currentPos+14,ios::beg);
            outFile << email << ",";
            outFile.seekp(currentPos+26,ios::beg);
            outFile << resume << "\n";
            outFile.close();
        } else {
            cerr << "Error opening file.\n";
        }
    }
    void saveToCSV_jobseekers();
};
class job_preferences{
    public:
    vector <string> locations;
    vector <string> job_type;
    string salary_range;
    job_preferences(){
        salary_range=0.0;
    }
    void create_job_pref();
};
class employer:public user{
    public:
    string company_name;
    string comp_location,comp_description;
    vector <job> posted_jobs;
    vector <application> applications_received;
    employer();
    void create_new_employer();
    int emp_login();
    void view_profile_emp();
    void comp_details();
    void post_job(string jb_title, string description, vector<string> req, float sal, string location, string jb_type);
    void view_posted_jobs();
    void review_applications(long long appl_id);
    void select_candidate(long long application_id);
    void reject_candidate(long long application_id);
    void update_job();
    void remove_job();
    void saveEmployerProfile();
    void saveToCSV_employers();
};
long long admid=7000000;
class admin{
    public:
    string name,email,pass;
    long long admin_id;
    admin(){
        name=" ";
        email=" ";
        pass=" ";
        admin_id=0;
    }
    void adm_register(){
        cout<<"\nEnter name : ";
        cin.ignore(); 
        getline(cin,name);
        eml:cout<<"Enter email : ";
        cin>>this->email;
        if(!isValidEmail(email)){
            cout<<"\n*** Please enter valid email id ***\n\n";
            goto eml;
        }
        pss:cout<<"Enter password : ";
        cin>>this->pass;
        if (!isValidPassword(pass)) {
           cout << "\n\n*** Password is invalid. ***\n\n" << endl;
           goto pss;
        } 
        this->admin_id=++admid;
        admin_list.push_back(*this);
        this->saveToCSV_admins();
        cout<<"\n\nAdmin Registered Successfully\n\n";
    }
    int adm_login(){
        string adm_uname;
        string pwd;
        d : cout<<"\nEnter admin username : ";
        cin>>adm_uname;
        cout<<"Enter password : ";
        cin>>pwd;
        int f1=0,f2=0;
        for(int i=0;i<admin_list.size();i++){
            if(adm_uname==admin_list[i].name){
                f1=1;
                if(pwd==admin_list[i].pass){
                    cout<<"\n****** Login Successful ******\n\n";
                    f2=1;
                    return 1;
                }
                else{
                    cout<<"\nPassword is wrong\n";
                    break;
                }
            }
        }
        if(f1==0){
            cout<<"\nAdmin username is wrong\n";
        }
        else if(f1==1 && f2==0){
            cout<<"\nPassword is wrong\n";
        }
        e : cout<<"\n1.Try again\t2.Go back\n\n";
        int ch;
        string input;
        cin>>input;
        try{
            stringstream ss(input);
            if (!(ss >> ch) || !(ss.eof())) {
                throw invalid_argument("Input must be an integer.\n");
            }
            switch(ch){
                case 1:
                    goto d;
                    break;
                case 2:
                    return 0;
                default:
                    cout<<"\n\nChoose valid option\n\n";
                    goto e;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Invalid Argument: " << e.what() << endl;
            goto e;
        }
    }
    void view_users();
    void remove_user();
    void view_all_jobs();
    void remove_job();
    void view_system_report();
    void saveToCSV_admins();
};
application::application(){
    appl_resume=" ";
    cover_letter=" ";
    appl_id=0;
    appl_st=pending;
    job_ref = new job();
    applicant = new jobseeker();
}
job::job(){
    job_title=" ";
    job_type=" ";
    job_id=0;
    job_emp = new employer();
    job_descr=" ";
    salary=0.0;
    job_location=" ";
    // appl_list = new application()
}
jobseeker::jobseeker(){
    name=" ";
    email=" ";
    password=" ";
    resume=" ";
    job_prefr=new job_preferences();
}
employer::employer(){
        name=" ";
        email=" ";
        password=" ";
        company_name=" ";
        comp_location=" ";
        comp_description=" ";
    }
void application::view_appl_details(){
    cout<<"\nApplication ID : "<<this->appl_id<<endl;
    cout<<"Application status : "<<this->appl_st<<endl;
    this->job_ref->view_details();
    this->applicant->view_profile();
}
void job:: saveToCSV_jobs() {
    ofstream file("jobs.csv", ios::app);
    if (!file.is_open()) {
        throw runtime_error("Unable to open jobs.csv");
    }
    file << job_id << "," << job_title << "," << job_type << ","<< job_descr << ","<< salary << ","<< job_location << ","<< job_emp->company_name <<","<< job_emp->comp_location<<","<<job_emp->comp_description<<"," ;
    file << endl;
    file.close();
}
void loadJobs() {
    job jb;
    ifstream file("jobs.csv");

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << "jobs.csv" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id_str, title, type, job_descr, salary, job_location, emp_company_name,comp_location,comp_descr;
        long long id;
        float sal;

        getline(ss, id_str, ',');
        getline(ss, title, ',');
        getline(ss, type, ',');
        getline(ss, job_descr, ',');
        getline(ss, salary, ',');
        getline(ss, job_location, ',');
        getline(ss, emp_company_name, ',');
        getline(ss, comp_location, ',');
        getline(ss, comp_descr, ',');

        if (!id_str.empty() && !title.empty() && !type.empty() && !job_descr.empty() &&
            !salary.empty() && !job_location.empty() && !emp_company_name.empty() && !comp_location.empty() && !comp_descr.empty()) {
            id = stoll(id_str);
            sal = stof(salary);

            jb.job_id=id;
            jb.job_title=title;
            jb.job_type=type;
            jb.job_descr=job_descr;
            jb.salary=sal;
            jb.job_location=job_location;
            jb.job_emp->company_name=emp_company_name;
            jb.job_emp->comp_location=comp_location;
            jb.job_emp->comp_description=comp_descr;
            job_list.push_back(jb);
            auto it = find_if(emp_list.begin(), emp_list.end(),
                              [&](const employer& emp) { return emp.company_name == emp_company_name; });

            if (it != emp_list.end()) {
                it->posted_jobs.push_back(jb);
            }
        }
    }
    file.close();
}
void jobseeker::saveToCSV_jobseekers() {
    ofstream file("jobseekers.csv", ios::app);
    if (!file.is_open()) {
        throw runtime_error("Unable to open jobseekers.csv");
    }
    file << name << "," << email << "," << password<<","<<resume<<",";
    file << endl;
    file.close();
}
void loadJobseekers() {
    jobseeker jbs;
    ifstream file("jobseekers.csv");

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << "jobseekers.csv" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, email, password, resume;

        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');
        getline(ss, resume, ',');

        if (!name.empty() && !email.empty() && !password.empty() && !resume.empty()) {;
            jbs.name=name;
            jbs.email=email;
            jbs.password=password;
            jbs.resume=resume;
            jobseek_list.push_back(jbs);
        }
    }

    file.close();
    return;
}
void employer::saveToCSV_employers() {
        ofstream file("employers.csv", ios::app);
        if (!file.is_open()) {
            throw runtime_error("Unable to open employers.csv");
        }
        file << name << "," << email << "," <<password<<","<< company_name << ","<<comp_location<<","<<comp_description<<",";
        file << endl;
        file.close();
    }
void loadEmployers() {
    employer emp;
    ifstream file("employers.csv");

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << "employers.csv" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, email, password, company_name,company_location,company_description;

        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');
        getline(ss, company_name, ',');
        getline(ss, company_location, ',');
        getline(ss, company_description, ',');
        if (!name.empty() && !email.empty() && !password.empty() && !company_name.empty() && !company_description.empty() && !company_location.empty()) {
            emp.name=name;
            emp.email=email;
            emp.password=password;
            emp.company_name=company_name;
            emp.comp_location=company_location;
            emp.comp_description=company_description;
            emp_list.push_back(emp);
        }
    }
    file.close();
    return;
}
void admin::saveToCSV_admins(){
    ofstream file("admins.csv", ios::app);
    if (!file.is_open()) {
        throw runtime_error("Unable to open admins.csv");
    }
    file << name << "," << email << "," <<pass<<",";
    file << endl;
    file.close();
}
void loadAdmins(){
    admin adm;
    ifstream file("admins.csv");

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << "admins.csv" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, email, password;
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');
        if (!name.empty() && !email.empty() && !password.empty()) {
            adm.name=name;
            adm.email=email;
            adm.pass=password;
            admin_list.push_back(adm);
        }
    }
    file.close();
    return;
}
void application::saveApplication() {
    ofstream outFile("applications.txt", ios::app);
    if (outFile.is_open()) {
        outFile << applicant->name << "," << job_ref->job_title << "," << applicant->resume << "\n";
        outFile.close();
    } else {
        cerr << "Error opening file.\n";
    }
}
void job::view_details(){
    cout<<"\nJob id : "<<job_id<<endl;
    cout<<"Job title : "<<job_title<<endl;
    cout<<"Job type : "<<job_type<<endl;
    cout<<"Job salary : "<<salary<<endl;
    cout<<"Job employer details =>\n";
    cout<<"Company Name : "<<job_emp->company_name<<endl;
    cout<<"Company Location : "<<job_emp->comp_location<<endl;
}
void job::view_compt_details(){
    cout<<"\nJob id : "<<job_id<<endl;
    cout<<"Job title : "<<job_title<<endl;
    cout<<"Job type : "<<job_type<<endl;
    cout<<"Job salary : "<<salary<<endl;
    cout<<"Job employer details : \n"<<endl;
    cout<<"Company Name : "<<job_emp->company_name<<endl;
    cout<<"Company Location : "<<job_emp->comp_location<<endl;
    cout<<"Company Description : "<<job_emp->comp_description<<endl;
    cout<<"\nJob description : "<<this->job_descr<<endl;
    cout<<"Job requirements : \n";
    for(int i=0;i<this->requirements.size();i++){
        cout<<i+1<<". "<<this->requirements[i]<<endl;
    }
    cout<<"\nJob location : "<<job_location<<endl;
    cout<<"No. of applications recieved : "<<this->appl_list.size()<<endl;
}
void job::create_job(string jb_title, string description, vector<string> req, float sal, string location, string jb_type){
    cout << "\nCreating job...\n";
    cout << "\nJob Title: " << jb_title << "\nDescription: " << description << endl;
    cout << "Salary: " << sal << " \nLocation: " << location << endl;
    cout << "Requirements size: " << req.size() << endl;
    job_title = jb_title;
    job_descr = description;
    job_location = location;
    job_type = jb_type;
    salary = sal;
    for (int i = 0; i < req.size(); i++) {
        requirements.push_back(req[i]);
        cout << "Requirement " << i + 1 << ": " << req[i] << " added" << endl;
    }
    job_id = ++jobid;
    cout << "\nJob created successfully. Job ID: " << job_id << endl;
}
void job::update_job_details(){
    int ch,c,i,choice,r;
    string new_jb,new_comp,new_req,new_descr,new_location,input,inp;
    a : cout<<"\n1.Job Title\n2.Job description\n3.Job requirements\n4.Job salary\n\n5.Job location\n6.Job type\n\n";
    cout<<"\nChoose what to update : ";
    cin>>input;
    try{
        stringstream ss(input);
        if (!(ss >> c) || !(ss.eof())) {
            throw invalid_argument("Input must be an integer.\n");
        }
        switch(c){
            case 1:
                cout<<"\nEnter new job title : ";
                cin.ignore(); 
                getline(cin,new_jb);
                this->job_title=new_jb;
                break;
            case 2:
                cout<<"\nEnter new job description : ";
                cin.ignore(); 
                getline(cin,new_descr);
                this->job_descr=new_descr;
                break;
            case 3:
                b : cout<<"\n1.Want to update requirements\t2.Add new requirement\n\n";
                cout<<"Enter your choice : ";
                cin>>inp;
                try{
                    stringstream ss(inp);
                    if (!(ss >> ch) || !(ss.eof())) {
                        throw invalid_argument("Input must be an integer.\n");
                    }
                    switch(ch){
                        case 1: 
                            for(i=0;i<this->requirements.size();i++){
                                cout<<"\n"<<i+1<<". "<<this->requirements[i];
                            }
                            cout<<"\nEnter which requirement to update or change : ";
                            cin>>r;
                            cout<<"Enter new or updated requirement : ";
                            cin.ignore(); 
                            getline(cin,this->requirements[r-1]);
                            break;
                        case 2:
                            cout<<"\nEnter new requirement : ";
                            cin.ignore();
                            getline(cin,new_req);
                            this->requirements.push_back(new_req);
                            break;
                        default:
                            cout<<"\nEnter valid choice\n";
                            goto b;
                    }
                }
                catch (const invalid_argument& e) {
                    cerr << "Invalid Argument: " << e.what() << endl;
                    goto b;
                }
                break;
            case 4:
                cout<<"\nEnter new job salary : ";
                cin>>this->salary;
                break;
            case 5:
                cout<<"\nEnter new job location : ";
                cin>>this->job_location;
                break;
            case 6:
                cout<<"\nEnter new job type : ";
                cin>>this->job_type;
                break;
            default:
                cout<<"\nChoose valid option"<<endl;
                goto a;
        }
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid Argument: " << e.what() << endl;
        goto a;
    }
    ofstream file("jobs.csv", ios::out);
    if (!file.is_open()) {
        throw runtime_error("Unable to open jobs.csv");
    }
    for(int i=0;i<job_list.size();i++){
        file << job_list[i].job_id << "," << job_list[i].job_title << "," << job_list[i].job_type << ","<< job_list[i].job_descr << ","<< job_list[i].salary << ","<< job_list[i].job_location << ","<< job_list[i].job_emp->company_name <<","<< job_list[i].job_emp->comp_location<<","<<job_list[i].job_emp->comp_description<<"," ;
        file << endl;
    }
    file.close();
    return;
}
void job_preferences::create_job_pref(){
    int ch;
    string lc,jb,input,inp;
    cout<<"\nEnter prefered locations =>\n";
    j : cout<<"\nEnter location : ";
        cin.ignore();
        getline(cin,lc);
        locations.push_back(lc);
        option : cout<<"\n1.Want to add another location\t2.Done\n\n";
        cout<<"Enter choice : ";
        cin>>input;
        try{
            stringstream ss(input);
            if (!(ss >> ch) || !(ss.eof())) {
                throw invalid_argument("Input must be an integer.\n");
            }
            switch(ch){
                case 1:
                    goto j;
                    break;
                case 2:
                    break;
                default:
                    cout<<"\nEnter valid choice\n";
                    goto option;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Invalid Argument: " << e.what() << endl;
            goto option;
        }
    cout<<"\nEnter prefered job types : \n";
    i : cout<<"\nEnter job type :  ";
        cin.ignore();
        getline(cin,jb);
        locations.push_back(jb);
        opt : cout<<"\n1.Want to add another job type\t2.Done\n\n";
        cout<<"Enter choice : ";
        cin>>input;
        try{
            stringstream ss(input);
            if (!(ss >> ch) || !(ss.eof())) {
                throw invalid_argument("Input must be an integer.\n");
            }
            switch(ch){
                case 1:
                    goto i;
                    break;
                case 2:
                    break;
                default:
                    cout<<"\nEnter valid choice\n";
                    goto opt;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Invalid Argument: " << e.what() << endl;
            goto opt;
        }
}
void jobseeker::create_new_jobseeker(){
    register_user();
    cout<<"\nEnter experiences => \n";
    int ch=0;
    string input;
    f : experience expr;
        expr.create_exp();
        exp_list.push_back(expr);
        choice : cout<<"\n1.Want to add another experience\t2.Done\n\n";
        cout<<"Enter choice : ";
        cin>>input;
        try{
            stringstream ss(input);
            if (!(ss >> ch) || !(ss.eof())) {
                throw invalid_argument("Input must be an integer.\n");
            }
            switch(ch){
                case 1:
                    goto f;
                    break;
                case 2:
                    break;
                default:
                    cout<<"\nEnter valid choice\n";
                    goto choice;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Invalid Argument: " << e.what() << endl;
            goto choice;
        }
    cout<<"\nEnter education details=> \n";
    g : education edc;
        edc.create_edc();
        edu_list.push_back(edc);
        list : cout<<"\n1.Want to add another qualification\t2.Done\n\n";
        cout<<"Enter choice : ";
        cin>>input;
        try{
            stringstream ss(input);
            if (!(ss >> ch) || !(ss.eof())) {
                throw invalid_argument("Input must be an integer.\n");
            }
            switch(ch){
                case 1:
                    goto g;
                    break;
                case 2:
                    break;
                default:
                    cout<<"\nEnter valid choice\n";
                    goto list;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Invalid Argument: " << e.what() << endl;
            goto list;
        }
    cout<<"\nEnter skills => ";
    h : string skill;
        cout<<"\nEnter the skill : ";
        cin.ignore();
        getline(cin,skill);
        skills.push_back(skill);
        loop : cout<<"\n1.Want to add another skill\t2.Done\n\n";
        cout<<"Enter choice : ";
        cin>>input;
        try{
            stringstream ss(input);
            if (!(ss >> ch) || !(ss.eof())) {
                throw invalid_argument("Input must be an integer.\n");
            }
            switch(ch){
                case 1:
                    goto h;
                    break;
                case 2:
                    break;
                default:
                    cout<<"\nEnter valid choice\n";
                    goto loop;
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Invalid Argument: " << e.what() << endl;
            goto loop;
        }
    cout<<"\nEnter job preferences => \n";
    job_preferences jbp;
    jbp.create_job_pref();
    job_prefr=&jbp;
    jobseek_list.push_back(*this);
    this->saveToCSV_jobseekers();
    return;
}
int jobseeker::jbs_login(){
    int ch,c,size;
    string uname,pass,input;
    d : cout<<"\nEnter username : ";
    cin.ignore();
    getline(cin,uname);
    cout<<"\nEnter password : ";
    cin>>pass;
    int f1=0,f2=0;
    size=jobseek_list.size();
    for(int i=0;i<size;i++){
        if(uname==jobseek_list[i].name){
            f1=1;
            if(pass==jobseek_list[i].password){
                cout<<"\n****** Login Successful ******\n\n";
                f2=1;
                return 1;
            }
            else{
                cout<<"\nPassword is wrong\n";
                break;
            }
        }
    }
    if(f1==0){
        cout<<"\nUsername is wrong\n";
    }
    else if(f1==1 && f2==0){
        cout<<"\nPassword is wrong\n";
    }
    e : cout<<"\n1.Try again\t2.Go back\n\n";
    cout<<"Enter choice : ";
    cin>>input;
    try{
        stringstream ss(input);
        if (!(ss >> c) || !(ss.eof())) {
            throw invalid_argument("Input must be an integer.\n");
        }
        switch(c){
            case 1:
                goto d;
                break;
            case 2:
                return 0;
            default:
                cout<<"\n\nChoose valid option\n\n";
                goto e;
        }
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid Argument: " << e.what() << endl;
        goto e;
    }
}
void jobseeker::view_profile_jbs(){
    cout<<"\nName : "<<name;
    cout<<"\nEmail : "<<email;
    cout<<"\nExperiences =>\n";
    for(int i=0;i<this->exp_list.size();i++){
        cout<<"\n"<<i+1<<". \n";
        cout<<"Job title : "<<this->exp_list[i].job_title<<endl;
        cout<<"Company name : "<<this->exp_list[i].company_name<<endl;
        cout<<"Job duration : "<<this->exp_list[i].duration<<endl;
    }
    cout<<"\nEducation =>\n";
    for(int i=0;i<this->edu_list.size();i++){
        cout<<"\n"<<i+1<<". \n";
        cout<<"Qualification : "<<this->edu_list[i].name_of_grade<<endl;
        cout<<"Institute name : "<<this->edu_list[i].institute<<endl;
        cout<<"Year of completion : "<<this->edu_list[i].year_dur<<endl;
    }
    cout<<"\nSkills =>\n";
    for(int i=0;i<this->skills.size();i++){
        cout<<"\n"<<i+1<<". "<<this->skills[i];
    }
    return;
}
void jobseeker::apply_for_job(job &jb, string job_resume,string cover_ltr){
    application appl;
    appl.appl_resume=job_resume;
    appl.cover_letter=cover_ltr;
    application_id++;
    appl.appl_id=application_id;
    appl.appl_st=pending;
    appl.job_ref=&jb;
    appl.applicant=this;
    jb.appl_list.push_back(appl);
    this->applied_jobs.push_back(jb);
    this->app_list.push_back(appl);
    appl.saveApplication();
}
void jobseeker::view_applied_jobs(){
    if(applied_jobs.size()==0){
        cout<<"\nYou have not applied for any job\n\n";
        return;
    }
    for(int i=0;i<this->applied_jobs.size();i++){
        cout<<"Job "<<i+1<<" : \n";
        this->applied_jobs[i].view_details();
        cout<<"\n";
    }
    cout<<"\n\n";
    return;
}
void jobseeker::update_skills(){
    m : cout<<"\n1.Update a skill\t2.Add new skill\t3.Exit\n\n";
    int ch,f=0,c;
    string skl,up_skl,input,inp;
    cout<<"Enter option : ";
    cin>>input;
    try{
        stringstream ss(input);
        if (!(ss >> ch) || !(ss.eof())) {
            throw invalid_argument("Input must be an integer.\n");
        }
        switch(ch){
            case 1:
                up_skl : cout<<"Enter the skill to update : ";
                cin.ignore();
                getline(cin,skl);
                for(int i=0;i<this->skills.size();i++){
                    if(this->skills[i]==skl){
                        f=1;
                        cout<<"\nEnter updated skill : ";
                        cin.ignore();
                        getline(cin,up_skl);
                        this->skills.push_back(up_skl);
                        break;
                    }
                }
                if(f==0){
                    cout<<"\nSkill not found";
                }
                skill : cout<<"\n1.Want to update another skill\t2.Exit\n\n";
                cout<<"Choose an option : ";
                cin>>inp;
                try{
                    stringstream ss(input);
                    if (!(ss >> c) || !(ss.eof())) {
                        throw invalid_argument("Input must be an integer.\n");
                    }
                    switch(c){
                        case 1:
                            goto up_skl;
                            break;
                        case 2:
                            goto m;
                            break;
                        default:
                            cout<<"\nEnter valid option";
                            goto skill;
                    }
                }
                catch (const invalid_argument& e) {
                    cerr << "Invalid Argument: " << e.what() << endl;
                    goto skill;
                }
                break;
            case 2:
                cout<<"\nEnter skill to add : ";
                cin.ignore();
                getline(cin,skl);
                this->skills.push_back(skl);
                goto m;
                break;
            case 3:
                return;
                break;
            default:
                cout<<"\nEnter valid option : ";
                goto m;
        }
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid Argument: " << e.what() << endl;
        goto m;
    }
    return;
}
void jobseeker::search_jobs(){
    long long jb_id;
    string input;
    int f=0,ans;
    cout<<"\nEnter job id : ";
    cin>>jb_id;
    for(int i=0;i<job_list.size();i++){
        if(jb_id==job_list[i].job_id){
            f=1;
            job_list[i].view_compt_details();
            n:cout<<"\n\nWant to apply for job";
            cout<<"\n1.Yes\t2.No\n\n";
            cout<<"Choose an option : ";
            cin>>input;
            try{
                string rsm,cvr_ltr;
                stringstream ss(input);
                if (!(ss >> ans) || !(ss.eof())) {
                    throw invalid_argument("Input must be an integer.\n");
                }
                switch(ans){
                    case 1:
                        cout<<"\nEnter resume : ";
                        cin>>rsm;
                        cout<<"Enter cover letter : ";
                        cin>>cvr_ltr;
                        this->apply_for_job(job_list[i],rsm,cvr_ltr);
                        break;
                    case 2:
                        return;
                        break;
                    default:
                        cout<<"\nEnter valid option"<<endl;
                        goto n;
                }
            }
            catch (const invalid_argument& e) {
                cerr << "Invalid Argument: " << e.what() << endl;
                goto n;
            }
            break;
        }
    }
    if(f==0){
        cout<<"\nJob not found"<<endl;
    }
    return;
}
void jobseeker::update_experiences(){
    int ch,c,n;
    string new_jb,new_comp,new_dur,input;
    experience e;
    if(this->exp_list.size()==0){
        cout<<"\nNo experiences listed\n\n";
        return;
    }
    m : cout<<"\n1.Update an experience\t2.Add an experience\t3.Exit\n\n";
    cin>>input;
    try{
        stringstream ss(input);
        if (!(ss >> n) || !(ss.eof())) {
            throw invalid_argument("Input must be an integer.\n");
        }
        switch(n){
            case 1:
                for(int i=0;i<this->exp_list.size();i++){
                    cout<<"\n"<<i+1<<". Job title : "<<this->exp_list[i].job_title;
                }
                cout<<"\nChoose which experience to update : ";
                cin>>ch;
                a : cout<<"\n1.Job Title\t2.Company Name\t3.Work duration\n\n";
                cin>>c;
                switch(c){
                    case 1:
                        cout<<"\nEnter new job title : ";
                        cin.ignore();
                        getline(cin,new_jb);
                        this->exp_list[ch-1].job_title=new_jb;
                        break;
                    case 2:
                        cout<<"\nEnter new company name : ";
                        cin.ignore();
                        getline(cin,new_comp);
                        this->exp_list[ch-1].company_name=new_comp;
                        break;
                    case 3:
                        cout<<"\nEnter new work duration : ";
                        cin.ignore();
                        getline(cin,new_dur);
                        this->exp_list[ch-1].duration=new_dur;
                        break;
                    default:
                        cout<<"\nChoose valid option"<<endl;
                        goto a;
                }
                break;
            case 2:
                e.create_exp();
                this->exp_list.push_back(e);
                break;
            case 3:
                return;
                break;
            default:
                cout<<"\nEnter valid option\n";
                goto m;
        }
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid Argument: " << e.what() << endl;
        goto m;
    }
    goto m;
}
void jobseeker::track_application_status(){
    for(int i=0;i<this->app_list.size();i++){
        cout<<"\n"<<i+1<<". Job title : "<<this->app_list[i].job_ref->job_title<<endl;
        switch(this->app_list[i].appl_st){
            case 0:
                cout<<"Status : "<<"hired"<<endl;
                break;
            case 1:
                cout<<"Status : "<<"rejected"<<endl;
                break; 
            case 2:
                cout<<"Status : "<<"pending"<<endl;
                break;
            case 3:
                cout<<"Status : "<<"shortlisted"<<endl;
                break;    
        }
    }
}
void employer::create_new_employer(){
    register_user();
    cout<<"\nEnter company details => \n";
    cout<<"\nCompany name : ";
    cin.ignore();
    getline(cin,company_name);
    cout<<"\nCompany location : ";
    getline(cin,comp_location);
    cout<<"\nCompany description : ";
    getline(cin,comp_description);
    emp_list.push_back(*this);
    saveToCSV_employers();
    return;
}
int employer::emp_login(){
    int ch,c,size;
    string uname,pass,input;
    d : cout<<"\nEnter username : ";
    cin.ignore();
    getline(cin,uname);
    cout<<"\nEnter password : ";
    cin>>pass;
    int f1=0,f2=0;
    for(int i=0;i<emp_list.size();i++){
        if(uname==emp_list[i].name){
            f1=1;
            if(pass==emp_list[i].password){
                cout<<"\n****** Login Successful ******\n\n";
                f2=1;
                return 1;
            }
            else{
                cout<<"\nPassword is wrong\n";
                break;
            }
        }
    }
    if(f1==0){
        cout<<"\nUsername is wrong\n";
    }
    else if(f1==1 && f2==0){
        cout<<"\nPassword is wrong\n";
    }
    f : cout<<"\n1.Try again\t2.Go back\n\n";
    cin>>input;
    try{
        stringstream ss(input);
        if (!(ss >> c) || !(ss.eof())) {
            throw invalid_argument("Input must be an integer.\n");
        }
        switch(c){
            case 1:
                goto d;
                break;
            case 2:
                return 0;
            default:
                cout<<"\n\nChoose valid option\n\n";
                goto f;
        }
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid Argument: " << e.what() << endl;
        goto f;
    }
    goto f;
}
void employer::comp_details(){
    user::view_profile();
    cout<<"\nCompany name : "<<company_name<<endl;
    cout<<"\nCompany location : "<<comp_location<<endl;
    cout<<"\nCompany description : "<<comp_description<<endl;
}
void employer:: view_profile_emp(){
    cout<<"\nName : "<<name;
    cout<<"\nEmail : "<<email;
    cout<<"\nCompany name : "<<company_name;
    cout<<"\nCompany description : "<<comp_description;
    cout<<"\nCompany location : "<<comp_location<<endl;
}
void employer::post_job(string jb_title, string description, vector<string> req, float sal, string location, string jb_type) {
    job j;  
    cout << "\nEntered post_job\n";
    j.create_job(jb_title, description, req, sal, location, jb_type);
    employer e;
    j.job_emp->company_name=company_name;
    j.job_emp->comp_description=comp_description;
    j.job_emp->comp_location=comp_location;
    this->posted_jobs.push_back(j);  
    job_list.push_back(j);  
    j.saveToCSV_jobs();  
    return;
}
void employer::view_posted_jobs(){
    for(int i=0;i<this->posted_jobs.size();i++){
        cout<<"\n Job "<<i+1<<" =>"<<endl;
        cout<<"Job title : "<<this->posted_jobs[i].job_title<<endl;
        cout<<"Job type : "<<this->posted_jobs[i].job_type<<endl;
        cout<<"Job salary : "<<this->posted_jobs[i].salary<<endl;
        cout<<"Job location : "<<this->posted_jobs[i].job_location<<endl;
    }
    return;
}
void employer::review_applications(long long appl_id){
    int f=0;
    application *a = new application();
    if(applications_received.size()==0){
        cout<<"\n\n *** No applications received till now ***\n\n";
        return;
    }
    for(int i=0;i<this->applications_received.size();i++){
        if(appl_id==applications_received[i].appl_id){
            a=&applications_received[i];
            f=1;
            break;
        }
    }
    if(f==0){
        cout<<"\nApplication not found\n\n";
        return;
    }
    a->view_appl_details();
}
void employer::select_candidate(long long application_id){
    int f=0;
    for(int i=0;i<this->applications_received.size();i++){
        if(application_id==this->applications_received[i].appl_id){
            this->applications_received[i].appl_st=hired;
            f=1;
            break;
        }
    }
    if(f==0){
        cout<<"\nApplication not found\n";
        return;
    }
}
void employer::reject_candidate(long long application_id){
    int f=0;
    for(int i=0;i<this->applications_received.size();i++){
        if(application_id==this->applications_received[i].appl_id){
            this->applications_received[i].appl_st=rejected;
            f=1;
            break;
        }
    }
    if(f==0){
        cout<<"\nApplication not found\n";
        return;
    }
}
void employer::update_job(){
    int ch,c,i,choice,r;
    string new_jb,new_comp,new_req,new_descr,new_location;
    for(i=0;i<this->posted_jobs.size();i++){
        cout<<"\n"<<i+1<<".Job title : "<<this->posted_jobs[i].job_title;
    }
    cout<<"\nChoose which job to update : ";
    cin>>ch;
    this->posted_jobs[ch-1].update_job_details();
    return;
}
void employer::remove_job(){
    int ch,c,i;
    for(i=0;i<this->posted_jobs.size();i++){
        cout<<"\n"<<i+1<<". Job title : "<<this->posted_jobs[i].job_title;
    }
    cout<<"\nChoose which job to remove : ";
    cin>>ch;
    this->posted_jobs.erase(this->posted_jobs.begin() + (ch-1));
    return;
}
void admin::view_users(){
    cout<<"\n******* Job Seekers *******\n";
    for(int i=0;i<jobseek_list.size();i++){
        cout<<"\n"<<i+1<<".";
        jobseek_list[i].view_profile_jbs();
        cout<<endl;
    }
    cout<<"\n******* Employers *******\n";
    for(int i=0;i<emp_list.size();i++){
        cout<<"\n"<<i+1<<".";
        emp_list[i].view_profile_emp();
        cout<<endl;
    }
}
void admin::remove_user(){
    string uname;
    int f=0;
    cout<<"\nEnter username : ";
    cin.ignore();
    getline(cin,uname);
    for(int i=0;i<jobseek_list.size();i++){
        if(jobseek_list[i].name==uname){
            f=1;
            jobseek_list.erase(jobseek_list.begin() + i+1);
            break;
        }
    }
    if(f==0){
        for(int i=0;i<emp_list.size();i++){
            if(emp_list[i].name==uname){
                f=1;
                emp_list.erase(emp_list.begin() + i+1);
                break;
            }
        }
        if(f==0){
            cout<<"\nUser not found\n";
            return;
        }
    }
    return;
}
void admin::view_all_jobs(){
    cout<<"\n****** All Jobs ******\n";
    for(int i=0;i<job_list.size();i++){
        cout<<"\n"<<i+1<<". \n";
        job_list[i].view_details();
        cout<<endl;
    }
}
void admin::remove_job(){
    long long jb_id;
    cout<<"\nEnter job id : ";
    cin>>jb_id;
    int f=0;
    for(int i=0;i<job_list.size();i++){
        if(jb_id==job_list[i].job_id){
            f=1;
            job_list.erase(job_list.begin() + i+1);
            break;
        }
    }
    if(f==0){
        cout<<"\nJob not found\n\n\n";
        return;
    }
    return;
}
void admin::view_system_report(){
    cout<<"\n\nTotal no. of users : "<<jobseek_list.size() + emp_list.size();
    cout<<"\nTotal no. of jobseekers : "<<jobseek_list.size();
    cout<<"\nTotal no. of employers : "<<emp_list.size();
    cout<<"\nTotal jobs available : "<<job_list.size()<<endl<<endl;
    return;
}
int main()
{
    loadAdmins();
    loadEmployers();
    loadJobseekers();
    loadJobs();
    cout<<"\n\n****** Welcome to the online job portal ******\n\n";
    menu1 : cout<<"\n1.User\n2.Admin\n3.Exit\n";
    cout<<"\nSelect : ";
    string inp1,inp2,inp3,inp4,inp5,inp6,inp7,inp8;
    int m1,m2,m3,m4,m5,m6,m7,m8;
    long long app_id;
    employer emp;
    jobseeker jbs;
    job jb;
    admin adm;
    cin>>inp1;
    try{
        stringstream ss(inp1);
        if (!(ss >> m1) || !(ss.eof())) {
            throw invalid_argument("Input must be an integer.\n");
        }
        switch(m1){
            case 1:
                menu2 : cout<<"\n1.Register\n2.Login\n3.Go back\n";
                cout<<"\nSelect : ";
                cin>>inp2;
                try{
                    stringstream ss(inp2);
                    if (!(ss >> m2) || !(ss.eof())) {
                        throw invalid_argument("Input must be an integer.\n");
                    }
                    switch(m2){
                        case 1:
                            menu3 : cout<<"\n1.Employer\n2.Job seeker\n3.Go back\n\n";
                            cout<<"\nSelect : ";
                            cin>>inp3;
                            try{
                                stringstream ss(inp3);
                                if (!(ss >> m3) || !(ss.eof())) {
                                throw invalid_argument("Input must be an integer.\n");
                                }
                                switch(m3){
                                    case 1:
                                        emp.create_new_employer();
                                        cout<<"\n\n##### Successfully Registered #####\n";
                                        cout<<"\n\nPress any key to proceed\n\n";
                                        getch();
                                        system("cls");
                                        break;
                                    case 2:
                                        jbs.create_new_jobseeker();
                                        cout<<"\n\n##### Successfully Registered #####\n";
                                        cout<<"\n\nPress any key to proceed\n\n";
                                        getch();
                                        system("cls");
                                        break;
                                    case 3:
                                        goto menu2;
                                        break;
                                    default:
                                        cout<<"\n\nChoose valid option\n\n";
                                        goto menu3;
                                }
                            }
                            catch (const invalid_argument& e) {
                                cerr << "Invalid Argument: " << e.what() << endl;
                                goto menu3;
                            }
                            goto menu3;
                            break;
                        case 2:
                            menu4 : cout<<"\n1.Job seeker\n2.Employer\n3.Go back\n\n";
                            cout<<"\nSelect : ";
                            cin>>inp4;
                            try{
                                stringstream ss(inp4);
                                if (!(ss >> m4) || !(ss.eof())) {
                                throw invalid_argument("Input must be an integer.\n");
                                }
                                switch(m4){
                                    case 1:
                                        if(jbs.jbs_login()){
                                            jobseeker *jbs_ptr = new jobseeker();
                                            for(int i=0;i<jobseek_list.size();i++){
                                                if(jbs.name==jobseek_list[i].name){
                                                    jbs_ptr=&jobseek_list[i];
                                                    break;
                                                }
                                            }
                                            menu7 : cout<<"\n1.Apply for job\n2.Update resume\n3.View applied jobs\n4.Update skills\n5.Search jobs\n6.Update experiences\n7.Track application status\n8.View profile\n9.Log out\n\n";
                                            cout<<"Enter choice : ";
                                            cin>>inp7;
                                            string rsm,cvr_ltr,n_rsm;
                                            long long jb_id;
                                            int f=0,target,c;
                                            try{
                                                stringstream ss(inp7);
                                                if (!(ss >> m7) || !(ss.eof())) {
                                                    throw invalid_argument("Input must be an integer.\n");
                                                }
                                                switch(m7){
                                                    case 1:
                                                        jobid : cout<<"Enter job id : ";
                                                        cin>>jb_id;
                                                        for(int i=0;i<job_list.size();i++){
                                                            if(job_list[i].job_id==jb_id){
                                                                f=1;
                                                                target=i;
                                                                break;
                                                            }
                                                        }
                                                        if(f==0){
                                                            cout<<"\nJob not found\nEnter valid job id\n";
                                                            ch : cout<<"\n1.Want to search another job\t2.Exit\n\n";
                                                            cout<<"Enter option : ";
                                                            cin>>c;
                                                            switch(c){
                                                                case 1:
                                                                    goto jobid;
                                                                    break;
                                                                case 2:
                                                                    goto menu7;
                                                                    break;
                                                                default :
                                                                    cout<<"\nChoose valid optio\n";
                                                                    goto ch;
                                                            }
                                                        }
                                                        else{
                                                            job j=job_list[target];
                                                            cout<<"\nEnter resume : ";
                                                            cin>>rsm;
                                                            cout<<"Enter cover letter : ";
                                                            cin>>cvr_ltr;
                                                            jbs_ptr->apply_for_job(job_list[target],rsm,cvr_ltr);
                                                            cout<<"\n******* You successfully applied for job ******\n\n";
                                                        }
                                                        
                                                        getch();
                                                        system("cls");
                                                        break;
                                                    case 2:
                                                        cout<<"Enter new resume : ";
                                                        cin>>n_rsm;
                                                        jbs_ptr->update_resume(n_rsm);
                                                        cout<<"\n******* Resume has been updated successfully ******\n\n";
                                                        break;
                                                    case 3:
                                                        jbs_ptr->view_applied_jobs();
                                                        getch();
                                                        system("cls");
                                                        break;
                                                    case 4:
                                                        jbs_ptr->update_skills();
                                                        cout<<"\n******* Skills have been updated successfully ******\n\n";
                                                        getch();
                                                        system("cls");
                                                        break;
                                                    case 5:
                                                        jbs_ptr->search_jobs();
                                                        getch();
                                                        system("cls");
                                                        break;
                                                    case 6:
                                                        jbs_ptr->update_experiences();
                                                        cout<<"\n******* Experiences have been updated successfully ******\n\n";
                                                        getch();
                                                        system("cls");
                                                        break;
                                                    case 7:
                                                        jbs_ptr->track_application_status();
                                                        break;
                                                    case 8:
                                                        jbs_ptr->view_profile_jbs();
                                                        getch();
                                                        system("cls");
                                                        break;
                                                    case 9:
                                                        jbs_ptr->logout();
                                                        goto menu2;
                                                        break;
                                                    default:
                                                        cout<<"\nEnter valid choice\n";
                                                        goto menu7;
                                                }
                                            }
                                            catch (const invalid_argument& e) {
                                                cerr << "Invalid Argument: " << e.what() << endl;
                                                goto menu7;
                                            }
                                            goto menu7;
                                        }
                                        break;
                                    case 2:
                                        if(emp.emp_login()){
                                            employer *emp_ptr = new employer;
                                            for(int i=0;i<emp_list.size();i++){
                                                if(emp.name==emp_list[i].name){
                                                    emp_ptr=&emp_list[i];
                                                    break;
                                                }
                                            }
                                            menu8 : cout<<"\n1.View profile\n2.Post a job\n3.View posted jobs\n4.Review application\n5.Select a candidate\n6.Reject a candidate\n7.Update a job\n8.Remove a job\n9.Log out\n\n";
                                            cout<<"Enter choice : ";
                                            cin>>inp8;
                                            string jb_title,jb_type,req,lctn,descr;
                                            float s;
                                            vector <string> r;
                                            int f=0,target,c=0;
                                            job *j;
                                            try{
                                                stringstream ss(inp8);
                                                if (!(ss >> m8) || !(ss.eof())) {
                                                    throw invalid_argument("Input must be an integer.\n");
                                                }
                                                switch(m8){
                                                    case 1:
                                                        emp_ptr->view_profile_emp();
                                                        getch();
                                                        system("cls");
                                                        break;
                                                    case 2:
                                                        cout<<"Enter job title : ";
                                                        cin.ignore();
                                                        getline(cin,jb_title);
                                                        cout<<"Enter job type : ";
                                                        getline(cin,jb_type);
                                                        cout<<"Enter job location : ";
                                                        getline(cin,lctn);
                                                        cout<<"Enter job description : ";
                                                        getline(cin,descr);
                                                        cout<<"Enter job salary : ";
                                                        cin>>s;
                                                        cout<<"Enter job requirements : \n";
                                                        r : cout<<"\nEnter requirement : ";
                                                        cin>>req;
                                                        r.push_back(req);
                                                        skill : cout<<"\n1.Want to add another requirement\t2.Done\n\n";
                                                        cout<<"Choose an option : ";
                                                        cin>>c;
                                                        switch(c){
                                                            case 1:
                                                                goto r;
                                                                break;
                                                            case 2:
                                                                break;
                                                            default:
                                                                cout<<"\nEnter valid option";
                                                                goto skill;
                                                        }
                                                        emp_ptr->post_job(jb_title,descr,r,s,lctn,jb_type);
                                                        cout<<"\n\n***** Job posted successfully *****\n\n";
                                                        getch();
                                                        system("cls");
                                                        break;
                                                    case 3:
                                                        emp_ptr->view_posted_jobs();
                                                        getch();
                                                        system("cls");
                                                        break;
                                                    case 4:
                                                        cout<<"\nEnter candidate application id : ";
                                                        cin>>app_id;
                                                        emp_ptr->review_applications(app_id);
                                                        cout<<"\n******* Application reviewed successfully ******\n\n";
                                                        break;
                                                    case 5:
                                                        cout<<"\nEnter candidate application id : ";
                                                        cin>>app_id;
                                                        emp_ptr->select_candidate(app_id);
                                                        cout<<"\n******* Candidate selected successfully ******\n\n";
                                                        break;
                                                    case 6:
                                                        cout<<"\nEnter candidate application id : ";
                                                        cin>>app_id;
                                                        emp_ptr->reject_candidate(app_id);
                                                        cout<<"\n******* Candidate rejection done ******\n\n";
                                                        break;
                                                    case 7:
                                                        emp_ptr->update_job();
                                                        cout<<"\n******* Job updated successfully ******\n\n";
                                                        getch();
                                                        system("cls");
                                                        break;
                                                    case 8:
                                                        emp_ptr->remove_job();
                                                        cout<<"\n******* Job removed successfully ******\n\n";
                                                        goto menu2;
                                                        break;
                                                    case 9:
                                                        goto menu2;
                                                        break;
                                                    default:
                                                        cout<<"\nEnter valid choice\n";
                                                        goto menu8;
                                                }
                                            }
                                            catch (const invalid_argument& e) {
                                                cerr << "Invalid Argument: " << e.what() << endl;
                                                goto menu8;
                                            }
                                            goto menu8;
                                        }
                                        break;
                                    case 3:
                                        goto menu2;
                                        break;
                                    default:
                                        cout<<"\n\nChoose valid option\n\n";
                                        goto menu4;
                                }
                            }
                            catch (const invalid_argument& e) {
                                cerr << "Invalid Argument: " << e.what() << endl;
                                goto menu4;
                            }
                            goto menu4;
                            break;
                        case 3:
                            goto menu1;
                            break;
                        default:
                            cout<<"\n\nChoose valid option\n\n";
                            goto menu2;
                    }
                }
                catch (const invalid_argument& e) {
                    cerr << "Invalid Argument: " << e.what() << endl;
                    goto menu2;
                }
                goto menu2;
                break;
            case 2:
                menu5 : cout<<"\n\n1.Register\n2.Login\n3.Go back\n\n";
                cout<<"Select : ";
                cin>>inp5;
                try{
                    stringstream ss(inp5);
                    if (!(ss >> m5) || !(ss.eof())) {
                        throw invalid_argument("Input must be an integer.\n");
                    }
                    switch(m5){
                        case 1:
                            adm.adm_register();
                            break;
                        case 2:
                            if(adm.adm_login()){
                                menu6 : cout<<"\n1.View all users\n2.Remove an user\n3.View all jobs\n4.Remove a job\n5.View system report\n6.Log out\n\n";
                                cout<<"Select : ";
                                cin>>inp6;
                                try{
                                    stringstream ss(inp6);
                                    if (!(ss >> m6) || !(ss.eof())) {
                                        throw invalid_argument("Input must be an integer.\n");
                                    }
                                    switch(m6){
                                        case 1:
                                            adm.view_users();
                                            getch();
                                            system("cls");
                                            break;
                                        case 2:
                                            adm.remove_user();
                                            break;
                                        case 3:
                                            adm.view_all_jobs();
                                            getch();
                                            system("cls");
                                            break;
                                        case 4:
                                            adm.remove_job();
                                            break;
                                        case 5:
                                            adm.view_system_report();
                                            break;
                                        case 6:
                                            goto menu5;
                                            break;
                                        default:
                                            cout<<"\nChoose valid option\n\n";
                                            goto menu6;
                                    }
                                }
                                catch (const invalid_argument& e) {
                                    cerr << "Invalid Argument: " << e.what() << endl;
                                    goto menu6;
                                }
                                goto menu6;
                            }
                            else{
                                goto menu5;
                            }
                            break;
                        case 3:
                            goto menu1;
                            break;
                        default:
                            cout<<"\n\nChoose valid option\n\n";
                            goto menu5;
                    }
                }
                catch (const invalid_argument& e) {
                    cerr << "Invalid Argument: " << e.what() << endl;
                    goto menu5;
                }
                goto menu5;
                break;
            case 3:
                exit(0);
                break;
            default:
                cout<<"\n\nChoose valid option\n\n";
                goto menu1;
        }
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid Argument: " << e.what() << endl;
        goto menu1;
    }
}
