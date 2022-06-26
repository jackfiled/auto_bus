//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_MAIN_WINDOW_H
#define AUTO_BUS_GUI_MAIN_WINDOW_H

#include <QMainWindow>
#include "QFileDialog"
#include "QThread"

#include "centralwidget.h"
#include "busModel.h"


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
     * 打开配置文件的信号
     * @param file_name 配置文件的文件路径
     */
    void OpenConfigFileSignal(QString file_name);

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
    /**
     * 控制类
     */
    BusControllerModel *controller;

    QThread *worker_thread;

    /**
     * 设置菜单栏的相关连接
     */
    void SetMenuBarConnection();

    void SetControlConnection();
};
#endif //AUTO_BUS_GUI_MAIN_WINDOW_H
