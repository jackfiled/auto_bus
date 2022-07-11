# Auto Pilot Bus

北京邮电大学计算机学院2021级《计算导论与程序设计》实践大作业项目仓库，本次课程的题目为“自动公交车调度”。

> `master`分支为控制台输出的核心版
>
> `gui`分支为采用`Qt`实现的动画版

### 特点

- 采用`cmake`进行项目管理，编译轻松快捷。
- 程序模块化设计，注释详尽，代码可读性高。
- 含有`GTest`单元测试模块和自行设计的全局测试模块，还提供了不少测试用例。
- 完全使用`markdown`撰写的文档

## 项目使用

### 结构

```
auto_pilot_bus
|
+-all_test //本地全局测试文件夹
|
+-docs // 文档文件夹
|
+-include // 头文件文件夹
|
+-src // 源代码文件夹
|
+-test //单元测试文件夹
|
+-main.c // 程序入口
+-convert.py //产生测试集的Python脚本
+-main.py //将C代码合并到同一个文件的Python脚本
+-CMakeLists.txt // CMake文件
+-.gitignore //git的忽略文件名录
+-README.md // 项目介绍文件
```

### 编译环境

- 编译工具 `cmake 3.23.1`
- 理论上不依赖特定的编译器

> `MinGW64 GCC`和`GNU GCC`编译器经过测试可正常编译。

### 使用

使用

```bash 
git clone https://github.com/jackfiled/auto_bus.git
```

下载完成后文件夹`auto_bus`即为项目的文件夹。

使用

> 可自行指定使用的编译器

```bash
cd auto_bus
mkdir build # 创建编译的文件夹
cd build
cmake .. -G "MinGW Makefiles" # 在第一次生成之后就不必再使用"-G"参数指定编译类型
cmake --build .
```

在编译执行完成之后，`build`文件下的`bus.exe`即为编译产生的程序。

程序具体支持的指令可以查看文档中的说明文档。

### 测试

#### 单元测试

在编译之后，`build/test`文件夹内即为`google test`框架生成的单元测试。

#### 全局测试

在编译之后，`build/all_test`内的`bus_all_test.exe`就是全局本地测试程序。

运行这个程序，根据程序的提示选择适当的测试集，程序会自动读取选定的测试集中的配置文件和输入文件，并且将程序的输出和测试集中的输出文件进行对比，输出比对的结果。

程序现有的测试集存储在`all_test/test_cases`下面，目前已有18个测试集，对应测试集采用的调度策略可以查看测试集中的配置文件。

## 支持

如果你在学习/使用的过程中遇到的任何问题，或者有任何的意见与建议，可以在仓库中提交`Issue`和`Pull Request`同我们讨论。

当然，也可以给我发电子邮件。

## 贡献者

[jackfiled](https://github.com/jackfiled)

[nvhaizi1](https://github.com/nvhaizi1)

[Yerolling](https://github.com/Yerolling)

## 鸣谢

[GoogleTest](https://github.com/google/googletest)

