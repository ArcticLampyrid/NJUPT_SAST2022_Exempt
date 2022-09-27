#include "data.h"
#include "loginui.h"
#include "mainui.h"

#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>

extern data global;

LoginUI::LoginUI(QWidget *parent)
    : QDialog(parent),
      mainLayout(new QVBoxLayout), layout{new QHBoxLayout, new QHBoxLayout, new QHBoxLayout},
      user(new QLabel(tr("Username:"))), passwd(new QLabel(tr("Password:"))),
      userTxt(new QLineEdit), passwdTxt(new QLineEdit),
      login(new QPushButton(tr("Log in"))), signup(new QPushButton(tr("Sign up")))
{
    setLayout(mainLayout);
    layout[0]->addWidget(user);
    layout[0]->addWidget(userTxt);
    layout[1]->addWidget(passwd);
    layout[1]->addWidget(passwdTxt);
    layout[2]->addWidget(login);
    layout[2]->addWidget(signup);
    mainLayout->addLayout(layout[0]);
    mainLayout->addLayout(layout[1]);
    mainLayout->addLayout(layout[2]);

    userTxt->setMaxLength(20);
    passwdTxt->setEchoMode(QLineEdit::Password);

    connect(login, &QPushButton::clicked, this, &LoginUI::onClicked);

    global.readSettings();
}

void LoginUI::onClicked() {
    global.makeHead(userTxt->text().toUtf8(), passwdTxt->text().toUtf8());
    loginSuccess();
}

void LoginUI::loginSuccess() {
    global.readLocal();
    global.load();
    (new MainUI)->show();
    this->close();
}
