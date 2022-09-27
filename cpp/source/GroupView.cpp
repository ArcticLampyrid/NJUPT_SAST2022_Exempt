#include "GroupView.h"
#include "data.h"
#include "GroupDetail.h"
#include "ListDetail.h"
#include "ListOrGroup.h"

extern data global;

GroupView::GroupView() {
    setHeaderHidden(true);
    onUpdate();
    connect(this, &GroupView::itemClicked, this, &GroupView::onClicked);
}

void GroupView::onClicked(QTreeWidgetItem* item, int index) {
    ((ListOrGroupDetail*)item)->onClicked();
}

void GroupView::onUpdate() {
    clear();
    groups = global.groups.values();
    std::sort(groups.begin(), groups.end(), ListOrGroup::compare);
    addTopLevelItem(new ListDetail(global.all));
    addTopLevelItem(new ListDetail(global.unfinished));
    addTopLevelItem(new ListDetail(global.important));
    addTopLevelItem(new ListDetail(global.today));
    for (auto i : groups)
        if (global.lists.contains(i->getKey()))
            addTopLevelItem(new ListDetail((List*)i));
        else
            addTopLevelItem(new GroupDetail((Group*)i));
}
