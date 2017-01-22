#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "album.h"
#include "albumdao.h"
#include "databasemanager.h"

using namespace std;

AlbumDao::AlbumDao(QSqlDatabase & database)
: mDatabase(database)
{
}

void AlbumDao::init() const
{
	if(mDatabase.tables().contains("albums") == false)
	{
		QSqlQuery query(mDatabase);
		query.exec("CREATE TABLE albums (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
	}
}

void AlbumDao::addAlbum(Album & album) const
{
	QSqlQuery query(mDatabase);
	query.prepare("insert into albums (name) values (:name)");
	query.bindValue(":name", album.name());
	query.exec();
	album.setId(query.lastInsertId().toInt());
}

unique_ptr<vector<unique_ptr<Album>>> AlbumDao::albums() const
{
	QSqlQuery query("SELECT * FROM albums", mDatabase);
	query.exec();
	unique_ptr<vector<unique_ptr<Album>>> list(new vector<unique_ptr<Album>>);
	while(query.next())
	{
		unique_ptr<Album> album(new Album());
		album->setId(query.value("id").toInt());
		album->setName(query.value("name").toString());
		list->push_back(move(album));
	}
	return list;
}
