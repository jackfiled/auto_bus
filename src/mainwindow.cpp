//
// Created by ricardo on 2022/6/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "header/moc_mainwindow.cpp"
#include "form/ui_MainWindow.h"
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    central_widget = new CentralWidget;
    controller = new BusControllerModel;

    ui->setupUi(this);
    this->setCentralWidget(central_widget);
    SetMenuBarConnection();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete central_widget;
    delete controller;
}

void MainWindow::SetMenuBarConnection()
{
    QObject::connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(ui->actionRead_ConfigFile, &QAction::triggered, this, &MainWindow::ReadConfigFileButtonClicked);
}

void MainWindow::ReadConfigFileButtonClicked()
{
    QString file_name = QFileDialog::getOpenFileName(
            this,
            "打开配置文件",
            "C:/",
            "Config Files(*.dic)"
            );

    if(file_name.isEmpty())
    {
        qDebug() << "文件名为空";
    }
    else
    {
        qDebug() << file_name;
        emit OpenConfigFileSignal(file_name);
    }
}
