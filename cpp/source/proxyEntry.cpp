#include "proxyEntry.h"
#include "entry.h"


ProxyEntry::operator const QString() {
    if (index == Title)
        return entry->title;
    if (index == Note)
        return entry->note;
    throw nullptr;
}

ProxyEntry::operator const QDate() {
    if (index == Due)
        return entry->due;
    if (index == From)
        return entry->start;
    throw nullptr;
}

ProxyEntry::operator const bool() {
    if (index == Finished)
        return entry->finished;
    if (index == Important)
        return entry->importance;
    if (index == Today)
        return entry->today;
    throw nullptr;
}

QByteArray& ProxyEntry::operator=(QString&& text) {
    if (index == Title)
        if (text.toUtf8() == entry->title)
            return entry->title;
        else
            return entry->title = text.toUtf8();
    if (index == Note)
        if (text.toUtf8() == entry->note)
            return entry->note;
        else
            return entry->note = text.toUtf8();
    throw nullptr;
}

bool ProxyEntry::operator=(bool value) {
    if (index == Finished)
        return entry->finished = value;
    if (index == Important)
        return entry->importance = value;
    if (index == Today)
        return entry->today = value;
    throw nullptr;
}

QDate& ProxyEntry::operator=(QDate&& value) {
    if (index == From)
        return entry->start = value;
    if (index == Due)
        return entry->due = value;
    throw nullptr;
}
