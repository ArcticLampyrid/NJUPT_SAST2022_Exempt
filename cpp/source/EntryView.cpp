#include "EntryView.h"
#include "data.h"
#include "entry.h"
#include "ListOrGroup.h"
#include "mainui.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

extern data global;

EntryView::EntryView(Entry* _entry)
    : title(new QLineEdit), start(new QLineEdit), due(new QLineEdit),
      importance(new QPushButton), finish(new QPushButton), shut(new QPushButton("X")),
      today(new QCheckBox),
      note(new QTextEdit),
      layout(new QVBoxLayout), head(new QHBoxLayout),
      entry(*_entry)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowModality(Qt::WindowModal);
    setAutoFillBackground(true);
    setLayout(layout);
    layout->addWidget(shut, 0, Qt::AlignRight);
    layout->addLayout(head);
    head->addWidget(finish);
    head->addWidget(importance);
    layout->addWidget(title);
    layout->addWidget(today);
    layout->addWidget(start);
    layout->addWidget(due);
    layout->addWidget(note);
    onUpdate();

    connect(shut, &QPushButton::clicked, this, &EntryView::onShut);
    connect(title, &QLineEdit::editingFinished, [this](){
        entry[Title] = title->text();
    });
    connect(importance, &QPushButton::clicked, [this](){
        bool status = entry[Important] = !entry[Important];
        importance->setText(important(status));
    });
    connect(finish, &QPushButton::clicked, [this](){
        bool status = entry[Finished] = !entry[Finished];
        finish->setText(isDone(status));
    });
    connect(today, &QCheckBox::stateChanged, [this](bool value){
        entry[Today] = value;
    });
    connect(start, &QLineEdit::editingFinished, [this](){
        entry[From] = QDate::fromString(start->text(), "yyyy.M.d");
    });
    connect(due, &QLineEdit::editingFinished, [this](){
        entry[Due] = QDate::fromString(due->text(), "yyyy.M.d");
    });
    connect(note, &QTextEdit::textChanged, [this](){
        entry[Note] = note->toPlainText();
    });
}

EntryView::EntryView(QDateTime _time) : EntryView(new Entry) {
    save = new QPushButton("Save");
    listKey = _time;
    layout->addWidget(save, 0, Qt::AlignRight);
    connect(save, &QPushButton::clicked, this, &EntryView::onSave);
}

void EntryView::onUpdate() {
    global.entryGuard.lockForRead();
    title->setText((const QString)entry[Title]);
    if (title->text().isEmpty())
        title->setPlaceholderText("Task Name");
    finish->setText(isDone(entry[Finished]));
    importance->setText(important(entry[Important]));
    today->setChecked(entry[Today]);
    today->setText("Today's Task");
    if (((const QDate)entry[From]).isValid())
        start->setText(((const QDate)entry[From]).toString("yyyy-M-d dddd"));
    else
        start->setPlaceholderText("Start from");
    if (((const QDate)entry[Due]).isValid())
        due->setText(((const QDate)entry[Due]).toString("yyyy-M-d dddd"));
    else
        due->setPlaceholderText("Due Date");
    note->setText((const QString)entry[Note]);
    if (note->toPlainText().isEmpty())
        note->setPlaceholderText("Note");
    global.entryGuard.unlock();
}

void EntryView::onSave() {
    hide();
    global.lock.lockForWrite();
    (*global.lists[listKey])[Content] += entry;
    global.lock.unlock();
    global.ui->onUpdate(ADD_ENTRY, listKey);
    close();
}

void EntryView::onShut() {
    hide();
    global.lock.lockForWrite();
    global.opened = nullptr;
    global.lock.unlock();
    global.ui->onUpdate(ALTER_ENTRY, listKey);
    close();
}
