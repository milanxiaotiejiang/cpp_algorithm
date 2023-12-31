//
// Created by io on 23-10-11.
//

#include <iostream>
#include <cstring>

#ifdef _DEBUG   //只在Debug（调试）模式下
#ifndef DEBUG_NEW
#define DEBUG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__) //重新定义new运算符
#define new DEBUG_NEW
#endif
#endif

//#include <boost/type_index.hpp>
using namespace std;
#pragma warning(disable : 4996)
//#pragma warning(disable : 6386)

#define MAX_LEN 250 //最大字符串长度（定长）

//采用定长数组存储结构
class MySString {
public:
    MySString()//构造函数
    {
        ch[0] = '\0'; //字符串结束标记，其实'\0'就是数字0，所以写成ch[0] = 0;也没问题
        length = 0; //字符串长度
    }

    //串赋值
    void StrAssign(const char *pcontent) {
        size_t iLen = strlen(pcontent);
        if (iLen >= MAX_LEN) //内容太长，容纳不下，字符串存储中要给字符串结束标记'\0'留出位置
            return;

        for (int i = 0; i < iLen; ++i) {
            ch[i] = pcontent[i];
        } //end for
        ch[iLen] = '\0'; //设置字符串结束标记，该标记不计入字符串长度中
        length = iLen; //记录字符串长度
    }

    //串拷贝（串复制）
    void StrCopy(const MySString &tmpstr) {
        for (int i = 0; i < tmpstr.length; ++i) {
            ch[i] = tmpstr.ch[i];
        } //end for
        length = tmpstr.length;
        ch[length] = '\0';
    }

    //判断空串
    bool IfStrEmpty() {
        if (ch[0] == '\0')
            return true;
        return false;
    }

    //串比较，比较其实就是逐个比较两个字符串中每个字符的ASCII码
    //结果大于返回1，等于返回0，小于返回-1
    int StrCmp(const MySString &tmpstr) {
        if (length == 0 && tmpstr.length == 0) //两个字符串都是空的，相等
            return 0;

        const char *p1 = ch;
        const char *p2 = tmpstr.ch;

        int result = 0;
        while (*p1 != '\0' && *p2 != '\0') {
            result = (*p1) - (*p2);
            if (result != 0) {
                if (result > 0)
                    return 1;
                else
                    return -1;
            }
            p1++;
            p2++;
        } //end while

        if (*p1 == '\0' && *p2 == '\0') //长度相同且内容相等
            return 0;

        //能走到下边流程的都是两个字符串一个长一个短，但长的和短的字符串的前面内容相同，比如字符串"ab"和"abc"
        if (*p1 == '\0')  //p1小，因为长度少
            return -1;

        //else if (*p2 == '\0')
        return 1;
    }

    //串连接
    bool StrCat(const MySString &tmpstr) {
        if (length + tmpstr.length >= MAX_LEN) //空间不够保存不下，这里直接返回false以通知开发者
            return false;

        int idx = 0;
        size_t i;
        for (i = length; i < (length + tmpstr.length); ++i) {
            ch[i] = tmpstr.ch[idx++];
        }
        ch[i] = '\0'; //字符串结束标记
        length += tmpstr.length;
        return true;
    }

    //获取串的一部分内容（求子串）
    void SubString(MySString &resultstr, int pos, int len) //求得的子串给到resultstr。pos：从该位置开始[注意位置从0开始计算]，截取len个字符
    {
        //注意pos位置从0开始计算
        if (pos < 0 || (pos + 1) > length || len <= 0)//pos位置要合法，len长度值要合法
            return;

        int icount = 0;
        while (true) {
            resultstr.ch[icount] = ch[pos + icount];
            icount++;
            if (icount == len) //截取够数量了
                break;
            if (ch[pos + icount] == '\0') //到主串末尾了，不够截取，截取多少算多少，直接跳出循环
                break;
        } //end while
        resultstr.length = icount;
        resultstr.ch[resultstr.length] = '\0';
        return;
    }

