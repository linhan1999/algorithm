#include<vector>
#include<iostream>

using namespace std;

class grape
{
public:
	grape() {
		map = move(vector<vector<int>>(6, vector<int>(6)));
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++)
				map[i][j] = 1000;
		}
		/*map[0][1] = 4; map[0][7] = 8;
		map[1][2] = 8; map[1][7] = 11; map[1][0] = 4;
		map[2][1] = 8; map[2][8] = 2; map[2][5] = 4; map[2][3] = 7;
		map[3][4] = 9; map[3][2] = 7; map[3][5] = 14;
		map[4][5] = 10; map[4][3] = 9;
		map[5][4] = 10; map[5][3] = 14; map[5][2] = 4; map[5][6] = 2;
		map[6][8] = 6; map[6][5] = 2; map[6][7] = 1;
		map[7][6] = 1; map[7][8] = 7; map[7][0] = 8; map[7][1] = 11;
		map[8][2] = 2; map[8][7] = 7; map[8][6] = 6;*/

		map[0][1] = 34; map[1][0] = 34;
		map[0][2] = 46; map[2][0] = 46;
		map[0][5] = 19; map[5][0] = 19;
		map[1][4] = 12; map[4][1] = 12;
		map[2][3] = 17; map[3][2] = 17;
		map[2][5] = 25; map[5][2] = 25;
		map[3][5] = 25; map[5][3] = 25;
		map[3][4] = 28; map[4][3] = 28;
		map[4][5] = 26; map[5][4] = 26;
	}
	vector<vector<int>> map;
	int length;
};


const int max = 100000;

void prim(vector<vector<int>> &VGraph, vector<int> &lowcost, vector<int> &parent, vector<bool> &visited) {

	int size = lowcost.size();
	visited[0] = true;
	for (int i = 0; i < size; i++)
	{
		lowcost[i] = VGraph[0][i];
		parent[i] = 0;
		visited[i] = false;  //访问
	}
	for (int i = 0; i < size; i++)
	{
		int min = max;
		int index = 1;
		for (int j = 0; j < size; j++)
		{
			if (lowcost[j] < min && !visited[j])
			{
				if (lowcost[j] < min) {
					min = lowcost[j];
					index = j;
				}
			}
		}
		visited[index] = true;
		for (int j = 1; j <size; j++)
		{
			if ((VGraph[index][j]<lowcost[j]) && (!visited[j]))
			{
				lowcost[j] = VGraph[index][j];
				parent[j] = index;
			}
		}
	}
#ifdef test

	for (int i = 1; i < 6; i++)
		cout << parent[i] << " " << i << "   " <<lowcost[i] << endl;
#endif

}

#define MAX_INT 999999

pair<int, int> GetShortestEdge(const vector<vector<int> >& Graph, const vector<bool>& isIncluded)//求当前在MST之外距离MST最近的点的id
{
	int minID = -1;
	int minDist = MAX_INT;
	pair<int, int> minEdge;
	for (int i = 0; i < Graph.size(); i++)
	{
		if (!isIncluded[i]) continue;//如果i已经在MST内则往下进行

		for (int j = 0; j < Graph.size(); j++) //j为MST外的点
			if (!isIncluded[j] && Graph[i][j] < minDist) { //找到不在MST内但是距离MST最近的点
				minID = j;
				minDist = Graph[i][j];
				minEdge = make_pair(i, j);
			}
	}
	return minEdge;
}

vector<pair<int, int> > Prim(const vector<vector<int> >& Graph, vector<bool>& isIncluded) {
	vector<pair<int, int> > MST;
	isIncluded[3] = true;
	//MST.push_back();
	for (int i = 1; i < Graph.size(); i++) {
		pair<int, int> minEdge = GetShortestEdge(Graph, isIncluded); //找到这次要放入的边i，j
		MST.push_back(minEdge); //放入
		isIncluded[minEdge.second] = true; //将j标记为已经放入
	}
	return MST;
}

int main() {
	grape Map;
	vector<int> lowcost(6);
	vector<int> parent(6);
	vector<bool> visited(6);
	vector<pair<int, int> > MST;
	//prim(Map.map, lowcost, parent, visited);
	MST = Prim(Map.map, visited);
	for (auto i : MST)
	    cout << i.first << " " << i.second << endl;
}
