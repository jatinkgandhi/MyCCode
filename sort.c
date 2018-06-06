#include <stdio.h>

void swap (int *a, int *b)
{
	int t;
#ifdef DEBUG
	printf("swap : %d, with %d\n",*a, *b);
#endif
	t = *a;
	*a = *b;
	*b = t;
	
}

void printarr(int *arr, int n)
{
	int loop;
	for(loop = 0; loop < n; loop++)
	{
		printf("%d, ", arr[loop]);
	}
	printf("\n");
}


void bubblesort(int *arr, int n)
{
	int outer, inner;

	for(outer = 0; outer < n -1 ; outer++)
	{
		for(inner = 0; inner < n - outer - 1; inner++)
		{
			if(arr[inner] > arr[inner+1])
			{
				swap(&arr[inner], &arr[inner+1]);
			}
#ifdef DEBUG
			printarr(arr,n);
#endif
		}
	}
}
void recursive_bubblesort(int *arr, int n)
{
	int inner;

	if (1 == n) return;

	for(inner = 0; inner < n - 1; inner++)
	{
		if(arr[inner] > arr[inner+1])
		{
			swap(&arr[inner], &arr[inner+1]);
		}
	}
	recursive_bubblesort(arr, n - 1);
}
void selectionsort(int *arr, int n)
{
	int outer, inner, min;

	for(outer = 0; outer < n -1 ; outer++)
	{
		min = outer;
#ifdef DEBUG
		printf("outer min = %d\n",min);
#endif
		for(inner = outer + 1; inner < n; inner++)
		{
			if(arr[inner] < arr[min])
			{
				min = inner;
#ifdef DEBUG
				printf("inner min = %d\n",min);
#endif
			}
			swap(&arr[min], &arr[outer]);


#ifdef DEBUG
			printarr(arr,n);
#endif
		}
	}

}

void insertionsort(int *arr, int n)
{
	int outer, inner, key;

	for(outer = 1; outer < n; outer++)
	{
		key = arr[outer];

		inner = outer - 1;
		while(inner >= 0 && arr[inner] > key)
		{
			arr[inner + 1] = arr[inner];

			inner --;
		}

		arr[inner + 1] = key;
	}
}

void insertionsort_recursive(int *arr, int n)
{
	int last, j;

	if(n <= 1) return;
	insertionsort_recursive(arr, n - 1);

	last = arr[n - 1];
	j = n - 2;

	while(j >= 0 && arr[j] > last)
	{
		arr[j+1] = arr[j];
		j --;
	}
	arr[j+1] = last;
}


void merge (int *arr, int l, int m, int r)
{
	int i,j,k;
	int n1 = m - l +1;
	int n2 = r - m;

	int L[n1], R[n2];

	for(i = 0; i < n1; i++)
		L[i] = arr[l + i];

	for(j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	i = 0;
	j = 0;
	k = l;
	while(i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}else
		{
			arr[k] = R[j];
			j++;
		}

		k++;
	}

	while(i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergesort(int *arr, int l, int r)
{
	if(l < r)
	{
		int m = l + (r - l)/2;

		mergesort(arr, l,m);
		mergesort(arr, m+1, r);
		merge(arr, l, m, r);
	}
}

int min(int x, int y) { return (x < y) ? x : y; }
void merge2(int arr[], int l, int m, int r)
{
	int i,j,k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int L[n1], R[n2];

	for(i = 0; i < n1; i++)
		L[i] = arr[l + i];

	for (j = 0; j < n2; j++)
		R[j] = arr[m+1+j];


	i = j = 0;
	k = l;

	while(i < n1 && j < n2)
	{
		if(L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}else
		{
			arr[k] = R[j];
			j++;
		}

		k++;
	}

	while(i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergesort_iterative(int *arr, int n)
{
	int curr_size;
	int left_start;
	
	for(curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
	{
		for(left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
		{

			int mid = left_start + curr_size - 1;
			int right_end = min(left_start + 2 * curr_size - 1, n - 1);

			merge2(arr, left_start, mid , right_end);
		}
	}
}

typedef void (*sortalgo)(int *arr, int n);

void ExecuteAlgo(char *name, sortalgo algo, int *arr, int n)
{
	printf("Algorithm: %s\n",name);

	printf("Before sorting...\n");
	printarr(arr, n);
	algo(arr, n);
	printf("After sorting...\n");
	printarr(arr, n);
}

#define ARRAYSIZE(a)	(sizeof(a)/sizeof(a[0]))
int main(int argc, char **argv)
{

	int array[] = { 6, 4, 2, 5, 3, 1};


	ExecuteAlgo("bubblesort",    bubblesort,    array, ARRAYSIZE(array));

	array[0] = 6, array[1] = 4, array[2] = 2, array[3] = 5, array[4] = 3, array[5] = 1;
	ExecuteAlgo("selectionsort", selectionsort, array, ARRAYSIZE(array));

	array[0] = 6, array[1] = 4, array[2] = 2, array[3] = 5, array[4] = 3, array[5] = 1;
	ExecuteAlgo("recursive_bubblesort", recursive_bubblesort, array, ARRAYSIZE(array));

	array[0] = 5, array[1] = 4, array[2] = 1, array[3] = 9, array[4] = 6, array[5] = 2;
	ExecuteAlgo("insertionsort", insertionsort, array, ARRAYSIZE(array));

	array[0] = 5, array[1] = 4, array[2] = 1, array[3] = 9, array[4] = 6, array[5] = 2;
	ExecuteAlgo("insertionsort recursive", insertionsort_recursive, array, ARRAYSIZE(array));



	array[0] = 6, array[1] = 4, array[2] = 1, array[3] = 2, array[4] = 8, array[5] = 3;
	printf("Before sorting...\n");
	printarr(array, ARRAYSIZE(array));
	mergesort(array, 0, ARRAYSIZE(array) - 1);
	printf("After sorting...\n");
	printarr(array, ARRAYSIZE(array));



	array[0] = 5, array[1] = 2, array[2] = 7, array[3] = 9, array[4] = 8, array[5] = 1;
	ExecuteAlgo("iterative mergesort", mergesort_iterative, array, ARRAYSIZE(array));
	return 0;
}

