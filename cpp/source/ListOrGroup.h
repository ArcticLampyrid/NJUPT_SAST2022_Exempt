#ifndef LISTORGROUP_H
#define LISTORGROUP_H

#include "proxyListOrGroup.h"

#define Title 0
#define Location 1
#define Content 2

class ListOrGroup : public QObject{
    Q_OBJECT

protected:
    QDateTime key;
    QByteArray title;       //UTF-8
    QList<QDateTime> content;
    int loc;
    bool empty;
    QByteArray md5;
public:
    ListOrGroup(QDateTime time = QDateTime::currentDateTime()) : key(time), empty(true) {}
    ListOrGroup(const QJsonObject&);

    inline ProxyListOrGroup operator[](int index) {
        return ProxyListOrGroup(this, index);
    }
    inline QDateTime getKey() const {
        return key;
    }
    inline QString getTitle() const {
        return title;
    }
    inline QDateTime first() const {
        if (content.empty())
            throw nullptr;
        return content.first();
    }
    virtual QJsonObject to_json();
    QByteArray to_md5();
    static bool compare(ListOrGroup *a,ListOrGroup *b) {
        return a->loc < b->loc;
    }
signals:
    void Update();
private slots:
    void onUpdate(){}

    friend class ProxyListOrGroup;
    friend struct data;
    friend QMap<QDateTime, ListOrGroup*> lists_or_groups_from_json(QJsonArray);
};

#endif // LISTORGROUP_H