    //串插入
    //在当前串的pos位置（从0开始计算），插入子串substr
    void StrInsert(int pos, const MySString &substr) {
        if (pos < 0 || pos > length) //插入位置不合法
            return;

        if (length + substr.length >= MAX_LEN) //容纳不下插入的新内容，则直接返回
            return;

        //把原来的必须的内容向后挪动
        int i = (int) (length - 1); //i为int类型，这样就可以为负数，保证下面这个for循环可以正确结束
        for (; i >= pos; --i) {
            ch[i + substr.length] = ch[i];
        }
        //把子串插入进来
        for (size_t i = 0; i < substr.length; ++i) {
            ch[pos + i] = substr.ch[i];
        }
        length += substr.length;
        ch[length] = '\0';
        return;
    }

    //串删除
    //在当前串的pos位置（从0开始计算），删除len个字符
    void StrDelete(int pos, int len) {
        //注意pos位置从0开始计算
        if (pos < 0 || (pos + 1) > length || len <= 0)//pos位置要合法，len长度值要合法
            return;

        if (pos + len > length) {
            //要删除的字符太多，串中没那么多可删的字符
            len = int(length - pos);  //只能删除这么多
        }

        //把剩余的字符串搬位置（向左搬）
        for (int i = pos; i < length; ++i) {
            ch[i] = ch[i + len];
        } //end for

        length = length - len;
        ch[length] = '\0';
        return;
    }

    //串清空
    void StrClear() {
        ch[0] = '\0';
        length = 0;
        return;
    }

    //朴素模式匹配算法接口，返回子串中第一个字符在主串中的下标，如果没找到子串，则返回-1
    int StrIndex(const MySString &substr, int pos = 0) //默认从位置0开始匹配子串
    {
        if (length < substr.length) //主串还没子串长，那不可能找到
            return -1;

        int point1 = pos, point2 = 0;
        while (ch[point1] != '\0' && substr.ch[point2] != '\0') {
            if (ch[point1] == substr.ch[point2]) {
                //两个指针都向后走
                point1++;
                point2++;
            } else //两者不同
            {
                //两个指针都恢复到该恢复的位置
                point1 = point1 - point2 + 1;
                point2 = 0; //子串指针恢复到0，不管原来是多少
            }
        } //end while

        if (substr.ch[point2] == '\0') {
            //找到了子串
            return point1 - point2;
        }
        return -1;
    }

    //串替换，主串中遇到内容为substr1的子串，全部替换成substr2子串
    void StrReplace(const MySString &substr1, const MySString &substr2) {
        int idx = -1;
        int pos = 0;
        int addlength = int(substr2.length) - int(substr1.length);
        while (pos < length) {
            idx = StrIndex(substr1, pos);
            if (idx == -1)
                return; //不存在substr1这样的子串，无需替换直接返回

            //能否替换，取决于空间是否够
            if (addlength > 0) {
                //被替换成的子串更长，要判断保存空间是否够
                if (length + addlength >= MAX_LEN)
                    return; //空间不够，不能替换成新内容
            }

            StrDelete(idx, int(substr1.length));  //删除老子串
            StrInsert(idx, substr2); //插入新子串

            //位置应该向后走，跳过被替换的子串部分内容
            pos = idx + (int) (substr2.length);
        } //end while
        return;
    }

public:
    //显示字符串内容
    void DispContent() {
        cout << ch << endl;
    }

public:
    char ch[MAX_LEN]; //串内容。每个位置保存一个字符
    size_t length; //串实际长度，专门引入该变量保存，提高程序运行效率
};

int main() {

    //朴素模式匹配算法接口，返回子串中第一个字符在主串中的下标，如果没找到子串，则返回-1
    MySString mys10, mys11;
    mys10.StrAssign("abdecdefg");//主串
    mys11.StrAssign("def"); //子串
    cout << "StrIndex()结果为" << mys10.StrIndex(mys11) << endl;


    //串替换，主串中遇到内容为substr1的，全部替换成substr2
    MySString mys12, substr1, substr2;
    mys12.StrAssign("abcdeabcde");
    cout << "mys12替换前的结果为" << mys12.ch << endl;
    substr1.StrAssign("cd");
    substr2.StrAssign("mno");
    mys12.StrReplace(substr1, substr2);
    cout << "mys12替换后的结果为" << mys12.ch << endl;

    return 0;
}
