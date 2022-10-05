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

int s = n_size * n_size;//源点
int t = n_size * n_size + 1;//汇点
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
		return sum;//sum是整条增广路对最大流的贡献
	long long k, res = 0;  //k是当前最小的剩余容量 
	for (register int i = now[x]; i && sum; i = e[i].net)
	{
		now[x] = i;  //当前弧优化 
		int v = e[i].to;
		if (e[i].val > 0 && (dis[v] == dis[x] + 1))
		{
			k = dfs(v, min(sum, e[i].val));
			if (k == 0) dis[v] = inf;  //剪枝，去掉增广完毕的点 
			e[i].val -= k;
			e[i ^ 1].val += k;
			res += k;  //res表示经过该点的所有流量和（相当于流出的总量） 
			sum -= k;  //sum表示经过该点的剩余流量 
		}
	}
	return res;
}





void init()
{
	//1. 源点和像素点相连
	for (int i = 0; i < n_size * n_size; i++)
	{
		add(s, i, points[i]); //有向边存储 
	}
	//2. 像素点和汇点相连
	for (int i = 0; i < n_size * n_size; i++)
	{
		add(i, t, 300 - points[i]); //有向边存储 
	}
	//3. 像素点之间相连
	for (int i = 0; i < n_size * n_size; i++)
	{
		//上下的连线
		if (i >= n_size)
		{
			add(i, i - n_size, p);
			add(i - n_size, i, p);
		}

		//左右的连线
		if (i % n_size != 0)
		{
			add(i, i - 1, p);
			add(i - 1, i, p);
		}
	}
}


void read_pic()
{
	Mat src = imread("C:/Users/HJX/Desktop/black.png");	//读取图片（使用图片的绝对路径）
	CV_Assert(src.depth() == CV_8U);
	if (src.empty())
	{
		printf("could not find the image!\n");
		return;
	}
	namedWindow("InputImage", WINDOW_AUTOSIZE);
	imshow("InputImage", src);//显示默认窗口


	//单通道图像操作
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
	waitKey(0);//不加此语句图片会一闪而过
}


void draw_pic()
{

	Mat src = imread("C:/Users/HJX/Desktop/black.png");	//读取图片（使用图片的绝对路径）
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
	imshow("OutPut", src);//显示默认窗口
	waitKey(0);//不加此语句图片会一闪而过

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
	cout << "分割后的最大流=" << ans << endl;


	cout << "交互过程......" << endl;


	for (int i = 0; i < 500; i++)
	{
		e[28852].val += 1;
		e[28853].val -= 1;

		while (bfs())
		{
			ans += dfs(s, inf);
		}
		//cout << "第" << i << "次增广后的最大流：" << ans << endl;
		cout << ans << "	";
	}



	bfs();
	draw_pic();
	return 0;
}
