#ifndef SORTABLEITEM_H
#define SORTABLEITEM_H

#include <QListWidgetItem>

template<typename U>
class SortableItem : public QListWidgetItem {
public:
    using T = std::decay_t<U>;
    T* value;
    std::function<bool(const T&, const T&)>* compare;

    SortableItem(U src) : QListWidgetItem(), value(&src) {}
    inline bool operator<(SortableItem<T>& other) {
        return (*compare)(*value, other);
    }
    inline void set(std::function<bool(const T&, const T&)> functor) {
        compare = &functor;
    }
};

#endif // SORTABLEITEM_H
