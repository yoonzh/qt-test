#ifndef TASK_H
#define TASK_H

#include "ui_task.h"

class Task : public QWidget
{
	Q_OBJECT

public:
	explicit Task(const QString & name, QWidget *parent = 0);

	void setName(const QString & name);
	QString name() const;
	bool isCompleted() const;

public slots:
	void rename();

signals:
	void removed(Task * task);
	void statusChanged(Task * task);

private slots:
	void checked(bool checked);

private:
	Ui::Task ui;
};

#endif // TASK_H
