//#include<iostream.h>
//#include "StdAfx.h"


#include <iostream> 
#include "GA.h"
#include "math.h"
using namespace std; 

const int CityNumber = 30;

void CCityPoint::GetPoint(int*p,int k)
{	
	x=*p;
	p++;
	y=*p;
	no=k;
}


void CGA::InitCityList(int city[], int num)				
{
	for(int i=0;i<num;i++)
	{
		citylist[i].GetPoint(city,i);
		city++;
		city++;
	}
}


void CGA::CalcDistance()           //距离表生成函数
{
	for(int i=0;i<CityNumber;i++)
	{
		for(int j=0;j<CityNumber;j++)
		{
			Distance[i][j]=sqrt(pow((citylist[i].re_x()-citylist[j].re_x()),2)+pow((citylist[i].re_y()-citylist[j].re_y()),2));
		}
	}
}


void CIndiv::Initdiv()
{
	for(int i=0;i<30;i++)
	{
		a[i]=i;
	}
}


void CIndiv::Calcfit(const double distance[30][30],CCityPoint list[])
{
	 length=0;
	 int m,n;	
	for(int j=0;j<29;j++)
	{
		m=list[a[j]].re_no();
		n=list[a[j+1]].re_no();
		length=length+distance[m][n];
	}
	m=list[a[29]].re_no();
	n=list[a[0]].re_no();
	length=length+distance[m][n];
	
	if(length>1500.0)
	{
		fit=0.0;
	}
	fit=1500.0-length;
}

/*
void CIndiv::pfdiv()
{
	for(int i=0;i<30;i++)
	{
		cout<<a[i]<<"->";
	}
	cout<<a[0];
	cout<<endl<<"fit="<<fit<<" "<<"最短路径length="<<length;
	cout<<endl<<"******************************"<<endl;
}

*/
//初始化种群
void CGA::Init_population()
{
	CIndiv tmpindiv;
	int tmp;
		
	population.reserve(450);
	parent.reserve(450);
	child.reserve(450);

	srand(time(NULL));                  //按当前时间生成种子
	
	for(int k=0;k<pop_num;k++)
	{
		tmpindiv.Initdiv();						//初始化个体 
		
		for(int i=1;i<30;i++)					//随机初始化个体
		{	
			int index;	
			index = rand() % (CityNumber - i) + i;   //产生[i,CityNumber-1]区间的随机数
			if (index != i)
			{
				tmp = tmpindiv.a[i];
				tmpindiv.a[i] = tmpindiv.a[index];
				tmpindiv.a[index] = tmp;			
			}
		}
	
		population.push_back(tmpindiv);
		population.at(k).Calcfit(Distance,citylist);

//		cout<<"初始个体编号"<<k<<"  length="<<population.at(k).length<<endl;
/**********************输出初始种群*****************************/
/*
		cout<<"初始种群个体"<<k<<"   ";				
		population.at(k).pfdiv();
/***************************************************/
	}  
}


void CGA::Select()
{
	double total_fit=0.0;
	vector<double> total_gr;

	double total_div_fit=0.0;
	double div_fit_pro=0.0;

	double index;
	
	parent.clear();	
	

	total_gr.clear();
	

	for(int i=0;i<pop_num;i++)						//计算总的累计概率
	{
		total_fit=total_fit+population.at(i).fit;	
	}

	for(int j=0;j<pop_num;j++)						//计算概率梯度
	{
		div_fit_pro=population.at(j).fit/total_fit;
		total_div_fit=total_div_fit+div_fit_pro;
/*************************输出个体适应度和个体概率梯度********************************/
/*
		cout<<"population.at()个体适应度="<<population.at(j).fit<<"  "<<total_div_fit<<endl;
/*************************************************************************************************/
		total_gr.push_back(total_div_fit);
/**************************输出概率梯度**********************************************/	

//		cout<<"概率梯度"<<total_gr.at(j)<<endl;			
	}
	
	index=0;
	for(int k=0;k<pop_num;k++)					//挑选pop_num个个体
	{

//		srand(time(NULL)+k*k);                	/*随机产生器函数种子，此处不能给种子，要不然会产生近似相连的值*/
		/*环境对物种是有选择的，但是环境的变化是缓慢的，可以认为此值是不变的*/
	
		index=rand()%10000;
		index=index/10000.0;
		
//		cout<<"index="<<index<<endl;
		
		for(int t=0;t<pop_num;t++)				//从种群选符合概率的个体
		{
			if(total_gr.at(t)>=index)
			{
				parent.push_back(population.at(t));	

//				cout<<"编号"<<t<<"  ";	//测试语句	调交叉概率与变异概率参数时用

				break;				
			}	
		}
		
//		cout<<parent.at(k).length<<endl;	//测试语句	调交叉概率与变异概率参数时用

/*********************打印挑选个体******************************/
/*
		parent.at(k).Calcfit(Distance,citylist);
		cout<<"挑选的个体"<<k<<endl;

		parent.at(k).pfdiv();					//打印个体
/***************************************************/
	} 
}

