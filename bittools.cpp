#include "bittools.h"
#include "ui_bittools.h"

BitTools::BitTools(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BitTools)
{
    ui->setupUi(this);
}

BitTools::~BitTools()
{
    delete ui;
}
