# Auto Bus GUI

北京邮电大学计算机学院2021级《计算导论与程序设计》实践大作业的GUI分支。

## 项目构建

### 构建环境

- 编译器`Visual Studio 2022 MSVC++ 14.3`
- Qt` 6.1.3`
- CMake `3.22`

### 构建

```bash
git clone git clone http://10.3.255.244:8801/2021211180/2021211180.git
git checkout -b gui origin/gui
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
```

再使用`Visual studio 2022`打开`build`文件夹下的解决方案文件，即可编译。

> 或者直接使用VS打开签出分支之后的项目文件夹，即可编译使用。
>
> 现代VS已经支持用`cmake`管理`C/C++`项目



