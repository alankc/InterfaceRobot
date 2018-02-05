#include "mygraphicsscene.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QMessageBox>
#include <QGraphicsPixmapItem>

void MyGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu("Title", event->widget());

    QAction *a1 = menu.addAction(LocalOcupado[0]);
    menu.addSeparator();
    QAction *a2 = menu.addAction(LocalOcupado[1]);
    //menu.addAction(event->pos().rx());
    QMessageBox m;
    QAction *res = menu.exec(event->screenPos());
    if(res == a1)
    {
        QImage image(":/Resources/place_icon.png");
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        item->setFlags(QGraphicsItem::ItemIsSelectable);
        item->setPos(event->scenePos());
        this->addItem(item);
    }
    else if (res == a2)
    {
        m.setText(a2->text());
        m.exec();
    }
}
