/*
 * ex6.cpp
 *
 *  Created on: 2018��10��15��
 *      Author: yyiust
 */

#include <iostream>
#include<string>
#include<cstring>
using namespace std;

void q1(){
	//dp[i]:��a[i]��β�ĵ�ǰ����������г���
	int n=0,a[26],dp[26]={0},max_count=0;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		dp[i]=1;
	}
	for(int i=1;i<n;i++){
		for(int j=0;j<i;j++){
			if(a[i]<=a[j])//����ǰ����֮ǰ��һ��һ�����бȽϣ��鿴�Ե�ǰ����β�������������
				if(dp[j]+1>dp[i])//�����ǰ���i����j�ĺ����ǰ��Ľ���ã����õ�ǰ������У������ǰ���֮ǰ�Ǹ�����
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