//交叉
void CGA::Crossover()
{	
	int locus,len;
	int tmpchro1[30]={0};
	int tmpchro2[30]={0};

	double index;
		
	int tmp=0;
	
	CIndiv tmpdiv1,tmpdiv2,tmpdiv3,tmpdiv4;
	vector<CIndiv> tmpdiv;
	CIndiv tmpdd;

	child.clear();	

	for(int wi=0;wi<pop_num;wi++)
	{
		tmpdiv.push_back(parent.at(wi));
	}

	for(int qi=0;qi<pop_num;qi++)
	{
		for(int qj=qi+1;qj<pop_num;qj++)
		{
			
			if(tmpdiv.at(qi).fit<tmpdiv.at(qj).fit)
			{
				tmpdd=tmpdiv.at(qi);
				tmpdiv.at(qi)=tmpdiv.at(qj);
				tmpdiv.at(qj)=tmpdd;
			}
		}

	}

		//tmpdiedai=tmpdiv.at(0).length;

		for (int qjj=0;qjj<8;qjj++)
		{
			tmpdiv.at(pop_num-qjj-1)=tmpdiv.at(qjj);
		}

	int ii;	
	CIndiv tmpd;

	for (int w=1;w<pop_num;w++)
	{
		
		ii = rand() % (pop_num - w) + w;   //产生[i,CityNumber-1]区间的随机数
		if (ii != w)
		{
			tmpd = tmpdiv.at(w);
			tmpdiv.at(w) = tmpdiv.at(ii);
			tmpdiv.at(ii) = tmpd;			
		}
	}


	for (int jj=0;jj<pop_num;jj++)
	{
		parent.at(jj)=tmpdiv.at(jj);
	}

	
	for(int i=0;i<pop_num-1;i=i+2)
	{	
		tmpdiv1=parent.at(i);
		tmpdiv2=parent.at(i+1);

		index=rand()%10000;
		index=index/10000.0;
		
		if(index<crossover_pro)
		{
//		locus=rand()%(26)+1;					//locus  1~26
//		len=rand()%(27-locus)+2;				//len	2~28-locus	复制的基因个数是len+1	//起始基因点事locus		终止基因基因点事locus+len
		locus=rand()%27+2;					//效果还行 locus=2~29  len=0~26
		len=rand()%(29-locus);	
		
//		locus=rand()%29+1;
//		len=rand()%(30-locus);
													
/***************************************************/
/*		
		cout<<"locus="<<locus<<endl;
		cout<<"len="<<len<<endl;
/***************************************************/
		
		
		for(int j=0;j<30;j++)					//复制染色体
		{
			tmp=(locus+len+j+1)%30;
			tmpchro1[j]=tmpdiv1.a[tmp];
			tmpchro2[j]=tmpdiv2.a[tmp];
					
		}

/***************************************************/
/*
		cout<<"个体1染色体"<<endl;
		for(int q=0;q<30;q++)
		{
			cout<<tmpchro1[q]<<" ";
		}
		cout<<endl;
		cout<<"个体2染色体"<<endl;
		for(int w=0;w<30;w++)
		{
			cout<<tmpchro2[w]<<" ";
		}
/***************************************************/


		for(int k=0;k<len+1;k++)							//剔除已有片段
		{
			for(int t=0;t<30;t++)							//寻找符合条件的基因
			{
				if(tmpchro1[t]==tmpdiv2.a[k+locus])
				{
					tmpdiv3.a[k+locus]=tmpchro1[t];
					for(int r=t;r<30;r++)
					{	
						tmpchro1[r]=tmpchro1[r+1];
					}
				}
				if(tmpchro2[t]==tmpdiv1.a[k+locus])
				{
					tmpdiv4.a[k+locus]=tmpchro2[t];
					for(int l=t;l<30;l++)
					{
						tmpchro2[l]=tmpchro2[l+1];
					}
				}
			}	
		}
/***************************************************/	
/*				
		cout<<endl;
		cout<<"个体1的基因片段"<<endl;		
		for(int c=locus;c<locus+len+1;c++)
		{
			cout<<tmpdiv4.a[c]<<"  ";
		}

		cout<<endl;
		cout<<"个体2基因片段"<<endl;					//测试用 输出复制基因片段
		for(int b=locus;b<locus+len+1;b++)
		{
			cout<<tmpdiv3.a[b]<<"  ";
		}

		cout<<endl;		
		cout<<"个体1剩余基因片段"<<endl;
		for(int a=0;a<30-len-1;a++)
		{
			cout<<tmpchro1[a]<<"  ";
		}

		cout<<endl;
		cout<<"个体2剩余基因片段"<<endl;

		for(int d=0;d<30-len-1;d++)
		{
			cout<<tmpchro2[d]<<"  ";
		}		
		cout<<endl;
/***************************************************/		

		for(int h=0;h<30-len-1;h++)	
		{
			tmpdiv3.a[(h+1+locus+len)%30]=tmpchro1[h];
			tmpdiv4.a[(h+1+locus+len)%30]=tmpchro2[h];	
		}

		}
		else
		{
			tmpdiv3=tmpdiv1;
			tmpdiv4=tmpdiv2;
		}
		child.push_back(tmpdiv3);
//		child.at(i).Calcfit(Distance,citylist);
		child.push_back(tmpdiv4);
//		child.at(i+1).Calcfit(Distance,citylist);
		
/*********************输出交叉后的个体******************************/
/*		
		cout<<"交叉后个体1"<<" "<<i<<endl;
		
		child.at(i).pfdiv();
		cout<<"交叉后个体2"<<" "<<i+1<<endl;
		
		child.at(i+1).pfdiv();
/***************************************************/		
	}
}

