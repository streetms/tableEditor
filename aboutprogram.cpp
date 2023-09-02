#include <cmath>
#include "aboutprogram.h"
#include "ui_aboutprogram.h"

AboutProgram::AboutProgram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutProgram)
{
    ui->setupUi(this);
}

AboutProgram::~AboutProgram()
{
    delete ui;
}

void AboutProgram::resizeEvent(QResizeEvent *event)
{
    QSize size = ui->logo->size();
    if (ui->logo->pixmap(Qt::ReturnByValue).isNull()){
        ui->logo->setPixmap(QPixmap(":/images/logo.png"));
    }
    if (event->oldSize() != QSize(-1,-1)){
    double scale_x = event->size().width() /double(event->oldSize().width());
    double scale_y = event->size().height()/double(event->oldSize().height());


    if (scale_x > 1){
        size.setWidth(ceil(size.width()*scale_x));
    } else{
        size.setWidth(floor(size.width()*scale_x));
    }
    if (scale_y > 1){
        size.setHeight(ceil(size.height()*scale_y));
    } else{
        size.setHeight(floor(size.height()*scale_y));
    }
    ui->logo->resize(size);
    }
//    ui->label->setText(QString::number(scale_x));
}
