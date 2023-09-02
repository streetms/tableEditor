#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QLibraryInfo>
#include "aboutprogram.h"
#include "app.h"
#include "settingwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    csvModel = new QStandardItemModel(this);
    ui->tableView->setModel(csvModel);
    createCsvModel();
    readSettings();
    connect(csvModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(changeItemTable(QStandardItem*)));

    changed = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QSettings* pst = App::theApp()->getSettings();
    pst->beginGroup("Settings");
    pst->setValue("mainFile",mainFile);

    if (changed){
        int res = yes_no_question(tr("you have not saved data. Do you want to save?"));
        if (res == QMessageBox::Yes){
            on_Save_triggered();
        }
    }
    pst->setValue("mainWindowGeometry",this->geometry());
    pst->endGroup();
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    }
}

int MainWindow::yes_no_question(const QString &text)
{
    QMessageBox quit(
        QMessageBox::Warning,
        "BH",
        text,
        QMessageBox::Yes | QMessageBox::No,
        this);
    quit.setButtonText(QMessageBox::Yes, tr("Yes"));
    quit.setButtonText(QMessageBox::No, tr("No"));
    quit.setModal(true);
    return quit.exec();
}

void MainWindow::createCsvModel()
{
    csvModel->setColumnCount(12);
    csvModel->setHorizontalHeaderLabels({"names","date_x","score","genre","overview","crew","orig_title","status","orig_lang","budget_x","revenue","country"});
    for (int i = 0; i < 12; i++){
//        ui->tableView->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }
    QSettings* pst = App::theApp()->getSettings();
    csvModel->setRowCount(pst->value("Settings/maxNumberOfLines").toInt());
}


void MainWindow::on_Open_triggered() {
    QString filename = QFileDialog::getOpenFileName(nullptr, tr("open file"), "", "*.csv",nullptr,QFileDialog::DontUseNativeDialog);
    Open(filename);
}

void MainWindow::Open(QString filename)
{
    if (not filename.isEmpty()) {
        changed = false;
        mainFile = filename;
        QFile file(filename);
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        QString firstLine = in.readLine();
        QStringList head;
        for (QString &item: firstLine.split(",")) {
            head.append(item);
        }
        csvModel->setRowCount(0);
        csvModel->setHorizontalHeaderLabels(head);
        while (!in.atEnd()) {
            QList<QStandardItem *> standardItemsList;
            bool is_text = false;
            QString text;
            for (auto &item: in.readLine().split(",")) {
                if (not item.isEmpty()) {
                    if (not is_text and item.front() != '\"' and item.back() != '\"') {
                        standardItemsList.append(new QStandardItem(item));
                    } else {
                        is_text = true;
                        text += item;
                        if (item.size() > 1) {
                            if (item.back() == '\"' and item[item.size() - 2] != '\"') {
                                standardItemsList.append(new QStandardItem(text));
                                text.clear();
                                is_text = false;
                            }
                        }
                    }
                } else {
                    standardItemsList.append(new QStandardItem(QString()));
                }

            }
            csvModel->insertRow(csvModel->rowCount(), standardItemsList);
        }
        file.close();
    }
    csvModel->setColumnCount(12);
    QSettings* pst =  App::theApp()->getSettings();
    int maxNumberOfRows = pst->value("Settings/maxNumberOfLines").toInt();
    if (csvModel->rowCount() < maxNumberOfRows){
        csvModel->setRowCount(maxNumberOfRows);
    } else{
        pst->setValue("Settings/maxNumberOfLines",csvModel->rowCount());
    }
}

void MainWindow::readSettings()
{
    QSettings* pst = App::theApp()->getSettings();
    pst->beginGroup("Settings");
    Open(pst->value("mainFile","").toString());
    if (not mainFile.isEmpty()){
        changed = false;
    }
    this->setGeometry(pst->value("mainWindowGeometry",this->geometry()).toRect());
    pst->endGroup();
}

void MainWindow::changeItemTable(QStandardItem* item)
{
    //(void)item;
    changed = true;
    this->setWindowTitle(tr("MainWindow")+"*");
}


void MainWindow::on_settings_triggered()
{
    SettingWindow w;
    w.setWindowTitle(tr("Settings"));
    w.exec();
    QSettings* pst = App::theApp()->getSettings();
    pst->beginGroup("Settings");
    int newRowCount = pst->value("maxNumberOfLines").toInt();

    csvModel->setRowCount(newRowCount);
    pst->endGroup();
}


void MainWindow::on_Exit_triggered()
{
    this->close();
}


void MainWindow::on_Save_triggered()
{
    if (not mainFile.isEmpty()){
        changed = false;
        this->setWindowTitle(tr("MainWindow"));
        QFile file(mainFile);

        file.open(QFile::WriteOnly | QFile::Text);
        QTextStream out (&file);
        out << "names,date_x,score,genre,overview,crew,orig_title,status,orig_lang,budget_x,revenue,country\n";

        for (int i = 0; i < csvModel->rowCount(); i++) {
            for (int j = 0; j < csvModel->columnCount(); j++) {
                auto item = csvModel->item(i,j);
                if (item != nullptr) {
                    out << item->text();
                    if (j != csvModel->columnCount()-1){
                        out << ",";
                    }
                }
            }
            out << "\n";
        }
        file.close();
    } else{
        on_Save_as_triggered();
    }
}


void MainWindow::on_Save_as_triggered()
{
    mainFile = QFileDialog::getSaveFileName(nullptr, tr("save file"),"","",nullptr,QFileDialog::DontUseNativeDialog);
    if (not mainFile.isEmpty()){
        on_Save_triggered();
    }
}


void MainWindow::on_Create_triggered()
{
    if (changed){
        int res = yes_no_question(tr("you have not saved data. Do you want to save?"));
        if (res == QMessageBox::Yes){
            on_Save_triggered();
        }
    }
    mainFile = "";
    csvModel->clear();
    createCsvModel();
    changed = false;
}



void MainWindow::on_About_programm_triggered()
{
    AboutProgram w;
    w.show();
    w.exec();
}

