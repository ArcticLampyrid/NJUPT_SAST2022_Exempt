#include "SearchBar.h"
#include "data.h"
#include "list.h"
#include "mainui.h"

#include <QHBoxLayout>

extern data global;

SearchBar::SearchBar()
    : layout(new QHBoxLayout),
      bar(new QLineEdit),
      button(new QPushButton(tr("search"))) {
    setLayout(layout);
    layout->addWidget(bar);
    layout->addWidget(button);
}

void SearchBar::onSearch() {
    List* nov = new List(global.all, tr("Search"), [text = bar->text()](Entry* entry)->bool{
        /*此处实现*/
    });
    global.ui->openList(nov);
}
