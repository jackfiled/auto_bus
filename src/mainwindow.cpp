//
// Created by ricardo on 2022/6/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "header/moc_mainwindow.cpp"
#include "form/ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    controller = new BusControllerModel;
    worker_thread = new QThread;

    // 开始多线程
    controller->moveToThread(worker_thread);
    worker_thread->start();

    central_widget = new CentralWidget(nullptr, controller);

    ui->setupUi(this);
    this->setCentralWidget(central_widget);
    SetMenuBarConnection();
    SetControlConnection();
}

MainWindow::~MainWindow()
{
    worker_thread->quit();

    delete ui;
    delete central_widget;
    delete controller;
    delete worker_thread;
}

void MainWindow::SetMenuBarConnection()
{
    // 连接退出按钮
    QObject::connect(ui->actionExit, SIGNAL(triggered()),
                     this, SLOT(close()));
    // 连接读取配置文件操作
    QObject::connect(ui->actionRead_ConfigFile, &QAction::triggered,
                     this, &MainWindow::ReadConfigFileButtonClicked);
    // 连接运行公交车按钮
    QObject::connect(ui->actionRun_Bus, &QAction::triggered,
                     this, &MainWindow::RunBusClicked);
    // 连接暂停公交车按钮
    QObject::connect(ui->actionPause_Bus, &QAction::triggered,
                     this, &MainWindow::PauseBusClicked);
    // 连接停止公交车按钮
    QObject::connect(ui->actionStop_Bus, &QAction::triggered,
                     this, &MainWindow::StopBusClicked);
}

void MainWindow::SetControlConnection()
{
    QObject::connect(this, &MainWindow::OpenConfigFileSignal,
                     controller, &BusControllerModel::ReadConfigFileSlot);
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

void MainWindow::RunBusClicked()
{
    emit RunBusSignal();
}

void MainWindow::PauseBusClicked()
{
    emit PauseBusSignal();
}

void MainWindow::StopBusClicked()
{
    emit StopBusSignal();
}