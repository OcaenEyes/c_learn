/*
 * @Author: OCEAN.GZY
 * @Date: 2022-08-09 23:52:05
 * @LastEditors: OCEAN.GZY
 * @LastEditTime: 2022-08-10 00:40:39
 * @FilePath: /c++/practices/encryption_demo/src/aes_test.cpp
 * @Description: 注释信息
 */

#ifndef CRYPTO_UTIL_DEMO_H
#define CRYPTO_UTIL_DEMO_H

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <cryptopp/aes.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/default.h>
#include <cryptopp/filters.h>
#include <cryptopp/osrng.h>

using namespace CryptoPP;

// 密钥长度
enum AESKeyLength
{
    AES_KEY_LENGTH_16 = 16,
    AES_KEY_LENGTH_24 = 24,
    AES_KEY_LENGTH_32 = 32
};

class aes_test
{
private:
    /* data */
public:
    aes_test(/* args */);
    ~aes_test();
    static int encrypt4aes(const std::string &inData,
                           const std::string &strKey,
                           std::string &outData,
                           std::string &errMsg)
    {
        outData = "";
        errMsg = "";
        // 判断待加密的字符串 或者密钥是否为空
        if (inData.empty() || strKey.empty())
        {
            errMsg = "indata or key is empty!!";
            return -1;
        }

        unsigned int iKeyLen = strKey.length();
        // 判断密钥的长度是否符合要求
        if (iKeyLen != AES_KEY_LENGTH_16 && iKeyLen != AES_KEY_LENGTH_24 && iKeyLen != AES_KEY_LENGTH_32)
        {
            errMsg = "aes key invalid";
            return -2;
        }

        byte iv[AES::BLOCKSIZE];
        int iResult = 0;
        try
        {
            CBC_Mode<AES>::Encryption e;
            e.SetKeyWithIV((byte *)strKey.c_str(), iKeyLen, iv);
            StringSource ss(inData, true, new StreamTransformationFilter(e, new StringSink(outData)));
        }
        catch (const CryptoPP::Exception &e)
        {
            errMsg = "Encryptor throw exception!";
            iResult = -3;
        }

        return iResult;
    }

    static int decrypt4aes(const std::string &inData,
                           const std::string &strKey,
                           std::string &outData,
                           std::string &errMsg)
    {
        outData = "";
        errMsg = "";

        if (inData.empty() || strKey.empty())
        {
            errMsg = "indata or key is empty";
            return -1;
        }

        unsigned int iKeyLen = strKey.length();
        if (iKeyLen != AES_KEY_LENGTH_16 && iKeyLen != AES_KEY_LENGTH_24 && iKeyLen != AES_KEY_LENGTH_32)
        {
            errMsg = "aes key invalid";
            return -2;
        }

        byte iv[AES::BLOCKSIZE];
        int iResult = 0;

        try
        {
            CBC_Mode<AES>::Decryption d;
            d.SetKeyWithIV((byte *)strKey.c_str(), iKeyLen, iv);
            StringSource ss(inData, true, new StreamTransformationFilter(d, new StringSink(outData)));
        }
        catch (const CryptoPP::Exception &e)
        {
            errMsg = "Encryptor throw exception";
            iResult = -3;
        }

        return iResult;
    }
};

int main(int argc, char *argv[])
{
    std::string strCipher; // 待加密的字符串
    std::string strKey;    //用来加解密的密钥

    std::cout << "请输入一个字符串" << std::endl;
    std::cin >> strCipher;

    std::cout << "请输入一个密钥，必须是16、24或32个英文数字英文标点字符" << std::endl;

    std::cin >> strKey;

    std::string strResult;
    std::string strErrMsg;

    int iResult = aes_test::encrypt4aes(strCipher, strKey, strResult, strErrMsg);
    if (iResult)
    {
        std::cout << "aes_test::encrypt4aes failed ,errmsg: " << strErrMsg << std::endl;
        return -1;
    }

    std::string strPlainText;
    iResult = aes_test::decrypt4aes(strResult, strKey, strPlainText, strErrMsg);
    if (iResult)
    {
        std::cout << "aes_test::decrypt4aes failed ,errmsg: " << strErrMsg << std::endl;
        return -2;
    }

    std::cout << "plaintext: " << strPlainText << std::endl;
    std::cout << "strResult: " << strResult << std::endl;
}

#endif