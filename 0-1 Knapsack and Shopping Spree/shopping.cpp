/************************************************
 **Class: CS325 
 **Prog: shopping.cpp
 **Author: Chia-Ling Hu
 **Date: 01/28/2021
**************************************************/
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<fstream>
#include<algorithm>

using namespace std;


int knapsack_dp(int W,int* wt,int* val,int n,int* take){
	// create table
	int dp[n+1][W+1];

	for(int i=0;i<=n;i++){
		for(int j=0;j<=W;j++){
			// zero item or zero affordable weight
			if(i==0||j==0){
				dp[i][j]=0;
			}
			//have enough weight to consider take item or not
			else if(wt[i-1]<=j){
				//	      exclude item       include item  
				dp[i][j] = max(dp[i-1][j], val[i-1]+dp[i-1][j-wt[i-1]]);
			}
			else{
				//item weight is heavier than affordable weight
				dp[i][j] = dp[i-1][j];
			}
		}
	}
	// an array to check if item is taken or not
	for(int i=0;i<n+1;i++){
		take[i]=0;
	}
	int i = n;
	int j = W;
	while(i>0&&j>0){
		// item is taken
		if(dp[i][j]!=dp[i-1][j]){
			// mark item
			take[i]=1;  
			j = j-wt[i-1];
			i--; //go up one row
		}
		// item is not taken
		else{
			i--; // go up one row
		}	
	}
	
	return dp[n][W];
}

int main(){	
	ifstream infile;
	ofstream outfile;
	infile.open("shopping.txt");
	outfile.open("results.txt");
	
	int num_case,num_item,num_fam,W,max_price;
	int wt[100];
	int val[100];
	if(infile.is_open()&&outfile.is_open()){
		//read in test case 
		infile >> num_case;
		for(int i=0;i<num_case;i++){
			// read in total item in each test case
			infile >> num_item;
			// read in value and weight
			for(int j=0;j<num_item;j++){
				infile >> val[j];
				infile >> wt[j];
			}
			// read in number of family member
			infile >> num_fam;
			max_price = 0;
			int** take = new int*[num_fam];
			for(int j=0;j<num_fam;j++){
				take[j] = new int[num_item+1];
			}
			for(int k=0;k<num_fam;k++){
				infile >> W;
				max_price = max_price + knapsack_dp(W,wt,val,num_item,take[k]);
			}
			outfile <<"Test case " << i+1 << endl;
			outfile <<"Total price  " << max_price << endl;
			outfile <<"Member items" << endl;
			for(int j=0;j<num_fam;j++){
				outfile<<j+1 <<": ";
				for(int t=0;t<num_item+1;t++){
					if(take[j][t]==1){
						outfile<< t <<" ";
					}
				}
				outfile << endl;
			}
			outfile << endl;
		}
		infile.close();
		outfile.close();
	}
	else{
		cout <<"Cannot open shopping.txt " << endl;
	}

	return 0;
}
