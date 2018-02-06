#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mygraphicsscene.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include "controller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateLocals()
{
    ui->listWidgetLocais->clear();
    ui->listWidgetTarefas->clear();

    for (auto i : ui->graphicsView->scene()->items())
    {
        if (i != ui->graphicsView->scene()->items().last())
        {
            delete(i);
            ui->graphicsView->update();
        }
    }

    for (auto l : Controller::myMap.locals)
    {
        QImage image(":/Resources/place_icon.png");
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
        item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        item->setPos(*(l->point));
        ui->graphicsView->scene()->addItem(item);
        ui->listWidgetLocais->addItem(QString(l->name));
    }
}

void MainWindow::Clear()
{
    Controller::myMap.Clear();
    ui->listWidgetLocais->clear();
    ui->listWidgetTarefas->clear();

    for (auto i : ui->graphicsView->items())
    {
        ui->graphicsView->items().removeOne(i);
        delete(i);
        ui->graphicsView->update();
    }
}

void MainWindow::on_actionAbrirImagem_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Selecione o Mapa", QDir::currentPath(), QObject::tr("PNG (*.png)") );
    if(!fileName.isEmpty())
    {
        QImage *image = new QImage(fileName, "PNG");
        if(image->isNull())
        {
            QMessageBox::critical(this, "Erro", "Arquivo inadequado!");
            return;
        }

        Clear();

        MyGraphicsScene* scene = new MyGraphicsScene();
        ui->graphicsView->setScene(scene);

        QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
        scene->addItem(item);

        Controller::myMap.SetImage(image);
    }
}

void MainWindow::on_btnEnviar_clicked()
{

}

void MainWindow::on_btnRemover_clicked()
{
    for(auto i : ui->listWidgetTarefas->selectedItems())
    {
        ui->listWidgetTarefas->removeItemWidget(i);
        delete(i);
    }
}

void MainWindow::on_actionSalvar_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Salvar Mapa"), "",
                                                    tr("MAP Files(*.bin)"));
    if (!fileName.isEmpty())
    {
        if (!fileName.contains(".bin"))
            fileName += ".bin";

        if(Controller::myMap.SaveMap(fileName))
            QMessageBox::information(this, "Robot", "Salvo com sucesso!");
        else
            QMessageBox::critical(this, "Robot", "Falha ao salvar!");
    }
}

void MainWindow::on_actionAbrirMapa_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Abrir Mapa"), "",
                                                    tr("MAP Files(*.bin)"));

    if (!fileName.isEmpty())
    {
        Clear();

        if(Controller::myMap.LoadMap(fileName))
        {
            MyGraphicsScene* scene = new MyGraphicsScene();
            ui->graphicsView->setScene(scene);

            QImage *image = Controller::myMap.GetImage();
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
            scene->addItem(item);

            UpdateLocals();
        }
        else
            QMessageBox::critical(this, "Robot", "Falha ao salvar!");
    }
}

void MainWindow::on_listWidgetLocais_itemDoubleClicked(QListWidgetItem *item)
{
    auto local = Controller::myMap.GetLocalByName(item->text());

    if (local != NULL)
    {
        for(auto item : ui->graphicsView->scene()->items())
        {
            if (item != ui->graphicsView->scene()->items().last())
            {
                if (item->pos().rx() == local->point->rx() && item->pos().ry() == local->point->ry())
                {
                    for (auto i : ui->graphicsView->scene()->selectedItems())
                        i->setSelected(false);

                    item->setSelected(true);
                    item->setFocus();
                    ui->graphicsView->update();
                    return;
                }
            }
        }
    }
}
