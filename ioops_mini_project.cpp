#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <map>
#include <stdexcept>
#include<conio.h>
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

vector <employer*> emp_list;
vector <jobseeker*> jobseek_list;
vector <job*> job_list;
vector <admin*> admin_list; 

class user{
    public:
    string name,email,password,user_type;
    void register_user(){
        int ch;
        cout<<"\nEnter name : ";
        cin.ignore(); 
        getline(cin,this->name);
        cout<<"Enter email : ";
        cin>>this->email;
        cout<<"Enter password : ";
        cin>>this->password;
    }
    void update_profile(){
        int ch;
        a : cout<<"\n1.Name\t2.Email\t3.Password\n\n";
        cout<<"Enter choice : ";
        cin>>ch;
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
    virtual void view_profile(){
        cout<<"\nName : "<<name<<endl;
        cout<<"Email : "<<email<<endl;
    }
};
class experience{
    public:
    string job_title,company_name,duration;
    void create_exp(){
        cout<<"\nEnter job title : ";
        cin.ignore(); 
        getline(cin,job_title);
        cout<<"Enter company name : ";
        cin.ignore(); 
        getline(cin,company_name);
        cout<<"Enter job duration : ";
        cin.ignore(); 
        getline(cin,duration);
        return;
    }
};
class education{
    public:
    string name_of_grade,institute;
    int year_dur;
    void create_edc(){
        cout<<"\nEnter name of qualification : ";
        cin.ignore(); 
        getline(cin,name_of_grade);
        cout<<"Enter institute or place from where you complete qualification : ";
        cin.ignore(); 
        getline(cin,institute);
        cout<<"Enter year of completion : ";
        cin>>year_dur;
    }
};
enum status{hired,rejected,pending,shortlisted};
class application{
    public:
    string appl_resume,cover_letter;
    long long appl_id;
    status appl_st;
    job *job_ref;
    jobseeker *applicant;
    void view_appl_details();
    void update_appl_status(){
        int ch;
        c : cout<<"\n1.Hired\t2.Rejected\t3.Pending\t4.Shortlisted\n\n";
        cout<<"Enter updated status : ";
        cin>>ch;
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
        return;
    }
    void view_appl_status(){
        cout<<"Application status : "<<this->appl_st<<endl;
    }
    void withdraw_application(){

    }
    void saveApplication();
};

long long jobid=9000000;
class job{
    public:
    string job_title,job_type;
    long long job_id;
    employer *job_emp;
    string job_descr;
    vector <string> requirements;
    float salary;
    string job_location;
    vector <application*> appl_list;
    void view_details();
    void view_compt_details();
    void create_job(string jb_title, string description, vector<string> req, float sal, string location, string jb_type);
    void update_job_details();
    void close_job(){

    }
    void saveToFile();
};
long long application_id=1000000;
class jobseeker:public user{
    public:
    string resume;
    vector <experience*> exp_list;
    vector <education*> edu_list;
    vector <string> skills;
    vector <job*> applied_jobs;
    vector <application*> app_list;
    job_preferences *job_prefr;
    void create_new_jobseeker();
    int jbs_login();
    void view_profile() override;
    void apply_for_job(job *jb, string job_resume,string cover_ltr=NULL);
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
        ofstream outFile;
        outFile.open("jobseekers.txt", ios::app); 
        if (outFile.is_open()) {
            outFile << name << "," << email << "," << resume << "\n";
            outFile.close();
        } else {
            cerr << "Error opening file.\n";
        }
    }
};
class job_preferences{
    public:
    vector <string> locations;
    vector <string> job_type;
    string salary_range;
    void create_job_pref();
};
class company_profile{
    public:
    string comp_location,comp_description;
    void create_comp_prof(){
        cout<<"\nEnter comp_description : ";
        cin.ignore(); 
        getline(cin,comp_description);
        cout<<"Enter company location : ";
        cin.ignore(); 
        getline(cin,comp_location);
    }
    void view_comp_prof(){
        cout<<"\nCompany description : "<<comp_description<<endl;
        cout<<"Company location : "<<comp_location<<endl;
    }
};
class employer:public user{
    public:
    string company_name;
    company_profile *comp_prof;
    vector <job*> posted_jobs;
    vector <application*> applications_received;
    void create_new_employer();
    int emp_login();
    void view_profile() override{
        user::view_profile();
        cout<<"\nCompany name : "<<company_name<<endl;
    }
    void comp_details();
    void post_job(string jb_title, string description, vector<string> req, float sal, string location, string jb_type);
    void view_posted_jobs();
    void review_applications(long long appl_id){

    }
    void select_candidate(long long application_id);
    void reject_candidate(long long application_id);
    void update_job();
    void remove_job();
    void saveEmployerProfile();
};
long long admid=7000000;
class admin{
    public:
    string name,email,pass;
    long long admin_id;
    void adm_register(){
        cout<<"\nEnter name : ";
        cin.ignore(); 
        getline(cin,name);
        cout<<"Enter email : ";
        cin>>this->email;
        cout<<"Enter password : ";
        cin>>this->pass;
        this->admin_id=++admid;
        admin_list.push_back(this);
    }
    int adm_login(){
        long long adm_id;
        string pwd;
        d : cout<<"\nEnter admin id : ";
        cin>>adm_id;
        cout<<"Enter password : ";
        cin>>pwd;
        int f1=0,f2=0;
        for(int i=0;i<admin_list.size();i++){
            if(adm_id==admin_list[i]->admin_id){
                f1=1;
                if(pwd==admin_list[i]->pass){
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
            cout<<"\nAdmin id is wrong\n";
        }
        else if(f1==1 && f2==0){
            cout<<"\nPassword is wrong\n";
        }
        e : cout<<"\n1.Try again\t2.Go back\n\n";
        int ch;
        cin>>ch;
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
    void view_users();
    void remove_user();
    void view_all_jobs();
    void remove_job();
    void view_system_report();
};
void application::view_appl_details(){
    cout<<"\nApplication ID : "<<this->appl_id<<endl;
    cout<<"Application status : "<<this->appl_st<<endl;
    this->job_ref->view_details();
    this->applicant->view_profile();
}
void job::saveToFile() {
    ofstream outFile("jobs.txt", ios::app); 
    if (outFile.is_open()) {
        outFile << job_title << "," << job_descr << "," << job_emp->company_name << "," << salary << "\n";
        outFile.close();
    } else {
        cerr << "Error opening file.\n";
    }
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
void employer::saveEmployerProfile() {
    ofstream outFile("employers.txt", ios::app);
    if (outFile.is_open()) {
        outFile << company_name << "," << email << "," << comp_prof->comp_description << "\n";
        outFile.close();
        cout << "Employer profile saved successfully.\n";
    } else {
        cerr << "Error opening file to save employer details.\n";
    }
}
void job::view_details(){
    cout<<"\nJob id : "<<job_id<<endl;
    cout<<"Job title : "<<job_title<<endl;
    cout<<"Job type : "<<job_type<<endl;
    cout<<"Job salary : "<<salary<<endl;
    cout<<"Job employer : "<<job_emp->company_name<<endl;
}
void job::view_compt_details(){
    cout<<"\nJob id : "<<job_id<<endl;
    cout<<"Job title : "<<job_title<<endl;
    cout<<"Job type : "<<job_type<<endl;
    cout<<"Job salary : "<<salary<<endl;
    cout<<"Job employer details : \n"<<endl;
    job_emp->comp_details();
    cout<<"\nJob description : "<<job_descr<<endl;
    cout<<"Job requirements : \n";
    for(int i=0;i<this->requirements.size();i++){
        cout<<i+1<<". "<<this->requirements[i]<<endl;
    }
    cout<<"\nJob location : "<<job_location<<endl;
    cout<<"No. of applications recieved : "<<this->appl_list.size()<<endl;
}
void job::create_job(string jb_title, string description, vector<string> req, float sal, string location, string jb_type){
    this->job_title=jb_title;
    this->job_descr=description;
    this->requirements=req;
    this->job_id=++jobid;
    this->job_type=jb_type;
    this->salary=sal;
    this->job_location=location;
    this->saveToFile();
    return;
}
void job::update_job_details(){
    int ch,c,i,choice,r;
    string new_jb,new_comp,new_req,new_descr,new_location;
    a : cout<<"\n1.Job Title\t2.Job description\t3.Job requirements\t4.Job salary\n\t5.Job location\t6.Job type\n\n";
    cin>>c;
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
            cin>>choice;
            switch(choice){
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
    return;
}

void job_preferences::create_job_pref(){
    int ch;
    string lc,jb;
    cout<<"\nEnter prefered locations =>\n";
    do{
        cout<<"\nEnter location : ";
        cin.ignore();
        getline(cin,lc);
        locations.push_back(lc);
        option : cout<<"\n1.Want to add another location\t2.Done\n\n";
        cout<<"Enter choice : ";
        cin>>ch;
        if(ch!=1 && ch!=2){
            cout<<"\nEnter valid choice\n";
            goto option;
        }
    }while(ch!=2);
    cout<<"\nEnter prefered job types : \n";
    do{
        cout<<"\nEnter job type :  ";
        cin.ignore();
        getline(cin,jb);
        locations.push_back(jb);
        opt : cout<<"\n1.Want to add another job type\t2.Done\n\n";
        cout<<"Enter choice : ";
        cin>>ch;
        if(ch!=1 && ch!=2){
            cout<<"\nEnter valid choice\n";
            goto opt;
        }
    }while(ch!=2);
}
void jobseeker::create_new_jobseeker(){
    register_user();
    cout<<"\nEnter experiences => \n";
    int ch=0;
    do{
        experience expr;
        expr.create_exp();
        exp_list.push_back(&expr);
        choice : cout<<"\n1.Want to add another experience\t2.Done\n\n";
        cout<<"Enter choice : ";
        cin>>ch;
        if(ch!=1 && ch!=2){
            cout<<"\nEnter valid choice\n";
            goto choice;
        }
    }while(ch!=2);
    cout<<"\nEnter education details=> \n";
    do{
        education edc;
        edc.create_edc();
        edu_list.push_back(&edc);
        list : cout<<"\n1.Want to add another qualification\t2.Done\n\n";
        cout<<"Enter choice : ";
        cin>>ch;
        if(ch!=1 && ch!=2){
            cout<<"\nEnter valid choice\n";
            goto list;
        }
    }while(ch!=2);
    cout<<"\nEnter skills => ";
    do{
        string skill;
        cout<<"\nEnter the skill : ";
        cin.ignore();
        getline(cin,skill);
        skills.push_back(skill);
        loop : cout<<"\n1.Want to add another skill\t2.Done\n\n";
        cout<<"Enter choice : ";
        cin>>ch;
        if(ch!=1 && ch!=2){
            cout<<"\nEnter valid choice\n";
            goto loop;
        }
    }while(ch!=2);
    cout<<"\nEnter job preferences => \n";
    job_preferences jbp;
    jbp.create_job_pref();
    job_prefr=&jbp;
    jobseek_list.push_back(this);
    this->saveProfile();
    return;
}
int jobseeker::jbs_login(){
    int ch,c,size;
    string uname,pass;
    d : cout<<"\nEnter username : ";
    cin.ignore();
    getline(cin,uname);
    cout<<"\nEnter password : ";
    cin>>pass;
    int f1=0,f2=0;
    size=jobseek_list.size();
    for(int i=0;i<size;i++){
        if(uname==jobseek_list[i]->name){
            f1=1;
            if(pass==jobseek_list[i]->password){
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
    cin>>c;
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
void jobseeker::view_profile(){
    user::view_profile();
    cout<<"\nExperiences =>\n";
    for(int i=0;i<this->exp_list.size();i++){
        cout<<"\n"<<i+1<<". \n";
        cout<<"Job title : "<<this->exp_list[i]->job_title<<endl;
        cout<<"Company name : "<<this->exp_list[i]->company_name<<endl;
        cout<<"Job duration : "<<this->exp_list[i]->duration<<endl;
    }
    cout<<"\nEducation =>\n";
    for(int i=0;i<this->edu_list.size();i++){
        cout<<"\n"<<i+1<<". \n";
        cout<<"Qualification : "<<this->edu_list[i]->name_of_grade<<endl;
        cout<<"Institute name : "<<this->edu_list[i]->institute<<endl;
        cout<<"Year of completion : "<<this->edu_list[i]->year_dur<<endl;
    }
    cout<<"\nSkills =>\n";
    for(int i=0;i<this->skills.size();i++){
        cout<<"\n"<<i+1<<". "<<this->skills[i];
    }
    return;
}
void jobseeker::apply_for_job(job *jb, string job_resume,string cover_ltr){
    application appl;
    appl.appl_resume=job_resume;
    appl.cover_letter=cover_ltr;
    appl.appl_id=++application_id;
    appl.appl_st=pending;
    appl.job_ref=jb;
    appl.applicant=this;
    jb->appl_list.push_back(&appl);
    jb->job_emp->applications_received.push_back(&appl);
    this->applied_jobs.push_back(jb);
    this->app_list.push_back(&appl);
    appl.saveApplication();
}
void jobseeker::view_applied_jobs(){
    for(int i=0;i<this->applied_jobs.size();i++){
        cout<<"Job "<<i+1<<" : \n";
        this->applied_jobs[i]->view_details();
        cout<<"\n";
    }
    return;
}
void jobseeker::update_skills(){
    m : cout<<"\n1.Update a skill\t2.Add new skill\t3.Exit\n\n";
    int ch,f=0,c;
    cout<<"Enter option : ";
    cin>>ch;
    string skl,up_skl;
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
            cin>>c;
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
    return;
}
void jobseeker::search_jobs(){
    long long jb_id;
    int f=0,ans;
    cout<<"\nEnter job id : ";
    cin>>jb_id;
    for(int i=0;i<job_list.size();i++){
        if(jb_id==job_list[i]->job_id){
            f=1;
            job_list[i]->view_compt_details();
            cout<<"\n\nWant to apply for job";
            n : cout<<"\n1.Yes\t2.No\n\n";
            cout<<"Choose an option : ";
            cin>>ans;
            string rsm,cvr_ltr;
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
    string new_jb,new_comp,new_dur;
    experience e;
    cout<<"\n1.Update an experience\t2.Add an experience\t3.Exit\n\n";
    cin>>n;
    switch(n){
        case 1:
            for(int i=0;i<this->exp_list.size();i++){
                cout<<"\n"<<i+1<<". Job title : "<<this->exp_list[i]->job_title;
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
                    this->exp_list[ch-1]->job_title=new_jb;
                    break;
                case 2:
                    cout<<"\nEnter new company name : ";
                    cin.ignore();
                    getline(cin,new_comp);
                    this->exp_list[ch-1]->company_name=new_comp;
                    break;
                case 3:
                    cout<<"\nEnter new work duration : ";
                    cin.ignore();
                    getline(cin,new_dur);
                    this->exp_list[ch-1]->duration=new_dur;
                    break;
                default:
                    cout<<"\nChoose valid option"<<endl;
                    goto a;
            }
                    break;
        case 2:
            e.create_exp();
            this->exp_list.push_back(&e);
            break;
        case 3:
            return;
            break;
    }
}
void jobseeker::track_application_status(){
    for(int i=0;i<this->app_list.size();i++){
        cout<<"\n"<<i+1<<". Job title : "<<this->app_list[i]->job_ref->job_title<<endl;
        cout<<"Status : "<<this->app_list[i]->appl_st<<endl;
    }
}
void employer::create_new_employer(){
    register_user();
    cout<<"\nCompany name : ";
    cin.ignore();
    getline(cin,company_name);
    cout<<"\nEnter company details => \n";
    company_profile cmp;
    cmp.create_comp_prof();
    comp_prof=&cmp;
    emp_list.push_back(this);
    saveEmployerProfile();
    return;
}
int employer::emp_login(){
    int ch,c,size;
    string uname,pass;
    d : cout<<"\nEnter username : ";
    cin.ignore();
    getline(cin,uname);
    cout<<"\nEnter password : ";
    cin>>pass;
    int f1=0,f2=0;
    for(int i=0;i<emp_list.size();i++){
        if(uname==emp_list[i]->name){
            f1=1;
            if(pass==emp_list[i]->password){
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
    cin>>c;
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
    goto f;
}
void employer::comp_details(){
    user::view_profile();
    cout<<"\nCompany name : "<<company_name<<endl;
    comp_prof->view_comp_prof();
}
void employer::post_job(string jb_title, string description, vector<string> req, float sal, string location, string jb_type){
    job j;
    j.create_job(jb_title,description,req,sal,location,jb_type);
    j.job_emp->company_name=this->company_name;
    j.job_emp->comp_prof->comp_description=this->comp_prof->comp_description;
    j.job_emp->comp_prof->comp_location=this->comp_prof->comp_location;
    this->posted_jobs.push_back(&j);
    j.job_emp->posted_jobs=this->posted_jobs;
    job_list.push_back(&j);
}
void employer::view_posted_jobs(){
    for(int i=0;i<this->posted_jobs.size();i++){
        cout<<"\n Job "<<i+1<<endl;
        cout<<"Job title : "<<this->posted_jobs[i]->job_title<<endl;
        cout<<"Job type : "<<this->posted_jobs[i]->job_type<<endl;
        cout<<"Job salary : "<<this->posted_jobs[i]->salary<<endl;
        cout<<"Job location : "<<this->posted_jobs[i]->job_location<<endl;
    }
    return;
}
void employer::select_candidate(long long application_id){
    int f=0;
    for(int i=0;i<this->applications_received.size();i++){
        if(application_id==this->applications_received[i]->appl_id){
            this->applications_received[i]->appl_st=hired;
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
        if(application_id==this->applications_received[i]->appl_id){
            this->applications_received[i]->appl_st=rejected;
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
        cout<<"\n"<<i+1<<". Job title : "<<this->posted_jobs[i]->job_title;
    }
    cout<<"\nChoose which job to update : ";
    cin>>ch;
    this->posted_jobs[ch-1]->update_job_details();
    return;
}
void employer::remove_job(){
    int ch,c,i;
    for(i=0;i<this->posted_jobs.size();i++){
        cout<<"\n"<<i+1<<". Job title : "<<this->posted_jobs[i]->job_title;
    }
    cout<<"\nChoose which job to remove : ";
    cin>>ch;
    this->posted_jobs.erase(this->posted_jobs.begin() + (ch-1));
    return;
}
void admin::view_users(){
    cout<<"\n******* Job Seekers *******\n";
    for(int i=0;i<jobseek_list.size();i++){
        cout<<"\n"<<i+1<<".\n";
        jobseek_list[i]->view_profile();
        cout<<endl;
    }
    cout<<"\n******* Employers *******\n";
    for(int i=0;i<emp_list.size();i++){
        cout<<"\n"<<i+1<<".\n";
        emp_list[i]->view_profile();
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
        if(jobseek_list[i]->name==uname){
            f=1;
            jobseek_list.erase(jobseek_list.begin() + i+1);
            break;
        }
    }
    if(f==0){
        for(int i=0;i<emp_list.size();i++){
            if(emp_list[i]->name==uname){
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
        job_list[i]->view_details();
        cout<<endl;
    }
}
void admin::remove_job(){
    long long jb_id;
    cout<<"\nEnter job id : ";
    cin>>jb_id;
    int f=0;
    for(int i=0;i<job_list.size();i++){
        if(jb_id==job_list[i]->job_id){
            f=1;
            job_list.erase(job_list.begin() + i+1);
            break;
        }
    }
    if(f==0){
        cout<<"\nJob not found\n";
        return;
    }
    return;
}
void admin::view_system_report(){
    cout<<"Total no. of users : "<<jobseek_list.size() + emp_list.size()<<endl;
    cout<<"Total jobs available : "<<job_list.size()<<endl;
    return;
}
int main()
{
    cout<<"\n\n****** Welcome to the online job portal ******\n\n";
    menu1 : cout<<"\n1.User\n2.Admin\n3.Exit\n";
    cout<<"\nSelect : ";
    int m1,m2,m3,m4,m5,m6,m7,m8;
    long long app_id;
    employer emp;
    jobseeker jbs;
    job jb;
    admin adm;
    cin>>m1;
    switch(m1){
        case 1:
            menu2 : cout<<"\n1.Register\n2.Login\n3.Go back\n";
            cout<<"\nSelect : ";
            cin>>m2;
            switch(m2){
                case 1:
                    menu3 : cout<<"\n1.Employer\n2.Job seeker\n3.Go back\n\n";
                    cout<<"\nSelect : ";
                    cin>>m3;
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
                    goto menu3;
                    break;
                case 2:
                    menu4 : cout<<"\n1.Job seeker\n2.Employer\n3.Go back\n\n";
                    cout<<"\nSelect : ";
                    cin>>m4;
                    switch(m4){
                        case 1:
                            if(jbs.jbs_login()){
                                jobseeker *jbs_ptr;
                                for(int i=0;i<jobseek_list.size();i++){
                                    if(jbs.name==jobseek_list[i]->name){
                                        jbs_ptr=jobseek_list[i];
                                        break;
                                    }
                                }
                                menu7 : cout<<"\n1.Apply for job\n2.Update resume\n3.View applied jobs\n4.Update skills\n5.Search jobs\n6.Update experiences\n7.Track application status\n8.View profile\n9.Log out\n\n";
                                cout<<"Enter choice : ";
                                cin>>m7;
                                string rsm,cvr_ltr,n_rsm;
                                long long jb_id;
                                int f=0,target,c;
                                job *j;
                                switch(m7){
                                    case 1:
                                        jobid : cout<<"Enter job id : ";
                                        cin>>jb_id;
                                        for(int i=0;i<job_list.size();i++){
                                            if(job_list[i]->job_id==jb_id){
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
                                            j=job_list[target];
                                        }
                                        cout<<"\nEnter resume : ";
                                        cin>>rsm;
                                        cout<<"Enter cover letter : ";
                                        cin>>cvr_ltr;
                                        jbs_ptr->apply_for_job(j,rsm,cvr_ltr);
                                        break;
                                    case 2:
                                        cout<<"Enter new resume : ";
                                        cin>>n_rsm;
                                        jbs_ptr->update_resume(n_rsm);
                                        break;
                                    case 3:
                                        jbs_ptr->view_applied_jobs();
                                        break;
                                    case 4:
                                        jbs_ptr->update_skills();
                                        break;
                                    case 5:
                                        jbs_ptr->search_jobs();
                                        break;
                                    case 6:
                                        jbs_ptr->update_experiences();
                                        break;
                                    case 7:
                                        jbs_ptr->track_application_status();
                                        break;
                                    case 8:
                                        jbs_ptr->view_profile();
                                        break;
                                    case 9:
                                        jbs_ptr->logout();
                                        goto menu2;
                                        break;
                                    default:
                                        cout<<"\nEnter valid choice\n";
                                        goto menu7;
                                }
                                goto menu7;
                            }
                            break;
                        case 2:
                            if(emp.emp_login()){
                                employer *emp_ptr;
                                for(int i=0;i<emp_list.size();i++){
                                    if(emp.name==emp_list[i]->name){
                                        emp_ptr=emp_list[i];
                                        break;
                                    }
                                }
                                menu8 : cout<<"\n1.View profile\n2.Post a job\n3.View posted jobs\n4.Review application\n5.Select a candidate\n6.Reject a candidate\n7.Update a job\n8.Remove a job\n9.Log out\n\n";
                                cout<<"Enter choice : ";
                                cin>>m8;
                                string jb_title,jb_type,req,lctn,descr;
                                float s;
                                vector <string> r;
                                int f=0,target,c=0;
                                job *j;
                                switch(m8){
                                    case 1:
                                        emp.comp_details();
                                        break;
                                    case 2:
                                        cout<<"Enter job title : ";
                                        cin.ignore();
                                        getline(cin,jb_title);
                                        cout<<"Enter job type : ";
                                        cin.ignore();
                                        getline(cin,jb_type);
                                        cout<<"Enter job location : ";
                                        cin.ignore();
                                        getline(cin,lctn);
                                        cout<<"Enter job description : ";
                                        cin.ignore();
                                        getline(cin,descr);
                                        cout<<"Enter job salary : ";
                                        cin>>s;
                                        cout<<"Enter job requirements : \n";
                                        r : cout<<"1. Press 1 to add  a requirement\n";
                                        cout<<"2. Press -1 to exit\n";
                                        cout<<"Choice : ";
                                        cin>>c;
                                        while(c!=-1){
                                            cout<<"Enter requirement : ";
                                            cin>>req;
                                            r.push_back(req);
                                            goto r;
                                        }
                                        emp.post_job(jb_title,descr,r,s,lctn,jb_type);
                                        emp_ptr->post_job(jb_title,descr,r,s,lctn,jb_type);
                                        break;
                                    case 3:
                                        emp_ptr->view_posted_jobs();
                                        break;
                                    case 4:
                                        cout<<"\nEnter candidate application id : ";
                                        cin>>app_id;
                                        emp_ptr->review_applications(app_id);
                                        break;
                                    case 5:
                                        cout<<"\nEnter candidate application id : ";
                                        cin>>app_id;
                                        emp_ptr->select_candidate(app_id);
                                        break;
                                    case 6:
                                        cout<<"\nEnter candidate application id : ";
                                        cin>>app_id;
                                        emp_ptr->reject_candidate(app_id);
                                        break;
                                    case 7:
                                        emp_ptr->update_job();
                                        break;
                                    case 8:
                                        emp_ptr->remove_job();
                                        goto menu2;
                                        break;
                                    case 9:
                                        goto menu2;
                                        break;
                                    default:
                                        cout<<"\nEnter valid choice\n";
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
                    goto menu4;
                    break;
                case 3:
                    goto menu1;
                    break;
                default:
                    cout<<"\n\nChoose valid option\n\n";
                    goto menu2;
            }
            goto menu2;
            break;
        case 2:
            menu5 : cout<<"\n\n1.Register\n2.Login\n3.Go back\n\n";
            cout<<"Select : ";
            cin>>m5;
            switch(m5){
                case 1:
                    adm.adm_register();
                    break;
                case 2:
                    if(adm.adm_login()){
                        menu6 : cout<<"\1.View all users\n2.Remove an user\n3.View all jobs\n4.Remove a job\n5.Log out\n\n";
                        cout<<"Select : ";
                        cin>>m6;
                        switch(m6){
                            case 1:
                                adm.view_users();
                                break;
                            case 2:
                                adm.remove_user();
                                break;
                            case 3:
                                adm.view_all_jobs();
                                break;
                            case 4:
                                adm.remove_job();
                                break;
                            case 5:
                                goto menu5;
                                break;
                            default:
                                cout<<"\nChoose valid option\n\n";
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