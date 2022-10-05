 #include <iostream>
#include <vector>
#include<queue>
#include <opencv2/opencv.hpp>
#include<math.h>
using namespace std;
using namespace cv;
const int INF = 2147483649;

const int n_size = 80;//size
const int n_points = n_size * n_size + 2;
const int n_edges = 6 * n_size * n_size;

int points[n_size * n_size];
int result[n_points];

int s = n_size * n_size;//源点
int t = n_size * n_size + 1;//汇点
int p = 50;


int ans, dis[640010];
int tot = 1, vis[640010], pre[640010], head[640010], flag[10000][10000];


struct node
{
	int net, to, val;
}e[n_edges];


inline void add(int u, int v, int w) 
{
	if (flag[u][v] == 0) 
	{
		e[++tot].to = v;
		e[tot].val = w;
		e[tot].net = head[u];
		head[u] = tot;
		e[++tot].to = u;
		e[tot].val = 0;
		e[tot].net = head[v];
		head[v] = tot;

		flag[u][v] = tot; //用一个数组记录这一条边 
	}
	else 
	{
		e[flag[u][v] - 1].val += w; //累加重边 
	}
}

inline int bfs() 
{
	for (register int i = 1; i <= n_points; i++) vis[i] = 0;
	queue<int> q;
	q.push(s);
	vis[s] = 1;
	dis[s] = 2005020600;
	while (!q.empty()) 
	{
		int x = q.front();
		q.pop();
		for (register int i = head[x]; i; i = e[i].net) {
			if (e[i].val == 0) continue;
			int v = e[i].to;
			if (vis[v] == 1) continue;
			dis[v] = min(dis[x], e[i].val);
			pre[v] = i;
			q.push(v);
			vis[v] = 1;
			if (v == t) return 1;
		}
	}
	return 0;
}




inline void update() 
{
	int x = t;
	while (x != s) {
		int v = pre[x];
		e[v].val -= dis[t];
		e[v ^ 1].val += dis[t];
		x = e[v ^ 1].to;
	}
	ans += dis[t];
}



//构造边集
//边集由两部分组成——
//1&2. 源点和汇点分别与像素点相连
// 3.  相邻像素点相连

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
	Mat src = imread("C:/Users/HJX/Desktop/color.jpg");	//读取图片（使用图片的绝对路径）
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

			points[row * n_size + col] = 255-gray + 10;//此处可以自行调整
		}
	}
	namedWindow("grayImgm", WINDOW_AUTOSIZE);
	imshow("grayImgm", grayImg);
	waitKey(0);//不加此语句图片会一闪而过
}




void draw_pic()
{
	Mat src = imread("C:/Users/HJX/Desktop/color.jpg");	//读取图片（使用图片的绝对路径）
	CV_Assert(src.depth() == CV_8U);
	if (src.empty())
	{
		printf("could not find the image!\n");
		return;
	}


	for (register int i = 1; i <= n_points; i++) vis[i] = 0;
	queue<int> q;
	q.push(s);
	vis[s] = 1;
	dis[s] = 2005020600;
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (register int i = head[x]; i; i = e[i].net)
		{
			if (e[i].val == 0) continue;
			int v = e[i].to;
			if (vis[v] == 1) continue;
			dis[v] = min(dis[x], e[i].val);
			pre[v] = i;
			q.push(v);
			vis[v] = 1;
			if (v == t) return;
		}
	}

	cv::Point key;
	for (int i = 0; i < n_points; i++)
	{
		if (vis[i])
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
	
	while (bfs() != 0) 
	{
		update();
	}
	cout << ans;


	draw_pic();

	return 0;

}

