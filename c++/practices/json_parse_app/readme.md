<!--
 * @Author: OCEAN.GZY
 * @Date: 2022-08-07 13:48:44
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-07 13:48:44
 * @FilePath: /c++/practices/json_parse_app/readme.md
 * @Description: 注释信息
-->
使用 stack 来存储 json 对象的深度，这个深度被用来控制打印输出 json 时的格式：比如标点符号；缩进对齐；换行。使得输出的 json 美观，工整，易于阅读。

栈是一种容器适配器，专门设计用于在 LIFO（后进先出），其中元素仅从容器的一端插入和提取。底层容器可以是任何标准容器类模板或一些其他特别设计的容器类。 容器应支持以下操作：

empty 测试容器是否为空
size 返回大小
top 返回栈顶元素
push 插入元素
emplace 构造和插入元素
pop 删除顶部元素
swap 交换内容