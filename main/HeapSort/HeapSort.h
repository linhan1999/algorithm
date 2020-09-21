#include<iostream>
#include<cstdio>
#include<ctime>
#include<algorithm>
#include<string>
#include<cmath>
#include<cassert>

#define erro -1

namespace LH
{

	//在一百万个数里找到前100位	时间复杂度nlogn
	//二叉堆 Binary Heap 任何一个子节点不小于父结点，完全二叉树  最大堆
	//左子节点是父节点的俩倍 右节点是左节点 + 1
	class test
	{
	public:
		test(int num) {
			generateRandomArry(num, 0, num);
			lengrh = num;
		};
		test()
		{
			generateRandomArry(10000, 0, 100000);
			lengrh = 10000;
		}

		void Test_Sort(std::string sortName, void(*sort)(int[], int));
		void printArry();

		void nearly_sort_array(int swaptimes)
		{
			MergeSort();
			srand(time(NULL));
			for (int i = 0; i < swaptimes; i++)
			{
				int posx = rand() % lengrh;
				int posy = rand() % lengrh;
				std::swap(arry[posx], arry[posy]);
			}
		}


		~test()
		{
			delete[] arry;
		}

	private:
		void generateRandomArry(int n, int rangeL, int rangeR);
		bool isSort();
		void MergeSort();
		void MSort(int tmpArray[], int left, int right);
		void merge(int tmpArray[], int lpos, int rpos, int rightend);
		void Insert_sort_improve(int l, int r);

		int *arry;
		int lengrh;
	};



	void test::generateRandomArry(int n, int rangeL, int rangeR)
	{
		arry = new int[n];
		srand(time(NULL));
		for (int i = 0; i < n; i++)
			arry[i] = rand() % (rangeR - rangeL + 1) + rangeL;
	}


	void test::printArry()
	{
		for (int i = 0; i < lengrh; i++)
		{
			std::cout << arry[i] << " ";
		}

	}

	void test::Test_Sort(std::string sortName, void(*sort)(int[], int))
	{
		clock_t startTime = clock();
		sort(arry, lengrh);
		clock_t endTime = clock();

		if (isSort())
			std::cout << sortName << ": " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" << std::endl;
	}

	bool test::isSort()
	{
		for (int i = 0; i < lengrh - 1; i++)
		{
			if (arry[i] > arry[i + 1])
				return false;
		}
		return true;
	}

	void test::merge(int tmpArray[], int lpos, int rpos, int rightend)
	{
		int leftend = rpos - 1;//前半段的最后位置
		int NumElements = rightend - lpos + 1;//待排序元素的总数
		int tmppos = lpos;

		while (lpos <= leftend && rpos <= rightend)
			if (arry[lpos] <= arry[rpos])
				tmpArray[tmppos++] = arry[lpos++];
			else
				tmpArray[tmppos++] = arry[rpos++];

		/*将剩余的部分加入到tmpArray中*/
		while (lpos <= leftend)
			tmpArray[tmppos++] = arry[lpos++];
		while (rpos <= rightend)
			tmpArray[tmppos++] = arry[rpos++];

		/*将tmpArray中的结果复制回原数组array中*/
		for (int i = 0; i < NumElements; i++, rightend--)
			arry[rightend] = tmpArray[rightend];
	}

	void test::MSort(int tmpArray[], int left, int right)
	{
		int center;
		if (right - left <= 20)
		{
			Insert_sort_improve(left, right);
		}
		else
		{
			center = (left + right) / 2;
			MSort(tmpArray, left, center);
			MSort(tmpArray, center + 1, right);
			merge(tmpArray, left, center + 1, right);
		}
	}


	void test::MergeSort()
	{
		int *tmpArray;
		tmpArray = new int[lengrh];
		if (tmpArray != NULL)
			MSort(tmpArray, 0, lengrh - 1);
		delete[] tmpArray;
	}


	void test::Insert_sort_improve(int l, int r)		//通过copy临时数据，赋值减少swap的调用
	{
		for (int i = l + 1; i <= r; i++)
		{

			auto e = arry[i];
			int j;
			for (j = i; j > l && arry[j - 1] > e; j--)
			{
				arry[j] = arry[j - 1];	//将数据后移
			}
			arry[j] = e;
		}
	}
  
//-------------------------------------------

	template<typename T>
	class MaxHeap
	{
	public:
		MaxHeap(int Heap_Length)
		{
			head = new T[Heap_Length + 1];
			count = 0;
			capacity_heap = Heap_Length + 1;
			num_std = Heap_Length;
		}

		MaxHeap(T arry[], int n)
		{
			head = new T[n + 1];
			capacity_heap = n;
			for(int i = 0; i < n; i++)
			{
				head[i + 1] = arry[i];
			}
			count = n;

			for(int i = count/2; i >= 1; i--)
			{
				ShiftDown(i);
			}
		}

		/*原地堆排序
		
		*/

		~MaxHeap()
		{
			delete[] head;
		}

		void Insert(T Data)
		{
			if (count >= capacity_heap - 1)
			{
				T *head_std = new T[capacity_heap + num_std];
				for (int i = 1; i <= count; i++)
					head_std[i] = head[i];
				T *p = nullptr;
				p = this->head;
				head = head_std;
				capacity_heap += num_std;
				delete[] p;
			}
			head[++count] = Data;
			ShiftUp(count);
		}

		T output()
		{
			if (IsEmpty())
				return erro;
			int k = head[1];
			head[1] = head[count--];
			ShiftDown(1);
			return k;
		}

		bool IsEmpty()
		{
			if (count)
				return false;
			else
				return true;
		}

		int GetSize()
		{
			return count;
		}

		void PrintHeap()
		{
			for (int i = 1; i <= count; i++)
			{
				std::cout << head[i] << " ";
			}
			std::cout << std::endl;
		}
	private:
		void ShiftUp(int k)
		{
			while (k > 1 && head[k / 2] < head[k])
			{
				swap(head[k / 2], head[k]);
				k /= 2;
			}
		}

		void ShiftDown(int k)
		{
			while (2 * k <= count) //判断是否有孩子
			{
				int j = 2 * k;
				if (j + 1 <= count && head[j + 1] > head[j])
					j += 1;
				if (head[k] >= head[j])
					break;
				swap(head[k], head[j]);
				k = j;
			}
		}

		T *head;
		int count;
		int capacity_heap;
		int num_std;
	};

	
}
