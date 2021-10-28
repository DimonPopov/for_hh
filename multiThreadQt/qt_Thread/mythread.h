/*
 * Класс управления потоком, имеющий сигналы необходимые для изменения состояния QProgressBar.
 */

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
private:
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    ~MyThread() = default;
    void run() override;
signals:
    void progress(int);
    void finish();
};

#endif
