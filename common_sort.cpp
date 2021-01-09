//
// Created by wuyao on 2020/11/14,16:24.
//


#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

void swap(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
    return;
}

void bubble_sort(vector<int>& nums) {
    if (nums.empty() || nums.size() == 1)   return;
    // 冒泡排序通过交换,使得每次外循环结束之后都可以把当前数组未排序中的最大值交换到数组后部分
    bool flag = false;  // 优化冒泡排序 若某次没有进行交换说明 已经成功排序
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = 1; j < nums.size() - i; ++j) {
            if (nums[j - 1] > nums[j]) {
                swap(nums[j - 1], nums[j]);
                flag = true;
            }
        }
        if (!flag) break;
    }
    return;
}

void select_sort(vector<int>& nums) {
    // 每趟都会选择出当前未选择的数组中的最大值
    // 并且与未排序数组中的最后一个元素交换位置
    if (nums.empty() || nums.size() == 1)   return;
    int len = nums.size();
    int cur_max = INT_MIN;
    int cur_max_pos = -1;
    for (int i = 0; i < len; ++i) {
        cur_max = INT_MIN;
        cur_max_pos = -1;
        for (int j = 0; j < len - i; ++j) {
            if (nums[j] > cur_max) {
                cur_max = nums[j];
                cur_max_pos = j;
            }
        }
        if (cur_max_pos == -1)  break;
        else 
            swap(nums[cur_max_pos], nums[len - i - 1]);
    }
    return;
}


void insert_sort(vector<int>& nums) {
    if (nums.empty() || nums.size() == 1)   return;
    // 插入排序的思想是在数组前端维持一个有序序列, 将未排序的元素逐个的插入到已经有序的序列中
    int len = nums.size();
    for (int i = 1; i < len; ++i) {
        int j = i;
        int cur = nums[i];
        while (j > 0 && cur < nums[j - 1]) {
            nums[j] = nums[j - 1];
            j--;
        }
        nums[j] = cur;
    }
    return;
}

void shell_sort_helper(vector<int>& nums, int h) {
    int len = nums.size();
    // 将 [0, h) 中的元素视为已经有序的序列
    for (int i = h; i < len; ++i) {
    // 下面的代码就完全是插入排序的过程
        for (int j = i; j < len; j += h) {
            int k = j;
            int cur = nums[j];
            while (k >= h && cur < nums[k - h]) {
                nums[k] = nums[k - h];
                k -= h;
            }
            nums[k] = cur;
        }
    }
}

void shell_sort(vector<int>& nums) {
    // 希尔排序是种特殊的插入排序,先让间隔为h的元素都有序,逐渐使得h的值变小,直到为1.
    // 一般来说h的取值为 h = 1 / 2 * length    h = 1 / 4 * length  h = 1 / 8 * length 直到 h == 1
    if (nums.empty() || nums.size() == 1) return;
    int len = nums.size();
    for (int h = len / 2; h >= 1; h /= 2) {
        shell_sort_helper(nums, h);
    }
}




void quick_sort_handle(vector<int>& nums, int start , int end) {
    if (nums.empty() || nums.size() == 1)   return;
    if (start >= end) return;
    int l = start, r = end;
    // pivot_pos 取当前数组[start, end]之间的随机某个位置
    // rand() 通用公式  a + rand() % n 
    // 其中的a是起始值, n是整数的范围
    int pivot_pos = (rand() % (end - start + 1)) + start;
    int pivot = nums[pivot_pos];
    while (l <= r) {
        while (l <= r && nums[l] < pivot) l++;
        while (l <= r && nums[r] > pivot) r--;
        if (l <= r) {
            swap(nums[l], nums[r]);
            l++;
            r--;
        }
    }
    quick_sort_handle(nums, start, r);
    quick_sort_handle(nums, l, end);
}

void quick_sort(vector<int>& nums) {
    if (nums.empty() || nums.size() == 1)   return;
    quick_sort_handle(nums, 0, nums.size() - 1);
}


void merge(vector<int>& nums, int left, int mid, int right) {
    // merge的过程其实就是一个打擂台的算法
    // 把小区间通过打擂台的方式排好序
    vector<int> tmp(right - left + 1, 0);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
      //这里一定要是<= 不然的归并排序就是不稳定排序了
        if (nums[i] <= nums[j])
            tmp[k++] = nums[i++];
        else
            tmp[k++] = nums[j++];
    }
    while (i <= mid)    tmp[k++] = nums[i++];
    while (j <= right)  tmp[k++] = nums[j++];

    // 将排好序的临时vector中的数组复制到原数组
    for (int i = 0, j = left; i < tmp.size(); ++i, ++j)
        nums[j] = tmp[i];
}

