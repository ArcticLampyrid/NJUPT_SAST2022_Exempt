#ifndef SELECTFILE_H
#define SELECTFILE_H
class MainUI;
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class SelectFile:public  QObject
{
    Q_OBJECT
public:
    SelectFile();
private:
    MainUI *ui;
    QPushButton *confirmBtn;
    QLabel  *show_dir_path;
private slots:
signals:


};

#endif // SELECTFILE_H
