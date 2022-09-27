#include "data.h"
#include "entry.h"
#include "group.h"
#include "list.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonObject>

data global;

void data::readLocal(const QString& path) {
    QFile file(path);
    if (!file.exists())
        return;
    if (!file.open(QIODevice::ReadOnly))
        throw nullptr;
    QJsonParseError parser;
    local = QJsonDocument::fromJson(file.readAll(), &parser);
    if (parser.error != QJsonParseError::NoError)
        throw nullptr;

    if (!local.object().contains(user))
        return;

    QJsonObject userdata = local.object()[user].toObject();
    groups = lists_or_groups_from_json(userdata["Group"].toArray());
    lists = lists_or_groups_from_json(userdata["List"].toArray());
    entries = entries_from_json(userdata["Entry"].toArray());
}

void data::load() {
    all = new List(entries.keys());
    unfinished = new List(all, QObject::tr("Unfinished"), [](Entry* entry)->bool{return !entry->finished;});
    important = new List(all, QObject::tr("Important"), [](Entry* entry)->bool{return entry->importance;});
    today = new List(all, QObject::tr("Today's"), [](Entry* entry)->bool{return entry->today;});
    current = all;
    for (auto& i : unGrouped)
        groups.insert(i, lists[i]);
}

void data::update() {
    auto _all = new List(entries.keys());
    auto _unfinished = new List(_all, QObject::tr("Unfinished"), [](Entry* entry)->bool{return !entry->finished;});
    auto _important = new List(_all, QObject::tr("Important"), [](Entry* entry)->bool{return entry->importance;});
    auto _today = new List(_all, QObject::tr("Today's"), [](Entry* entry)->bool{return entry->today;});
    all->content = _all->content;
    unfinished->content = _unfinished->content;
    important->content = _important->content;
    today->content = _today->content;
    delete _all;
    delete _unfinished;
    delete _important;
    delete _today;
}

void data::save(const QString& path) {
    QJsonArray g, l, e;
    for (auto i : groups)
        for (auto i : groups) {
            if (unGrouped.contains(i->key))
                g.append(Group(i->key).to_json());
            else
                g.append(i->to_json());
        }
    for (auto i : lists)
        l.append(i->to_json());
    for (auto i : entries)
        e.append(i->to_json());

    QJsonObject userdata;
    userdata.insert("Groups", g);
    userdata.insert("List", l);
    userdata.insert("Entry", e);

    QJsonObject all = local.object();
    all[user] = userdata;

    if (all.isEmpty())
        return;
    local.setObject(all);

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        throw nullptr;
    file.write(local.toJson());
    file.close();
}
