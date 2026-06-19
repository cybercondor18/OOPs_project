# 💼 Online Job Portal — Console Application

> A feature-rich **console-based Job Portal** built in **C++** demonstrating core **Object-Oriented Programming** principles. The system connects **Job Seekers**, **Employers**, and **Admins** through a unified platform for job posting, searching, applying, and recruitment management.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [OOP Concepts Demonstrated](#oop-concepts-demonstrated)
- [Class Architecture](#class-architecture)
- [User Roles & Workflows](#user-roles--workflows)
- [Data Persistence](#data-persistence)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Build & Run](#build--run)
- [Sample Credentials](#sample-credentials)
- [Screenshots / Usage Flow](#screenshots--usage-flow)
- [Contributors](#contributors)

---

## Overview

The **Online Job Portal** is an IOOP (Introduction to Object-Oriented Programming) lab project that simulates a real-world job recruitment platform entirely within the terminal. It supports three distinct user roles — **Job Seekers**, **Employers**, and **System Admins** — each with dedicated dashboards and capabilities.

All data (users, jobs, applications) is persisted to **CSV/text files**, making the system stateful across sessions without requiring a database.

---

## Features

### 👤 Job Seeker
| Feature | Description |
|---|---|
| **Register & Login** | Create a profile with name, email, password, experience, education, skills, and job preferences |
| **Search Jobs** | Look up jobs by ID and view complete details (salary, requirements, employer info) |
| **Apply for Jobs** | Submit a resume and cover letter to any available job listing |
| **Track Applications** | Monitor the status of all submitted applications (Pending / Shortlisted / Hired / Rejected) |
| **Update Profile** | Modify name, email, password, resume, skills, and work experience at any time |
| **View Applied Jobs** | See a consolidated list of all jobs applied for |

### 🏢 Employer
| Feature | Description |
|---|---|
| **Register & Login** | Create a profile with personal and company details (name, location, description) |
| **Post Jobs** | Create new job listings with title, type, description, salary, location, and requirements |
| **View Posted Jobs** | Browse all jobs posted by the logged-in employer |
| **Review Applications** | Inspect applications received for posted jobs |
| **Select / Reject Candidates** | Update application status to hired or rejected |
| **Update / Remove Jobs** | Edit job details or delete listings entirely |

### 🔐 Admin
| Feature | Description |
|---|---|
| **Register & Login** | Dedicated admin registration and authentication |
| **View All Users** | List all registered job seekers and employers with full profiles |
| **Remove Users** | Delete any job seeker or employer from the system (with CSV sync) |
| **View All Jobs** | Browse every job listing in the system |
| **Remove Jobs** | Delete any job listing by ID (with CSV sync) |
| **System Report** | View aggregate stats — total users, job seekers, employers, and active jobs |

### 🛡️ Input Validation & Error Handling
- **Email validation** using regex (`^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$`)
- **Password strength enforcement** — minimum 8 characters, must include uppercase, lowercase, digit, and special character
- **Exception handling** with `try-catch` blocks and `invalid_argument` throughout all menu inputs
- **Custom exceptions** (`InvalidBidException` in the prototype file)

---

## OOP Concepts Demonstrated

| Concept | Implementation |
|---|---|
| **Classes & Objects** | `user`, `jobseeker`, `employer`, `admin`, `job`, `application`, `experience`, `education`, `job_preferences`, `company_profile` |
| **Inheritance** | `jobseeker` and `employer` inherit from `user` base class |
| **Polymorphism** | `virtual void view_profile()` in `user` is overridden in derived classes; `virtual void place_bid() = 0` (pure virtual) in the prototype |
| **Encapsulation** | Private/public access control across all classes |
| **Abstraction** | Complex operations (CSV I/O, login validation) hidden behind clean method interfaces |
| **Friend Functions** | `friend void user::create_auction()` in the `auction` class (prototype); `friend class bid` in the `tim` class |
| **Static Members** | `static long long jobid` in `job`, `static int userCount` in `user` (prototype) |
| **Enums** | `enum status { hired, rejected, pending, shortlisted }` for application tracking |
| **Exception Handling** | Custom exception classes, `try-catch` blocks with `invalid_argument` and `runtime_error` |
| **File I/O** | CSV read/write for persistent data storage using `fstream`, `ifstream`, `ofstream` |
| **STL Containers** | `vector`, `map`, `string`, `stringstream` used extensively |
| **Composition** | `job` contains a pointer to `employer`; `application` contains pointers to both `job` and `jobseeker` |
| **Aggregation** | `jobseeker` holds vectors of `experience`, `education`, and `skills` |

---

## Class Architecture

```
                        ┌──────────┐
                        │   user   │  (Base Class)
                        │──────────│
                        │ name     │
                        │ email    │
                        │ password │
                        └────┬─────┘
                ┌────────────┴────────────┐
                ▼                         ▼
        ┌───────────┐            ┌──────────┐
        │ jobseeker  │            │ employer  │
        │───────────│            │──────────│
        │ resume     │            │ company  │
        │ skills[]   │            │ location │
        │ exp_list[] │            │ descript.│
        │ edu_list[] │            │ posted   │
        │ applied[]  │            │  _jobs[] │
        │ app_list[] │            │ applics[]│
        │ job_prefr* │            └──────────┘
        └───────────┘
                                  ┌──────────┐
        ┌───────────┐             │  admin   │
        │    job     │             │──────────│
        │───────────│             │ name     │
        │ job_id     │             │ email    │
        │ title      │             │ pass     │
        │ type       │             │ admin_id │
        │ salary     │             └──────────┘
        │ location   │
        │ job_emp*   │──────► employer
        │ appl_list[]│
        └───────────┘
                                  ┌─────────────┐
        ┌─────────────┐          │  experience  │
        │ application  │          │─────────────│
        │─────────────│          │ job_title    │
        │ appl_id      │          │ company_name │
        │ resume       │          │ duration     │
        │ cover_letter │          └─────────────┘
        │ status       │
        │ job_ref*     │──────► job
        │ applicant*   │──────► jobseeker
        └─────────────┘          ┌─────────────┐
                                  │  education   │
        ┌────────────────┐       │─────────────│
        │ job_preferences │       │ grade_name   │
        │────────────────│       │ institute    │
        │ locations[]     │       │ year_dur     │
        │ job_type[]      │       └─────────────┘
        │ salary_range    │
        └────────────────┘
```

---

## User Roles & Workflows

### Job Seeker Flow
```
Start → Register (name, email, password, experience, education, skills, job preferences)
      → Login
      → Dashboard:
            ├─ Apply for Job (by Job ID → submit resume + cover letter)
            ├─ Update Resume
            ├─ View Applied Jobs
            ├─ Update Skills (add / modify)
            ├─ Search Jobs (by ID → view full details → optionally apply)
            ├─ Update Experiences (add / modify)
            ├─ Track Application Status
            ├─ View Profile
            └─ Log Out
```

### Employer Flow
```
Start → Register (name, email, password, company name, location, description)
      → Login
      → Dashboard:
            ├─ View Profile
            ├─ Post a Job (title, type, location, description, salary, requirements)
            ├─ View Posted Jobs
            ├─ Review Application (by Application ID)
            ├─ Select Candidate (set status → hired)
            ├─ Reject Candidate (set status → rejected)
            ├─ Update a Job
            ├─ Remove a Job
            └─ Log Out
```

### Admin Flow
```
Start → Register / Login
      → Dashboard:
            ├─ View All Users (job seekers + employers)
            ├─ Remove a User (by username, syncs CSV)
            ├─ View All Jobs
            ├─ Remove a Job (by ID, syncs CSV)
            ├─ View System Report (user/job counts)
            └─ Log Out
```

---

## Data Persistence

The system uses flat **CSV files** and a **text file** for persistent storage. Data is loaded on startup and saved on every mutation.

| File | Format | Description |
|---|---|---|
| `admins.csv` | `name,email,password` | Admin credentials |
| `employers.csv` | `name,email,password,company_name,location,description` | Employer profiles |
| `jobseekers.csv` | `name,email,password,resume,job_title,company,duration,qualification,institute,year,skills` | Job seeker profiles with experience & education |
| `jobs.csv` | `job_id,title,type,description,salary,location,company_name,company_location,company_description` | All job listings |
| `applications.txt` | `applicant_name,job_title,resume` | Submitted applications log |

### Data Loading (on startup)
```
main() → loadAdmins()
       → loadEmployers()
       → loadJobseekers()
       → loadJobs()
```

---

## Project Structure

```
OOPs_project/
│
├── ioops_mini_project.cpp    # Main source (1959 lines) — full portal implementation
├── IOOP_Main.cpp             # Prototype / early design with auction system classes
├── loading_files_fn.cpp      # Standalone data-loading function drafts
├── copy.cpp                  # Backup copy of the main source
├── tempCodeRunnerFile.cpp    # VS Code temp file (auto-generated)
│
├── admins.csv                # Admin credentials store
├── employers.csv             # Employer profiles store (20+ records)
├── jobseekers.csv            # Job seeker profiles store (20 records)
├── jobs.csv                  # Job listings store (42+ records)
├── applications.txt          # Application submissions log
│
├── ioops_mini_project.exe    # Compiled executable (Windows)
├── copy.exe                  # Compiled backup executable
│
└── README.md                 # This file
```

---

## Prerequisites

- **C++ Compiler** with C++11 or later support (e.g., `g++`, MSVC, MinGW)
- **Windows OS** (uses `<conio.h>` for `getch()` and `system("cls")`)
- No external libraries or package managers required

---

## Build & Run

### Using g++ (MinGW on Windows)

```bash
# Compile
g++ -o job_portal ioops_mini_project.cpp -std=c++11

# Run
./job_portal
```

### Using MSVC (Developer Command Prompt)

```bash
cl ioops_mini_project.cpp /EHsc /Fe:job_portal.exe
job_portal.exe
```

### Using the Pre-built Executable

```bash
# Simply run the included executable
ioops_mini_project.exe
```

> **Note:** Ensure the CSV data files (`admins.csv`, `employers.csv`, `jobseekers.csv`, `jobs.csv`) and `applications.txt` are in the **same directory** as the executable.

---

## Sample Credentials

### Admin
| Name | Email | Password |
|---|---|---|
| admin | admin@gmail.com | 1Admin@25 |

### Employer (examples)
| Name | Company | Password |
|---|---|---|
| anup | Google | 1Anup@25 |
| harshit | Amazon | 1Harshit@25 |
| shivang | Infosys | Shiv@25 |

### Job Seeker (examples)
| Name | Email | Password |
|---|---|---|
| shivang | shivang@gmail.com | 1Shiv@18 |
| dipesh | dipesh@gmail.com | 1Dipu@25 |
| anup | anup@gmail.com | 1Anup@25 |

---

## Screenshots / Usage Flow

### Main Menu
```
****** Welcome to the online job portal ******

1.User
2.Admin
3.Exit

Select :
```

### Job Seeker Dashboard
```
1.Apply for job
2.Update resume
3.View applied jobs
4.Update skills
5.Search jobs
6.Update experiences
7.Track application status
8.View profile
9.Log out
```

### Employer Dashboard
```
1.View profile
2.Post a job
3.View posted jobs
4.Review application
5.Select a candidate
6.Reject a candidate
7.Update a job
8.Remove a job
9.Log out
```

### Admin Dashboard
```
1.View all users
2.Remove an user
3.View all jobs
4.Remove a job
5.View system report
6.Log out
```

---

## Contributors

| Name | Role |
|---|---|
| **Anup** | Developer |
| **Cybercondor18** | Developer |

---

<p align="center">
  Built with ❤️ using C++ for the IOOP Lab Project
</p>
