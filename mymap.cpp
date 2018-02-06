#include "mymap.h"
#include <iostream>
#include <fstream>
#include <QBuffer>

MyMap::MyMap()
{
    this->image = NULL;
}

void MyMap::SetImage(QImage *image)
{
    this->image = image;
}

QImage* MyMap::GetImage()
{
    return this->image;
}

bool MyMap::InsertLocal(Local *local)
{
    for(auto l: locals)
    {
        if ((l->point->rx() == local->point->rx()) && (l->point->ry() == local->point->ry()))
            return false;
    }
    locals.append(local);
    return true;
}

Local *MyMap::RemoveLocal(MyPoint point)
{
    for(auto l : locals)
    {
        if ((l->point->rx() == point.rx()) && (l->point->ry() == point.ry()))
        {
            locals.removeOne(l);
            return l;
        }
    }
    return NULL;
}

Local *MyMap::GetLocalByName(QString name)
{
    for(auto l : locals)
    {
        if (name == l->name)
        {
            return l;
        }
    }
    return NULL;
}


bool MyMap::SaveMap(QString fileName)
{
    if (image == NULL)
        return false;

    std::string path = fileName.toStdString();

    std::ofstream outFile;
    outFile.open(path, std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);

    if (!outFile.is_open())
        return false;

    //Used to save the map image
    QByteArray arr;
    QBuffer buffer(&arr);
    buffer.open(QIODevice::WriteOnly);
    image->save(&buffer, "PNG");
    int len = arr.size();

    //Used to save the locals
    int numLocals = locals.count();

    //First write image number of bytes, after that, numbers of locals
    outFile.write((char*)&len, sizeof(int));
    outFile.write((char*)&numLocals, sizeof(int));

    //Writing the image
    outFile.write(arr.data(), len);

    //Writing the locals
    for(auto l : locals)
    {
        outFile.write(l->name, Local::MAXIMUM_NAME_SIZE);
        outFile.write((char*)&(l->point->rx()), sizeof(qreal));
        outFile.write((char*)&(l->point->ry()), sizeof(qreal));
    }

    outFile.close();
    return true;
}

bool MyMap::LoadMap(QString fileName)
{
    std::string path = fileName.toStdString();

    std::ifstream inFile;
    inFile.open (path, std::ios::in | std::ios::binary);

    if (!inFile.is_open())
        return false;

    int len;
    inFile.read((char*)&len, sizeof(int));
    int numLocals;
    inFile.read((char*)&numLocals, sizeof(int));

    char* ptr = new char[len];
    //Reading the image
    inFile.read(ptr, len);

    if (this->image != NULL)
        delete(this->image);

    this->image = new QImage();
    bool tst = this->image->loadFromData((uchar*)ptr, len, "PNG");
    if(!tst)
        return false;

    //Reading the locals
    for(auto l : this->locals)
    {
        locals.removeOne(l);
        delete(l);
    }
    for (int i = 0; i < numLocals; i++)
    {
        qreal x, y;
        char* name = new char[Local::MAXIMUM_NAME_SIZE];

        inFile.read(name, Local::MAXIMUM_NAME_SIZE);
        inFile.read((char*)&x, sizeof(qreal));
        inFile.read((char*)&y, sizeof(qreal));
        Local* l = new Local(name, new QPointF(x, y));
        locals.append(l);
    }
    inFile.close();
    return true;
}

QString MyMap::LocalsToString()
{
    QString ret = "";
    for(auto l : locals)
    {
        ret += QString(l->name) + " - " + QString::number(l->point->rx()) + " " + QString::number(l->point->ry()) + "\n";
    }
    return ret;
}

void MyMap::Clear()
{
    this->image = NULL;
    locals.clear();
}
