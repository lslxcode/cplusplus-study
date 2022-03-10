#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;


namespace jj01{
    class string
    {
        private:
            /* data */
            char *m_data;
            int m_size;
        public:

            // 默认构造函数
            string(const char *str = nullptr){
            if(str == nullptr){
                m_data = new char[1];
                m_data[0] = '\0';
            }else{
                m_size = strlen(str);
                m_data = new char[m_size + 1];
                strcpy(m_data, str);
            }
            }

            // 析构函数
            ~string(){
                delete[] m_data;
            }


            // 字符串赋值函数
            /*
            我们先用delete释放了实例m_data的内存，如果此时内存不足导致new char抛出异常，则m_data将是一个空指针，
            这样非常容易导致程序崩溃。违背了异常安全性原则。
            */
            string& operator=(const string &str){
                if(this == &str){//得分点：检查自赋值
                    return *this;
                }
                delete[] m_data; //得分点：释放原有的内存资源
                m_size = strlen(str.m_data);
                m_data = new char[m_size + 1];
                strcpy(m_data, str.m_data);
                return *this;   //得分点：返回本对象的引用
            }

            // 拷贝构造函数
            string(const string &str){// 得分点：输入参数为const型
                m_size = str.m_size;
                m_data = new char[m_size + 1]; //加分点：对m_data加NULL 判断
                strcpy(m_data, str.m_data);
            }
    };
}


namespace jj02{
    //拼接char*
    char *strcat(char *dest, const char *src)
    {
        char *ret = dest;
        assert(dest != NULL);
        assert(src != NULL);
        while (*dest)
        {
            dest++;
        }
        while ((*dest++ = *src++));
        return ret;
    }

    //拷贝char*
        char * strcap(char *str1,char *str2){
            char *res = str1;
            int len = strlen(str2);
            res[len + 1] = '\0';
            while(len){
                *str1++ = *str2++;
                len--;
            }

            return res;
        }
}


int main(){

    return 0;
}