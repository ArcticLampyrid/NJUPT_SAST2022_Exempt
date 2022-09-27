#ifndef LISTORGROUPDETAIL_H
#define LISTORGROUPDETAIL_H

#include <QTreeWidgetItem>

class ListOrGroupDetail : public QTreeWidgetItem {
public:
    ListOrGroupDetail(const QString &string, int type = UserType)
        : QTreeWidgetItem(QStringList()<<string, type) {}
    virtual void onClicked() = 0;
};

#endif // LISTORGROUPDETAIL_H
