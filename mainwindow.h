#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Dataset_button_clicked();

    void on_Normal_button_clicked();

    void on_Binary_button_clicked();

    void on_Find_button_clicked();

    void on_STL_button_clicked();

    void on_Merge_button_clicked();

private:
    Ui::MainWindow *ui;
    int size;
    int *nums = new int [size];
    QString indexfound;
    int sortTime;
    int searchTime;

};
#endif // MAINWINDOW_H
