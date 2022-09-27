#include "EntryDetail.h"
#include "data.h"
#include "entry.h"
#include "EntryView.h"
#include "list.h"
#include "mainui.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

extern data global;

inline static QString format(QDate time) {
    if (time == QDate::currentDate())
        return QObject::tr("Today");
    if (time == QDate::currentDate().addDays(1))
        return QObject::tr("Tomorrow");
    if (time == QDate::currentDate().addDays(-1))
        return QObject::tr("Yesterday");
    int *week = new int, *current = new int;
    if (time.weekNumber(week) == QDate::currentDate().weekNumber(current) && *week == *current)
        return time.toString("M.d ddd");
    return time.toString("M.d");
}

inline static QString getStatus(Entry* entry) {
    return important(entry->isImportant()) + format(entry->getDue());
}

EntryDetail::EntryDetail(Entry* src)
    : entry(src),
      title(new QLabel(entry->getTitle())), status(new QLabel(getStatus(entry))),
      button(new QPushButton(tr(isDone((*entry)[Finished])))),
      text(new QVBoxLayout), horizon(new QHBoxLayout)
{
    setLayout(horizon);
    horizon->addLayout(text);
    text->addWidget(title);
    text->addWidget(status);
    horizon->addWidget(button, 0, Qt::AlignRight);
    connect(button, &QPushButton::clicked, [this](){
        bool status = (*entry)[Finished] = !(*entry)[Finished];
        button->setText(isDone(status));
        global.ui->onUpdate(ALTER_ENTRY, global.current->getKey());
    });
}
