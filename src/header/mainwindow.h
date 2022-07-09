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
#include "Settings.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

/**
 * 主窗口的策略控制类
 */
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
     * 停止运行公交车的信号
     */
    void StopBusSignal();

    /**
     * 时钟信号
     * @param remain_time bus_timer计时器剩余的时间
     */
    void BusTickSignal(int remain_time);

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
     * 处理点击停止公交车按钮的槽函数
     */
    void StopBusClicked();

    /**
     * 开始全局计时器的槽函数
     */
    void BeginTickTimerSlot();

    /**
     * 结束全局计时器的槽函数
     */
    void EndTickTimerSlot();

    /**
     * 每一tick的槽函数
     */
    void OneTickSlot();

    /**
     * 开始公交车行驶计时器的槽函数
     * @param direction 公交车前进的防线 此处不需要
     * @param duration 持续的时间
     */
    void BeginBusTimerSlot([[maybe_unused]] int direction, int duration);

private:

    /**
     * UI控件
     */
    Ui::MainWindow *ui;

    /**
     * 中间的显示框架
     */
    CentralWidget *central_widget;

    /**
     * 控制器工作的线程
     */
    QThread *worker_thread;

    /**
     * 控制器指针
     */
    BusStrategyBase *controller;

    /**
     * 时刻计时器
     * 每隔一个tick发出一个时钟信号
     */
    QTimer *tick_timer;

    /**
     * 公交车计时器
     */
    QTimer *bus_timer;

    /**
     * 设置菜单栏的相关连接
     */
    void SetWidgetConnection();

    /**
     * 设置控制器的相关连接
     */
    void SetControlConnection();

    /**
     * 开始多线程
     */
    void BeginThread();
};
#endif //AUTO_BUS_GUI_MAIN_WINDOW_H
