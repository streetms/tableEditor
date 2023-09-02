#ifndef APP_H
#define APP_H

#include <QApplication>
#include <QSettings>
class App : public QApplication
{
    Q_OBJECT
public:
    App(int& argc, char** argv,const QString& strArgName,const QString& strAppName);
    ~App();
    static App *theApp();
    QSettings *getSettings();
    void setLanguage(const QString& data);
private:
    QTranslator* appTranslator;
    QTranslator* qtTranslator;
    QSettings* settings;
};

#endif // APP_H
