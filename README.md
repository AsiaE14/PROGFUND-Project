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
- [x] Create repository
- [x] Implement base code structure
- [x] Add CSV header creation

Phase 2: Core Features
- [x] Add Project (regis) ( only 1975 to 2037)
- [x] Display All Projects (Sall)
- [x] Sorts All Projects (Name, Date,Status)
- [x] Search Project (by project Name)
- [x] Edit Project 
- [x] Delete Project 

Phase 3: Advanced Features
- [x] Full interactive menu
- [x] Input validation (date format,spcial charater check)


Phase 4: Testing
- [x] Unit tests for each function
- [x] End-to-End (E2E) test scenario


Phase 5: Documentation
- ✅ README / User Manual
- ✅ Example CSV (15+ records)
- [x] Usage guide for unit tests

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

   gcc -DTEST_MODE -DTEST_FILE=\"test_data.csv\" main.c test_unit.c -o test_unit.exe

   gcc -DTEST_MODE -DTEST_FILE=\"test_data.csv\" main.c test_e2e.c -o test_e2e.exe 


2. Run:

   ./main.exe

   ./test_unit.exe

   ./test_e2e.exe

3. CSV File:
   The program will create "data.csv" and "test_data.csv" automatically 
   if it does not exist. 

---------------------------------------------------
📌 Example Usage
---------------------------------------------------
Menu:
1 = Add New Project
2 = Search and Edit Project
3 = Show All Projects
4 = unit test
5 = e2e test
0 = Exit Program

Example:
> Select 1
> Enter Project-Name: Website
> Enter Start-Date: 2025-01-01
> Enter End-Date: 2025-05-01


---------------------------------------------------
📌 Testing
---------------------------------------------------
Unit Test:
- Each function tested with sample input
- Example: regis(), Sall(), search()

E2E Test:
- Add -> Search -> Edit -> Delete -> Show All
- Confirm CSV updated correctly

Warining : Unit Test & E2E Test use the same test_data.csv file.

---------------------------------------------------
📌 Notes
---------------------------------------------------
- This project is for academic purposes (Final Project).
- Status field uses: Completed, In Progress, Not Started.
