#include<iostream>
//#include<simplecpp>
#include<cstdlib>
#include<cmath>
#include"Polynomial.h"
//#include"quicksort.h"
using namespace std;

double Polynomial :: valueAt(const double a)
{	
	double sum=0;
	for(int i=0;i<n;i++)
	{
		sum += cof[i]*pow(a,deg[i]);
	}
	return sum;
}



double Polynomial :: valueat(const double a)
{	
	double sum=0;
	for(int i=0;i<n;i++)
	{
		sum += cof[i]*pow(a,deg[i]);
	}
	return sum;
}

bool Polynomial :: is_root(double a, double b)
{	double mid,epsilon=1e-10;

	bool a_is_positive,mid_is_positive;
	a_is_positive = valueat(a) > 0 ;
	if(valueat(a)<=epsilon && valueat(a)>= - epsilon)	return  true;
	else if(valueat(b)<=epsilon && valueat(b)>= - epsilon)	return  true;
	else if(valueat(a)*valueat(b)>0)	return  false;
	else return true;

}

double Polynomial :: rootbetween(double a, double b)
{	double mid,epsilon=1e-10;

	bool a_is_positive,mid_is_positive;
	a_is_positive = valueat(a) > 0 ;
	if(valueat(a)<=epsilon && valueat(a)>= - epsilon)	return a;
	else if(valueat(b)<=epsilon && valueat(b)>= - epsilon)	return b;
	else if(valueat(a)*valueat(b)>0)	return 0;
	else
	{
		while(valueat(a) > epsilon || valueat(a) < -epsilon )
		{
			mid=a+(b-a)/2;
			mid_is_positive = valueat(mid) > 0 ;
			if(a_is_positive == mid_is_positive)
				a=mid;
			else
				b=mid;
		}
		return a;
	}
}

void Polynomial :: roots()
{
	int x = 0;
	int range = 100000;
	if(deg[n-1]>2)
	{
		Polynomial d;
		d=derivative();
		//d.print();
		//print();
		root = new double[d.numroots+1];
		int k = 0 ;
		if(cof[n-1]>0)
		{
			if(deg[n-1]%2==0)
			{
				
				if(valueat(d.root[0])<0)
				{
					double x = d.root[0];
					while(valueat(x)<0)
						x = x-range;
					root[k] = rootbetween(x,x+range);
					k++;
				}
			}
			else
			{
				if(valueat(d.root[0])>0)
				{
					double x = d.root[0];
					while(valueat(x)>0)
						x = x-range;
					root[k] = rootbetween(x,x+range);
					k++;
				}
			}
		}
		else
		{	
			if(deg[n-1]%2==0)
			{
				if(valueat(d.root[0])>0)
				{
					double x = d.root[0];
					while(valueat(x)>0)
						x = x-range;
					root[k] = rootbetween(x,x+range);
					k++;
				}
			}
			else
			{
				if(valueat(d.root[0])<0)
				{
					double x = d.root[0];
					while(valueat(x)<0)
						x = x-range;
					root[k] = rootbetween(x,x+range);
					k++;
				}
			}
		}
		int i = 0;
		while( i< d.numroots-1)
		{
			if(is_root(d.root[i],d.root[i+1]))
			{
				root[k] = rootbetween(d.root[i],d.root[i+1]);
				k++;
			}
			i++;
		}
		if(cof[n-1]>0)
		{
			if(valueat(d.root[d.numroots-1])<0)
			{
				double x = d.root[d.numroots-1];
				while(valueat(x)<0)
					x = x+range;
				root[k] = rootbetween(x-range,x);
				k++;
			}
		}
		else
		{
			if(valueat(d.root[0])>0)
			{
				double x = d.root[0];
				while(valueat(x)>0)
					x = x+range;
				root[k] = rootbetween(x-range,x);
				k++;
			}
		}
		numroots = k;
		double arr[numroots];
		for(i=0;i<numroots;i++)
			arr[i]=root[i];
		delete []root;
		root = new double [numroots];
		for(i=0;i<numroots;i++)
			root[i]=arr[i];
	}
	else
		if(deg[n-1]==2)
		{

			Polynomial d;
			d = derivative();
			if(cof[n-1]>0)
			{	if(valueat(d.root[0])>0)
				{
					
					numroots = 0;
					root = new double[numroots];
				}
				else
				{
					numroots = 2;
					root = new double[numroots];
					double x = d.root[0];
					while(valueat(x)<0)
						x = x-range;
					root[0] = rootbetween(x,x+range);
					x = d.root[0];
					while(valueat(x)<0)
						x = x+range;
					root[1] = rootbetween(x-range,x);
				}
			}
			else
			{
				if(valueat(d.root[0])<0)
				{
					numroots = 0;
					root = new double[numroots];
				}
				else
				{
					numroots = 2;
					root = new double[numroots];
					double x = d.root[0];
					while(valueat(x)>0)
						x = x-range;
					root[0] = rootbetween(x,x+range);
					x = d.root[0];
					while(valueat(x)>0)
						x = x+range;
					root[1] = rootbetween(x-range,x);
				}
			}
		}
		else
			if(deg[n-1]==1)
			{
				numroots = 1;
				root = new double [numroots];
				if(n==1)
					root[0] = 0;
				else
					{
						root[0]=-cof[0]*1.0/cof[1];
					}

			}
			else
			{
				numroots = 1;
				root = new double [numroots];
				root[0] = 0;
			}
	//print_root();
	if(numroots>1)
	{
		double arr[numroots];
		int k = 0;
		int i = 0;
		while(i < numroots -1)
		{
			while(root[i]==root[i+1])
			{
				i++;
				if(i == numroots-1)
					break;
			}
			arr[k] = root[i];
			k++;
			i++;
		}
		if(arr[k-1]!=root[numroots-1])
		{
			arr[k] = root[numroots-1];
			k++;
		}
		numroots = k;
		delete [] root;
		root = new double[numroots];
		for(i=0;i<numroots;i++)
			root[i] = arr[i];
	}
	//print_root();
}

