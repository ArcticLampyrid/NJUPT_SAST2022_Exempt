#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QLineEdit>
#include <QPushButton>

class SearchBar : public QWidget {
    Q_OBJECT
private:
    QLayout *layout;
    QLineEdit *bar;
    QPushButton* button;
public:
    SearchBar();
public slots:
    void onSearch();
};

#endif // SEARCHBAR_H
