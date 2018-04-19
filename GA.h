#ifndef _GA_
#define _GA_
/************每个城市信息********************/
#include <stdlib.h>
#include <vector>
#include <iostream> 
using namespace std; 

//城市坐标
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

//种群个体
class CIndiv
{
public:
	int a[30];
	double length;
	double fit;
public:
	void Calcfit(const double Distance[30][30],CCityPoint list[]);			//适应度计算
	void Initdiv();
	void pfdiv();
};

/*************************/

/***********************/

class CGA 
{
private:
	CCityPoint citylist[30];   //城市编号列表
	int iteration;					//迭代次数
	int pop_num;			//种群大小；只能输入偶数
	double crossover_pro;		//交叉概率
	double mutation_pro;		//变异概率	

	double Distance[30][30];		//城市距离表
	
	
	vector<CIndiv> population;			//种群
	vector<CIndiv> parent;				//父代
	vector<CIndiv> child;				//子代
	
	CIndiv tmp;
	
public:
	CGA(){
		iteration = 800;
		pop_num = 50;	
		crossover_pro=0.8;
		mutation_pro=0.15;
	}
	void Start();
	void InitCityList(int city[], int num);		//初始化城市列表，这个列表很重要，只有列表真正保存了城市的坐标和城市的编号。
	//种群和个体中编号，只是数
	void Set_iteration(int m)		//设置迭代次数
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
	double Output(int city[], int num);//输出最好解
private:
	void CalcDistance();			//计算城市间的距离
	void Init_population();			//初始化种群
	void Select();					//选择算子
	void Crossover();				//交叉算子
	void Mutation();				//变异算子
	void Evolution();				//适应度评估函数
						

};

#endif
