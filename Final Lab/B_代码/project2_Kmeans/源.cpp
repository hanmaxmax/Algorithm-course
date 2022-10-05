#include "kmeans.h"
//簇的个数（即k的大小，根据自己需要调整）
const int numOfCluster = 3;
//最大像素值
const int MAX_PIX_VALUE = 255;
//存放所有点
vector<point> points;
//存放所有簇中心
vector<point> centers;
//存放所有点颜色特征
vector<double> pixVec;

//读取图像
Mat readImage(String imageName)
{
    Mat image = imread(imageName);
    return image;
}

//初始化k-means聚类中心
void initializeCenters(const Mat& img)
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < numOfCluster; i++)
    {
        int randomX = rand() % img.rows;
        int randomY = rand() % img.cols;
        uchar pixVal = img.at<uchar>(randomX, randomY);
        point cp(randomX, randomY, (double)pixVal);
        centers.push_back(cp);
    }
}

//将图像中的所有点装入points中
void initializePoints(const Mat& img)
{
    for (int i = 0; i < img.rows; i++)
    {
        const uchar* data = img.ptr<uchar>(i);
        for (int j = 0; j < img.cols; j++)
        {
            uchar pixVal = data[j];
            point p(i, j, (double)pixVal);
            points.push_back(p);
        }
    }
}

int main()
{
    String imageName = "C:/Users/HJX/Desktop/color2.jpg";
    Mat img = readImage(imageName);
    cvtColor(img, img, COLOR_BGR2GRAY);//转化为灰度图像
    namedWindow(imageName, WINDOW_NORMAL);
    imshow(imageName, img);
    waitKey(0);
    int rows = img.rows;
    int cols = img.cols;
    initializeCenters(img);
    initializePoints(img);
    Kmeans* km = new Kmeans(points, centers, numOfCluster, 1);
    cout << "---------------k-means start-------------" << endl;
    km->kmeans();
    cout << "---------------k-means end---------------" << endl;
    vector<point>* clusters = km->getClusters();


    Mat src = imread(imageName);	//读取图片（使用图片的绝对路径）
    CV_Assert(src.depth() == CV_8U);
    if (src.empty())
    {
        printf("could not find the image!\n");
        return 0;
    }



    for (int i = 0; i < numOfCluster; i++)
    {
        vector<point> tmpVec = clusters[i];
        //用不同颜色标记分类结果
        for (int j = 0; j < tmpVec.size(); j++)
        {
            //res.at<uchar>(tmpVec[j].row, tmpVec[j].col) = i * div;
            if (i == 0)
                cv::circle(src, Point(tmpVec[j].col, tmpVec[j].row), 1, CV_RGB(0, 255, 0));
            if (i == 1)
                cv::circle(src, Point(tmpVec[j].col, tmpVec[j].row), 1, CV_RGB(0, 0, 0));
            if (i == 2)
                cv::circle(src, Point(tmpVec[j].col, tmpVec[j].row), 1, CV_RGB(255, 0, 0));
            if (i == 3)
                cv::circle(src, Point(tmpVec[j].col, tmpVec[j].row), 1, CV_RGB(0, 0, 255));
       
        }
    }

    namedWindow("OutPut", WINDOW_AUTOSIZE);
    imshow("OutPut", src);//显示默认窗口

    waitKey(0);
    system("pause");
}
