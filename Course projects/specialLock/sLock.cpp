/*
 * rhombus.cpp
 *
 *  Created on: 2018Äê9ÔÂ5ÈÕ
 *      Author: yyi
 */
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int lock(int b1,int b2,int len);

int lock(int b1,int b2,int len){
	int b1_2=b1;
	int c1=0,c2=0;
	for (int i=len-1;i>0;i--){
		if (i==len-1){
			if ((b1&(1<<i))==(b2&(1<<i)))
				continue;
			else if (len<3){
				if ((b1^b2)==(1<<i)-1)
					return 1;

				else
					return -1;

			}
			else{
				b1_2 =b1_2^((1<<i)+(1<<(i-1))+(1<<(i-2)));
				b1 =b1^((1<<i)+(1<<(i-1)));
				c1=c2=1;
			}
	}

		else{
			int tmp = (1<<(i-1))+(1<<i);
			if (i>1)
				tmp += 1<<(i-2);

			if ((b1&(1<<i))!=(b2&(1<<i))){
				b1=b1^tmp;
				c1+=1;

			}
			if ((b1_2&(1<<i))!=(b2&(1<<i))){
				b1_2=b1_2^tmp;
				c2+=1;

			}
		}


	}

	if (b1==b2)
		return c1;
	else if (b1_2==b2)
		return c2;
	else
		return -1;
}

int main(){

	string s1,s2;
	getline(cin,s1);
	getline(cin,s2);
	int b1=0;
	int b2=0;
	int len=s1.length();
	for (int i=0;i<len;i++){
		if (s1[i]!='0')
			b1+=(1<<(len-1-i));
		if (s2[i]!='0')
			b2+=(1<<(len-1-i));
	}
	int t;
	t = lock(b1,b2,len);
	if (t>-1){
		cout<<t<<endl;
		return 0;
	}
	b1=0;
	b2=0;
	for (int i=0;i<len;i++){
		if (s1[i]!='0')
			b1+=(1<<i);
		if (s2[i]!='0')
			b2+=(1<<i);
	}
	t = lock(b1,b2,len);
	if (t>-1)
		cout<<t<<endl;
	else
		cout<<"impossible"<<endl;
	return 0;
}



