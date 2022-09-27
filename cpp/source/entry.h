#ifndef ENTRY_H
#define ENTRY_H

#include "proxyEntry.h"

#define Title 0
#define Important 1
#define Today 2
#define From 3
#define Due 4
#define Note 5
#define Finished 6

class Entry : public QObject {
    Q_OBJECT

    QDateTime key;
    QByteArray title;       //UTF-8
    QDate start, due;       //默认值QDate()
    bool importance, today;  //默认值false
    QByteArray note;        //UTF-8
    bool finished;          //默认值false
    QByteArray md5;

public:
    Entry(QDateTime time = QDateTime::currentDateTime()) : key(time), importance(false), today(false), finished(false) {}
    Entry(const QJsonObject& src);

    inline ProxyEntry operator[](int index) {
        return ProxyEntry(this, index);
    }
    inline QDateTime getKey() const {
        return key;
    }
    inline QString getTitle() const {
        return title;
    }
    inline QDate getDue() const {
        return due;
    }
    inline bool isImportant() const {
        return importance;
    }
    inline bool isToday() const {
        return today;
    }
    inline bool isFinished() const {
        return finished;
    }

private:
    QJsonObject to_json();
    QByteArray to_md5();

signals:
    void Update();
private slots:
    void onUpdate(){}

    friend class ProxyEntry;
    friend QMap<QDateTime, Entry*> entries_from_json(QJsonArray);
    friend struct data;
};

#endif // ENTRY_H
