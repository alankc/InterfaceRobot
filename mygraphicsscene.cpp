#include "mygraphicsscene.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QMessageBox>

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
        m.setText(a1->text());
        m.exec();
    }
    else if (res == a2)
    {
        m.setText(a2->text());
        m.exec();
    }
}
