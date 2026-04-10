# Student Attendance Management System (Qt GUI)

A desktop-based management system built with **C++** and the **Qt Framework**. This project demonstrates the integration of a custom backend logic (using 2D arrays) with a modern Graphical User Interface.

## Key Features
* **Student Enrollment**: Add names and IDs directly into the system.
* **Interactive Attendance Marking**: Use a calendar interface to mark students as 'Present' or 'Absent' for specific days.
* **Real-time Analytics**: Automatically calculates attendance percentages based on active days.
* **Visual Indicators**: 
    * **Color-Coded Rows**: Entire rows turn Green (Present) or Red (Absent) based on the selected calendar date.
    * **Attendance Warnings**: Student names turn red if their total attendance falls below **75%**.
* **Quick Summary**: Click on a student's name to see a detail of their attendance.

## Technical Details
* **Data Structures**: Uses 2D arrays for optimized attendance tracking.
* **UI Framework**: Developed using Qt Widgets Designer.
* **IDE**: Visual Studio 2022.

## How to Run
1. Clone the repository.
2. Open the `.sln` file in Visual Studio with the Qt VS Tools extension installed.
3. Build and Run in x64 Debug/Release mode.
