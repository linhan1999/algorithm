#include<cassert>

namespace LH
{
	class UnionFInd //查找俩个点是否连接
	{
	private:
		int* parent;
		int* rank;
		int count;

	public:
		UnionFInd(int count)
		{
			parent = new int[count];
			rank = new int[count];
			this->count = count;
			for(int i = 0; i < count; i++)
			{
				parent[i] = i; //父节点为自己
				rank[i] = 1;
			}
		}

		~UnionFInd()
		{
			delete[] rank;
			delete[] parent;
		}

		int size()
		{
			return count;
		}

		int find(int p)
		{
			assert(p >= 0 && p < count);
			/*while (p != parent[p])
			{
				parent[p] = parent[parent[p]];
				p = parent[p];
			}
			return p;*/

			if (p != parent[p])
				parent[p] = find(parent[p]);
			return parent[p];
		}

		void unionElements(int p, int q)
		{
			int pr = find(p);
			int qr = find(q);
			
			if (pr == qr)
				return;

			if (rank[pr] < rank[qr])
				parent[pr] = qr;
			else if (rank[pr] > rank[qr])
				parent[qr] = pr;
			else //rank[pr] == rank[qr]
			{
				parent[pr] = qr;
				rank[qr] += 1;
			}
		}

		bool isConnected(int p, int q)
		{
			return find(q) == find(p);
		}

		void print()
		{
			for (int i = 0; i < count; i++)
				std::cout << parent[i] << std::endl;
		}
	};

}
