#include <QApplication>
#include "calculator.h"
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLabel* lbl = new QLabel();
    lbl->setMinimumSize(200, 50);
    lbl->show();

    Calculator w(nullptr,lbl);
    w.setWindowTitle("Calculator");
    w.setMinimumSize(230, 200);
    w.show();

    return a.exec();
}
