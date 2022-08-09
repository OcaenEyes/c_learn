<!--
 * @Author: OCEAN.GZY
 * @Date: 2022-08-09 22:58:30
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-10 00:04:09
 * @FilePath: /c++/practices/encryption_demo/readme.md
 * @Description: 注释信息
-->
### 加密的类型介绍
根据密钥类型不同将现代密码技术分为两类： 对称加密算法（秘密钥匙加密）和非对称加密算法（公开密钥加密）。

对称钥匙加密系统是加密和解密均采用同一把秘密钥匙，而且通信双方都必须获得这把钥匙，并保持钥匙的隐秘。 非对称密钥加密系统采用的加密钥匙（公钥）和解密钥匙（私钥）是不同的。

对称加密算法：
1. DES（Data Encryption Standard）：数据加密标准，速度较快，适用于加密大量数据的场合。
2. 3DES（Triple DES）：是基于DES，对一块数据用三个不同的密钥进行三次加密，强度更高
3. AES（Advanced EncryptionStandard）：高级加密标准，是下一代的加密算法标准，速度快，安全级别高

非对称算法：
1. RSA：由 RSA 公司发明，是一个支持变长密钥的公共密钥算法，需要加密的文件块的长度也是可变的。
2. DSA（Digital Signature Algorithm）：数字签名算法，是一种标准的 DSS（数字签名标准）
3. ECC（Elliptic Curves Cryptography）：椭圆曲线密码编码学。

散列算法：
1. MD5（Message Digest Algorithm 5）：是RSA数据安全公司开发的一种单向散列算法。
2. SHA（Secure Hash Algorithm）：可以对任意长度的数据运算生成一个160位的数值。

著名的密码学算法库还有 OpenSSL 。OpenSSL 为网络通信提供安全及数据完整性的一种安全协议 ，囊括了主要的密码算法、常用的密钥和证书封装管理功能以及 SSL 协议，并提供了丰富的应用程序供测试或其它目的使用。通过比较 Crypto++ 和 Openssl，我们可以发现 Crypto++ 支持的算法比 Openssl 多。


### MD5摘要算法

MD5 的全称是 Message-Digest Algorithm 5，在90年代初由 MIT 的计算机科学实验室和 RSA Data Security Inc 发明，由 MD2/MD3/MD4 发展而来的。MD5 的实际应用是对一段 Message (字节串)产生 fingerprint (指纹)，可以防止被“篡改”，因此通常用于密码的加密存储，数字签名，文件完整性验证等。 在很多操作系统中，用户的密码是以 MD5 值（或类似的其它算法）的方式保存的，用户 Login 的时候，系统是把用户输入的密码计算成 MD5 值， 然后再去和系统中保存的MD5值进行比较，来验证该用户的合法性。 使用 crypto++ 库生成 MD5 值很简单，理解这个函数即可：

以下是我们用到函数的原型：
```
StringSource (const std::string &string,
              bool pumpAll,
              BufferedTransformation *attachment=NU
```

stringsource 是一个字符数组和字符串的源，源（Source）就是指数据的来源。
Crypto++ 提供以下常用的源：
- File
- Random Number
- Socket
- String
- Windows Pipe

关于它的更多细节，请查阅官方手册
打开终端输入：
```
cd /home/shiyanlou
vim md5.cpp
```

```
int main()
{
  std::string digest, inData;
  std::cin >> inData;
  Weak1::MD5 md5;   //创建 md5 对象
  StringSource(inData, true, new HashFilter(md5, new HexEncoder(new StringSink(digest))));    //转换的关键

  std::cout<< digest ;
}
#endif//_CRYPTO_UTIL_H_
```
这里提供了完整的代码：
```
wget http://labfile.oss.aliyuncs.com/courses/654/md5.cpp
```

```
// 编译生成程序
g++ -o md5 md5.cpp -lcryptopp
./md5
```


### 实现AES加密解密
AES 采用的是对称加密，在密码学中又称 Rijndael 加密法，是美国联邦政府采用的一种区块加密标准。这个标准用来替代原先的 DES ，已经被多方分析且广为全世界所使用。 AES 设计有三个密钥长度:128,192,256 比特, 相对而言, AES 的128比特密钥比 DES 的56比特密钥强10^21倍 。 AES有五种加密模式:

1. 电码本模式（ECB模式）： 这种模式是将整个明文分成若干段相同的小段，然后对每一小段进行加密。
2. 密码分组链接模式（CBC模式）：这种模式是先将明文切分成若干小段，然后每一小段与初始块或者上一段的密文段进行异或运算后，再与密钥进行加密。
3. 计算器模式（CTR模式）：计算器模式不常见，在CTR模式中， 有一个自增的算子，这个算子用密钥加密之后的输出和明文异或的结果得到密文，相当于一次一密。
4. 密码反馈模式（CFB模式）：与ECB和CBC模式只能够加密块数据不同，CFB能够将块密文（Block Cipher）转换为流密文（Stream Cipher）。
5. 输出反馈模式（OFB模式）：OFB是先用块加密器生成密钥流（Keystream），然后再将密钥流与明文流异或得到密文流，解密是先用块加密器生成密钥流， 再将密钥流与密文流异或得到明文，由于异或操作的对称性所以加密和解密的流程是完全一样的。

本实验采用 CBC 模式。在设计类 CCryptoUtil 中，分为两个模块， encrypt4aes 加密， decrypt4aes 解密。


http://labfile.oss.aliyuncs.com/courses/654/md5.cpp


http://labfile.oss.aliyuncs.com/courses/654/aes.cpp