#include <QDebug>
#include <QInputDialog>

#include "mainwindow.h"
#include "task.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
	, mTasks()
{
	ui.setupUi(this);

	connect(ui.addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);

	updateStatus();
}

void MainWindow::addTask()
{
	bool ok;
	QString name = QInputDialog::getText(this
										 , tr("Add task")
										 , tr("Task name")
										 , QLineEdit::Normal
										 , tr("Untitled task")
										 , &ok
										 );

	if(ok && name.isEmpty() == false)
	{
		qDebug() << "Adding new task";
		Task * task = new Task(name);

		connect(task, &Task::removed, this, &MainWindow::removeTask);
		connect(task, &Task::statusChanged, this, &MainWindow::taskStatusChanged);

		mTasks.append(task);
		ui.taskslLayout->addWidget(task);
		updateStatus();
	}
}

void MainWindow::removeTask(Task *task)
{
	mTasks.removeOne(task);
	ui.taskslLayout->removeWidget(task);
	task->setParent(NULL);
	delete task;
	updateStatus();
}

void MainWindow::updateStatus()
{
	int completedCount = 0;
	for (auto t : mTasks)
	{
		if(t->isCompleted())
		{
			++completedCount;
		}
	}

	int todoCount = mTasks.size() - completedCount;

	ui.statusLabel->setText(QString("Status: %1 todo / %2 completed")
								.arg(todoCount)
								.arg(completedCount)
							);
}

void MainWindow::taskStatusChanged(Task *task)
{
	(void)task;
	updateStatus();
}
