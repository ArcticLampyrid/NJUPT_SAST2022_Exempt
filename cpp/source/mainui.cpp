#include "data.h"
#include "mainui.h"
#include "entry.h"
#include "EntryView.h"
#include "ListView.h"
#include "GroupView.h"
#include "SearchBar.h"

extern data global;

MainUI::MainUI(QWidget *parent)
    : QDialog(parent),
      mainLayout(new QHBoxLayout), leftLayout(new QVBoxLayout),
      searchBar(new SearchBar)
{
    global.ui = this;
    global.readLocal();
    global.load();

    setAttribute(Qt::WA_DeleteOnClose);
    setLayout(mainLayout);
    mainLayout->addLayout(leftLayout);
    groups = new GroupView;
    entries = new ListView(global.current);
    mainLayout->addWidget(entries);
    leftLayout->addWidget(searchBar);
    leftLayout->addWidget(groups);
}

MainUI::~MainUI() {
    global.save();
}

void MainUI::openList(List* list) {
    if (global.current == list)
        return;
    global.lock.lockForWrite();
    ((ListView*)entries)->show(list);
    global.lock.unlock();
}

void MainUI::openEntry(Entry* entry) {
    if (global.opened == entry)
        return;
    global.entryGuard.lockForRead();
    global.opened = entry;
    details = new EntryView(global.opened);
    details->setParent(this);
    details->setGeometry(this->width() * 2 / 3, 0, this->width() / 3, this->height());
    details->show();
    global.entryGuard.unlock();
}

void MainUI::addEntry(QDateTime list) {
    details = new EntryView(list);
    details->setGeometry(this->width() * 2 / 3, 0, this->width() / 3, this->height());
    details->setParent(this);
    details->show();
}
