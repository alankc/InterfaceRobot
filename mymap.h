#ifndef MYMAP_H
#define MYMAP_H

#include <QImage>
#include <QPointF>
#include <QString>
#include <QLinkedList>

#include "local.h"

class MyMap
{
private:
    QImage *image;

public:
    MyMap();
    QLinkedList<Local*> locals;

    void SetImage(QImage *image);
    QImage* GetImage();
    bool InsertLocal(Local* local);
    Local *RemoveLocal(MyPoint point);
    Local *GetLocalByName(QString name);
    bool SaveMap(QString fileName);
    bool LoadMap(QString fileName);
    QString LocalsToString();
    void Clear();
};

#endif // MYMAP_H
