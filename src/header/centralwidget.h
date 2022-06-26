//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_CENTRAL_WIDGET_H
#define AUTO_BUS_GUI_CENTRAL_WIDGET_H

#include <QWidget>
#include "QListWidgetItem"
#include "string"
#include "list"

#include "mainScene.h"
#include "queryListItem.h"

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
    /**
     * 处理添加一个请求的槽函数
     * @param query_type 请求的类型
     * @param node_id 请求指向的站点id
     */
    void AppendQueryItem(int query_type, int node_id);

    void DeleteQueryItem(int query_id);

private:
    /**
     * UI控件
     */
    Ui::CentralWidget *ui;

    /**
     * 画图的场景管理器
     */
    SceneManager *scene_manager;

    /**
     * 请求列表中的对象
     */
    std::list<QueryListItem *> query_items;

    /**
     * 初始化请求展示列表
     * 展示表头的说明文字
     */
    void SetupQueryList();

    /**
     * 清除展示对象占用的内存空间
     */
    void DeleteQueryList();
};


#endif //AUTO_BUS_GUI_CENTRAL_WIDGET_H
