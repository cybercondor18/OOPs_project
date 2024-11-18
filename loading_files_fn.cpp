// Function to load Employer data
vector<Employer> loadEmployers(const string& filename) {
    vector<Employer> employers;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return employers;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, email, password, company_name;

        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');
        getline(ss, company_name, ',');

        if (!name.empty() && !email.empty() && !password.empty() && !company_name.empty()) {
            employers.emplace_back(name, email, password, company_name);
        }
    }

    file.close();
    return employers;
}

// Function to load Jobseeker data
vector<Jobseeker> loadJobseekers(const string& filename) {
    vector<Jobseeker> jobseekers;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return jobseekers;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, email, password, resume, job_type, location;

        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');
        getline(ss, resume, ',');
        getline(ss, job_type, ',');
        getline(ss, location, ',');

        if (!name.empty() && !email.empty() && !password.empty() && !resume.empty()) {
            JobPreferences prefs(job_type, location);
            jobseekers.emplace_back(name, email, password, resume, prefs);
        }
    }

    file.close();
    return jobseekers;
}

// Function to load Job data
vector<Job> loadJobs(const string& filename, const vector<employer>& employers) {
    // vector<Job> jobs;
    job jb;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return jobs;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id_str, title, type, job_descr, salary, job_location, emp_company_name,comp_location,comp_descr;
        long long id;
        float salary;

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
            salary = stof(salary);

            // Find the employer matching the name and company (assuming unique employer per job)
            // auto it = find_if(employers.begin(), employers.end(),
            //                   [&](const Employer& emp) { return emp.name == emp_name && emp.company_name == emp_company; });

            // if (it != employers.end()) {
            //     jobs.emplace_back(id, title, type, *it, descr, salary, location);
            // }

        }
    }

    file.close();
    return jobs;
}