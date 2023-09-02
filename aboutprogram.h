#ifndef ABOUTPROGRAM_H
#define ABOUTPROGRAM_H

#include <QWidget>
#include <QDialog>
#include <QResizeEvent>
namespace Ui {
class AboutProgram;
}

class AboutProgram : public QDialog
{
    Q_OBJECT

public:
    explicit AboutProgram(QWidget *parent = nullptr);
    ~AboutProgram();
    void resizeEvent(QResizeEvent* event) override;
    QSize startSize;
private:
    Ui::AboutProgram *ui;
};

#endif // ABOUTPROGRAM_H
