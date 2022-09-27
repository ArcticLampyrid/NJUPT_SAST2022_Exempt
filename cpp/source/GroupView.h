#ifndef GROUPVIEW_H
#define GROUPVIEW_H

#include <QLabel>
#include <QTreeWidget>
#include <QDateTime>

class ListOrGroup;

class GroupView : public QTreeWidget {
    Q_OBJECT

    QList<ListOrGroup*> groups;
public:
    GroupView();

    void onUpdate();
public slots:
    void onClicked(QTreeWidgetItem*, int);
};

#endif // GROUPVIEW_H
