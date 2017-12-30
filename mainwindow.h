#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow* GetUI();

private slots:
    void on_actionAbrirImagem_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H