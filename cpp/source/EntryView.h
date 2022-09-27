#ifndef ENTRYVIEW_H
#define ENTRYVIEW_H

#include <QBoxLayout>
#include <QCheckBox>
#include <QDateTime>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

class Entry;

class EntryView : public QWidget {
    Q_OBJECT

    QLineEdit *title, *start, *due;
    QPushButton *importance, *finish, *shut, *save;
    QCheckBox* today;
    QTextEdit* note;
    QBoxLayout *layout, *head;

    Entry& entry;
    QDateTime listKey;
public:
    EntryView(Entry*);
    EntryView(QDateTime);

    void onUpdate();

public slots:
    void onSave();
    void onShut();
};

#define important(flag) (flag) ? "⭐" : ""
#define isDone(flag) (flag) ? "√" : "O"

#endif
