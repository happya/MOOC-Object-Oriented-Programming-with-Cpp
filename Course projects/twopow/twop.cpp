/*
 * twop.cpp
 *
 *  Created on: 2018Äê9ÔÂ6ÈÕ
 *      Author: yyi
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int bits_dict[16][4]={0};


int main(){
	for (int i=1;i<16;i++){
		for (int j=3;j>-1;j--){
			if ((i&(1<<j))!=0)
				bits_dict[i][j]=1;
		}

	}
	vector<string> s(4);
	vector<string> d(16);
	s[0]="2(0)";
	s[1]="2";
	s[2]="2(2)";
	s[3]="2(2+2(0))";
	d[1]="2(0)";
	d[2]="2";
	for (int i=3;i<16;i++){
		for(int j=3;j>-1;j--){
			if (bits_dict[i][j]){
				if (d[i]=="")
					d[i]=s[j];
				else
					d[i]=d[i]+"+"+s[j];
			}
		}
	}
	int n;
	string res;
	cin>>n;
	if (n<16){
		cout<<d[n]<<endl;
		return 0;
	}
	for (int i=15;i>1;i--){
		if ((n&(1<<i))!=0){
			if (res=="")
				res = "2("+d[i]+")";
			else
				res = res+"+"+"2("+d[i]+")";
		}
	}
	if ((n&2)!=0)
		res =res+"+"+"2";
	if ((n&1)!=0)
		res = res+"+"+"2(0)";

	cout<<res<<endl;
	return 0;
}


