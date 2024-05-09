#include "Dinosaur.h"
#include "config.h"
#include <QResource>
#include <QApplication>
#include "newscene.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Dinosaur w;
    NewScene new_w(&w);
    new_w.show();
    new_w.setFocus();
    return a.exec();
}
