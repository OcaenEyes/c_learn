<!--
 * @Author: OCEAN.GZY
 * @Date: 2022-08-12 00:29:51
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-12 01:11:55
 * @FilePath: /c++/practices/rtti_demo/readme.md
 * @Description: 注释信息
-->
RTTI 是运行时类型识别的英文缩写，C++ 本身提供了运行时类型识别的运算符 dynamic_cast 和 typeid，然而 dynamic_cast 的效率其实并不理想，需要牺牲一定性能。本项目将手动实现一个高性能 RTTI 库。

项目涉及的知识点
运行时类型识别 dynamic_cast, typeid
显式类型转换 static_cast, const_cast, reinterpret_cast

http://labfile.oss.aliyuncs.com/courses/658/rttilib.zip