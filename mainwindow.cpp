#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mygraphicsscene.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsPixmapItem>

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

Ui::MainWindow* MainWindow::GetUI()
{
    return ui;
}

void MainWindow::on_actionAbrirImagem_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Selecione o Mapa", QDir::currentPath(), QObject::tr("PNG (*.png)") );
        if(!fileName.isEmpty())
        {
            QImage *image = new QImage(fileName);

            if(image->isNull())
            {
                QMessageBox::critical(this, "Erro", "Arquivo inadequado!");
                return;
            }

            MyGraphicsScene* scene = new MyGraphicsScene();
            ui->graphicsView->setScene(scene);

            QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*image));
            scene->addItem(item);
        }
}
