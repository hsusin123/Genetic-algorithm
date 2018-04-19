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


void CGA::CalcDistance()           //��������ɺ���
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
	cout<<endl<<"fit="<<fit<<" "<<"���·��length="<<length;
	cout<<endl<<"******************************"<<endl;
}

*/
//��ʼ����Ⱥ
void CGA::Init_population()
{
	CIndiv tmpindiv;
	int tmp;
		
	population.reserve(450);
	parent.reserve(450);
	child.reserve(450);

	srand(time(NULL));                  //����ǰʱ����������
	
	for(int k=0;k<pop_num;k++)
	{
		tmpindiv.Initdiv();						//��ʼ������ 
		
		for(int i=1;i<30;i++)					//�����ʼ������
		{	
			int index;	
			index = rand() % (CityNumber - i) + i;   //����[i,CityNumber-1]����������
			if (index != i)
			{
				tmp = tmpindiv.a[i];
				tmpindiv.a[i] = tmpindiv.a[index];
				tmpindiv.a[index] = tmp;			
			}
		}
	
		population.push_back(tmpindiv);
		population.at(k).Calcfit(Distance,citylist);

//		cout<<"��ʼ������"<<k<<"  length="<<population.at(k).length<<endl;
/**********************�����ʼ��Ⱥ*****************************/
/*
		cout<<"��ʼ��Ⱥ����"<<k<<"   ";				
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
	

	for(int i=0;i<pop_num;i++)						//�����ܵ��ۼƸ���
	{
		total_fit=total_fit+population.at(i).fit;	
	}

	for(int j=0;j<pop_num;j++)						//��������ݶ�
	{
		div_fit_pro=population.at(j).fit/total_fit;
		total_div_fit=total_div_fit+div_fit_pro;
/*************************���������Ӧ�Ⱥ͸�������ݶ�********************************/
/*
		cout<<"population.at()������Ӧ��="<<population.at(j).fit<<"  "<<total_div_fit<<endl;
/*************************************************************************************************/
		total_gr.push_back(total_div_fit);
/**************************��������ݶ�**********************************************/	

//		cout<<"�����ݶ�"<<total_gr.at(j)<<endl;			
	}
	
	index=0;
	for(int k=0;k<pop_num;k++)					//��ѡpop_num������
	{

//		srand(time(NULL)+k*k);                	/*����������������ӣ��˴����ܸ����ӣ�Ҫ��Ȼ���������������ֵ*/
		/*��������������ѡ��ģ����ǻ����ı仯�ǻ����ģ�������Ϊ��ֵ�ǲ����*/
	
		index=rand()%10000;
		index=index/10000.0;
		
//		cout<<"index="<<index<<endl;
		
		for(int t=0;t<pop_num;t++)				//����Ⱥѡ���ϸ��ʵĸ���
		{
			if(total_gr.at(t)>=index)
			{
				parent.push_back(population.at(t));	

//				cout<<"���"<<t<<"  ";	//�������	����������������ʲ���ʱ��

				break;				
			}	
		}
		
//		cout<<parent.at(k).length<<endl;	//�������	����������������ʲ���ʱ��

/*********************��ӡ��ѡ����******************************/
/*
		parent.at(k).Calcfit(Distance,citylist);
		cout<<"��ѡ�ĸ���"<<k<<endl;

		parent.at(k).pfdiv();					//��ӡ����
/***************************************************/
	} 
}

//����
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
		
		ii = rand() % (pop_num - w) + w;   //����[i,CityNumber-1]����������
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
//		len=rand()%(27-locus)+2;				//len	2~28-locus	���ƵĻ��������len+1	//��ʼ�������locus		��ֹ����������locus+len
		locus=rand()%27+2;					//Ч������ locus=2~29  len=0~26
		len=rand()%(29-locus);	
		
//		locus=rand()%29+1;
//		len=rand()%(30-locus);
													
/***************************************************/
/*		
		cout<<"locus="<<locus<<endl;
		cout<<"len="<<len<<endl;
/***************************************************/
		
		
		for(int j=0;j<30;j++)					//����Ⱦɫ��
		{
			tmp=(locus+len+j+1)%30;
			tmpchro1[j]=tmpdiv1.a[tmp];
			tmpchro2[j]=tmpdiv2.a[tmp];
					
		}

/***************************************************/
/*
		cout<<"����1Ⱦɫ��"<<endl;
		for(int q=0;q<30;q++)
		{
			cout<<tmpchro1[q]<<" ";
		}
		cout<<endl;
		cout<<"����2Ⱦɫ��"<<endl;
		for(int w=0;w<30;w++)
		{
			cout<<tmpchro2[w]<<" ";
		}
/***************************************************/


		for(int k=0;k<len+1;k++)							//�޳�����Ƭ��
		{
			for(int t=0;t<30;t++)							//Ѱ�ҷ��������Ļ���
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
		cout<<"����1�Ļ���Ƭ��"<<endl;		
		for(int c=locus;c<locus+len+1;c++)
		{
			cout<<tmpdiv4.a[c]<<"  ";
		}

		cout<<endl;
		cout<<"����2����Ƭ��"<<endl;					//������ ������ƻ���Ƭ��
		for(int b=locus;b<locus+len+1;b++)
		{
			cout<<tmpdiv3.a[b]<<"  ";
		}

		cout<<endl;		
		cout<<"����1ʣ�����Ƭ��"<<endl;
		for(int a=0;a<30-len-1;a++)
		{
			cout<<tmpchro1[a]<<"  ";
		}

		cout<<endl;
		cout<<"����2ʣ�����Ƭ��"<<endl;

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
		
/*********************��������ĸ���******************************/
/*		
		cout<<"��������1"<<" "<<i<<endl;
		
		child.at(i).pfdiv();
		cout<<"��������2"<<" "<<i+1<<endl;
		
		child.at(i+1).pfdiv();
/***************************************************/		
	}
}

//ͻ��
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

			locus=rand()%(27)+2;	//locus  1~26		//Ч������
			len=rand()%(29-locus);	//len	2~28-locus	���ƵĻ��������len+1	//��ʼ�������locus	��ֹ����������locus+len
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
			cout<<endl<<"Ⱦɫ������Ƭ��"<<endl;		
			for(int b=0;b<len+1;b++)					//���Ⱦɫ������Ƭ��
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
		cout<<"�����������"<<endl;
		population.at(i).pfdiv();

/***************************************************/
	}
}

//������Ӧ��
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
		Evolution();						//������Ӧ��
		Select();						//ѡ������
		Crossover();						//��������
		Mutation();						//��������
	}
}


