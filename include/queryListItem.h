//
// Created by ricardo on 2022/6/25.
//

#ifndef AUTO_BUS_GUI_QUERY_LIST_ITEM_H
#define AUTO_BUS_GUI_QUERY_LIST_ITEM_H
#include "QWidget"
#include "QObject"
#include "QLabel"
#include "QHBoxLayout"

class QueryListItem : public QWidget
{
    Q_OBJECT
public:
    explicit QueryListItem(const int &type, const int &node_id);

    void SetColumnName();

private:
    /**
     * 请求的类型
     */
    QLabel type_text;

    /**
     * 请求的目标站点
     */
    QLabel target_pos_text;

    /**
     * 水平排列布局
     */
    QHBoxLayout *layout;
};
#endif //AUTO_BUS_GUI_QUERY_LIST_ITEM_H
