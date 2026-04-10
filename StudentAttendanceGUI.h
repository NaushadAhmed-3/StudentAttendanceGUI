#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_StudentAttendanceGUI.h"

class StudentAttendanceGUI : public QMainWindow
{
    Q_OBJECT

public:
    StudentAttendanceGUI(QWidget *parent = nullptr);
    ~StudentAttendanceGUI();
private slots:
    void on_btnAdd_clicked();
    void on_btnPresent_clicked();
    void on_btnAbsent_clicked();
    void on_btnUpdate_clicked();
    void on_attendanceTable_cellDoubleClicked(int row, int column);
    void on_attendanceCalendar_selectionChanged();

private:
    Ui::StudentAttendanceGUIClass ui;
};

