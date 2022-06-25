//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_MAIN_WINDOW_H
#define AUTO_BUS_GUI_MAIN_WINDOW_H

#include <QMainWindow>
#include "QFileDialog"

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

public slots:
    /**
     * 点击打开配置文件按钮的槽函数
     */
    void ReadConfigFileButtonClicked();

private:
    Ui::MainWindow *ui;
    CentralWidget *central_widget;
    BusControllerModel *controller;

    void SetMenuBarConnection();
};
#endif //AUTO_BUS_GUI_MAIN_WINDOW_H
