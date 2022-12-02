/**************************************
** Class: CS325
** Prog: knapsack.cpp
** Author: Chia-Ling Hu
** Date: 01/28/2021
***************************************/
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<chrono>
#include<algorithm>

using namespace std;

int knapsack_rec(int W,int* wt,int* val,int n){
	// both wt[] and val[] start from index 0 and end in index n-1
	//base case	
	if(n==0||W==0){
		return 0;
	}
	// if current item weight is bigger than affordable weight
	if(wt[n-1]>W){
		return knapsack_rec(W,wt,val,n-1);
	}
	else{		//   exclude  the current item       include the curret item
		return max(knapsack_rec(W,wt,val,n-1),val[n-1]+knapsack_rec(W-wt[n-1],wt,val,n-1));
	}

}

int knapsack_dp(int W,int* wt,int* val,int n){
	// both wt[] and val[] start from index 0 and end in index n-1
	// create table
	int dp[n+1][W+1];

	for(int i=0;i<=n;i++){
		for(int j=0;j<=W;j++){
			// zero item or zero affordable weight
			if(i==0||j==0){
				dp[i][j]=0;
			}
			// have enough weight to consider take item or not 
			else if(wt[i-1]<=j){
				//	      exclude item       include item  
				dp[i][j] = max(dp[i-1][j], val[i-1]+dp[i-1][j-wt[i-1]]);
			}
			// item weight is heavier than affordable weight
			else{
				dp[i][j] = dp[i-1][j];
			}
		}
	}
	// max value can take	
	return dp[n][W];
}

int main(){
	
	int W=100;
	int n []= {10,15,20,25,30,35,40,45};
	srand(time(NULL));
	int** wt = new int*[8];
	int** val = new int*[8];
	for(int i=0;i<8;i++){
		wt[i] = new int[n[i]];
		val[i] = new int[n[i]];
		for(int j=0;j<n[i];j++){
			wt[i][j] = rand()%26+2;
			val[i][j] = rand()%100+1;
		}
	}	
	for(int i=0;i<8;i++){
		auto start1 = chrono::steady_clock::now();
		int max_rec = knapsack_rec(W,wt[i],val[i],n[i]);
		auto end1 = chrono::steady_clock::now(); 
		auto start2 = chrono::steady_clock::now();
		int max_dp = knapsack_dp(W,wt[i],val[i],n[i]);
		auto end2 = chrono::steady_clock::now();
		cout <<"n=" << n[i] <<" W=" << W << " Rec time(microsec)= "<<chrono::duration_cast<chrono::microseconds>(end1-start1).count() <<"  DP time(microsec)= "<< chrono::duration_cast<chrono::microseconds>(end2-start2).count() <<" max Rec= " << max_rec << " max DP= "<< max_dp << endl;
		delete[] wt[i];
		delete[] val[i];
	}

	delete []wt;
	delete []val;

	return 0;
}
