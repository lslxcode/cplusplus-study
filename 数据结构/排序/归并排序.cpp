#include <iostream>
#include <vector>

/*
    a. 整体就是一个简单递归，左边排好序、右边排好序、让其整体有序 
    b. 让其整体有序的过程里用了排外序方法
    c. 利用master公式来求解时间复杂度
    d.  归并排序的实质 时间复杂度O(N*logN)，额外空间复杂度O(N)
*/
using namespace std;
void merge(vector<int> &nums, int l, int r, int m);

void mergeSort(vector<int> &nums, int l, int r){
    if(l>=r){
        return;
    }
    int mid = (l + r) >> 1;
    mergeSort(nums, l, mid);
    mergeSort(nums, mid + 1, r);
    merge(nums, l, r, mid);
}

void merge(vector<int> &nums, int l,int r,int m){
    int p1 = l, p2 = m+1;
    vector<int> helper(r - l + 1);
    int index = 0;
    while (p1<=m && p2<=r){
        //能保证稳定性
        helper[index++] = nums[p1] <= nums[p2] ? nums[p1++] : nums[p2++];

        //helper[index++] = nums[p1] < nums[p2] ? nums[p1++] : nums[p2++];
        //无法保证稳定性，但是可以求逆序对
    }

    while(p1<=m || p2<=r){
        helper[index++] = p1 <= m ? nums[p1++] : nums[p2++];
    }

    for (int i = 0; i < (int)helper.size();++i){
        nums[l + i] = helper[i];
    }
}

int main(){
    vector<int> arr = {9,88,88,88,4,54,15,54,848};
    mergeSort(arr, 0, arr.size() - 1);
    for(auto &x:arr){
        cout << x << " ";
    }
    return 0;
}