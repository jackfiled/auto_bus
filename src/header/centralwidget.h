//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_CENTRALWIDGET_H
#define AUTO_BUS_GUI_CENTRALWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui
{
    class CentralWidget;
}
QT_END_NAMESPACE

class CentralWidget : public QWidget
{
Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = nullptr);

    ~CentralWidget() override;

private:
    Ui::CentralWidget *ui;
};


#endif //AUTO_BUS_GUI_CENTRALWIDGET_H
