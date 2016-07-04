#include<iostream>
//#include<simplecpp>
#include<cstdlib>
#include<cmath>
#include"Polynomial.h"
#include"quicksort.h"
using namespace std;


Polynomial :: Polynomial()
{
	n = 1;
	deg = new int[n];
	cof = new double[n];
	deg[0] = 0;
	cof[0] = 0;
}

Polynomial :: ~Polynomial()
{
	delete [] deg;
	delete [] cof;
		
}

Polynomial :: Polynomial(const Polynomial &source)
{
	
	n = source.n;
	deg = new int [n];
	cof = new double [n];
	for(int i = 0; i<n; i++)
	{
		deg[i] = source.deg[i];
		cof[i] = source.cof[i];
	}
	if( source.numroots != -50)
	{
		numroots = source.numroots;
		root = new double [numroots];
		for(int i = 0; i<numroots; i++)
			root[i] = source.root[i];
	}
}

void Polynomial :: read(){
	//cout<<"Enter the number of terms"<<endl;
	cin>>n;
	deg = new int [n];
	cof = new double [n];
	for(int i=0;i< n;i++)
	{
		cin>>deg[i]>>cof[i];
	}
	if(n>1)
		quicksort(deg,cof,0,n-1);		// to sort the deg and cof array such that they deg is in increasing order and cof[i] corresponds coefficient of x^deg[i]
	roots();							// to calculate roots and put in root array
}

void Polynomial :: print()
{
	if(deg[0]!=0)
		if(cof[0]>0)
			cout<<cof[0]<<"x^"<<deg[0];
		else
			cout<<cof[0]<<"x^"<<deg[0];
	else
		if(cof[0]>0)
			cout<<cof[0];
		else
			cout<<cof[0];
	for(int i=1;i<n;i++)
	{
		if(cof[i]>0)
			cout<<" + "<<cof[i]<<"x^"<<deg[i];
		else
			cout<<" - "<<-cof[i]<<"x^"<<deg[i];
	}
	cout<<endl;
}

Polynomial Polynomial :: derivative()
{	Polynomial d;
	if(deg[n-1]>=1)
	{
		if(deg[0]==0)
		{
			d.n = n-1;
			d.cof=new double[d.n];
			d.deg = new int[d.n];
			for(int i = 1;i<n;i++)
			{
				d.deg[i-1] = deg[i] - 1;
				d.cof[i-1] = cof[i]*deg[i];
			}
		}
		else
		{

			d.n=n;
			d.cof=new double[d.n];
			d.deg = new int[d.n];

			for(int i = 0;i<d.n;i++)
			{
				d.deg[i] = deg[i] - 1;
				d.cof[i] = cof[i]*deg[i];
			}

		}
	}
	else
	{
		d.n = 1;
		d.cof=new double[d.n];
		d.deg = new int[d.n];
		d.deg[0]=0;
		d.cof[0]=0;
	}
	d.roots();
	//d.print_root();
	//d.print();
	//cout<<d.numroots<<endl;
	return d;
}

Polynomial Polynomial :: integral()			//Initially I used rand() to generate constant of integration but in testcases constant of integration was not considered so i removed it
{
	Polynomial i;
	i.n = n;
	i.cof=new double[i.n];
	i.deg = new int[i.n];
	for(int k=0; k< i.n ;k++)
	{
		i.deg[k] = deg[k] +1;
		i.cof[k] = cof[k]/i.deg[k];
	}
	i.roots();
	return i;
}

Polynomial Polynomial :: operator + (const Polynomial &p)				//debugging required in addition
{

	Polynomial sum;
	sum.n = n+p.n;

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<p.n;j++)
		{
			if(deg[i]==p.deg[j])
			{	sum.n --;
				if(cof[i]+p.cof[j]==0)
					sum.n--;
			}
		}
	}
	sum.deg = new int [sum.n];
	sum.cof = new double [sum.n];

	int k = 0,i=0,j=0;
	while(i<n && j<p.n && k<sum.n)
	{
			if(deg[i]<p.deg[j])
			{
				sum.deg[k]=deg[i];
				sum.cof[k]=cof[i];
				k++;
				i++;
			}
			else
				if(deg[i]>p.deg[j])
				{
					sum.deg[k]=p.deg[j];
					sum.cof[k]=p.cof[j];
					k++;
					j++;
				}
				else
				{
					if(cof[i]+p.cof[j]!=0)
					{
						sum.deg[k]=deg[i];
						sum.cof[k]=cof[i]+p.cof[j];
						k++;

					}
					i++;
					j++;
				}
	}
	if(i<n && j==p.n)
	{
		while( i<n && k<sum.n)
		{
			sum.deg[k]=deg[i];
			sum.cof[k]=cof[i];
			k++;
			i++;
		}
	}
	else
		if(j<p.n && i == n)
		{
			while(j<p.n  && k<sum.n)
			{
				sum.deg[k]=p.deg[j];
				sum.cof[k]=p.cof[j];
				k++;
				j++;
			}
		}
	sum.roots();
	return sum;
}

