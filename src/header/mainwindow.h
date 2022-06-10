//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_MAINWINDOW_H
#define AUTO_BUS_GUI_MAINWINDOW_H

#include <QMainWindow>
#include "centralwidget.h"


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

private:
    Ui::MainWindow *ui;
    CentralWidget *central_widget;

    void SetMenuBarConnection();
};


#endif //AUTO_BUS_GUI_MAINWINDOW_H
