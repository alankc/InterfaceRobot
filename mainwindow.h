#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "defines.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void UpdateLocals();

private slots:
    void on_actionAbrirImagem_triggered();
    void on_btnEnviar_clicked();
    void on_btnRemover_clicked();
    void on_actionSalvar_triggered();
    void on_actionAbrirMapa_triggered();
    void on_listWidgetLocais_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    void Clear();
};

#endif // MAINWINDOW_H
