#include<iostream>
using namespace std;

const int NX=21;       //x���򼸸������ 
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
//	Re = (rho*ue*D)/niu; //������ŵ��;
	ue = 1;
	D = 1; 
	Re = 5000;	
	dy = D/(NY-1);//NY-1��ʾΪ NY-1������� 
//	dt = 0.001;
	E = 1;
dt = E*Re*(dy)*dy;

	
	//dy = D/(NY);
	//dt = 0.001;		//���� dy��dt; 
	
	
	//A = -(dt)/(2*(dy)*(dy)*Re);
	//B = 1+(dt)/((dy)*(dy)*Re); //����ϵ������,�����Ƕ�ֵ 
	
	A= -E/2;  //����ϵ������,�����Ƕ�ֵ
	B=1+E; 
	
	//cout << A << endl;
	//cout << B << endl;
	
//	K[i] = (1-(dt)/((dy)*(dy)*Re))*uo[i] + ((dt)/(2*dy*Re))/(uo[i+1]-uo[j-1]);//���� K����(��Ҫ�� uo ���󹹳�);

//=========================��һ�γ�ʼ��ֵ===============================================//	
	
	//��ʼ��ϵ����������Խ��� (������ֵ) 
	
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
	
	//��ʼ��ϵ��������¶Խ��� (������ֵ)
	 
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
	
	//��ʼ��ϵ��������϶Խ��� (������ֵ) 
	
	
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
	//����ԭ���� 
		for(int i=0;i<NX-2;i++)
	{
		for(int j=0;j<NX-2;j++)
		{
		
	
	      a1[i][j] = a[i][j];
	
		}

	}
	
	
/*����޸�ǰ������		
for(int i2=0;i2<NX-2;i2++)
	{
		for(int j2=0;j2<NX-2;j2++)
		{
	         cout << a[i2][j2]<<"===";
	
		}
      cout << endl;
	
	}
*/
//============================��ϵ�������ʼ�� 

//���ٶȳ�ʼ�� (������������ϵ��ٶȳ�ʼ�������ٶ���ߵĶ��ǿ�ʼ)
   for(int i=NX-2;i>=0;i--)
   {
   	u[NX-1] = ue;
   	u[i] = 0;
	 }	
int t=0;	 
for(int t0=0;t0<1e4;t0++)
{
  
  //cout << t<< endl;
//��Kֵ��ʼ��
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
//���� K����Ϊ K1 
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
		  
			a[i][j] = a1[i][j] - (a1[i][j-1])*(a1[i-1][j])/a[i-1][j-1]; //Ҫ��ֵԭ����; 
	    }

		}

	}

//�޸�Kֵ 
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
		
//���ȫ������ 
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
	
	u[j] = (K[j-1]-a1[j-1][j]*u[j+1])/a[j-1][j-1]; //�㷢ɢ��ԭ����ǣ�ԭ���� (1-x)/y����   ȴд���� 1-x/y; 
	
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
