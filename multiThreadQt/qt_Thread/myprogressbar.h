#ifndef MYPROGRESSBAR_H
#define MYPROGRESSBAR_H

#include <QProgressBar>

class myProgressBar : public QProgressBar
{
public:
    myProgressBar(QWidget *parent = nullptr);
public slots:
    void endProcess();
};

#endif
