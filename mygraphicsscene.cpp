#include "mygraphicsscene.h"
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QInputDialog>
#include <QListWidgetItem>
#include "controller.h"

void MyGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QImage image(":/Resources/place_icon.png");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    item->setFlags(QGraphicsItem::ItemIsSelectable);
    item->setPos(event->scenePos());

    //Check if there is an item in the area
    for (auto i : this->items())
    {
        if (i != this->items().last())
        {
            //Ask if the user wants remove an item or insert a new task
            if(item->collidesWithItem(i))
            {
                QMenu menu("", event->widget());
                QAction *a1 = menu.addAction(LocalOcupado[0]);
                menu.addSeparator();
                QAction *a2 = menu.addAction(LocalOcupado[1]);

                QAction *res = menu.exec(event->screenPos());
                if(res == a1) //Remove local
                {
                    auto removed = Controller::myMap.RemoveLocal(i->pos());
                    if (removed != NULL)
                    {
                        delete(removed);
                        /*this->items().removeOne(i);
                        delete(i);*/
                        Controller::mainWindow->UpdateLocals();
                    }
                }
                else if (res == a2) //Add task
                {

                }
                return;
            }
        }
    }

    //Ask if the user wants add as new place
    bool ok;
    QString text = QInputDialog::getText(event->widget(), LocalLivre[0], LocalLivre[1], QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty())
    {
        //Add new place to list into form
        //Add new place to scene and map
        Local *l = new Local();
        l->name = new char[Local::MAXIMUM_NAME_SIZE];
        strcpy(l->name, text.toStdString().c_str());
        l->point = new MyPoint(event->scenePos().rx(), event->scenePos().ry());
        Controller::myMap.InsertLocal(l);
        Controller::mainWindow->UpdateLocals();
    }
}
