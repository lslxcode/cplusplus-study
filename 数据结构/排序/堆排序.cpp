#include <iostream>
#include <vector>

/*
	堆排序是利用堆这种数据结构而设计的一种排序算法，堆排序是一种选择排序，它的最坏，最好，平均时间复杂度均为O(nlogn)，它也是不稳定排序。
	
	完全二叉树：
	设二叉树的深度为h，除第 h 层外，其它各层 (1～h-1) 的结点数都达到最大个数，
	第 h 层所有的结点都连续集中在最左边
	
	满二叉树:
	一棵深度为k，且有 2^{k+1}-1 个节点的二叉树，称为满二叉树（Full Binary Tree）。 这种树的特点是每一层上的节点数都是最大节点数。
	
	完全二叉树性质：
		a. 结点i的子节点为  2i+1 和 2i+2
		b. 结点i的父节点为  (i-1)/2

*/
using namespace std;

/*
    heapinsert过程：
        首先一个数插入到大根堆的底部，然后跟自己的父节点（结点i的父节点为  (i-1)/2）比较，
        如果比父节点大，则和父节点交换，再和自己的父节点比较，直到到达头结点或者比父节点小为止;
*/
void heapInsert(vector<int> &nums,int index){
    while(nums[index] > nums[(index-1)/2]){
        swap(nums[index], nums[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

/*
	4. 移除最大值的过程：
		a. 先把堆顶取出
		b. 将堆顶和最后一个元素交换
		c. 堆整体元素减一
		d. 对堆顶做一次heapify
*/
void heapify(vector<int> &arr, int index, int heapsize){
    int left = 2 * index + 1;
    while (left < heapsize) {
        //下方还有孩子的时候
        //两个孩子中，谁的值大，把小标给largest
        //left + 1 : 右孩子的下标
        int largest = left + 1 < heapsize && arr[left + 1] > arr[left] ? left + 1 : left;
        //父和较大孩子之间，谁的值大，把小标给largest
        largest = arr[largest] > arr[index] ? largest : index;
        if (largest == index) { //如果下标还是父节点，说明父节点已经是最大值，不用继续heapify了
            break;
        }
        swap(arr[largest], arr[index]);
        index = largest;     //index 设置为当前的值
        left = index * 2 + 1; //下一次循环左孩子
    }
}

/**
 * 	5. 如果更改堆的某个位置的值，若修改的值比原来的值大，则往上进行一次heapinsert过程即可重新变为大根堆，如果比原来的值小，则往下进行一次heapify过程即可重新变为大根堆
	如果不确定值的大小，则先往上进行一次heapinsert，再往下进行一次heapify
	6. heapinsert的时间复杂度O(logN)
    移除最大值的时间复杂度O（logN）
 */

/*
	7. 堆排序O(N*logN)
		将待排序序列构造成一个大顶堆，此时，整个序列的最大值就是堆顶的根节点。将其与末尾元素进行交换，此时末尾就为最大值。然后将剩余n-1个元素重新构造成一个堆，这样会得到n个元素的次小值。如此反复执行，便能得到一个有序序列了
*/
    void heapSort(vector<int> &nums) {
        if (nums.size() < 2) {
            return;
        }
        for (int i = 0; i < nums.size(); i++) { // O(N)
            heapInsert(nums, i);// O(logN)
        }
        int size = nums.size();
        swap(nums[0], nums[--size]);
        while (size > 0) {// O(N)
            heapify(nums, 0, size);// O(logN)
            swap(nums[0], nums[--size]);// O(1)
        }
    }

int main(){
    return 0;
}