#include"MaxHeap.h"

using namespace std;

template <typename T>
void HeapSort1(T arry[],int n)
{
	LH::MaxHeap<T> case1_std = LH::MaxHeap<T>(n);
	for (int i = 0; i < n; i++)
		case1_std.Insert(arry[i]);
	for (int i = n - 1; i >= 0; i--)
		arry[i] = case1_std.output();
}

template <typename T>
void HeapSort2(T arry[],int n)
{
	LH::MaxHeap<T> maxheap = LH::MaxHeap<T>(arry, n);
	for (int i = n - 1; i >= 0; i--)
		arry[i] = maxheap.output();
}

template <typename T>
void ShiftDown(T arry[],int n,int k)
{
	while (2 * k + 1< n) //判断是否有孩子
	{
		int j = 2 * k + 1;
		if (j + 1 < n && arry[j + 1] > arry[j])
			j += 1;
		if (arry[k] >= arry[j])
			break;
		swap(arry[k], arry[j]);
		k = j;
	}
}

template <typename T>
void HeapSort3(T arry[], int n)
{
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		ShiftDown(arry, n, i);
	}
	for (int i = n - 1; i > 0; i--)
	{
		swap(arry[0], arry[i]);
		ShiftDown(arry, i, 0);
	}
}


int main(int argc, char* argv[])
{
	LH::test case1(1000000);
	LH::test case2(1000000);
	LH::test case3(1000000);
	case1.Test_Sort("HeapSort1", HeapSort1<int>);
	case2.Test_Sort("HeapSort2", HeapSort2<int>);
	case3.Test_Sort("HeapSort3", HeapSort3<int>);
	system("pause");
}
