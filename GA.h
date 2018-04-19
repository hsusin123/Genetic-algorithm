#ifndef _GA_
#define _GA_
/************ÿ��������Ϣ********************/
#include <stdlib.h>
#include <vector>
#include <iostream> 
using namespace std; 

//��������
class CCityPoint{
private:
	int x,y;
	int no;
public:
	void GetPoint(int*,int);
	int re_x()
	{
		return x;
	}
	int re_y()
	{
		return y;
	}
	int re_no()
	{
		return no;
	}	
};

//��Ⱥ����
class CIndiv
{
public:
	int a[30];
	double length;
	double fit;
public:
	void Calcfit(const double Distance[30][30],CCityPoint list[]);			//��Ӧ�ȼ���
	void Initdiv();
	void pfdiv();
};

/*************************/

/***********************/

class CGA 
{
private:
	CCityPoint citylist[30];   //���б���б�
	int iteration;					//��������
	int pop_num;			//��Ⱥ��С��ֻ������ż��
	double crossover_pro;		//�������
	double mutation_pro;		//�������	

	double Distance[30][30];		//���о����
	
	
	vector<CIndiv> population;			//��Ⱥ
	vector<CIndiv> parent;				//����
	vector<CIndiv> child;				//�Ӵ�
	
	CIndiv tmp;
	
public:
	CGA(){
		iteration = 800;
		pop_num = 50;	
		crossover_pro=0.8;
		mutation_pro=0.15;
	}
	void Start();
	void InitCityList(int city[], int num);		//��ʼ�������б�����б����Ҫ��ֻ���б����������˳��е�����ͳ��еı�š�
	//��Ⱥ�͸����б�ţ�ֻ����
	void Set_iteration(int m)		//���õ�������
	{
		iteration=m;
	}
	void Set_popNum(int val){
		pop_num = val;			
	}
	void Set_cross_mutation(int cross, int mutation){
		crossover_pro = cross;
		mutation_pro = mutation;	
	}
	double Output(int city[], int num);//�����ý�
private:
	void CalcDistance();			//������м�ľ���
	void Init_population();			//��ʼ����Ⱥ
	void Select();					//ѡ������
	void Crossover();				//��������
	void Mutation();				//��������
	void Evolution();				//��Ӧ����������
						

};

#endif
