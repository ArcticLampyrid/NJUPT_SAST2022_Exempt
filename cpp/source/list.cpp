#include "list.h"
#include "data.h"
#include "entry.h"

extern data global;

List::List(List* src, QString name, std::function<bool(Entry*)> f) {
    key = QDateTime();
    title = name.toUtf8();
    for (auto& i : (QList<QDateTime>)(*src)[Content])
        if (f(global.entries[i]))
            content.append(i);
    empty = content.isEmpty();
}
