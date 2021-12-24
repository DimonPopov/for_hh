/*
 * Основное окно программы.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow{

private:
    Q_OBJECT
    void init();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;
};
#endif
