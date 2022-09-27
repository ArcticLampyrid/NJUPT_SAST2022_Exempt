#ifndef GROUP_H
#define GROUP_H

#include "ListOrGroup.h"

class Group : public ListOrGroup {
public:
    Group(QDateTime key) : ListOrGroup(QDateTime()){
        content.append(key);
    }
};

#endif // GROUP_H
