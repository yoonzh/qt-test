#include "albummodel.h"
#include "databasemanager.h"

using namespace std;

AlbumModel::AlbumModel(QObject * parent)
: QAbstractListModel(parent)
, mDB(DatabaseManager::instance())
, mAlbums(mDB.albumDao.albums())
{
}

int AlbumModel::rowCount(const QModelIndex &parent) const
{
	return mAlbums->size();
}

QVariant AlbumModel::data(const QModelIndex &index, int role) const
{
	if(!isValidIndex(index))
	{
		return QVariant();
	}

	const Album & album = *mAlbums->at(index.row());

	switch(role)
	{
	case Roles::IdRole:
		return album.id();
	case Roles::NameRole:
	case Qt::DisplayRole:
		return album.name();
	default:
		return QVariant();
	}
}

QHash<int, QByteArray> AlbumModel::roleNames() const
{
	QHash<int, QByteArray> roles;
	roles[Roles::IdRole] = "id";
	roles[Roles::NameRole] = "name";
	return roles;
}

QModelIndex AlbumModel::addAlbum(const Album & album)
{
	int rowIndex = rowCount();
	beginInsertRows(QModelIndex(), rowIndex, rowIndex);
	{
		unique_ptr<Album> newAlbum(new Album(album));
		mDB.albumDao.addAlbum(*newAlbum);
		mAlbums->push_back(move(newAlbum));
	}
	endInsertRows();
	return index(rowIndex, 0);
}

bool AlbumModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(!isValidIndex(index) || role != Roles::NameRole)
		return false;

	Album & album = *mAlbums->at(index.row());
	album.setName(value.toString());
	mDB.albumDao.updateAlbum(album);
	emit dataChanged(index, index);
	return true;
}

bool AlbumModel::removeRows(int row, int count, const QModelIndex &parent)
{
	if(row < 0
			|| row >= rowCount()
			|| count < 0
			|| (row + count) > rowCount())
		return false;

	beginRemoveRows(parent, row, row + count - 1);
	{
		int countLeft = count;
		while(countLeft--)
		{
			const Album & album = *mAlbums->at(row + countLeft);
			mDB.albumDao.removeAlbum(album.id());
		}
		mAlbums->erase(mAlbums->begin() + row, mAlbums->begin() + row + count);
	}
	endRemoveRows();
	return true;
}

bool AlbumModel::isValidIndex(const QModelIndex & index) const
{
	if(index.row() > rowCount())
		return false;
	return true;
}
