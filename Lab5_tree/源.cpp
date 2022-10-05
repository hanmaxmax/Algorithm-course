# include <iostream>
using namespace std;

class edge
{
public:
	int u;
	int v;
	int weight;
};

void SSwap(edge& a, edge& b)
{
	edge t = a;
	a = b;
	b = t;
}
void ShellSort(edge* arry, int len)
{
	for (int gap = len / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < len; i++)
		{
			int j = i;
			while (j - gap >= 0 && arry[j].weight < arry[j - gap].weight)
			{
				SSwap(arry[j], arry[j - gap]);
				j -= gap;
			}
		}
	}
}




int find(int x,int *set) 
{
	if (x == set[x])
		return x;
	else
	{
		return set[x] = find(set[x],set);
	}
	
}


int main()
{
	int n, m;
	int result = 0;
	int T_num = 0;
	cin >> n >> m;
	
	edge* edges = new edge[m];
	for (int i = 0; i < m; i++)
	{
		cin >> edges[i].u >> edges[i].v >> edges[i].weight;
	}
	ShellSort(edges, m);


	int* set = new int[n+1];//记录每个顶点的集合index
	for (int i = 0; i <= n; i++)
	{
		set[i] = i;
	}



	for (int i = 0; i < m; i++)
	{
		int m_u = find(edges[i].u,set);
		int m_v = find(edges[i].v,set);


		if (set[m_u] != set[m_v])
		{
			result += edges[i].weight;
			T_num++;

			//合并集合
			set[m_u] = m_v;
		}

		if (T_num == n - 1)
		{
			break;
		}

	}

	cout << result;









	/*for (int i = 0; i < m; i++)
	{
		cout << edges[i].u << " " << edges[i].v << " " << edges[i].weight << endl;
	}*/

}