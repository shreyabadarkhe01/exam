/*
Name: Alwis Shaji
Roll no: COBA001

Write a program to implement Parallel Bubble Sort. Use existing algorithms
and measure the performance of sequential and parallel algorithms.
*/
#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include<chrono>


using namespace std;

void bubble(int *, int);
void swap(int &, int &);

void bubble(int *a, int n)
{
 	for( int i = 0; i < n; i++ )
 	{ 
 	int first = i % 2; 
 	#pragma omp parallel for shared(a,first)
 	for( int j = first; j < n-1; j += 2 )
 	{ 
 		if( a[ j ] > a[ j+1 ] )
 		{ 
 			swap( a[ j ], a[ j+1 ] );
 		} 
 	} 
 	}
}

void swap(int &a, int &b)
{
 	int test;

 	test=a;
 	a=b;
 	b=test;
}


void merge(int* arr, int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
 
    int L[n1],R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];
 
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


 
void mergeSort(int* arr, int left, int right) {
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;

    #pragma omp parallel sections num_threads(2)
    {
        #pragma omp section
        {
            mergeSort(arr, left, middle);
        }

        #pragma omp section
        {
            mergeSort(arr, middle + 1, right);
        }
    }

    merge(arr, left, middle, right);
}





int main()
{
 	int n=6;
    int a[n] = { 12, 11, 13, 5, 6, 7 };
    auto start = chrono::high_resolution_clock::now();
    bubble(a, n);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> bubbleTime = end - start;

    cout << "Bubble sort execution time: " << bubbleTime.count() << " seconds" << endl; 
 	cout<<"\n sorted array is=>";
 	for(int i=0;i<n;i++)
 	{
 		cout<<a[i]<<" ";
 	}
    cout<<endl;

       


        int N=6;
    int arr[N] = { 12, 11, 13, 5, 6, 7 };
   
 
    start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, N - 1);
     end = chrono::high_resolution_clock::now();

    chrono::duration<double> mergeTime = end - start;

    cout << "Merge sort execution time: " << mergeTime.count() << " seconds" << endl;
 
    cout << "Sorted array: ";
    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;


return 0;
}