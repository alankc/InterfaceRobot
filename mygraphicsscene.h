#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QString>

class MyGraphicsScene : public QGraphicsScene
{
private:
    QString LocalLivre[2] = {"Deseja adicionar Local?", "Nome do local:"};
    QString LocalOcupado[2] = {"Remover Local", "Adicionar Tarefa"};
private slots:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
};

#endif // MYGRAPHICSSCENE_H
