/*
 * w5e1.cpp
 *
 *  Created on: 2018Äê10ÔÂ8ÈÕ
 *      Author: yyiust
 *
 */
#include <iostream>
#include <iomanip>
using namespace std;


void ex4(){
	int L,a[10001],part,s,t,count=0;
	cin>>L>>part;
	for (int i=0;i<L+1;i++) a[i]=true;
	for (int i=0;i<part;i++){
		cin>>s>>t;
		for (int j=s;j<t+1;j++) a[j]=false;
	}
	for(int i=0;i<L+1;i++)
		if (a[i]) count++;
	cout<<count;
		//cout<<fixed<<setprecision(2)<<double(a[i])/n*100<<"%"<<endl;

}

void ex5(){
	int A[5][5];
	for (int i=0;i<5;i++)
		for (int j=0;j<5;j++)
			cin>>A[i][j];
	int row,col;
	bool flag=false;
	for(row=0;row<5;row++){
		col=0;
		for(int j=1;j<5;j++){
			if(A[row][j]>A[row][col])
				col=j;//find the max in current row
		}
		flag=true;
		//to see if this value is the min in its column
		for(int i=0;i<5;i++){
			if (A[i][col]<A[row][col]){
				flag=false;
				break;
			}
		}
		if (flag) break;
	}
	if (flag)
		cout<<row+1<<" "<<col+1<<" "<<A[row][col]<<endl;
	else
		cout<<"not found"<<endl;
}
void ex6(){
	int img[101][101]={0},blur[101][101],n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			cin>>img[i][j];
			blur[i][j]=img[i][j];
		}
	for(int i=1;i<n-1;i++){
		for (int j=1;j<m-1;j++)
			{
			double average=(img[i-1][j]+img[i+1][j]+img[i][j-1]+img[i][j+1]+img[i][j])/5.0;
			blur[i][j]=int(average+0.5);
			}
	}
	for(int i=0;i<n;i++){
		for (int j=0;j<m-1;j++){
			cout<<blur[i][j]<<' ';
		}
		cout<<blur[i][m-1]<<endl;

	}

}
void ex7(){
	int n,m,a[101][101]={0};
	int i,j;
	cin>>n>>m;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			cin>>a[i][j];
	for(j=0;j<m;j++){
		for(i=0;i<n-1;i++){
			cout<<a[i][j]<<' ';
		}
		cout<<a[n-1][j]<<endl;
	}

}

