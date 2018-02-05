#ifndef MYMAP_H
#define MYMAP_H

#include <QImage>
#include <QPointF>
#include <QString>
#include <QLinkedList>

typedef QPointF MyPoint;

class MyMap
{
private:
    QImage *image;
    QLinkedList<MyPoint*> locals;

public:
    MyMap();
    void SetImage(QImage *image);
    QImage* GetImage();
    bool InsertLocal(MyPoint* point);
    MyPoint *RemoveLocal(MyPoint* point);
    bool SaveMap(QString fileName);
    bool LoadMap(QString fileName);
    QString LocalsToString();
    void Clear();
};

#endif // MYMAP_H
