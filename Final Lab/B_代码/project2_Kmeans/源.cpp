#include "kmeans.h"
//�صĸ�������k�Ĵ�С�������Լ���Ҫ������
const int numOfCluster = 3;
//�������ֵ
const int MAX_PIX_VALUE = 255;
//������е�
vector<point> points;
//������д�����
vector<point> centers;
//������е���ɫ����
vector<double> pixVec;

//��ȡͼ��
Mat readImage(String imageName)
{
    Mat image = imread(imageName);
    return image;
}

//��ʼ��k-means��������
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

//��ͼ���е����е�װ��points��
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
    cvtColor(img, img, COLOR_BGR2GRAY);//ת��Ϊ�Ҷ�ͼ��
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


    Mat src = imread(imageName);	//��ȡͼƬ��ʹ��ͼƬ�ľ���·����
    CV_Assert(src.depth() == CV_8U);
    if (src.empty())
    {
        printf("could not find the image!\n");
        return 0;
    }



    for (int i = 0; i < numOfCluster; i++)
    {
        vector<point> tmpVec = clusters[i];
        //�ò�ͬ��ɫ��Ƿ�����
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
    imshow("OutPut", src);//��ʾĬ�ϴ���

    waitKey(0);
    system("pause");
}
