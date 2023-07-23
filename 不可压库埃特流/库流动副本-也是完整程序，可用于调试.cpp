#include<iostream>
using namespace std;

const int NX=21;       //x方向几个网格点 
const int NY=21;
double dy,dt,rho,ue,D,niu,Re;
double a[NX-2][NY-2],a1[NX-2][NY-2],K[NX-2],K1[NX-2];

double u[NX];
double A,B,E;


int main()
{
/*
	niu = 1e-3;
	rho = 1000;
	ue = 1;
	D = 1;
	*/
//	Re = (rho*ue*D)/niu; //计算雷诺数;
	ue = 1;
	D = 1; 
	Re = 5000;	
	dy = D/(NY-1);//NY-1表示为 NY-1个网格空 
//	dt = 0.001;
	E = 1;
dt = E*Re*(dy)*dy;

	
	//dy = D/(NY);
	//dt = 0.001;		//设置 dy、dt; 
	
	
	//A = -(dt)/(2*(dy)*(dy)*Re);
	//B = 1+(dt)/((dy)*(dy)*Re); //计算系数矩阵,并且是定值 
	
	A= -E/2;  //计算系数矩阵,并且是定值
	B=1+E; 
	
	//cout << A << endl;
	//cout << B << endl;
	
//	K[i] = (1-(dt)/((dy)*(dy)*Re))*uo[i] + ((dt)/(2*dy*Re))/(uo[i+1]-uo[j-1]);//计算 K矩阵(主要由 uo 矩阵构成);

//=========================第一次初始化值===============================================//	
	
	//初始化系数矩阵的主对角线 (内流场值) 
	
		for(int i=0;i<NX-2;i++)
	{
		for(int j=0;j<NY-2;j++)
		{
		if(i==j)
		{
		  
			a[i][j] = B;
	    }

		}

	}
	
	//初始化系数矩阵的下对角线 (内流场值)
	 
	 	for(int i1=0;i1<NX-2;i1++)
	{
		for(int j1=0;j1<NY-2;j1++)
		{
	         if(i1==j1+1)
	         
	        {
	        	a[i1][j1] = A;
	        	
			}
	
		}

	}
	
	//初始化系数矩阵的上对角线 (内流场值) 
	
	
	for(int i2=0;i2<NX-2;i2++)
	{
		for(int j2=0;j2<NX-2;j2++)
		{
	         if(i2==j2-1)
	         
	        {
	        	a[i2][j2] = A;
	        	
			}
	
		}

	}
	//复制原矩阵 
		for(int i=0;i<NX-2;i++)
	{
		for(int j=0;j<NX-2;j++)
		{
		
	
	      a1[i][j] = a[i][j];
	
		}

	}
	
	
/*输出修改前的数据		
for(int i2=0;i2<NX-2;i2++)
	{
		for(int j2=0;j2<NX-2;j2++)
		{
	         cout << a[i2][j2]<<"===";
	
		}
      cout << endl;
	
	}
*/
//============================对系数矩阵初始化 

//对速度初始化 (对所有网格点上的速度初始化，从速度最高的顶盖开始)
   for(int i=NX-2;i>=0;i--)
   {
   	u[NX-1] = ue;
   	u[i] = 0;
	 }	
int t=0;	 
for(int t0=0;t0<1e4;t0++)
{
  
  //cout << t<< endl;
//对K值初始化
   for(int i=0;i<NX-2;i++)
   {
   	
   	K[i] = (1-E)*u[i+1]+(E/2)*(u[i+2]+u[i]);
   	if(i==NX-3)
   	{
   		K[i] = K[i]-A;
	   }
	
	} 
	/*
	if(i==2)
	{
		for(int i=0;i<NX-2;i++)
   		cout << K[i] << endl;		
	}
	*/
//复制 K矩阵为 K1 
 for(int i=0;i<NX-2;i++)
   {
   	
   	K1[i] = K[i];
   	
	} 
		

	
//for(int i=0;i<NX-2;i++)	
//cout << K[i] << endl;

	for(int i=1;i<NX-2;i++)
	{
		for(int j=0;j<NY-2;j++)
		{
		if(i==j)
		{
		  
			a[i][j] = a1[i][j] - (a1[i][j-1])*(a1[i-1][j])/a[i-1][j-1]; //要赋值原矩阵; 
	    }

		}

	}

//修改K值 
for(int i=1;i<NX-2;i++)
{
	
	
	K[i] = K1[i]- K[i-1]*a1[i][i-1]/a[i-1][i-1];
	
	
 } 	
/* 
for(int i=0;i<NX-2;i++)
{
	
	
cout << K[i] << "==";
	
	
 } 
*/


	//cout << a[2][2]; 
		
//输出全部数组 
/*
for(int i2=0;i2<NX-2;i2++)
	{
		for(int j2=0;j2<NX-2;j2++)
		{
	         cout << a[i2][j2]<<"===";
	
		}
      cout << endl;
	
	}
*/	

u[NX-2] = K[NX-3]/a[NX-3][NX-3];
/*
if(t==3)
{
cout<<u[NX-2] << endl;
}
*/

for(int j=NX-3;j>0;j--)
{
	
	u[j] = (K[j-1]-a1[j-1][j]*u[j+1])/a[j-1][j-1]; //算发散的原因就是：原本是 (1-x)/y类型   却写成了 1-x/y; 
	
 } 
 /*
 if(t==3)
 {
 	cout << K[17] << "  " << a1[17][18] << "  " << u[19] << " "<<a[17][17];
 }
 */
 for(int i=0;i<NX-2;i++)
	{
		for(int j=0;j<NX-2;j++)
		{
		
	
	      a[i][j] = a1[i][j];
	
		}

	}
//t = t+1;
 
}
 

 for(int j=NX-2;j>0;j--)
{
	cout << u[j] <<"===";
	
	
 } 

 



return 0; 
}
