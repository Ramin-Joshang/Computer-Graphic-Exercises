#include <QApplication>
#include "src/ui/welcomewindow.h"
#include "src/ui/messagedialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WelcomeWindow welcomeWindow;
    welcomeWindow.show();
    return a.exec();
}