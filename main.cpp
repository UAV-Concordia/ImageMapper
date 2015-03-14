#include "imagemapper.h"
#include <QApplication>

/*
 * Main runner
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageMapper w;
    w.show();

    return a.exec();
}
