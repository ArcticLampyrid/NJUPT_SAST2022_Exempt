#ifndef PROXYLIST_H
#define PROXYLIST_H

#include <QByteArray>
#include <QReadWriteLock>
#include <QDateTime>

class ListOrGroup;
class Entry;

class ProxyListOrGroup {
    ListOrGroup* list;
    int index;
public:
    ProxyListOrGroup(ListOrGroup* from, int _index) : list(from), index(_index) {}

    operator const QString();
    QByteArray& operator=(QString&&);
    operator const QList<QDateTime>();
    QList<QDateTime>& operator+=(Entry&);
};

#endif // PROXYLIST_H
