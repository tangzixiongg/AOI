#include <stdint.h>
#include <QApplication>
#include <QWidget>

int32_t main(int32_t argc, char* argv[])
{
    QApplication app(argc, argv);

    QWidget w;
    w.show();


    app.exec();
    return 0;
}