void Polynomial :: print_root()
{
	for(int i=0; i<numroots;i++)
		cout<<root[i]<<" ";
	cout<<endl;
}

double Polynomial :: maximum (double x1, double x2)
{

	int num;
	Polynomial d=derivative();
	d.roots();
	int i=0;
	while(d.root[i]<x1)	i++;
	int j=d.numroots-1;
	while(d.root[j]>x2) j--;
	num = (j-i+1) + 2;
	double k[num];
	k[0]=x1;
	k[num-1]=x2;
	for(int x=1;x<num-1;x++)
		k[x] = d.root[i+x-1];
	int max;
	max=valueat(k[0]);
	for(int x=1;x<num;x++)
	{
		if(valueat(k[x])>max)	max=valueat(k[x]);
	}
	return max;
}

double Polynomial :: minimum (double x1, double x2)
{
	int num;
	Polynomial d=derivative();
	d.roots();
	int i=0;
	while(d.root[i]<x1)	i++;
	int j=d.numroots-1;
	while(d.root[j]>x2) j--;
	num = j-i+1 + 2;
	double k[num];
	k[0]=x1;
	k[num-1]=x2;
	for(int x=1;x<num-1;x++)
		k[x] = d.root[i+x-1];
	int min;
	min=valueat(k[0]);
	for(int x=1;x<num;x++)
	{
		if(valueat(k[x]) < min)
			min=valueat(k[x]);
	}
	return min;
}

double absolute(double x)
{
	if(x>0)
		return x;
	else
		return -x;
}

/*void Polynomial :: plot(double x1, double x2)
{
	double y1 = minimum(x1,x2);
	double y2 = maximum(x1,x2);
	cout<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<endl;

	double screen_width=600;
	double &screen_height=screen_width;
	initCanvas("Polynomial",screen_width,screen_height);
	Line L1(0,screen_height/2,screen_width,screen_height/2), L2(screen_width/2,0,screen_width/2,screen_height);
	//Line a(x1+(screen_width/2),100,x1+(screen_width/2),screen_height);
	//a.imprint();
	double k = absolute(x1);
	if(absolute(x2)>k)	k = absolute(x2);
	if(absolute(y1)>k)	k = absolute(y1);
	if(absolute(y2)>k)	k = absolute(y2);
	cout<<k<<endl;
	double factor = screen_width/(2*k);
	double x = x1;
	//double y = -valueat(x);
	double dx = 0.001;
	double dy = -derivative().valueat(x)*dx;
	while( x < x2 )
	{	Circle c(x*factor + (screen_width/2),(-valueat(x))*factor+(screen_height/2),1);
		c.penDown();
		c.move(dx*factor,(-valueat(x+dx)+valueat(x))*factor);

		//Line L(x*factor+(screen_width/2),(-valueat(x))*factor+(screen_height/2),(x+dx)*factor+(screen_width/2),(-valuat(x+dx))*factor+(screen_height/2));
		//L.imprint();
		//Line b(x1*factor+(screen_width/2),200,x1+(screen_width/2),screen_height-200);

		x = x+dx;
		//y = -valueat(x);
	}
	wait(20);
}*/


void Polynomial :: operator = (const Polynomial & p)
{

	n = p.n;
	deg = new int[n];
	cof = new double [n];
	for(int i=0;i<n;i++)
	{
		deg[i] = p.deg[i];
		cof[i] = p.cof[i];
	}
	if(p.numroots != -50)
	{	numroots = p.numroots;
		root = new double[numroots];
		for(int i =0;i<numroots;i++)
			root[i] = p.root[i];
	}
	
	//print();
}

