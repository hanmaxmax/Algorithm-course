#include <iostream>
#include<iomanip>
using namespace std;

class treeNode
{
public:
	int weight;
	int parent, lchild, rchild;
	treeNode()
	{
		weight = 0;
		parent = -1;
		lchild = -1;
		rchild = -1;
	}
};



//���庯��
int findmin(int x);//�ҵ���Сֵ�͵����ڶ�Сֵ
int creatRstr(int i);//�γɱ��루�����ӽڵ㿪ʼ����Ѱ�ұ��룩

int Num;
int num;
treeNode *tree;
int* words;
int main()
{
	cin >> Num;
	tree = new treeNode[2 * Num + 100];
	words = new int[Num];
	for (int i = 0; i < Num; i++)
	{
		cin >> words[i];
		tree[i].weight = words[i];
	}

	//�����������  
	//������Сֵ�͵����ڶ�Сֵ
	num = Num;
	while (true)
	{
		int minn = findmin(-1);
		int minn2 = findmin(minn);
		if (minn != -1 && minn2 == -1)
		{
			break;
		}
		int sum = tree[minn].weight + tree[minn2].weight;
		tree[num].weight = sum;
		tree[num].lchild = minn;
		tree[num].rchild = minn2;
		tree[minn].parent = num;
		tree[minn2].parent = num;
		num++;
	}


	//�ҵ�ÿ���ַ���Ӧ�ı���
	int up = 0;
	int bottom = 0;
	for (int i = 0; i < Num; i++)
	{
		int len=creatRstr(i);
		up += len * words[i];
		bottom += words[i];
	}
	float result = up * 1.0 / bottom;

	cout.setf(ios::fixed);
	cout <<  fixed << setprecision(2) << result ;
}


int findmin(int x)
{
	int a = 10000; int index = -1;//���index��ķ���-1��˵��ֻʣһ��treenode��
	for (int i = 0; i < num; i++)
	{
		if (tree[i].parent == -1 && i != x && tree[i].weight < a)
		{
			a = tree[i].weight;
			index = i;
		}
	}
	return index;
	return 0;
}

int creatRstr(int i)
{
	int strnum = 0;
	while (true)
	{
		int tmp = tree[i].parent;
		if (tmp == -1)
		{
			break;
		}
		strnum++;
		i = tree[i].parent;
	}
	return strnum;
}


