//
// Created by ricardo on 2022/6/25.
//

#include "moc_queryListItem.cpp"

QueryListItem::QueryListItem(const int &type, const int &node_id) : QWidget()
{
    QFont font("Microsoft YaHei", 10, 75);
    layout = new QHBoxLayout(this);

    layout->addWidget(&type_text);
    layout->addWidget(&target_pos_text);
    layout->setContentsMargins(0, 0, 0, 0);

    this->setFixedHeight(20);

    // 设置文本
    type_text.setText(QString::number(type));
    target_pos_text.setText(QString::number(node_id));
    type_text.setFont(font);
    target_pos_text.setFont(font);

    type_text.resize(30, 20);
    target_pos_text.resize(30, 20);
}

void QueryListItem::SetColumnName()
{
    type_text.setText(QString("请求类型"));
    target_pos_text.setText(QString("目标站点"));
}
