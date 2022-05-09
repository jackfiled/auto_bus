# Auto Pilot Bus

## 项目简介

北京邮电大学计算机学院2021级《计算导论与程序设计》实践大作业项目仓库。

在指定的公交车行驶模型下，实现指定的算法以实现对于公交车的自动调度。

## 项目使用

### 项目结构

```
auto_pilot_bus
|
+-docs // 文档文件夹
|
+-include // 头文件文件夹
|
+-src // 源代码文件夹
|
+-main.c // 程序入口
+-CMakeLists.txt // CMake文件
+-.gitignore //git的忽略文件名录
+-README.md // 项目介绍文件
```

### 编译环境

- 编译器 `MinGW-W64 gcc 8.1.0`
- 编译工具 `cmake 3.23.1`

### 项目使用

处在校园网环境在

> 参考信息化中心的这篇[文章](https://nic.bupt.edu.cn/info/1016/1301.htm)安装VPN客户端

使用

```bash 
git clone http://10.3.255.244:8801/2021211180/2021211180.git
```

来下载仓库，在下载过程中可能提示输入账号和密码认证，账号即为你的学号，密码就是你登录`GitLab`时输入的密码。

下载完成后文件夹`2021211180`即为项目的文件夹。

使用

```bash
cd 20212111180
mkdir build # 创建编译的文件夹
cd build
cmake .. -G "MinGW Makefiles" # 在第一次生成之后就不必再使用"-G"参数指定编译类型
cmake --build .
```

在编译执行完成之后，`build`文件下的`bus.exe`即为编译产生的程序。
