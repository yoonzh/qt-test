#include <QSqlDatabase>
#include <QSqlQuery>

#include "picturedao.h"

PictureDao::PictureDao(QSqlDatabase & database)
: mDatabase(database)
{

}

void PictureDao::init() const
{
	if(!mDatabase.tables().contains("pictures"))
	{
		QSqlQuery query(mDatabase);
		query.exec(QString("CREATE TABLE PICTURES (id INTEGER PRIMARY KEY AUTOINCREMENT, album_id INTEGER, url TEXT)"));
	}
}
