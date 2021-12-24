#include <QtWidgets>

#include "mainwindow.h"
#include "table.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    init();
}


// Инициализация главного окна приложения. Задаем слои, кнопки, таблицу и связываем все вместе.
void MainWindow::init(){

    setWindowTitle(tr("task_2.5", "Задание 2.5"));
    setWindowIcon(QIcon(":/img/icon_qt.png"));
    setGeometry(300,300, 700, 500);

    QWidget *new_main_widget = new QWidget;

    QVBoxLayout *left_vbx = new QVBoxLayout;

    QPushButton* add_b = new QPushButton(tr("Add task", "Добавление процесса"));
    QPushButton* clear_b = new QPushButton(tr("Clear", "Почистить таблицу"));

    left_vbx->addSpacing(3);
    left_vbx->addWidget(add_b);
    left_vbx->addWidget(clear_b);
    left_vbx->addStretch(1);

    Table *table = new Table(0, 2);

    connect(add_b  , &QPushButton::clicked, table, &Table::addRow);
    connect(clear_b, &QPushButton::clicked, table, &Table::deleteAllRow);

    QHBoxLayout *main_hbl = new QHBoxLayout;

    main_hbl->addLayout(left_vbx);
    main_hbl->addWidget(table);

    new_main_widget->setLayout(main_hbl);

    setCentralWidget(new_main_widget);
}
