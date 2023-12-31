//
// Created by io on 23-10-11.
//

#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <assert.h>

using namespace std;
#pragma warning(disable : 4996)

//分割函数：一趟快速排序的实现函数。该函数是快速排序算法实现的核心函数，返回枢轴位置下标
template<typename T>
int Partition(T myarray[], int low, int high) //low：低位置。high：高位置
{
    static int icount = 0;
    icount++;
    cout << "【当前Partition调用的次数是： " << icount << "】" << endl;

    //选取枢轴，就用最低位置指向的元素（首元素）作为枢轴即可
    T pivot = myarray[low]; //把枢轴保存起来
    while (low < high) {
        //先从高位置来
        while (low < high && myarray[high] >= pivot)
            high--;

        if (low == high) //如果原始集合已经是从小到大排序，这个条件就会成立
            break;

        if (low < high)
            myarray[low] = myarray[high];

        //再从低位来
        while (low < high && myarray[low] < pivot)
            low++;

        if (low == high) //如果原始集合已经是从大到小排序，这个条件就会成立
            break;

        if (low < high)
            myarray[high] = myarray[low];

    } //end while (low < high)

    myarray[low] = pivot; //此时low与high相等
    return low;
}

template<typename T>
void QuickSort(T myarray[], int low, int high, int length, int lvl = 1) //lvl用于统计递归调用深度
{
    //断言low值一定是小于high值的
    assert(low < high); //记得#include <assert.h>

    //调用者要保证low < high
    cout << "【当前QuickSort递归调用深度是： " << lvl << "层】";

    int pivotpos = Partition(myarray, low, high);  //分割函数
    //输出中间结果看看：
    cout << "low = " << low << ";high = " << high << ";枢轴位置 = " << pivotpos << "。本趟快排结果为： ";
    for (int i = 0; i < length; ++i)
        cout << myarray[i] << "  ";
    cout << endl;

    if (low < (pivotpos - 1))
        QuickSort(myarray, low, pivotpos - 1, length, lvl + 1);//枢轴左侧子表做快速排序，即继续分割

    if ((pivotpos + 1) < high)
        QuickSort(myarray, pivotpos + 1, high, length, lvl + 1);//枢轴右侧子表做快速排序，即继续分割

    return;
}

//快速排序（从小到大）
template<typename T>
void QuickSort(T myarray[], int length) {
    if (length <= 1) //不超过1个元素的数组，没必要排序
        return;

    int low = 0;  //低位置
    int high = length - 1; //高位置

    //调用重载函数
    QuickSort(myarray, low, high, length); //传递length值是为了显示中间的输出结果方便
}

int main() {

    int arr[] = {16, 1, 45, 23, 99, 2, 18, 67, 42, 10};
    int length = sizeof(arr) / sizeof(arr[0]);   //数组中元素个数
    QuickSort(arr, length);//对数组元素进行快速排序
    cout << "快速排序结果为：";
    for (int i = 0; i < length; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl; //换行

    return 0;
}