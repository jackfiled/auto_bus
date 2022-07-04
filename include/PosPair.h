//
// Created by ricardo on 2022/6/28.
//

#ifndef AUTO_BUS_GUI_POSPAIR_H
#define AUTO_BUS_GUI_POSPAIR_H

/**
 * 储存每个站点位置的类
 */
class PosPair{

public:
    /**
     * 设定的轨道开始坐标x
     */
    static const int stop_begin_x = 100;

    /**
     * 设定的轨道开始坐标y
     */
    static const int stop_begin_y = 80;

    /**
     * 轨道的宽度
     */
    static const int stop_rail_width = 300;

    /**
     * 轨道的高度
     */
    static const int stop_rail_height = 200;

    /*
     * 站点位置的x坐标
     */
    int pos_x;
    /**
     * 站点位置的y坐标
     */
    int pos_y;

    PosPair();

    /**
     * 获取两个站点之间的距离
     * @param stop_number 站点的数量
     * @return 站点之间的距离
     */
    static int GetStopSpaceLength(int stop_number) ;

    /**
     * 加上一定的距离
     * @param length 需要加上的距离
     */
    void AddLength(int length);

    /**
     * 获得该站点公交车停车的位置x坐标
     * @return
     */
    int GetBusPosX() const;

    /**
     * 获得该站点公交车停车位置的y坐标
     * @return
     */
    int GetBusPosY() const;

private:

    /**
     * 公交车到站点的距离
     */
    const int stop_bus_distance = 30;

    int distance = 0;
};

#endif //AUTO_BUS_GUI_POSPAIR_H
