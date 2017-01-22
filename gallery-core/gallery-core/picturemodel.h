#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include <QAbstractListModel>

#include "gallery-core_global.h"
#include "picture.h"

class Album;
class DatabaseManager;
class AlbumModel;

class GALLERYCORESHARED_EXPORT PictureModel : public QAbstractListModel
{
	Q_OBJECT
public:
	enum pictureRole { FilePathRole = Qt::UserRole + 1 };

public:
	PictureModel(const AlbumModel & model, QObject * parent = 0);

	QModelIndex addPicture(const Picture & picture);

	int rowCount(const QModelIndex & parent = QModelIndex()) const override;
	QVariant data(const QModelIndex & index, int role) const override;
	bool removeRows(int row, int count, const  QModelIndex & parent) override;

	void setAlbumId(int albumId);
	void clearAlbum();

public slots:
	void deletePicturesFromAlbum();

private:
	void loopPictures(int alumbId);
	bool isIndexValid(const QModelIndex & index) const;

private:
	DatabaseManager & mDB;
	int mAlbumId;
	std::unique_ptr<std::vector<std::unique_ptr<Picture>>> mPicture;
};

#endif // PICTUREMODEL_H
