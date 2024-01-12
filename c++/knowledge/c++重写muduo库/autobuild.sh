#!/bin/bash

set -e

# 没有build目录则创建build目录
if [ ! -d `pwd`/build ];then
    mkdir `pwd`/build 
fi

rm -rf `pwd`/build/*

cd `pwd`/build &&
    cmake .. &&
    cmake --build .


# 回到项目跟目录
cd ..


# 把头文件拷贝到 指定目录， so库 拷贝到指定目录
if [ ! -d `pwd`/output/ocean_muduo/include ];then
    mkdir -p `pwd`/output/ocean_muduo/include
fi

# for header in `ls *.h`
# do
#     cp $header `pwd`/output/include/ocean_muduo
# done
cp -r `pwd`/include/.  `pwd`/output/ocean_muduo/include


if [ ! -d `pwd`/output/ocean_muduo/lib ];then
    mkdir -p `pwd`/output/ocean_muduo/lib
fi

cp `pwd`/build/lib/libocean_muduo.so  `pwd`/output/ocean_muduo/lib

# 刷新动态库缓存
# ldconfig
