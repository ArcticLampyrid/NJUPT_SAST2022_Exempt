#ifndef GROUPDETAIL_H
#define GROUPDETAIL_H

#include "ListOrGroupDetail.h"

class Group;

class GroupDetail : public QObject, public ListOrGroupDetail{
    Q_OBJECT

    Group& group;
    QList<QTreeWidgetItem*> storage;
public:
    GroupDetail(Group*);

    void onClicked();
public slots:
    void onUpdate();
};

#endif // GROUPDETAIL_H
