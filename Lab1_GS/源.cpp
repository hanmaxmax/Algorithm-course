#include <iostream>
using namespace std;

bool man_null(int* man_data,int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (man_data[i] == -1)
		{
			return true;
		}
	}
	return false;
}
bool judge(int** woman, int n, int w, int chman, int otherman)//w更喜欢chman——true
{
	int* inverse = new int[n + 1];

	for (int i = 1; i <= n; i++)
	{
		int k = woman[w][i];
		inverse[k] = i;
	}

	if (inverse[chman] < inverse[otherman])
	{
		return true;
	}
	return false;

}



int main()
{
	int n;
	cin >> n;
	int** man = new int* [n + 1];
	int** woman = new int* [n + 1];
	int* man_data = new int[n + 1];
	int* woman_data = new int[n + 1];
	int* position = new int[n + 1];
	
	//初始化Man、Woman优先列表
	for (int i = 0; i < n + 1; i++)
		man[i] = new int[n + 1];
	for (int i = 0; i < n + 1; i++)
		woman[i] = new int[n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			man[i][j] = 0;
			woman[i][j] = 0;
		}
	}




	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < n + 1; j++)
			cin >> man[i][j];


	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < n + 1; j++)
			cin >> woman[i][j];

	//初始化man、woman的约会对象记录
	for (int i = 0; i < n + 1; i++)
		man_data[i] = -1;

	for (int i = 0; i < n + 1; i++)
		woman_data[i] = -1;

	//初始化man的优先表位置
	for (int i = 0; i < n + 1; i++)
		position[i] = 0;
	

	while (man_null(man_data,n))
	{
		//选择当前循环要找对象的man，记为chman
		int chman = 1;
		for (chman = 1; chman <= n; chman++)
		{
			if (man_data[chman] == -1)
			{
				break;
			}
		}

		//选择chman要提出约会的woman w   ///////////////////////////////////////////
		int tem = position[chman] + 1;
		int w = man[chman][tem];
		if (woman_data[w] == -1)//w is free
		{
			//让chman和w约会
			woman_data[w] = chman;
			man_data[chman] = w;
			position[chman]++;
		}
		else// w 正在和别人约会
		{
			int otherman = woman_data[w];
			if (judge(woman,n,w,chman,otherman))//w更喜欢chman
			{
				//让 otherman free
				man_data[otherman] = -1;

				//让chman和w约会
				woman_data[w] = chman;
				man_data[chman] = w;
				position[chman]++;

			}
			else//w更喜欢原来的otherman
			{
				position[chman]++;
			}
		}

	}


	for (int i = 1; i <= n; i++)
	{
		cout << man_data[i] << " ";
	}



}