#ifndef LIST_H
#define LIST_H

#include "ListOrGroup.h"

class Entry;

class List : public ListOrGroup{
public:
    List(QList<QDateTime> _content) {
        key = QDateTime();
        title = tr("All").toUtf8();
        content = _content;
        empty = content.isEmpty();
    }
    List(List* src, QString name, std::function<bool(Entry*)> f);
};

#endif // LIST_H
