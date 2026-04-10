#include "StudentAttendanceGUI.h"
#include <string>
#include <QMessageBox>
// This tells the GUI that these variables exist in your Source.cpp
extern std::string names[50];
extern int ids[50];
extern int studentCount;
extern char attendance[50][30];
extern int dayCount;

StudentAttendanceGUI::StudentAttendanceGUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

StudentAttendanceGUI::~StudentAttendanceGUI()
{}

void StudentAttendanceGUI::on_btnAdd_clicked()
{
    QString qName = ui.txtName->text();
    QString qId = ui.txtID->text();

    if (qName.isEmpty() || studentCount >= 50) return;

    // --- LINK TO YOUR CODE ---
    names[studentCount] = qName.toStdString();
    ids[studentCount] = qId.toInt();
    studentCount++;
    // -------------------------

    // Update the Table display
    int row = ui.attendanceTable->rowCount();
    ui.attendanceTable->insertRow(row);
    ui.attendanceTable->setItem(row, 0, new QTableWidgetItem(qName));
    ui.attendanceTable->setItem(row, 1, new QTableWidgetItem(qId));
    ui.attendanceTable->setItem(row, 2, new QTableWidgetItem("0")); // Initial Present
    ui.attendanceTable->setItem(row, 3, new QTableWidgetItem("0")); // Initial Absent
    ui.attendanceTable->setItem(row, 4, new QTableWidgetItem("0%")); // Initial %

    ui.txtName->clear();
    ui.txtID->clear();
}
void StudentAttendanceGUI::on_btnUpdate_clicked()
{
    // 1. Get the ID from the input box to search
    int searchID = ui.txtID->text().toInt();
    int day = ui.attendanceCalendar->selectedDate().day();

    // 2. SEARCH YOUR ARRAY (Just like your original code)
    int foundIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (ids[i] == searchID) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        // Optional: Show a message if not found
        return;
    }

    // 3. Update the record in your 2D array
    // Here we assume "Update" means flipping the status for that day
    // If it was 1 (P), make it 0 (A). If it was 0, make it 1.
    attendance[foundIndex][day - 1] = !attendance[foundIndex][day - 1];

    // 4. Update the GUI Table at that specific row
    int pCount = 0;
    for (int d = 0; d < 30; d++) {
        if (attendance[foundIndex][d] == 1) pCount++;
    }

    int aCount = (dayCount > pCount) ? (dayCount - pCount) : 0;

    ui.attendanceTable->item(foundIndex, 2)->setText(QString::number(pCount));
    ui.attendanceTable->item(foundIndex, 3)->setText(QString::number(aCount));

    double percent = (dayCount > 0) ? (pCount * 100.0 / dayCount) : 0.0;
    ui.attendanceTable->item(foundIndex, 4)->setText(QString::number(percent, 'f', 1) + "%");
}

