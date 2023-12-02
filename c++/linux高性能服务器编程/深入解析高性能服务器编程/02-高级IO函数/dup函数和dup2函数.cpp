#include <unistd.h>

/// @brief 创建一个新的文件描述符，该新文件描述符和原有文件描述符file_descriptor指向相同的文件、管道、或网络连接
/// @param file_descriptor 
/// @return dup返回的文件描述符 总是取系统当前可用的最小整数值
int dup(int file_descriptor) {}

/// @brief 
/// @param file_deacriptor_one 
/// @param file_deacriptor_two 
/// @return 
int dup2(int file_deacriptor_one,int file_deacriptor_two) {}