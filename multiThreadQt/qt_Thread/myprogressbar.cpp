#include "myprogressbar.h"

myProgressBar::myProgressBar(QWidget *parent)
    : QProgressBar(parent)
{
    setTextVisible(true);
    setAlignment(Qt::AlignCenter);
}


// Слот. Принимает сигнал от потока о завершений работы.
void myProgressBar::endProcess(){
    setFormat(tr("Complete!", "Выполнено!"));
}