void StudentAttendanceGUI::on_btnPresent_clicked()
{
    int currentRow = ui.attendanceTable->currentRow();
    if (currentRow < 0) return;

    int day = ui.attendanceCalendar->selectedDate().day();
    if (day > 30) day = 30;

    if (day > dayCount) dayCount = day;

    // Set to 1 (Present) - This overwrites any previous 'Absent' status for this day
    attendance[currentRow][day - 1] = 1;

    // Recalculate BOTH counts from scratch for this student
    int pCount = 0;
    int aCount = 0;
    for (int d = 0; d < dayCount; d++) {
        if (attendance[currentRow][d] == 1)
            pCount++;
        else
            aCount++;
    }

    // Update the UI
    ui.attendanceTable->item(currentRow, 2)->setText(QString::number(pCount));
    ui.attendanceTable->item(currentRow, 3)->setText(QString::number(aCount));

    double percentage = (dayCount > 0) ? (pCount * 100.0 / dayCount) : 0.0;
    ui.attendanceTable->item(currentRow, 4)->setText(QString::number(percentage, 'f', 1) + "%");
    // Add this at the end of both Mark and Absent button functions
    if (percentage >= 75.0) {
        ui.attendanceTable->item(currentRow, 0)->setBackground(Qt::green);
        ui.attendanceTable->item(currentRow, 0)->setForeground(Qt::black);
    }
    else {
        ui.attendanceTable->item(currentRow, 0)->setBackground(Qt::red);
        ui.attendanceTable->item(currentRow, 0)->setForeground(Qt::white);
    }
}
void StudentAttendanceGUI::on_btnAbsent_clicked()
{
    int currentRow = ui.attendanceTable->currentRow();
    if (currentRow < 0) return;

    int day = ui.attendanceCalendar->selectedDate().day();
    if (day > 30) day = 30;

    if (day > dayCount) dayCount = day;

    // Set to 0 (Absent) - This overwrites any previous 'Present' status for this day
    attendance[currentRow][day - 1] = 0;

    // Recalculate BOTH counts from scratch
    int pCount = 0;
    int aCount = 0;
    for (int d = 0; d < dayCount; d++) {
        if (attendance[currentRow][d] == 1)
            pCount++;
        else
            aCount++;
    }

    // Update the UI
    ui.attendanceTable->item(currentRow, 2)->setText(QString::number(pCount));
    ui.attendanceTable->item(currentRow, 3)->setText(QString::number(aCount));

    double percentage = (dayCount > 0) ? (pCount * 100.0 / dayCount) : 0.0;
    ui.attendanceTable->item(currentRow, 4)->setText(QString::number(percentage, 'f', 1) + "%");
    // Add this at the end of both Mark and Absent button functions
    if (percentage >= 75.0) {
        ui.attendanceTable->item(currentRow, 0)->setBackground(Qt::green);
        ui.attendanceTable->item(currentRow, 0)->setForeground(Qt::black);
    }
    else {
        ui.attendanceTable->item(currentRow, 0)->setBackground(Qt::red);
        ui.attendanceTable->item(currentRow, 0)->setForeground(Qt::white);
    }
}
void StudentAttendanceGUI::on_attendanceTable_cellDoubleClicked(int row, int column)
{
    // 1. Get student name from your array
    std::string studentName = names[row];

    // 2. Build a "History" string
    QString history = "Attendance History for " + QString::fromStdString(studentName) + ":\n\n";

    for (int d = 0; d < dayCount; d++) {
        QString status = (attendance[row][d] == 1) ? "PRESENT" : "ABSENT";
        history += "Day " + QString::number(d + 1) + ": " + status + "\n";
    }

    if (dayCount == 0) {
        history = "No attendance has been marked for this student yet.";
    }

    // 3. Pop up the window
    QMessageBox::information(this, "Student History", history);
}
void StudentAttendanceGUI::on_attendanceCalendar_selectionChanged()
{
    int day = ui.attendanceCalendar->selectedDate().day();
    if (day > 30) return;

    // Loop through all students currently in the table
    for (int i = 0; i < studentCount; i++) {
        // Check your 2D array for this specific student and day
        if (attendance[i][day - 1] == 1) {
            // Present = Green Row
            for (int col = 0; col < ui.attendanceTable->columnCount(); col++) {
                ui.attendanceTable->item(i, col)->setBackground(Qt::green);
                ui.attendanceTable->item(i, col)->setForeground(Qt::black);
            }
        }
        else if (day <= dayCount) {
            // Absent = Red Row (Only if the day has actually passed/been marked)
            for (int col = 0; col < ui.attendanceTable->columnCount(); col++) {
                ui.attendanceTable->item(i, col)->setBackground(Qt::red);
                ui.attendanceTable->item(i, col)->setForeground(Qt::white);
            }
        }
        else {
            // Future days = Reset to White
            for (int col = 0; col < ui.attendanceTable->columnCount(); col++) {
                ui.attendanceTable->item(i, col)->setBackground(Qt::white);
                ui.attendanceTable->item(i, col)->setForeground(Qt::black);
            }
        }
    }
}