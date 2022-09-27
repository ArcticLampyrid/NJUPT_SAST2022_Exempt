#ifndef PROXYENTRY_H
#define PROXYENTRY_H

#include <QByteArray>
#include <QReadWriteLock>
#include <QDateTime>

class Entry;

class ProxyEntry {
    Entry* entry;
    int index;
public:
    ProxyEntry(Entry* from, int _index) : entry(from), index(_index) {}

    operator const QString();
    QByteArray& operator=(QString&&);
    operator const QDate();
    QDate& operator=(QDate&&);
    operator const bool();
    bool operator=(bool);
};

#endif // PROXYENTRY_H
