//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_CENTRAL_WIDGET_H
#define AUTO_BUS_GUI_CENTRAL_WIDGET_H

#include <QWidget>
#include "string"
#include "mainScene.h"

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

public slots:


private:
    Ui::CentralWidget *ui;
    SceneManager *scene_manager;
};


#endif //AUTO_BUS_GUI_CENTRAL_WIDGET_H
