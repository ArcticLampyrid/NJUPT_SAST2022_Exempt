#include "data.h"
#include "mainui.h"
#include "entry.h"
#include "EntryView.h"
#include "ListView.h"
#include "GroupView.h"
#include "SearchBar.h"
#include <QFileDialog>
#include <QMessageBox>

extern data global;
QString currectDataPath;

MainUI::MainUI(QWidget *parent)
    : QDialog(parent),
      mainLayout(new QHBoxLayout), leftLayout(new QVBoxLayout),
      searchBar(new SearchBar), openButton(new QPushButton(tr("open a file")))
{
    global.ui = this;
    global.load();
    setAttribute(Qt::WA_DeleteOnClose);
    setLayout(mainLayout);
    mainLayout->addLayout(leftLayout);
    groups = new GroupView;
    entries = new ListView(global.current);
    mainLayout->addWidget(entries);
    leftLayout->addWidget(searchBar);
    leftLayout->addWidget(groups);
    leftLayout->addWidget(openButton);
    connect(openButton, &QPushButton::clicked, this, &MainUI::openFile);
}

MainUI::~MainUI() {
    if (!currectDataPath.isNull())
    {
        global.save(currectDataPath);
    }
}

void MainUI::onUpdate(int kind, QDateTime key)
{
    global.update();
    ((ListView*)entries)->onUpdate();
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

void MainUI::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open data"), ".", tr("JSON Files(*.json)"));
    if (path.isNull())
    {
        QMessageBox::information(this, tr("Information"), tr("You've given up opening a file."));
        return;
    }
    if (!currectDataPath.isNull())
    {
        global.save(currectDataPath);
    }
    currectDataPath = std::move(path);
    global.readLocal(currectDataPath);
    global.update();
    ((ListView*)entries)->onUpdate();
}