void merge_sort_handle(vector<int>& nums, int left, int right) {
    if (nums.empty() || nums.size() == 1)   return;
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    merge_sort_handle(nums, left, mid);
    merge_sort_handle(nums, mid + 1, right);
    merge(nums, left, mid, right);
}

void merge_sort(vector<int>& nums) {
    if (nums.empty() || nums.size() == 1)   return;
    merge_sort_handle(nums, 0, nums.size() - 1);
}

void heapfiy(vector<int>& nums, int start, int n) {
    // 将当前堆调整为大顶堆
    if (start >= n) return;
    int left_child =start * 2 + 1;
    int right_child =start * 2 + 2;
    // 找出 父子节点中最大值
    int max_idx = start;
    if (left_child <= n && nums[left_child] >= nums[max_idx])
        max_idx = left_child;
    if (right_child <= n && nums[right_child] >= nums[max_idx])
        max_idx = right_child;
    // 如果最大值不是父节点, 将其与子节点交换并递归的调整交换过的节点
    if (max_idx != start) {
        swap(nums[start], nums[max_idx]);
        heapfiy(nums, max_idx, n);
    }
}

void build_heap(vector<int>& nums) {
    // 建堆要从倒数第二层开始建
    int size = nums.size() - 1;
    int parent = size / 2 - 1;
    for (int i = parent; i >= 0; --i)
        heapfiy(nums, i, size);
}

void heap_sort(vector<int>& nums) {
    if (nums.empty() || nums.size() == 1)   return;
    build_heap(nums);
    for (int i = nums.size() - 1; i >= 0; --i) {
        // 每次把最大值都放到数组的队尾,然后逐步缩小堆的范围.
        swap(nums[0], nums[i]);
        heapfiy(nums, 0, i - 1);
    }
}


void cnt_sort(vector<int>& nums) {
    // 计数排序一般来说只适合数据范围不太大的排序(因为数据的上下限决定着哈希表的大小,太大容易爆栈)
    // 思路其实很简单:就是把待排的数组中的元素都映射都哈希表中,哈希表key表示待排元素的值,val表示值出现的次数
    if (nums.empty() || nums.size() == 1)   return;
    int nums_min = INT_MAX, nums_max = INT_MIN;
    for (const auto& i : nums) {
        if (nums_min > i) nums_min = i;
        if (nums_max < i) nums_max = i;
    }
    // 哈希表的长度
    int diff = nums_max - nums_min + 1;
    int size = nums.size();
    // 一个简单的哈希表
    vector<int> _count(diff, 0);       

    int dist = 0 - nums_min;
    for (int i = 0; i < size; ++i)
        _count[nums[i] + dist]++;
    for (int i = 0, idx = 0; i < _count.size(); ++i) {
        while (_count[i]) {
            nums[idx++] = i - dist;
            _count[i]--;
        }
    }
    return;
}



int main()
{
    vector<vector<int>> test_example{{1, 4, 2, 5, 2, 0, -1, 9, 23, 5}, {12, 9124, 12341, 234, 23, -12, 42, -113}, {1, 1, 1, 1, 1},{}, {1, 2, 3}, {5, 4, 3, 2, 1},
    {10, 2, 3, 7, 11, 15, 18, 17, 16, 16, 15, 13, 1, 2, 3, 4, 7, -10, -25}, {41, 8467, 6334, 6500, 9169, 5724, 1478, 9358, 6962, 4464, 5705, 8145, 3281, 6827, 9961, 491, 2995, 1942, 4827, 5436, 2391, 4604, 3902, 153, 292, 2382, 7421, 8716, 9718, 9895, 5447, 1726, 4771, 1538, 1869, 9912, 5667, 6299, 7035, 9894},
    {41, 92, 209, 40, 59, 44, 208, 203, 12}, {10, 22, 10, 26, 11, 7, 8, 1, 23}, {0, 0, 0}, {1, 2}, {-4, -5, -9, -13} };
    for (auto v : test_example) {
        heap_sort(v);
        cout << "len = " << v.size() << "  ==> ";
        for (auto i : v)
            cout << i << "  ";
        cout << endl << endl;
    }

}


