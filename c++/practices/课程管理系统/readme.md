<!--
 * @Author: OCEAN.GZY
 * @Date: 2022-08-12 22:41:31
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-12 22:46:25
 * @FilePath: /c++/practices/课程管理系统/readme.md
 * @Description: 注释信息
-->

# 需求分析：

项目功能需求可以拆分成下面两个模块：

- 命令输入及处理
- 课程存储及管理

提炼每个模块中的参与者：
- 命令管理对象
- 课程对象
- 课程管理对象

其中命令管理对象对命令进行管理。课程对象存储每个课程的信息，课程管理对象对课程列表进行维护和管理。

我们需要课程类，课程管理类，命令管理类三个类。如果命令对象包含的信息很复杂的话也可以单独设计成类，在本项目中命令仅仅是一个数字及相关的描述信息，为了便于查找我们只需要把命令定义在命令管理类中。

根据需求，课程类为基础类，表示基础课，子类分别为项目课，评估课。但我们的需求中并没有什么地方需要用到这两个子类的虚函数实现，所以这部分会作为扩展内容。


# 抽象与细化
根据上面的需求分析，设计所需的类：

1. 定义课程类Course及课程管理类CourseManager，命令处理类CmdManager
2. Course类成员包括：

课程ID（课程对象创建时自动生成）
课程名称

3. Course类成员函数至少包括：

构造函数（参数课程名称）
拷贝构造函数
返回和设置课程名称
获得课程ID的函数
打印信息函数（考虑重载 <<）
4. CourseManager类成员至少包括：

课程列表（可以思考下使用什么数据类型存储？）

5. CourseManager类成员函数至少包括：

构造函数（参数为课程对象vector）
获取课程数量函数
添加课程函数（参数为课程名称）
添加课程函数（参数为课程对象）
删除最新课程函数
删除课程函数（指定ID或指定课程名称）
打印课程列表
打印指定课程（指定ID或指定课程名称）
打印最长名称课程函数
6. CmdManager类成员至少包括：

命令列表（可以思考下使用什么数据类型存储？）
课程管理对象（用在需要调用课程管理的地方）

7. CmdManager类成员函数至少包括：

初始化函数：课程及命令信息初始化
打印帮助信息
命令处理函数

8. 实现中请注意:

哪些函数可以定义为const?
是否有类成员可以定义为静态或const?
哪些函数可以定义为友元？
哪些构造函数等于默认构造函数？
根据这些细化的思路，我们先创建必要的程序文件，每个类都会创建一个头文件和一个cpp文件，另外为了未来命令对象的扩展，我们先创建了一个Cmd.h文件定义所有支持的命令数字。

首先为要实现的程序命名为cmsys（Course Manager System缩写）:
```
# 在 /home/shiyanlou/ 目录下创建代码目录
cd ~
mkdir cmsys
cd cmsys

# 创建所需的文件
touch Course.h Course.cpp
touch CourseManager.h CourseManager.cpp
touch Cmd.h CmdManager.h CmdManager.cpp
touch main.cpp
touch Makefile
```
这就是我们这个项目所需要的所有文件：

1. Course.h 与 Course.cpp：定义课程类
2. CourseManager.h 与 CourseManager.cpp：定义课程管理类
3. Cmd.h，CmdManager.h，CmdManager.cpp：定义命令管理类
4. Makefile：实现自动化编译

其中 CourseManager 中需要包含一个 Course 容器，存储课程列表。CmdManager 中需要存储一个 CourseManager对象，以便于调用相应的接口对课程进行访问及处理。




http://labfile.oss.aliyuncs.com/courses/1052/cmsys.zip