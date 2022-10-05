#include <iostream>
#include<queue>
#include <opencv2/opencv.hpp>
#include<math.h>
using namespace std;
using namespace cv;
const long long inf = 2005020600;


const int n_size = 70;//size
const int n_points = n_size * n_size + 2;
const int n_edges = 6 * n_size * n_size;

int points[n_size * n_size];
int result[n_points];

int s = n_size * n_size;//Դ��
int t = n_size * n_size + 1;//���
int p = 50;



long long  ans, dis[800010];
int tot = 1, now[800010], head[800010];




struct edge {
	int to, net, val;
} e[n_edges];

inline void add(int u, int v, int w)
{
	e[++tot].to = v;
	e[tot].val = w;
	e[tot].net = head[u];
	head[u] = tot;


	e[++tot].to = u;
	e[tot].val = 0;
	e[tot].net = head[v];
	head[v] = tot;
}


inline int bfs()
{
	for (register int i = 1; i <= n_points; i++) dis[i] = inf;
	queue<int> q;
	q.push(s);
	dis[s] = 0;
	now[s] = head[s];
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (register int i = head[x]; i; i = e[i].net) {
			int v = e[i].to;
			if (e[i].val > 0 && dis[v] == inf)
			{
				q.push(v);
				now[v] = head[v];
				dis[v] = dis[x] + 1;
				if (v == t) return 1;
			}
		}
	}
	return 0;
}


int dfs(int x, int sum)
{
	if (x == t)
		return sum;//sum����������·��������Ĺ���
	long long k, res = 0;  //k�ǵ�ǰ��С��ʣ������ 
	for (register int i = now[x]; i && sum; i = e[i].net)
	{
		now[x] = i;  //��ǰ���Ż� 
		int v = e[i].to;
		if (e[i].val > 0 && (dis[v] == dis[x] + 1))
		{
			k = dfs(v, min(sum, e[i].val));
			if (k == 0) dis[v] = inf;  //��֦��ȥ��������ϵĵ� 
			e[i].val -= k;
			e[i ^ 1].val += k;
			res += k;  //res��ʾ�����õ�����������ͣ��൱�������������� 
			sum -= k;  //sum��ʾ�����õ��ʣ������ 
		}
	}
	return res;
}





void init()
{
	//1. Դ������ص�����
	for (int i = 0; i < n_size * n_size; i++)
	{
		add(s, i, points[i]); //����ߴ洢 
	}
	//2. ���ص�ͻ������
	for (int i = 0; i < n_size * n_size; i++)
	{
		add(i, t, 300 - points[i]); //����ߴ洢 
	}
	//3. ���ص�֮������
	for (int i = 0; i < n_size * n_size; i++)
	{
		//���µ�����
		if (i >= n_size)
		{
			add(i, i - n_size, p);
			add(i - n_size, i, p);
		}

		//���ҵ�����
		if (i % n_size != 0)
		{
			add(i, i - 1, p);
			add(i - 1, i, p);
		}
	}
}


void read_pic()
{
	Mat src = imread("C:/Users/HJX/Desktop/black.png");	//��ȡͼƬ��ʹ��ͼƬ�ľ���·����
	CV_Assert(src.depth() == CV_8U);
	if (src.empty())
	{
		printf("could not find the image!\n");
		return;
	}
	namedWindow("InputImage", WINDOW_AUTOSIZE);
	imshow("InputImage", src);//��ʾĬ�ϴ���


	//��ͨ��ͼ�����
	Mat grayImg;

	cvtColor(src, grayImg, COLOR_BGR2GRAY);
	int height = grayImg.rows;
	int width = grayImg.cols;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int gray = grayImg.at<uchar>(row, col);

			points[row * n_size + col] = 255 - gray + 10;

		}
	}
	namedWindow("grayImgm", WINDOW_AUTOSIZE);
	imshow("grayImgm", grayImg);
	waitKey(0);//���Ӵ����ͼƬ��һ������
}


void draw_pic()
{

	Mat src = imread("C:/Users/HJX/Desktop/black.png");	//��ȡͼƬ��ʹ��ͼƬ�ľ���·����
	CV_Assert(src.depth() == CV_8U);
	if (src.empty())
	{
		cout << "could not find the image!";
		return;
	}


	cv::Point key;
	for (int i = 0; i < n_points; i++)
	{
		if (dis[i] < inf)
		{
			key.y = i / n_size;
			key.x = i % n_size;
			cv::circle(src, key, 1, CV_RGB(0, 255, 0));
		}
	}

	namedWindow("OutPut", WINDOW_AUTOSIZE);
	imshow("OutPut", src);//��ʾĬ�ϴ���
	waitKey(0);//���Ӵ����ͼƬ��һ������

}









int main()
{
	read_pic();
	init();
	while (bfs())
	{
		ans += dfs(s, inf);
	}
	draw_pic();
	cout << "�ָ��������=" << ans << endl;


	cout << "��������......" << endl;


	for (int i = 0; i < 500; i++)
	{
		e[28852].val += 1;
		e[28853].val -= 1;

		while (bfs())
		{
			ans += dfs(s, inf);
		}
		//cout << "��" << i << "���������������" << ans << endl;
		cout << ans << "	";
	}



	bfs();
	draw_pic();
	return 0;
}
