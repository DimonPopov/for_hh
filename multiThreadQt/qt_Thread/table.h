#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include <QList>

#include "mythread.h"

class Table : public QTableWidget
{
private:
    Q_OBJECT
    void init();
    void createRow(MyThread *t);
    void closeThreads();
    QList<MyThread*> arr_t;
public:
    Table(int, int, QWidget* = nullptr);
    ~Table();
public slots:
    void addRow();
    void deleteAllRow();
};

#endif
