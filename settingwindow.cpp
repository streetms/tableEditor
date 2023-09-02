#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QTranslator>
#include "app.h"
SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    readSettings();
}

SettingWindow::~SettingWindow()
{

    delete ui;
}

void SettingWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    }
}

void SettingWindow::readSettings()
{
    QSettings* pst = App::theApp()->getSettings();
    pst->beginGroup("Settings");
    ui->LanguageComboBox->setCurrentText(pst->value("Language","ru").toString());
    this->setGeometry(pst->value("settingWindowGeometry",this->geometry()).toRect());
    ui->number_of_lines->setValue(pst->value("maxNumberOfLines").toInt());
    pst->endGroup();
}

void SettingWindow::closeEvent(QCloseEvent *event)
{
    QSettings* pst = App::theApp()->getSettings();
    pst->beginGroup("Settings");
    pst->setValue("settingWindowGeometry",this->geometry());
    pst->setValue("maxNumberOfLines",ui->number_of_lines->value());
    pst->endGroup();
}

void SettingWindow::on_LanguageComboBox_currentTextChanged(const QString &arg1)
{
    QSettings* pst = App::theApp()->getSettings();
    pst->setValue("Settings/Language",arg1);
    App::theApp()->setLanguage(arg1);
}

