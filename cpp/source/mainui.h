#ifndef MAINUI_H
#define MAINUI_H

#include <QBoxLayout>
#include <QDateTime>
#include <QDialog>
#include <QPushButton>
#include <QListWidget>

class List;
class Entry;

class MainUI : public QDialog
{
    Q_OBJECT
private:
    QBoxLayout *mainLayout, *leftLayout;
    QWidget *searchBar;
    QWidget *groups, *entries, *details;
    QPushButton *openButton;

public:
    MainUI(QWidget *parent = nullptr);
    ~MainUI();

    void onUpdate(int, QDateTime);
public slots:
    void openList(List*);
    void openEntry(Entry*);
    void addEntry(QDateTime);
    void openFile();
};

#endif // MAINUI_H
