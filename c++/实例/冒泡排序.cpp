#include <iostream>
using namespace std;

void bubbleSort(int * arr, int len){
    cout << arr << "\n";
    cout << *arr << "\n";

    for (int i =0; i < len-1; i++)
    {
        /* code */
        cout << "arr[i] first print" << arr[i] << "\n";
        for (int j =0; j<len-1; j++){
            // cout  << "arr[j] first print" << arr[j] << "\n";
            // cout  << "arr[j+1] first print" << arr[j+1] << "\n";
            if (arr[j] > arr[j+1]){
                
                int temp = arr[j];
                // cout  << "arr[j] second print" << arr[j] << "\n";
                arr[j] = arr[j+1];
                // cout  << "arr[j] third print" << arr[j] << "\n";
                arr[j+1] = temp;
                // cout  << "arr[j+1] second print" << arr[j+1] << "\n";
            }
        }
    }
    
}


void parintArr(int *arr, int len){
    for (int i=0; i <len; i++){
        cout << arr[i] << "\n";
    }

}

int main(){

    // 创建数组
    int arr[10] = {4,3,6,9,1,2,10,8,7,5};

    // 数组长度
    int len = sizeof(arr) / sizeof(arr[0]);
    cout << arr << "\n";

    // 创建函数,实现冒泡排序
    bubbleSort(arr,len);

    // 打印数组
    parintArr(arr,len);
    return 0;
}