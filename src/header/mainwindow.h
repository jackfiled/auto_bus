//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_MAIN_WINDOW_H
#define AUTO_BUS_GUI_MAIN_WINDOW_H

#include <QMainWindow>
#include "QFileDialog"
#include "QThread"
#include "QMessageBox"

#include "centralwidget.h"
#include "BusStrategyBase.h"
#include "StrategyFactory.h"


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

signals:

    /**
     * 开始运行公交车的信号
     */
    void RunBusSignal();

    /**
     * 暂停运行公交车的信号
     */
    void PauseBusSignal();

    /**
     * 停止运行公交车的信号
     */
    void StopBusSignal();

public slots:
    /**
     * 点击打开配置文件按钮的槽函数
     */
    void ReadConfigFileButtonClicked();

    /**
     * 处理点击运行公交车按钮的槽函数
     */
    void RunBusClicked();

    /**
     * 处理点击暂停公交车按钮的槽函数
     */
    void PauseBusClicked();

    /**
     * 处理点击停止公交车按钮的槽函数
     */
    void StopBusClicked();

private:
    /**
     * UI控件
     */
    Ui::MainWindow *ui;
    /**
     * 中间的显示框架
     */
    CentralWidget *central_widget;

    QThread *worker_thread;

    BusStrategyBase *controller;

    /**
     * 设置菜单栏的相关连接
     */
    void SetMenuBarConnection();

    /**
     * 设置控制器的相关连接
     */
    void SetControlConnection();

    void BeginThread();
};
#endif //AUTO_BUS_GUI_MAIN_WINDOW_H
