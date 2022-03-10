#include <iostream>

using namespace std;

namespace jj01
{
    
     union IP{
         struct{
             unsigned char a1;   //地址低位
             unsigned char a2;
             unsigned char a3;
             unsigned char a4;  //地址高位
         } ip;
         unsigned int num;
     };

     void test(){
         union IP p;
         char str[100] = {0};
         int arr[4];
         while(~scanf("%s",str)){
             sscanf(str, "%d.%d.%d.%d", arr, arr + 1, arr + 2, arr + 3);
             p.ip.a1 = arr[3];
             p.ip.a2 = arr[2];
             p.ip.a3 = arr[1];
             p.ip.a4 = arr[0];
             cout << p.num << endl;
         }
     }

    /**
     * @brief 
     * 大端：数字的低位存储在高地址处；
     * 小端：数字的低位存储在低地址处（一般是小端机）
     *          
     */
        //若返回1则是小端机，返回0则是大端机
        //int a = 1           |__地址低位__|____|____|__地址高位__|
        // 小端机存储方式           1         0    0        0   
        // 大端机存储方式           0         0    0        1  
     int is_little(){
         static int num = 1;
         return ((char *)(&num))[0];  //int 转为char*数组，取低位地址内的数据回1则是小端机，返回0则是大端机
     }

    /**
     * @brief 
     * 字节序 （大小端的问题，为了使数据在网络传输有统一的存放格式）
     * 主机字节序 <----->  网络字节序
     */

} // namespace jj01


int main(){
    //jj01::test();
    cout << jj01::is_little() << endl;
    return 0;
}