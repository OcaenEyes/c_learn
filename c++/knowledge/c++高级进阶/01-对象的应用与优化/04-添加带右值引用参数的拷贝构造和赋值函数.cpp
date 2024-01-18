int main()
{
    /**
     * 左值： 有内存，有名字
     * 左值： 没名字(临时量)  或 没内存
     */
    int a = 10;
    int &b = a; // 左值引用
    // int &&c = a;  // 无法将左值绑定到右值引用上
    // int &c = 20;  // 无法将右值绑定到左值引用上

    /**
     * @brief  相当于
     *      int tmp=20;
     *      const int &c = tmp; // c不能修改临时量的值
     */
    const int &c = 20;

    /**
     * @brief 相当于
     *      int tmp=20;
     *      int &&d = tmp;  // d可以修改临时量的值
     */
    int &&d = 20; // 右值 绑定到右值引用上

    return 0;
}