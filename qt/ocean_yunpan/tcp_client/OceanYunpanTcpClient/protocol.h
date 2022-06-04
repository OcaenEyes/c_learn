#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "stdlib.h"
#include "unistd.h"
#include "string.h"

typedef unsigned int uint;

struct PDU{
    uint caPDULen; //总的协议数据单元大小
    uint caMsgType; //消息类型
    char caData[64]; //文件名
    uint caMsgLen; // 实际消息长度
    int caMsg[];  // 实际消息
};

PDU *mkPDU(uint msgLen);

#endif // PROTOCOL_H
