//#include<iostream.h>
#include "GA.h"
//#include <iostream> 
//using namespace std; 
int coordinate[30][2] ={									//将所有城市的坐标放进数组,
	41,94,37,84,54,67,25,62,		//每一行放一组坐标
		7,64,2,99,68,58,71,44,54,		
		62,83,69,64,60,18,54,22,
		60,83,46,91,38,25,38,24,
		42,58,69,71,71,74,78,87,
		76,18,40,13,40,82,7,62,32,
		58,35,45,21,41,26,44,35,4,50
						};



int main(){
	CGA a;
	int city[30];
	a.InitCityList(&coordinate[0][0],30);     //初始化城市列表
	a.Start();
	int min = a.Output(city,30);
	cout<<"lenth = "<<min<<endl;
	cout<<"city:"<<endl;
	for(int i=0;i<29;i++){
		cout<<city[i]<<"->";
	}
	cout<<city[29]<<endl;
	return 0;
}
