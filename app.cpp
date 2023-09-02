#include "app.h"
#include <QTranslator>
#include <QDebug>
#include <QLibraryInfo>
App::App(int &argc, char **argv, const QString &strArgName, const QString &strAppName) :
    QApplication(argc,argv)
{
    settings = new QSettings(strArgName,strAppName);
    int lines = settings->value("Settings/maxNumberOfLines",0).toInt();
    if (lines == 0){
        settings->setValue("Settings/maxNumberOfLines",10000);
    }
    setOrganizationName(strArgName);
    setApplicationName(strAppName);
    appTranslator = new QTranslator;
    qtTranslator = new QTranslator;
    setLanguage(settings->value("Settings/Language","en").toString());
}

App::~App()
{
    delete settings;
    delete appTranslator;
    delete qtTranslator;
}

App *App::theApp()
{
    return (App*)qApp;
}

QSettings *App::getSettings()
{
    return settings;
}

void App::setLanguage(const QString &data)
{
    appTranslator->load(":/translations/BH_"+data);
    qtTranslator->load(":/translations/qtbase_"+data);
    installTranslator(appTranslator);
    installTranslator(qtTranslator);
}
