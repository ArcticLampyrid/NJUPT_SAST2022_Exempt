#ifndef DATA_H
#define DATA_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QReadWriteLock>
#include <QNetworkRequest>

#define LOCAL "./data.json"
#define SETTINGS "./settings.json"

class ListOrGroup;
class List;
class Group;
class Entry;
class MainUI;

#define ALTER_ENTRY 0
#define ADD_ENTRY 1

class data {
    QJsonDocument local;
public:
    const char* user = "Administrator";
    List *all, *unfinished, *important, *today, *current;
    QList<QDateTime> unGrouped;
    Entry* opened = nullptr;
    QMap<QDateTime, ListOrGroup*> groups, lists;
    QMap<QDateTime, Entry*> entries;
    MainUI* ui;
    QReadWriteLock lock, entryGuard;

    void readLocal();
    void load();
    void update();
    void save();
};

QMap<QDateTime, ListOrGroup*> lists_or_groups_from_json(QJsonArray);
QMap<QDateTime, Entry*> entries_from_json(QJsonArray);

#endif // DATA_H
