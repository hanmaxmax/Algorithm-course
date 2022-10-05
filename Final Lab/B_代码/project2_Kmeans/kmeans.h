#pragma once

#include<opencv2\opencv.hpp>
#include<random>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<list>
#include<iostream>
#include<math.h>

using namespace cv;
using namespace std;



//point�ṹ��Ҫ�����洢ͼ���нڵ�ĺ����꣬�������Լ��Ҷ�ֵ
struct point
{
    int row;
    int col;
    double pixVal;
    point(int row, int col, double pixVal) :row(row), col(col), pixVal(pixVal) {}
};




class Kmeans {
private:
    //�洢���е�
    vector<point> points;
    //�洢�ص����ĵ�
    vector<point> centers;
    //�洢ÿ���㵽��Ӧ�Ĵ�
    vector<point>* clusters;
    //������ά��
    int dimension;
    //�صĸ���
    int k;
public:
    //���캯��
    Kmeans(vector<point> points, vector<point> centers, int k, int dimension)
    {
        this->points = points;
        this->centers = centers;
        this->dimension = dimension;
        this->k = k;
        clusters = new vector<point>[k];
    }

    //��������
    ~Kmeans()
    {
        delete clusters;
    }

    //��ȡ��
    vector<point>* getClusters()
    {
        return this->clusters;
    }

    //������������֮���ŷʽ����
    double getDistanceBetweenTwoPoints(const point& point1, const point& point2)
    {
        double sum = 0;
        sum = pow(point1.pixVal - point2.pixVal, 2);
        return sum;
    }

    //����ÿ���㵽��������Ĵ����ĵ㣬������浽vector��
    vector<int> getClosetClusterCenterLabel()
    {
        double min;
        int label;
        vector<int> labels;
        for (int i = 0; i < points.size(); i++)
        {
            label = 0;
            min = getDistanceBetweenTwoPoints(points[i], centers[0]);
            for (int j = 1; j < centers.size(); j++)
            {
                double tmp = getDistanceBetweenTwoPoints(points[i], centers[j]);
                if (tmp < min)
                {
                    min = tmp;
                    label = j;
                }
            }
            labels.push_back(label);
        }
        return labels;
    }

    //��ÿ��������������������ĵ��Ӧ�Ĵ���
    void computeClusters(const vector<int>& labels)
    {
        for (int i = 0; i < k; i++)
        {
            clusters[i].clear();
        }
        for (int i = 0; i < labels.size(); i++)
        {
            int label = labels[i];
            clusters[label].push_back(points[i]);
        }
    }

    //���¼������дص����ĵ�ĻҶ�ֵ
    void computeCenters()
    {
        centers.clear();
        for (int i = 0; i < k; i++)
        {
            double sum = 0;
            for (int j = 0; j < clusters[i].size(); j++)
            {
                sum += clusters[i][j].pixVal;
            }
            double meanVal = sum / clusters[i].size();
            point cp(-1, -1, meanVal);
            centers.push_back(cp);
        }
    }

    //ȷ���µ����ĵ�����¼���һ��cost
    double computeCost()
    {
        double sum = 0;
        for (int i = 0; i < k; i++)
        {
            vector<point> tmpVec = clusters[i];
            for (int j = 0; j < tmpVec.size(); j++)
            {
                sum += getDistanceBetweenTwoPoints(tmpVec[j], centers[i]);
            }
        }
        return sum / points.size();
    }

    //����ִ��k-means�㷨�Ĳ���
    void kmeans()
    {
        double oldCost, newCost;
        vector<int> labels = getClosetClusterCenterLabel();
        computeClusters(labels);
        newCost = computeCost();

        computeCenters();
        labels = getClosetClusterCenterLabel();
        computeClusters(labels);
        oldCost = newCost;
        newCost = computeCost();

        while (oldCost != newCost)
        {
            oldCost = newCost;
            computeCenters();
            labels = getClosetClusterCenterLabel();
            computeClusters(labels);
            newCost = computeCost();
        }
        cout << "Final Cost: " << newCost << endl;
    }
};