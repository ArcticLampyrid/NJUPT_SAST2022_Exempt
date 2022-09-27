#include "GroupDetail.h"
#include "data.h"
#include "group.h"
#include "ListDetail.h"

extern data global;

GroupDetail::GroupDetail(Group* src) : ListOrGroupDetail(src->getTitle()), group(*src) {
    setExpanded(false);
    onUpdate();
}

void GroupDetail::onUpdate() {
    global.lock.lockForRead();
    QList<ListOrGroup*> content;
    for (auto i : (const QList<QDateTime>)group[Content])
        content.append(global.lists[i]);
    std::sort(content.begin(), content.end(), ListOrGroup::compare);
    for (auto i : content) {
        addChild(new ListDetail((List*)i));
    }
    global.lock.unlock();
}

void GroupDetail::onClicked() {
    onUpdate();
    setExpanded(true);
}
