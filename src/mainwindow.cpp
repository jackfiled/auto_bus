//
// Created by ricardo on 2022/6/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "header/moc_mainwindow.cpp"
#include "form/ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    central_widget = new CentralWidget;

    ui->setupUi(this);
    this->setCentralWidget(central_widget);
    SetMenuBarConnection();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete central_widget;
}

void MainWindow::SetMenuBarConnection()
{
    QObject::connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
}
