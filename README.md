Project: Project Management Information System
Language: C
Repository: https://github.com/AsiaE14/PROGFUND-Project

---------------------------------------------------
📌 Overview
---------------------------------------------------
This program is a Project Management Information System
that stores project data in a CSV file. The system supports:

- Add Project
- Search Project
- Update Project
- Delete Project
- Display All Projects
- Manage Data in CSV File

---------------------------------------------------
📌 CSV File Format
---------------------------------------------------
The program stores data in CSV format with 4 columns:

ProjectName, StartDate, EndDate, Status

Example (data.csv):
Website Development,2025-06-01,2025-09-01,In Progress
Mobile App Launch,2025-05-15,2025-08-15,Completed

In this repository, we provide a sample CSV with 15 records.

---------------------------------------------------
📌 Roadmap (Development Plan)
---------------------------------------------------
Phase 1: Setup (✅ Done)
- Create repository
- Implement base code structure
- Add CSV header creation

Phase 2: Core Features
- [x] Add Project (regis)
- [x] Display All Projects (Sall)
- [ ] Search Project
- [ ] Edit Project
- [ ] Delete Project

Phase 3: Advanced Features
- [ ] Full interactive menu
- [ ] Input validation (date format check)
- [ ] Secure data deletion (boom)

Phase 4: Testing
- [ ] Unit tests for each function
- [ ] End-to-End (E2E) test scenario
- [ ] Linux testing environment

Phase 5: Documentation
- ✅ README / User Manual
- ✅ Example CSV (15+ records)
- [ ] Usage guide for unit tests

---------------------------------------------------
📌 Progress Status (CSV Records)
---------------------------------------------------
- Total Records: 15
- Completed Projects: 6
- In Progress Projects: 4
- Not Started Projects: 3
- Ongoing until Dec 2025: 2

---------------------------------------------------
📌 How to Compile & Run
---------------------------------------------------
1. Compile:
   gcc main.c -o main.exe

2. Run:
   ./main.exe

3. CSV File:
   The program will create "data.csv" automatically 
   if it does not exist. 

---------------------------------------------------
📌 Example Usage
---------------------------------------------------
Menu:
1 = Add New Project
2 = Search and Edit Project
3 = Show All Projects
4 = Other (in process)
0 = Exit Program

Example:
> Select 1
> Enter Project-Name: Website
> Enter Start-Date: 2025-01-01
> Enter End-Date: 2025-05-01
> Enter Status: Completed

---------------------------------------------------
📌 Testing
---------------------------------------------------
Unit Test:
- Each function tested with sample input
- Example: regis(), Sall(), search()

E2E Test:
- Add -> Search -> Edit -> Delete -> Show All
- Confirm CSV updated correctly

---------------------------------------------------
📌 Notes
---------------------------------------------------
- This project is for academic purposes (Final Project).
- Status field uses: Completed, In Progress, Not Started.
