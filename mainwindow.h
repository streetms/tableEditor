#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QSettings>
#include <QTranslator>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent* event) override;
    void changeEvent(QEvent* event);
private:
    int yes_no_question(const QString& text);
    void createCsvModel();
    Ui::MainWindow *ui;
    QStandardItemModel *csvModel;
    QStringList horizontalHeaderLabels;
    QString mainFile;
    void readSettings();
    bool changed;
public slots:
    void changeItemTable(QStandardItem* item);
private slots:
    void on_Open_triggered();
    void Open(QString file);
    void on_settings_triggered();
    void on_Exit_triggered();
    void on_Save_as_triggered();
    void on_Save_triggered();
    void on_Create_triggered();
    void on_About_programm_triggered();
};
#endif // MAINWINDOW_H
