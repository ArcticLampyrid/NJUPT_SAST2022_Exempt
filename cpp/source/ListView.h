#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "list.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QDateTime>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

class ListView : public QWidget {
    Q_OBJECT

    QBoxLayout *layout, *head;
    QLabel *title;
    QComboBox *sort;
    QPushButton *add;
    QListWidget *details;
    List* list;
public:
    ListView(List*);
    void show(List*);
signals:
    void open(Entry*);
    void addEntry(QDateTime);
public slots:
    void onUpdate();
    void onCreate();
    void onOpen(QListWidgetItem*);
};

#endif // LISTVIEW_H
