#include "list.h"
#include "data.h"
#include "entry.h"

extern data global;

ProxyListOrGroup::operator const QList<QDateTime>() {
    if (index == Content)
        return list->content;
    throw nullptr;
}

QList<QDateTime>& ProxyListOrGroup::operator+=(Entry& entry) {
    global.entries.insert(entry.getKey(), &entry);
    if (list) {
        list->content.append(entry.getKey());
        return list->content;
    }
    else
        global.lists.remove(QDateTime());
}
