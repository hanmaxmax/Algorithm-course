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
bool judge(int** woman, int n, int w, int chman, int otherman)//w��ϲ��chman����true
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
	
	//��ʼ��Man��Woman�����б�
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

	//��ʼ��man��woman��Լ������¼
	for (int i = 0; i < n + 1; i++)
		man_data[i] = -1;

	for (int i = 0; i < n + 1; i++)
		woman_data[i] = -1;

	//��ʼ��man�����ȱ�λ��
	for (int i = 0; i < n + 1; i++)
		position[i] = 0;
	

	while (man_null(man_data,n))
	{
		//ѡ��ǰѭ��Ҫ�Ҷ����man����Ϊchman
		int chman = 1;
		for (chman = 1; chman <= n; chman++)
		{
			if (man_data[chman] == -1)
			{
				break;
			}
		}

		//ѡ��chmanҪ���Լ���woman w   ///////////////////////////////////////////
		int tem = position[chman] + 1;
		int w = man[chman][tem];
		if (woman_data[w] == -1)//w is free
		{
			//��chman��wԼ��
			woman_data[w] = chman;
			man_data[chman] = w;
			position[chman]++;
		}
		else// w ���ںͱ���Լ��
		{
			int otherman = woman_data[w];
			if (judge(woman,n,w,chman,otherman))//w��ϲ��chman
			{
				//�� otherman free
				man_data[otherman] = -1;

				//��chman��wԼ��
				woman_data[w] = chman;
				man_data[chman] = w;
				position[chman]++;

			}
			else//w��ϲ��ԭ����otherman
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