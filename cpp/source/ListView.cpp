#include "ListView.h"
#include "data.h"
#include "entry.h"
#include "EntryDetail.h"
#include "mainui.h"
#include "SortableItem.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

extern data global;

#define BY_IMPORTANCE 0
#define TODAY_FIRST 1
#define BY_DUE 2
#define BY_CREATION 3
#define TOTAL 4

static std::function<bool(const EntryDetail*, const EntryDetail*)> compare[TOTAL] = {
    //BY_IMPORTANCE
    [](const EntryDetail* a, const EntryDetail* b)->bool {
        if (a->getEntry()->isFinished())
            return false;
        if (b->getEntry()->isFinished())
            return true;
        if (a->getEntry()->isImportant())
            return true;
        if (b->getEntry()->isImportant())
            return false;
        if (a->getEntry()->getDue().isValid() && b->getEntry()->getDue().isValid())
            return a->getEntry()->getDue() < b->getEntry()->getDue();
        if (a->getEntry()->getDue().isValid())
            return true;
        if (b->getEntry()->getDue().isValid())
            return false;
        return a->getEntry()->getKey() > b->getEntry()->getKey();
    },
    //TODAY_FIRST
    [](const EntryDetail* a, const EntryDetail* b)->bool {
        if (a->getEntry()->isFinished())
            return false;
        if (b->getEntry()->isFinished())
            return true;
        if (a->getEntry()->isToday())
            return true;
        if (b->getEntry()->isToday())
            return false;
        if (a->getEntry()->isImportant())
            return true;
        if (b->getEntry()->isImportant())
            return false;
        if (a->getEntry()->getDue().isValid() && b->getEntry()->getDue().isValid())
            return a->getEntry()->getDue() < b->getEntry()->getDue();
        if (a->getEntry()->getDue().isValid())
            return true;
        if (b->getEntry()->getDue().isValid())
            return false;
        return a->getEntry()->getKey() > b->getEntry()->getKey();
    },
    //BY_DUE
    [](const EntryDetail* a, const EntryDetail* b)->bool {
        if (a->getEntry()->isFinished())
            return false;
        if (b->getEntry()->isFinished())
            return true;
        if (a->getEntry()->getDue().isValid() && b->getEntry()->getDue().isValid())
            return a->getEntry()->getDue() < b->getEntry()->getDue();
        if (a->getEntry()->getDue().isValid())
            return true;
        if (b->getEntry()->getDue().isValid())
            return false;
        if (a->getEntry()->isImportant())
            return true;
        if (b->getEntry()->isImportant())
            return false;
        return a->getEntry()->getKey() > b->getEntry()->getKey();
    },
    //BY_CREATION
    [](const EntryDetail* a, const EntryDetail* b)->bool {
        if (a->getEntry()->isFinished())
            return false;
        if (b->getEntry()->isFinished())
            return true;
        return a->getEntry()->getKey() > b->getEntry()->getKey();
    }
};

ListView::ListView(List* _list)
    : layout(new QVBoxLayout), head(new QHBoxLayout),
      title(new QLabel(_list->getTitle())),
      sort(new QComboBox),
      add(new QPushButton("+")),
      details(new QListWidget),
      list(_list)
{
    setLayout(layout);
    head->addWidget(title);
    head->addWidget(sort);
    sort->addItems(QStringList()<<"Importance"<<"Today's First"<<"Due Date"<<"Creation Date");
    sort->setCurrentIndex(0);
    head->addWidget(add);
    layout->addLayout(head);
    layout->addWidget(details);
    onUpdate();
    connect(details, &QListWidget::itemClicked, this, &ListView::onOpen);
    connect(this, &ListView::open, global.ui, &MainUI::openEntry);
    connect(add, &QPushButton::clicked, this, &ListView::onCreate);
    connect(this, &ListView::addEntry, global.ui, &MainUI::addEntry);
    connect(sort, &QComboBox::activated, this, &ListView::onUpdate);
}

void ListView::show(List* nov) {
    global.current = nov;
    onUpdate();
}

void ListView::onUpdate() {
    list = global.current;
    int index = sort->currentIndex();
    details->clear();
    title->setText(list->getTitle());
    for (auto &i : (QList<QDateTime>)(*list)[Content]) {
        EntryDetail* detail = new EntryDetail(global.entries[i]);
        auto item = new SortableItem(detail);
        item->setSizeHint(detail->sizeHint());
        details->addItem(item);
        details->setItemWidget(item, detail);
        item->set(compare[index]);
    }
    details->sortItems();
}

void ListView::onCreate() {
    emit addEntry(list->getKey());
}

void ListView::onOpen(QListWidgetItem* item) {
    EntryDetail* widget = (EntryDetail*)details->itemWidget(item);
    emit open(widget->getEntry());
}
