#include "data.h"
#include "entry.h"
#include "group.h"

#include <QCryptographicHash>
#include <QJsonArray>
#include <QJsonObject>

extern data global;

inline static QString format(QDateTime time) {
    if (time.isValid())
        return time.toString("yyyy MMdd hh:mm:ss");
    return "null";
}
inline static QString format(QDate time) {
    if (time.isValid())
        return time.toString("yyyyMMdd");
    return "null";
}
inline static QDateTime decode(QString time) {
    return QDateTime::fromString(time, "yyyy MMdd hh:mm:ss");
}
inline static QDate decode_date(QString time) {
    return QDate::fromString(time, "yyyyMMdd");
}

ListOrGroup::ListOrGroup(const QJsonObject& src) {
    key = decode(src["key"].toString());
    title = src["title"].toString().toUtf8();
    loc = src["loc"].toInt();
    empty = src["empty"].toBool();
    for (const auto &i : src["content"].toArray())
        content.append(decode(i.toString()));
    md5 = src["md5"].toString().toUtf8();
}

QJsonObject ListOrGroup::to_json() {
    QJsonObject result;
    result.insert("key", format(key));
    result.insert("title", QString::fromUtf8(title));
    result.insert("loc", loc);
    result.insert("empty", empty);
    QJsonArray c;
    std::sort(content.begin(), content.end());
    for (auto &i : content)
        c.append(format(i));
    result.insert("content", c);
    QJsonDocument temp(result);
    md5 = QCryptographicHash::hash(temp.toJson(QJsonDocument::Compact), QCryptographicHash::Md5);
    result.insert("md5", QString::fromUtf8(md5));
    return result;
}

QByteArray ListOrGroup::to_md5() {
    QJsonObject result;
    result.insert("key", format(key));
    result.insert("title", QString::fromUtf8(title));
    result.insert("loc", loc);
    result.insert("empty", empty);
    QJsonArray c;
    std::sort(content.begin(), content.end());
    for (auto &i : content)
        c.append(format(i));
    result.insert("content", c);
    QJsonDocument temp(result);
    md5 = QCryptographicHash::hash(temp.toJson(QJsonDocument::Compact), QCryptographicHash::Md5);
    return md5;
}

QMap<QDateTime, ListOrGroup*> lists_or_groups_from_json(QJsonArray data) {
    QMap<QDateTime, ListOrGroup*> result;
    for (const auto& i : data) {
        ListOrGroup* each = new ListOrGroup(i.toObject());
        if (each->getKey().isValid())
            result.insert(each->key, each);
        else
            global.unGrouped.append(each->first());
    }
    return result;
}

QJsonObject Entry::to_json() {
    QJsonObject result;
    result.insert("key", format(key));
    result.insert("title", QString::fromUtf8(title));
    result.insert("important", importance);
    result.insert("today", today ? format(QDate::currentDate()) : "null");
    result.insert("finished", finished);
    result.insert("start", format(start));
    result.insert("due", format(due));
    result.insert("note", QString::fromUtf8(note));

    QJsonDocument temp(result);
    md5 = QCryptographicHash::hash(temp.toJson(QJsonDocument::Compact), QCryptographicHash::Md5);
    result.insert("md5", QString::fromUtf8(md5));
    return result;
}

QByteArray Entry::to_md5() {
    QJsonObject result;
    result.insert("key", format(key));
    result.insert("title", QString::fromUtf8(title));
    result.insert("important", importance);
    result.insert("today", today);
    result.insert("finished", finished);
    result.insert("start", format(start));
    result.insert("due", format(due));
    result.insert("note", QString::fromUtf8(note));

    QJsonDocument temp(result);
    md5 = QCryptographicHash::hash(temp.toJson(QJsonDocument::Compact), QCryptographicHash::Md5);
    return md5;
}

Entry::Entry(const QJsonObject& src) {
    key = decode(src["key"].toString());
    title = src["title"].toString().toUtf8();
    importance = src["important"].toBool();
    today = decode_date(src["today"].toString()) == QDate::currentDate();
    finished = src["finished"].toBool();
    start = decode_date(src["start"].toString());
    due = decode_date(src["due"].toString());
    note = src["note"].toString().toUtf8();
    md5 = src["md5"].toString().toUtf8();
}

QMap<QDateTime, Entry*> entries_from_json(QJsonArray data) {
    QMap<QDateTime, Entry*> result;
    for (const auto& i : data) {
        Entry* each = new Entry(i.toObject());
        result.insert(each->key, each);
    }
    return result;
}
