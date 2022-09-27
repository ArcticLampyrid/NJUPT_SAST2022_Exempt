#include "SearchBar.h"
#include "data.h"
#include "list.h"
#include "mainui.h"
#include "entry.h"
#include <QHBoxLayout>

extern data global;

SearchBar::SearchBar()
    : layout(new QHBoxLayout),
      bar(new QLineEdit),
      button(new QPushButton(tr("search"))) {
    setLayout(layout);
    layout->addWidget(bar);
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, &SearchBar::onSearch);
}

void SearchBar::onSearch() {
    QDate date = QDate::fromString(bar->text(), "yyyy.M.d");
    List* nov = new List(global.all, tr("Search"), [text = bar->text(), date](Entry* entry)->bool{
        /*此处实现*/
        if (date.isValid())
        {
            if (!entry->getStart().isValid())
            {
                if (entry->getDue().isValid() && date == entry->getDue())
                {
                    // only due is valid, then requires to match the due exactly
                    return true;
                }
            }
            else
            {
                if (entry->getDue().isValid())
                {
                    if (date >= entry->getStart() && date <= entry->getDue()) 
                    {
                        // both start and due are valid, 
                        // then requires to be included in [start, due]
                        return true;
                    }
                }
                else
                {
                    if (date == entry->getStart())
                    {
                        // only start is valid, then requires to match the start exactly
                        return true;
                    }
                }
            }
        }
        if (entry->getNote().contains(text)) {
            return true;
        }
        return entry->getTitle().contains(text);
    });
    global.ui->openList(nov);
}