Polynomial Polynomial :: operator - (Polynomial p)
{
	Polynomial sub;
	sub.n = n+p.n;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<p.n;j++)
		{
			if(deg[i]==p.deg[j])
			{	sub.n --;
				if(cof[i]-p.cof[j]==0)
					sub.n--;
			}
		}
	}
	sub.deg = new int [sub.n];
	sub.cof = new double [sub.n];
	int k = 0,i=0,j=0;
	while(i<n && j<p.n && k<sub.n)
	{
			if(deg[i]<p.deg[j])
			{
				sub.deg[k]=deg[i];
				sub.cof[k]=cof[i];
				k++;
				i++;
			}
			else
				if(deg[i]>p.deg[j])
				{
					sub.deg[k]=p.deg[j];
					sub.cof[k]= - p.cof[j];
					k++;
					j++;
				}
				else
				{
					if(cof[i]-p.cof[j]!=0)
					{
						sub.deg[k]=deg[i];
						sub.cof[k]=cof[i]-p.cof[j];
						k++;

					}
					i++;
					j++;
				}
	}
	if(i<n && j==p.n)
	{
		while( i<n && k<sub.n)
		{
			sub.deg[k]=deg[i];
			sub.cof[k]=cof[i];
			k++;
			i++;
		}
	}
	else
		if(j<p.n && i == n)
		{
			while(j<p.n  && k<sub.n)
			{
				sub.deg[k]=p.deg[j];
				sub.cof[k]= - p.cof[j];
				k++;
				j++;
			}
		}
	sub.roots();
	return sub;
}

Polynomial Polynomial :: operator * (Polynomial p)
{
	Polynomial mult;
	mult.n = n*p.n;
	mult.deg = new int [mult.n];
	mult.cof = new double[mult.n];
	int k=0;
	for(int i = 0; i<n; i++)
	{
		for(int j = 0; j<p.n; j++)
		{
			mult.deg[k] = deg[i] + p.deg[j];
			mult.cof[k] = cof[i]*p.cof[j];
			k++;
		}
	}
	quicksort(mult.deg,mult.cof,0,mult.n-1);
	int power[mult.n];
	double arr[mult.n];
	int i=0;
	k=0;
	//mult.print();
	while(i < mult.n -1)
	{
		while(mult.deg[i]==mult.deg[i+1])
		{
			i++;
			if(i == mult.n-1)
				break;
		}
		power[k] = mult.deg[i];
		k++;
		i++;
	}
	if(power[k-1]!=mult.deg[mult.n-1])
	{
		power[k] = mult.deg[mult.n-1];
		k++;
	}
	
	i = 0;
	for(int x=0;x<mult.n;x++)
		arr[x]=0;
	int x = 0;
	//mult.print();
	while(i<mult.n && x < k)
	{
		if(mult.deg[i]==power[x])
		{
			arr[x] += mult.cof[i];
			i++;
		}
		else
		{
			if(arr[x]==0)
			{
				for(int m = x;m<k-1;m++)
				{
					power[m] = power[m+1];
				}
				k--;
			}
			else
				x++;
		}
	}
	mult.n = k;
	delete [] mult.deg;
	delete [] mult.cof;
	mult.deg = new int[mult.n];
	mult.cof = new double[mult.n];
	for(int i=0;i<mult.n;i++)
	{
		mult.deg[i]=power[i];
		mult.cof[i]=arr[i];
	}
	mult.numroots = -50;		//so that the = operator will no not to copy the roots as they are not initialized
	//mult.print();
	return mult;
}

Polynomial Polynomial :: operator / (Polynomial p)
{
	Polynomial quo,divd;
	divd = *this;							//Copying dividend to polynomial divd
	if(divd.deg[divd.n-1]-p.deg[p.n-1] >= 0)
	{
		quo.n = 1;
		quo.deg = new int[quo.n];
		quo.cof = new double[quo.n];
		quo.deg[quo.n-1] = divd.deg[divd.n-1] - p.deg[p.n -1];
		quo.cof[quo.n-1] = divd.cof[divd.n-1]/p.cof[p.n-1];
		Polynomial x;
		x=quo*p;
		divd = divd - x;
		quo = quo + (divd/p);
	}
	return quo;
}

Polynomial Polynomial :: operator % (Polynomial p)
{
	Polynomial quo,rem,divd = *this;
	quo= divd/p;
	rem =divd - (p*quo) ;
	return rem;
}
