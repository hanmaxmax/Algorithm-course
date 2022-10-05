#include <iostream>
#include<math.h>
#include<string>
#include<vector>
using namespace std;
int res[2005][2];
int main()
{
	string strA;
	string strB;

	int k;

	cin >> strA >> strB >> k;

	int my_m = strA.length();
	int my_n = strB.length();

	for (int i = 0; i <= my_m; i++)
	{
		res[i][0] = i * k;
	}

	for (int j = 1; j <= my_n; j++)
	{
		res[0][1] = j * k;
		for (int i = 1; i <= my_m; i++)
		{
			int a = abs(strA[i - 1] - strB[j - 1]) + res[i - 1][0];
			int b = k + res[i - 1][1];
			int c = k + res[i][0];
			res[i][1] = min(a,min( b, c));
		}

		for (int i = 0; i <= my_m; i ++ )
		{
			res[i][0] = res[i][1];
		}

	}

	cout << res[my_m][1] << endl;






	/*string strA;
	string strB;
	
	int k;

	cin >> strA >> strB >> k;

	int my_m = strA.length();
	int my_n = strB.length();



	vector<vector<int>> res(my_m + 1);
	for (int i = 0; i <= my_m; i++)
		res[i].resize(my_n + 1);

	for (int i = 0; i <= my_m; i++)
	{
		res[i][0] = i * k;
	}

	for (int i = 0; i <= my_n; i++)
	{
		res[0][i] = i * k;
	}
	
	for (int i = 1; i <= my_m; i++)
	{
		for (int j = 1; j <= my_n; j++)
		{
			int a;
			if (strA[i - 1] == ' ' && strB[j - 1] != ' ')
			{
				a = k;
			}
			else if (strA[i - 1] != ' ' && strB[j - 1] == ' ')
			{
				a = k;
			}
			else if (strA[i - 1] == ' ' && strB[j - 1] == ' ')
			{
				a = 0;
			}
			else
			{
				a = abs(strA[i - 1] - strB[j - 1]) + res[i - 1][j - 1];
			}
			int b = k + res[i - 1][j];
			int c = k + res[i][j - 1];

			int tem = a < b ? a : b;
			res[i][j] = tem < c ? tem : c;

		}
	}

	cout << res[my_m][my_n];*/




}