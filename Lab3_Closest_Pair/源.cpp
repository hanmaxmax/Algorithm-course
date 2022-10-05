#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Point
{
public:
	float x;
	float y;
	Point(float X = 0, float Y = 0)
	{
		x = X;
		y = Y;
	}
};

//全局变量
Point* P;

void SSwap(Point& a, Point& b)
{
	Point t = a;
	a = b;
	b = t;
}


void ShellSort_x(Point* arry, int len)
{
	for (int gap = len / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < len; i++)
		{
			int j = i;
			while (j - gap >= 0 && arry[j].x < arry[j - gap].x)
			{
				SSwap(arry[j], arry[j - gap]);
				j -= gap;
			}
		}
	}
}
void ShellSort_y(Point* arry, int len ,int* res)
{
	Point* temp = new Point[len];


	for (int i = 0; i < len; i++)
	{
		temp[i] = arry[i];
		res[i] = i;
	}


	for (int gap = len / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < len; i++)
		{
			int j = i;
			while (j - gap >= 0 && temp[j].y < temp[j - gap].y)
			{
				SSwap(temp[j], temp[j - gap]);

				//Swap( res[j] , res[j-gap] )
				int t = res[j];
				res[j] = res[j - gap];
				res[j - gap] = t;

				j -= gap;
			}
		}
	}
}



float dist(Point a, Point b)
{
	float d = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	return d;

}


float func(int* Px, int* Py, int len)
{
	float min_d = dist(P[Px[0]], P[Px[1]]);

	//如果|P|<=3，则简单穷举
	if (len <= 3)
	{
		for (int i = 0; i < len-1; i++)
		{
			for (int j = i+1; j < len; j++)
			{
				float temp_d = dist(P[Px[i]], P[Px[j]]);
				min_d = min_d < temp_d ? min_d : temp_d;
			}
		}
		return min_d;
	}

	//构造Qx、Qy（左）、Rx、Ry（右）
	int len_Q = len / 2;
	int len_R = len - len_Q;


	int* Qx = new int[len_Q];
	int* Qy = new int[len_Q];
	int* Rx = new int[len_R];
	int* Ry = new int[len_R];
	//Qx和Rx只需要在原来的Px基础上对半分即可
	//Qy和Ry需要遍历一遍Py
	
	for (int i = 0; i < len_Q; i++)
	{
		Qx[i] = Px[i];
	}
	for (int i = len_Q; i < len; i++)
	{
		Rx[i - len_Q] = Px[i];
	}

	int k1 = 0, k2 = 0;
	for (int i = 0; i < len; i++)
	{
		if (Py[i] < Rx[0])
		{
			Qy[k1] = Py[i];
			k1++;
		}
		else
		{
			Ry[k2] = Py[i];
			k2++;
		}
	}

	//左右递归
	float min_Q = func(Qx, Qy, len_Q);
	float min_R = func(Rx, Ry, len_R);
	float delta = min_Q < min_R ? min_Q : min_R;

	//找中间窄带，构造Sy
	int* Sy = new int[len];
	float x_star = P[Qx[len_Q - 1]].x;
	int index = 0;//记录Sy的大小
	for (int i = 0; i < len; i++)
	{
		if (abs(P[Py[i]].x - x_star) < delta)
		{
			Sy[index] = Py[i];
			index++;
		}
	}

	//对Sy中每个点，计算与其下标差小于12的点的距离
	for (int i = 0; i < index-1; i++)
	{
		for (int j = i + 1; j <= i + 12 && j < index; j++)
		{
			float temp_d = dist(P[Sy[i]], P[Sy[j]]);
			min_d = min_d < temp_d ? min_d : temp_d;
		}
	}
	
	return min_d < delta ? min_d : delta;

}


int main()
{
	int n;
	cin >> n;
	Point* pp = new Point[n];
	P = pp;
	int* Px = new int[n];
	int* Py = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> P[i].x;
		cin >> P[i].y;
	}
	
	ShellSort_x(P, n);

	for (int i = 0; i < n; i++)
	{
		Px[i] = i;
	}

	ShellSort_y(P, n, Py);
	


	float result = func(Px, Py, n);
	cout << fixed << setprecision(2) << result;


}