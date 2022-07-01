//
// Created by ricardo on 2022/6/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "header/moc_mainwindow.cpp"
#include "form/ui_MainWindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    worker_thread = new QThread;
    tick_timer = new QTimer;
    bus_timer = new QTimer;
    controller = nullptr;

    central_widget = new CentralWidget(nullptr);

    ui->setupUi(this);
    this->setCentralWidget(central_widget);

    SetWidgetConnection();

    //开始多线程事件循环
    worker_thread->start();

    // 设置计时器只工作一次
    bus_timer->setSingleShot(true);
}

MainWindow::~MainWindow()
{
    controller->deleteLater();
    worker_thread->quit();

    delete ui;
    delete central_widget;
    delete worker_thread;
    delete tick_timer;
    delete bus_timer;
}

void MainWindow::SetWidgetConnection()
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

    // 连接停止公交车按钮
    QObject::connect(ui->actionStop_Bus, &QAction::triggered,
                     this, &MainWindow::StopBusClicked);

    // 开始全局计时器连接
    QObject::connect(this, &MainWindow::RunBusSignal,
                     this, &MainWindow::BeginTickTimerSlot);

    // 结束全局计时器连接
    QObject::connect(this, &MainWindow::StopBusSignal,
                     this, &MainWindow::EndTickTimerSlot);

    // 处理计时器tick连接
    QObject::connect(tick_timer, &QTimer::timeout,
                     this, &MainWindow::OneTickSlot);
}

void MainWindow::SetControlConnection()
{
    // 开始运行连接
    QObject::connect(this, &MainWindow::RunBusSignal,
                     controller, &BusStrategyBase::BusBeginSlot);

    QObject::connect(this, &MainWindow::StopBusSignal,
                     controller, &BusStrategyBase::BusEndSlot);

    // 每一tick连接
    QObject::connect(this, &MainWindow::BusTickSignal,
                     controller, &BusStrategyBase::OneTickSlot);

    QObject::connect(bus_timer, &QTimer::timeout,
                     controller, &BusStrategyBase::OnStopSlot);

    QObject::connect(controller, &BusStrategyBase::BusRunningSignal,
                     this, &MainWindow::BeginBusTimerSlot);
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
        QMessageBox::warning(this, "警告", "文件错误");
        return;
    }
    else
    {
        if(controller != nullptr)
        {
            controller->deleteLater();
        }

        controller = StrategyFactory::GetStrategy(file_name);
        // 开始多线程
        BeginThread();
        // 设置controller相关连接
        SetControlConnection();
        central_widget->SetController(controller);
        // 重设公交车的状态
        controller->bus_model->ResetBus(controller->rails_model->rails);
        // 设置策略的标签
        central_widget->SetStrategyLabel(controller->strategy);
    }
}

void MainWindow::RunBusClicked()
{
    if (controller == nullptr)
    {
        QMessageBox::warning(this, "警告", "未读取配置文件");
    }
    else
    {
        emit RunBusSignal();
    }
}

void MainWindow::StopBusClicked()
{
    central_widget->ResetOutput();
    emit StopBusSignal();
}

void MainWindow::BeginThread()
{
    if(controller != nullptr)
    {
        controller->moveToThread(worker_thread);
    }
}

void MainWindow::BeginTickTimerSlot()
{
    tick_timer->setInterval(Settings::tick);

    tick_timer->start();
}

void MainWindow::OneTickSlot()
{
    int time = bus_timer->remainingTime();

    emit BusTickSignal(time);
}

void MainWindow::EndTickTimerSlot()
{
    tick_timer->stop();
}

void MainWindow::BeginBusTimerSlot([[maybe_unused]] int direction, int duration)
{
    // 这里得多计上一段时间
    // 执行动画需要消耗时间
    bus_timer->start(duration + 20);
}