#ifndef LOGINUI_H
#define LOGINUI_H

#include <QDialog>
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class LoginUI : public QDialog
{
    Q_OBJECT
private:
    QBoxLayout *mainLayout, *layout [3];
    QLabel *user, *passwd;
    QLineEdit *userTxt, *passwdTxt;
    QPushButton *login, *signup;
public:
    LoginUI(QWidget *parent = nullptr);
    ~LoginUI() {}

    void loginSuccess();
public slots:
    void onClicked();
};

#endif // LOGINUI_H
