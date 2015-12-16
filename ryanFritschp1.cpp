
//ryanFritschp1.cpp
//09/09/2015
//Milestone #1
//1.0.1


/*
PROJECT 1 Description
This project is designed to take in data sets of exercise patterns
in the form of "steps per day" for multiple individuals, and run an
insertion and merge sort algorithm (both in serial and parallel) on
the data sets, as well as an average number of steps per day calculation
(in serial and parallel).
*/





#include <iostream>
#include <math.h>
#include <fstream>
#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

using namespace std;

static long num_steps = 100000000;
#define NUM_THREADS 5 //number of threads
double step;


void getData();
void start();
int endFunc();
void insertionSort();
void selection();
void merge(int*, int*, int, int, int);
void mergesort(int*, int*, int, int);
void parMergesort(int*, int*, int, int);
void selectAlgorithm(int, int, int);
void average();
void pAverage();
void exitProgram();

ifstream Name; //define an input stream, need to include fstream.h

int N = 0;
int sorted = 0;
int mSwap = 0;
int mComp = 0;
string com = "";
string name = "";

int *testing; //define the array that saves the data

int main()
{
	clock_t beginT;
	clock_t endT;
	
	do{
	
		cin >> com;

		if ((strcmp(com.c_str(), "Start") == 0)){
			cin >> name;
			start();
		}
		else if ((strcmp(com.c_str(), "End") == 0)){
			cin >> name;
			endFunc();
		}
		else if ((strcmp(com.c_str(), "InsertionSort") == 0)){
			getData();
			beginT = clock();
			insertionSort();
			endT = clock();
			double totalTime = ((double)((endT - beginT) * 1000)) / CLOCKS_PER_SEC;

			//for (int y = 0; y < N; y++){
			//	cout << testing[y] << endl;
			//}

			printf("Time to run insertion sort (ms): %f\n", totalTime);
		}
		else if ((strcmp(com.c_str(), "Select") == 0)){
			beginT = clock();
			selection();
			endT = clock();
			double avgTime = ((double)((endT - beginT) * 1000)) / CLOCKS_PER_SEC;
			printf("Time to run selection (ms): %f\n", avgTime);
		}
		else if ((strcmp(com.c_str(), "Average") == 0)){
			getData();
			beginT = clock();
			average();
			endT = clock();
			double avgTime = ((double)((endT - beginT) * 1000)) / CLOCKS_PER_SEC;
			printf("Time to run average (ms): %f\n", avgTime);
		}
		else if ((strcmp(com.c_str(), "ParallelMergeSort") == 0)){
			mSwap = 0;
			mComp = 0;
			getData();
			beginT = clock();
			int b[N];
			parMergesort(testing, b, 0, N - 1);
			endT = clock();

			//for (int y = 0; y < N; y++){
				//cout << testing[y] << endl;
			//}

			double avgTime = ((double)((endT - beginT) * 1000)) / CLOCKS_PER_SEC;
			cout << "Number of comparissons made by parallel merge sort: " << mComp << endl;
			cout << "Number of swaps made by parallel merge sort: " << mSwap << endl;
			printf("Time to run parallel merge sort (ms): %f\n", avgTime);
			sorted = 1;
		}
		else if ((strcmp(com.c_str(), "ParallelAverage") == 0)){
			getData();
			beginT = clock();
			pAverage();
			endT = clock();
			double avgTime = ((double)((endT - beginT) * 1000)) / CLOCKS_PER_SEC;
			printf("Time to run parallel average (ms): %f\n", avgTime);
		}
		else if ((strcmp(com.c_str(), "MergeSort") == 0)){
			mSwap = 0;
			mComp = 0;
			getData();
			beginT = clock();
			int b[N];
			mergesort(testing, b, 0, N - 1);
			endT = clock();

			//for (int y = 0; y < N; y++){
			//	cout << testing[y] << endl;
			//}

			double avgTime = ((double)((endT - beginT) * 1000)) / CLOCKS_PER_SEC;
			cout << "Number of comparissons made by merge sort: " << mComp << endl;
			cout << "Number of swaps made by merge sort: " << mSwap << endl;
			printf("Time to run merge sort (ms): %f\n", avgTime);
			sorted = 1;
		}
		else if ((strcmp(com.c_str(), "Exit") == 0)){
			exitProgram();
		}
		else{
			cout << "Command not recognized. Please try again." << endl;
		}
	
	} while ((strcmp(com.c_str(), "Exit") != 0));

	return 0;

}

void getData(){
	//cin >> name;

	delete[] testing; //free the memory that was dynamically allocated for the array before

	char fName[20] = "";

	strcpy(fName, name.c_str());   //move name into fName for concatenation
	strcat(fName, ".txt");     //concatenate .txt onto the name to complete the file name

	Name.open(fName); //open a file

	Name >> N; //read size from the opened file
	
	testing = new int[N]; //dynamically allocate the array

	for (int i = 0; i < N; i++){
		Name >> testing[i]; //read the remaining N integers into the array
		//cout << testing[i] << endl;     //print all elements of array
	}

	Name.close();
}


