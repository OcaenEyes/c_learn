#include <iostream>
using namespace std;

// 100 块买100只鸡， 公鸡1只5块钱， 母鸡一只3块钱， 小鸡3只1块钱
int main()
{
    int gongji, muji, xiaoji;
    for (gongji = 0; gongji <= 20; gongji++)
    {
        /* code */
        for (muji = 0; muji <= 33; muji++)
        {
            /* code */
            for (xiaoji = 0; xiaoji <= 99; xiaoji++)
            {
                /* code */
                if (5 * gongji + 3 * muji + xiaoji / 3 == 100)
                {
                    if (gongji + muji + xiaoji == 100)
                    {
                        if (xiaoji % 3 == 0)
                        {
                            printf("公鸡：%d  母鸡：%d 小鸡：%d \n", gongji, muji, xiaoji);
                        }
                    }
                }
            }
        }
    }

    return 0;
}