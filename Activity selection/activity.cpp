/*********************************************
 **Class: CS325
 **Prog: activity.cpp
 **Author: Chia-Ling Hu
 **Date: 02/10/2021
************************************************/ 
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>

using namespace std;

struct activity{
	int start;
	int end;
	int num;
};

void swap(activity* a, activity* b){
	activity temp = *a;
	*a = *b;
	*b = temp;
}
// sort activity array by start time in descending order
void selectionsort(activity* array,int size){
	int max_index;
	for(int i=0;i<size-1;i++){
		max_index = i;
		for(int j=i+1;j<size;j++){
			if(array[j].start > array[max_index].start){
				max_index = j;
			}
		}
		swap(&array[i],&array[max_index]);
	}
}


int main(){

	ifstream file;
	file.open("act.txt");
	int size;
	int set = 1;
	vector <int> select;
	if(file.is_open()){
		while(!file.eof()){
			file >> size;
			activity* a_arr = new activity[size];
			// read in each activity's num, start and end time 
			for(int i=0;i<size;i++){
				file >> a_arr[i].num;
				file >> a_arr[i].start;
				file >> a_arr[i].end;
			}
			//sort activity array by start time in descending order
			selectionsort(a_arr,size);
			// the first sorted activity aka activity with last start time is always selected
			int act_start = a_arr[0].start;
			select.push_back(a_arr[0].num);
			// loop through the rest activities in activity array
			for(int i=1;i<size;i++){
				// the end time of activity is not overlapping with the previously selected activity's start time
				if(a_arr[i].end <= act_start){
					select.push_back(a_arr[i].num);
					act_start = a_arr[i].start;
				}
			}
			cout <<"Set " << set << endl;
			cout <<"Number of activities selected = " << select.size() << endl;
			cout <<"Activities: ";
			for(int i=select.size()-1;i>=0;i--){
				cout << select[i] <<" ";
			}
			set++;
			// clear vector 
			select.clear();
			cout << endl;
			delete [] a_arr;

		}

		file.close();
	}

	else{
		cout<<" Cannot open act.txt" << endl;
	}

	return 0;

}