void start(){
	//cin >> name;

	char fName[20] = "";

	cout << "Processing fitness data of: " << name << endl;

	strcpy(fName, name.c_str());   //move name into fName for concatenation
	strcat(fName, ".txt");     //concatenate .txt onto the name to complete the file name

	Name.open(fName); //open a file

	Name >> N; //read size from the opened file

	testing = new int[N]; //dynamically allocate the array
	for (int i = 0; i < N; i++){
		Name >> testing[i]; //read the remaining N integers into the array
		//cout << testing[i] << endl;     //print all elements of array
	}
	Name.close();
}



int endFunc(){

	//Name.close(); //close the file opened before
	delete[] testing; //free the memory that was dynamically allocated for the array before

	cout << "End of processing fitness data for: " << name << endl;

	return 0;
}


void insertionSort(){

	int testingLength = N;   //variable declarations for insertion sort
	int swaps = 0;
	int comps = 0;

	//Insertion Sort Algorithm
	for (int i = 1; i < N; i++){
		int j = i;
		while (j > 0 && testing[j] < testing[j - 1]){
			int temp = testing[j];
			testing[j] = testing[j - 1];
			testing[j - 1] = temp;
			swaps++; //increment the number of swaps
			comps++; //increment the number of comparisons
			j--;
		}

		comps++; //increment the number of comparisons
	}

	sorted = 1;   //tells program that array has been sorted

	cout << "Number of comparissons made by insertion sort: " << comps << endl;
	cout << "Number of swaps made by insertion sort: " << swaps << endl;

}


void mergesort(int *A, int*B, int lo, int hi) {
	int mid = 0;
	if (lo < hi) {
		mid = (lo + hi) / 2;
		mergesort(A, B, lo, mid);
		mergesort(A, B, mid + 1, hi);
		merge(A, B, lo, mid, hi);
	}
}

void parMergesort(int *A, int*B, int lo, int hi) {
	int mid = 0;
	if (lo < hi) {
		mid = (lo + hi) / 2;

		omp_set_nested(1);

		#pragma omp parallel
		{
			#pragma omp single
			{
				mergesort(A, B, lo, mid);
			}
			#pragma omp single
			{
				mergesort(A, B, mid + 1, hi);
			}
		}
		merge(A, B, lo, mid, hi);
	}
}


void merge(int *a, int *b, int lo, int mid, int hi) {
	int w, x, y, z;
	w = lo;
	x = lo;
	y = mid + 1;

	while ((w <= mid) && (y <= hi)) {
		if (a[w] <= a[y]) {
			b[x] = a[w];
			mSwap++;
			w++;
		}
		else {
			b[x] = a[y];
			mComp++;
			mSwap++;
			y++;
		}
		x++;
		mComp++;
	}
	if (w > mid) {
		for (z = y; z <= hi; z++) {
			b[x] = a[z];
			mSwap++;
			x++;
		}
	}
	else {
		for (z = w; z <= mid; z++) {
			b[x] = a[z];
			mSwap++;
			x++;
		}
	}

	for (z = lo; z <= hi; z++) {
		a[z] = b[z];
	}
}





void selection(){
	string sel = "";

	if (sorted == 0){    //checks if array is sorted
		cout << "Unable to select from an unsorted array." << endl;
	}
	else{
		cin >> sel;   //gets selection type

		if ((strcmp(sel.c_str(), "min") == 0)){
			cout << "Selecting item: "<< testing[0] << endl;   //min value
		}
		else if ((strcmp(sel.c_str(), "max") == 0)){
			cout << "Selecting item: " << testing[N-1] << endl;  //max value
		}
		else if ((strcmp(sel.c_str(), "median") == 0)){
			cout << "Selecting item: " << testing[N/2] << endl;  //median value
		} 
		else {
			int num = atoi(sel.c_str());
			if (num > N){
				cout << "Invalid input." << endl;
			}
			else{
				srand(time(NULL));
				int pvt = rand() % (N + 1);
				if (pvt == num){
					cout << "Selecting item: " << testing[num] << endl;
				}
				else if (num < pvt){
					selectAlgorithm(0, pvt, num);
				}
				else if (num > pvt){
					selectAlgorithm(pvt, (N-1), num);
				}
			}
			
		}
	
	}
}

void selectAlgorithm(int lo, int hi, int num){
	//cout << num << "   " << lo << "   "<< hi << endl;
	
	if (num < hi){
		selectAlgorithm(0, hi/2, num);
	}
	else if (num > hi && num != hi){
		selectAlgorithm(((num + hi) / 2), num, num);
	}
	else if (lo < hi && num == hi){
		if ((hi - lo) == 1){
			selectAlgorithm(((lo + hi) / 2)+1, hi, num);
		}
		else{
			selectAlgorithm(((lo + hi) / 2), hi, num);
		}
	}
	else if (lo == hi){
		cout << "Selecting item: " << testing[hi] << endl;
		//cout << "Correct item: " << testing[150] << endl; 
	}
}

void average(){

	clock_t avgB, avgE;

	double sum = 0.0;

	for (int i = 0; i < N; i++){
		sum = sum + testing[i];   //increase the sum for average calculation
	}

	double average = sum / N;  //compute the average

	cout << "Average number of steps: " << average << endl;

}

void pAverage(){

	double sumP = 0.0;

#pragma omp parallel for shared(N,testing) reduction(+:sumP) num_threads(4)
	for (int i = 0; i < N; i++){
		sumP += testing[i];
	}
	
		double pAvg = sumP / N;
		cout << "Average number of steps (parallel sum): " << pAvg << endl;
}


void exitProgram(){
	cout << "Program terminating." << endl;
}

