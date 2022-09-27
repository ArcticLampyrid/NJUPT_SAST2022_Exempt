#ifndef ENTRYDETAIL_H
#define ENTRYDETAIL_H

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>

class Entry;

class EntryDetail : public QWidget {
    Q_OBJECT

    Entry* entry;
    QLabel *title, *status;
    QPushButton* button;
    QBoxLayout *text, *horizon;
public:
    EntryDetail(Entry* src);

    inline Entry* getEntry() const{
        return entry;
    }
    void onUpdate();
};

#endif // ENTRYDETAIL_H
