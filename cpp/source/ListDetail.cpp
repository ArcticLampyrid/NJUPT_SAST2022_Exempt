#include "ListDetail.h"
#include "data.h"
#include "list.h"
#include "mainui.h"

extern data global;

ListDetail::ListDetail(List* src)
    : ListOrGroupDetail(src->getTitle()), list(src) {
    connect(this, &ListDetail::open, global.ui, &MainUI::openList);
}

void ListDetail::onClicked() {
    emit open(list);
}
