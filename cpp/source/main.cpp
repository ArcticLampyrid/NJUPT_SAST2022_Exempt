#include "mainui.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("TO-DO_PANEL_zh_CN.qm");
    a.installTranslator(&translator);

    MainUI* w = new MainUI;
    w->show();
    return a.exec();
}
