#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>


#include "table.h"
#include "myprogressbar.h"


Table::Table(int rows, int columns, QWidget *parent)
    : QTableWidget(rows, columns, parent)
{
    init();
}


// Инициализация таблицы. Задаются названия столбцов, выставляется запрет на редактирование ячеек и убирается вертикальный Header.
void Table::init(){

    QStringList Hheader;
    Hheader << tr("ID", "Идентификатор задачи") << tr("Progress bar", "Индикатор выполнения");

    setHorizontalHeaderLabels(Hheader);
    horizontalHeader()->setStretchLastSection(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    verticalHeader()->setVisible(false);

    //arr_t.resize(8);
    for(int i = 0; i < 10; ++i){
        arr_t.append(nullptr);
    }
}



// Слот. Проверяет наличие свободного потока, который можно предоставить строке. В случае его отсутствия - информирующее окно.
void Table::addRow(){

    bool check = true;

    for(auto &t : arr_t){
        if(!t){
            check = false;
            t = new MyThread(this);
            createRow(t);
            break;
        }else if(t->isFinished()){
            check = false;
            delete t;
            t = new MyThread(this);
            createRow(t);
            break;
        }else{
            continue;
        }
    }
    if(check){
        QMessageBox::information(0, tr("Information", "Информация"), tr("All threads are busy!", "Все потоки заняты!"));
    }
}


// Слот. Чистит таблицу, предварительно дождавшись завершения работы потоков.
void Table::deleteAllRow(){

    bool check = true;

    for(auto &t : arr_t){
        if(t){
            if(t->isRunning()){
               check = false;
               QMessageBox::information(0, tr("Information", "Информация"), tr("Wait for execution!", "Ожидайте выполнения!"));
               break;
            }
        }
    }
    if(check){
        clearContents();
        setRowCount(0);
    }
}


// Функция создания строки.
void Table::createRow(MyThread *t){

    insertRow(rowCount());

    QTableWidgetItem *leftRowItem = new QTableWidgetItem(QString::number(rowCount()));
    myProgressBar *rightRowItem = new myProgressBar(this);

    leftRowItem->setTextAlignment(Qt::AlignCenter);

    setItem(rowCount() - 1, 0, leftRowItem);
    setCellWidget(rowCount() - 1, columnCount() - 1, rightRowItem);

    connect(t, &MyThread::progress, rightRowItem, &QProgressBar::setValue);
    connect(t, &MyThread::finish  , rightRowItem, &myProgressBar::endProcess);

    t->start();
}


// Деструктор ожидает завершение работы потоков.
Table::~Table()
{
    for(auto &t : arr_t){
        if(t){
            if(t->isRunning()){
                t->quit();
                t->wait();
            }
        }
    }
}
