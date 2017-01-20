#include <QInputDialog>

#include "task.h"

Task::Task(const QString & name, QWidget *parent) :
	QWidget(parent)
{
	ui.setupUi(this);
	setName(name);

	connect(ui.editButton, &QPushButton::clicked, this, &Task::rename);

	connect(ui.removeButton, &QPushButton::clicked, [this]{
		emit removed(this);
	});

	connect(ui.checkbox, &QCheckBox::toggled, this, &Task::checked);
}

void Task::setName(const QString &name)
{
	ui.checkbox->setText(name);
}

QString Task::name() const
{
	return ui.checkbox->text();
}

bool Task::isCompleted() const
{
	return ui.checkbox->isChecked();
}

void Task::rename()
{
	bool ok;
	QString name = QInputDialog::getText(this
										 , tr("Edit task")
										 , tr("Task name")
										 , QLineEdit::Normal
										 , this->name()
										 , &ok
										 );

	if(ok && name.isEmpty() == false)
	{
		setName(name);
	}
}

void Task::checked(bool checked)
{
	QFont font(ui.checkbox->font());
	font.setStrikeOut(checked);
	ui.checkbox->setFont(font);;
	emit statusChanged(this);
}
