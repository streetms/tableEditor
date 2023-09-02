#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingWindow(QWidget *parent = nullptr);
    ~SettingWindow();
    void changeEvent(QEvent * event);
    void readSettings();
    void closeEvent(QCloseEvent* event) override;
private slots:
    void on_LanguageComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::SettingWindow *ui;
//    QTranslator()
};

#endif // SETTINGWINDOW_H
