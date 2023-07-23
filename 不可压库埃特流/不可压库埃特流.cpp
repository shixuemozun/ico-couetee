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
//复制系数矩阵 
	for(int i=0;i<NX-2;i++)
	{
		for(int j=0;j<NX-2;j++)
		{
		
	
	      a1[i][j] = a[i][j];
	
		}

	}

//============================对系数矩阵初始化 

//对速度初始化 (对所有网格点上的速度初始化，从速度最高的顶盖开始)
   for(int i=NX-2;i>=0;i--)
   {
   	u[NX-1] = ue;
   	u[i] = 0;
	 }	
	 



//对K值初始化
   	E = 1;
   A= -E/2;  //计算系数矩阵,并且是定值
	B=1+E;
 for(int t=1;t<1000;t++)
 {
 	
 	E = 1;
   A= -E/2;  //计算系数矩阵,并且是定值
	B=1+E;
     
   for(int i=0;i<NX-2;i++)
   {
   	
   	K[i] = (1-E)*u[i+1]+(E/2)*(u[i+2]+u[i]);
   	if(i==NX-3)  //最后面的矩阵为 K-A 
   	{
   		K[i] = K[i]-double(A);
	   }
   	
	} 
	
	//复制 K矩阵为 K1 
 for(int i=0;i<NX-2;i++)
   {
   	
   	K1[i] = K[i];
   	
	} 
//cout << K[NX-1] << endl;	 
//==========================================================================================//

//==========================托马斯算法=====================================//

//改变主对角线上的数值(第一行是不变的)


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

	
//修改 K 矩阵(第一行是不变的)

	
for(int i=1;i<NX-2;i++)
{
	
	
	K[i] = K1[i]- K[i-1]*a1[i][i-1]/a[i-1][i-1];
	
	
 } 	
 	
 
/*	
//修改下对角线后的矩阵

	for(int i1=1;i1<9;i1++)
	{
		for(int j1=0;j1<9;j1++)
		{
	         if(i1==j1+1)
	         
	        {
	        	a[i1][j1] = 0;
	        	
			}
	
		}

	}	
*/	
	
//求解此时速度

u[NX-2] = K[NX-3]/a[NX-3][NX-3];//获得第一个初始条件解 

for(int j=NX-3;j>0;j--)
{
	
	u[j] = (K[j-1]-a1[j-1][j]*u[j+1])/a[j-1][j-1];//算发散的原因就是：原本是 (1-x)/y类型   却写成了 1-x/y; 
	
 } 

//处理上下边界的速度

u[0] = 0;
u[NX-1] = ue; 	


/*
for(int j=NX-1;j>=0;j--)
{
	cout << u[j] <<endl;
	
	
 } 
*/

/*
//输出这一时刻下的速度分布
u[NX+1] = 1; 
for(int j=0;j<NX+2;j++)
{
	
	cout << u[j] << endl;
	}	
*/	

/*
for(int j=NX-1;j>=0;j--)
{
	cout << u[j] <<endl;
	
	
 } 	
*/	

for(int i=0;i<NX-2;i++)
	{
		for(int j=0;j<NX-2;j++)
		{
		
	
	      a[i][j] = a1[i][j];
	
		}

	}
 








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
}
for(int j=NX-1;j>=0;j--)
{
	cout << u[j] <<endl;
	
	
 } 


	return 0;
}
