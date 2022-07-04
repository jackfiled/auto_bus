//
// Created by ricardo on 2022/6/10.
//

#ifndef AUTO_BUS_GUI_CENTRAL_WIDGET_H
#define AUTO_BUS_GUI_CENTRAL_WIDGET_H

#include <QWidget>
#include "QListWidgetItem"
#include "string"
#include "list"
#include "QMessageBox"
#include "QTextCursor"

#include "mainScene.h"
#include "queryListItem.h"
#include "BusStrategyBase.h"

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

    /**
     * 重新设置控制器
     * @param c 控制器指针
     */
    void SetController(BusStrategyBase *c);

    /**
     * 设置显示当前策略的标签
     * @param strategy 当前选择的策略
     */
    void SetStrategyLabel(int strategy);

    /**
     * 清除输出信息
     */
    void ResetOutput();

signals:
    /**
     * 添加一个请求的信号
     */
    void AppendQuerySignal(int type, int node);

public slots:
    /**
     * 处理添加一个请求的槽函数
     * @param query_type 请求的类型
     * @param node_id 请求指向的站点id
     */
    void AppendQueryItemSlot(int query_type, int node_id);

    /**
     * 处理删除一个请求的槽函数
     * @param query_type 请求的类型
     * @param node_id 请求的站点id
     */
    void DeleteQueryItemSlot(int query_type, int node_id);

    /**
     * 处理点击添加请求按钮的槽函数
     */
    void AddQueryButtonClicked();

    /**
     * 处理打印状态事件的槽函数
     * @param string 状态字符串
     */
    void PrintStateSlot(const QString& string);

    /**
     * 开始公交车动画的槽函数
     * 实际上就是将公交车移动到上一个或者下一个站点
     * @param direction 公交车前进的方向
     * @param duration 动画需要持续的时间
     */
    void BeginBusAnimationSlot(int direction, int duration);

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
     * 控制器
     */
    BusStrategyBase *controller = nullptr;

    /**
     * 请求列表中的对象
     */
    std::list<QueryListItem *> query_items;

    /**
     * 设置同控制器的连接
     */
    void SetControlConnection();

    /**
     * 设置同控件的连接
     */
    void SetWidgetConnection();

    /**
     * 初始化请求展示列表
     * 展示表头的说明文字
     */
    void SetupQueryList();

    /**
     * 清除展示对象占用的内存空间
     */
    void DeleteQueryList();

    /**
     * 设置站点选择下拉栏
     * @param 站点的个数
     */
    void SetRailsComboBox(int node_num);

    /**
     * 处理轨道重新生成的槽函数
     * 重绘轨道画面
     * 重新设置站点选择下拉栏
     * @param node_num
     */
    void SetRailsScene(int node_num, int node_distance);
};


#endif //AUTO_BUS_GUI_CENTRAL_WIDGET_H
