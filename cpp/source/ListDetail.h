#ifndef LISTDETAIL_H
#define LISTDETAIL_H

#include "ListOrGroupDetail.h"

class List;

class ListDetail : public QObject, public ListOrGroupDetail{
    Q_OBJECT

    List* list;
public:
    ListDetail(List* src);

    void onClicked();
signals:
    void open(List*);
};

#endif // LISTDETAIL_H
