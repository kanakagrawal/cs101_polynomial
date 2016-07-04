#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int good_pivot(int *a, int l, int r)
{	
	int size = r-l+1;
	 srand(time(NULL));
	int k = rand()%size;
	return l+k;
}

int partition(int* a,double *b,int l, int r,int pivot)
{
	int i=l+1;
	for(int j=l+1;j<=r;j++)
	{
		if(a[j]<pivot)
		{	if(i<=r)
			{
				swap(a[i],a[j]);
				swap(b[i],b[j]);
				i++;	
			}
		}
	}
	if(i==r && a[i]<pivot)
	{	
		swap(a[i],a[l]);
		swap(b[i],b[l]);
		return i;
	}
	else
	{
		swap(a[i-1],a[l]);
		swap(b[i-1],b[l]);
		return i-1;
	}
}

void quicksort(int *a, double *b,int l, int r)
{
	if(r>l)
	{
		int pivot_position = good_pivot(a,l,r);
		int pivot = a[pivot_position];
		swap(a[l],a[pivot_position]);
		swap(b[l],b[pivot_position]);
		pivot_position = partition(a,b,l,r,pivot);
		quicksort(a,b,l,pivot_position - 1);
		quicksort(a,b,pivot_position + 1,r);

	}
	
}