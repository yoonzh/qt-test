#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class Task;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);

public:
	void updateStatus();

public slots:
	void addTask();
	void removeTask(Task * task);
	void taskStatusChanged(Task * task);

private:
	Ui::MainWindow ui;
	QVector<Task*> mTasks;
};

#endif // MAINWINDOW_H
