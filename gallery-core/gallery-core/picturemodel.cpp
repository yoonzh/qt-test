#include "picturemodel.h"
#include "databasemanager.h"
#include "albummodel.h"

using namespace std;

PictureModel::PictureModel(const AlbumModel & albumModel, QObject * parent)
: QAbstractListModel(parent)
, mDB(DatabaseManager::instance())
, mAlbumId(-1)
, mPicture(new vector<unique_ptr<Picture>>())
{
	connect(&albumModel, &AlbumModel::rowsChanged, this, &PictureModel::deletePicturesFromAlbum);
}

void PictureModel::setAlbumId(int albumId)
{
	beginResetModel();
	{
		mAlbumId = albumId;
		loopPictures(mAlbumId);
	}
	endResetModel();
}

void PictureModel::loopPictures(int albumId)
{
	if(albumId <= 0)
	{
		mPicture.reset(new vector<unique_ptr<Picture>>());
		return;
	}
	mPicture = mDB.pictureDao.pictureFromAlbum(albumId);
}
