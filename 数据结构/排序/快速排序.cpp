#include <iostream>
#include <vector>
//#include <pair>

/*
    a. 不改进的快速排序 
            i. 把数组范围中的最后一个数作为划分值，然后把数组通过荷兰国旗问题分成三个部分：
                左侧<划分值、中间==划分值、右侧>划分值
            ii. 对左侧范围和右侧范围，递归执行 
        分析
            i. 划分值越靠近两侧，复杂度越高；划分值越靠近中间，复杂度越低 
            ii. 可以轻而易举的举出最差的例子，所以不改进的快速排序时间复杂度为O(N^2) 
    b. 随机快速排序（改进的快速排序）
        i. 1）在数组范围中，等概率随机选一个数作为划分值，然后把数组通过荷兰国旗问题分 成三个部分： 左侧划分值 
        ii. 2）对左侧范围和右侧范围，递归执行 
    3）时间复杂度为O(N*logN)
*/
using namespace std;

pair<int,int> partition(vector<int> &nums, int l, int r){
    int less = l - 1;
    int more = r;
    while (l<more)
    {
        if(nums[l]<nums[r]){
            swap(nums[++less], nums[l++]);
        }else if(nums[l]>nums[r]){
            swap(nums[--more], nums[l]);
        }else{
            l++;
        }
    }
    swap(nums[more], nums[r]);
    return {less + 1, more};
}


void quickSort(vector<int> &nums, int l, int r){
    if(l>=r){
        return;
    }
    int index = rand() % (r - l + 1) + l;
    swap(nums[index], nums[r]);
    auto p = partition(nums, l, r);
    quickSort(nums, l, p.first - 1);
    quickSort(nums, p.second + 1, r);
}

int main(){
    srand((unsigned)time(NULL));
    vector<int> arr = {9,88,88,88,4,54,15,54,848};
    quickSort(arr, 0, arr.size() - 1);
    for(auto &x:arr){
        cout << x << " ";
    }
    return 0;
}