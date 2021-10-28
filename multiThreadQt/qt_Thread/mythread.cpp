#include "mythread.h"
#include <QDebug>


MyThread::MyThread(QObject *parent) : QThread(parent){ }


// Перегруженный метод в котором имитируется выполнение задачи.
void MyThread::run(){

    for(int i = 1; i <= 100; ++i){
        usleep(100000);
        emit progress(i);
    }

    emit finish();
}
