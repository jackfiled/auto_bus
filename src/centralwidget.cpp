//
// Created by ricardo on 2022/6/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CentralWidget.h" resolved

#include "header/moc_centralwidget.cpp"
#include "form/ui_CentralWidget.h"


CentralWidget::CentralWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::CentralWidget)
{
    ui->setupUi(this);
}

CentralWidget::~CentralWidget()
{
    delete ui;
}
