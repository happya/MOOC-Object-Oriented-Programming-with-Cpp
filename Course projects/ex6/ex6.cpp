/*
 * ex6.cpp
 *
 *  Created on: 2018年10月15日
 *      Author: yyiust
 */

#include <iostream>
#include<string>
#include<cstring>
using namespace std;

void q1(){
	//dp[i]:以a[i]结尾的当前最长非增子序列长度
	int n=0,a[26],dp[26]={0},max_count=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		dp[i]=1;
	}
	for(int i=1;i<n;i++){
		for(int j=0;j<i;j++){
			if(a[i]<=a[j])//将当前数与之前的一个一个进行比较，查看以当前数结尾的最长非增子序列
				if(dp[j]+1>dp[i])//如果当前这个i接在j的后面比前面的结果好，就用当前这个序列；否则还是按照之前那个序列
					dp[i]=dp[j]+1;
		}
		if(dp[i]>max_count)
			max_count=dp[i];

		//cout<<dp[i]<<endl;
	}

	cout<<max_count<<endl;
}

void zipper(){
	int n;
	cin>>n;
	string a,b,c;
	int dp[201][201];
	int len1,len2;

	int count=1;
	while(n--){
		cin>>a>>b>>c;

		len1=a.size();
		len2=b.size();
		memset(dp,0,sizeof(dp));
		dp[0][0]=1;
		int i,j;
		for(i=0;i<=len1;i++){
			for(j=0;j<=len2;j++){
				if(i>0 && dp[i-1][j]==1 && a[i-1]==c[i+j-1])dp[i][j]=1;
				if(j>0 && dp[i][j-1]==1 && b[j-1]==c[i+j-1])dp[i][j]=1;
				//cout<<i<<' '<<j<<' '<<dp[i][j]<<endl;
			}
		}
		//cout<<dp[i][j]<<endl;
		cout<<"Data set "<<count++<<": ";
		if(dp[len1][len2])
			cout<<"yes"<<endl;
		else
			cout<<"no"<<endl;

	}

}


int main(){
	zipper();
	return 0;
}
