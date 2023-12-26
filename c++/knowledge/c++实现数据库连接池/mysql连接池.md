
# mysql连接池

- 在高并发情况下，频繁的创建和销毁数据库连接，会大大降低系统的吞吐量。
  - 大量的TCP三次握手
  - mysql server认证
  - mysql server关闭连接回收资源
  - TCP四次挥手