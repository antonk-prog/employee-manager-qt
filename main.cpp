#include <QtWidgets>
#include <container.h>
#include "card.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Container container;
    container.show();



    return a.exec();
}