//突变
void CGA::Mutation()
{
	double index;
	int locus;
	int len;
	int tmpchro1[30]={0};
	int tmpchro2[30]={0};

	CIndiv tmpdiv1;


	int r=0;
	int h=0;

	population.clear();

	for(int i=0;i<pop_num;i++)
	{	

		tmpdiv1=child.at(i);

		for(int j=0;j<30;j++)
		{
			tmpchro1[j]=tmpdiv1.a[j];
		}
	

		index=rand()%1000;
		index=index/1000.0;
		if(index<=mutation_pro)	
		{

			locus=rand()%(27)+2;	//locus  1~26		//效果还行
			len=rand()%(29-locus);	//len	2~28-locus	复制的基因个数是len+1	//起始基因点事locus	终止基因基因点事locus+len
//			locus=rand()%(29)+1;					
//			len=rand()%(30-locus);	
											
/***************************************************/
/*
			cout<<"locus="<<locus<<endl;
			cout<<"len="<<len<<endl;			
/***************************************************/
			
			r=0;
			for(int k=locus+len;k>=locus;k--)
			{								
				tmpchro2[r]=tmpchro1[k];
				r++;									
			}

/***************************************************/
/*	
			cout<<endl<<"染色体逆序片段"<<endl;		
			for(int b=0;b<len+1;b++)					//输出染色体逆序片段
			{
				cout<<tmpchro2[b]<<" ";
			}
			cout<<endl;			
/***************************************************/

			h=0;
			for(int t=locus;t<locus+len+1;t++)
			{
				tmpdiv1.a[t]=tmpchro2[h];
				h++;
			}				
		}
		
		population.push_back(tmpdiv1);
//		population.at(i).Calcfit(Distance,citylist);
		
/***************************************************/
/*		
		cout<<"输出变异后个体"<<endl;
		population.at(i).pfdiv();

/***************************************************/
	}
}

//计算适应度
void CGA::Evolution()
{

	for(int i=0;i<pop_num;i++)
	{
		population.at(i).Calcfit(Distance,citylist);
	}
}


double CGA::Output(int city[], int num)
{
	CIndiv bestdiv;
	this->Evolution();
	bestdiv=population.at(0);
	for(int i=1;i<pop_num;i++)
	{
		if(population.at(i).fit>bestdiv.fit)
		{
			bestdiv=population.at(i);
		}
	}

	for(int j=0;j<num;j++)
	{
		city[j]=bestdiv.a[j];
	}
	return bestdiv.length;
}
void CGA::Start()
{
	srand(time(NULL)); 
	CalcDistance();
	Init_population();
	for(int abi=0;abi<iteration;abi++)
	{
		Evolution();						//计算适应度
		Select();						//选择算子
		Crossover();						//交叉算子
		Mutation();						//变异算子
	}
}


