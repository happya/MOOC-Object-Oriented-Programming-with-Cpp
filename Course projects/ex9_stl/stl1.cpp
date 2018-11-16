/*
 * stl1.cpp
 *
 *  Created on: 2018��10��29��
 *      Author: yyiust
 */

#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <iterator>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

//global function
int sumSquares(int total,int value){
	return total+value*value;
}

//����ģ��
template <class T>
void PrintInterval(T first, T last){
	for(;first!=last;first++)
		cout<<*first<<" ";
	cout<<endl;
}
//��������
template <class T>
class sumPowers{
private:
	int power;
public:
	sumPowers(int p):power(p){};
	const T operator()(const T &total, const T &value){
		T v=value;
		for(int i=0;i<power-1;i++){
			v=v*value;
		}
		return total+v;
	}
};

void week8_1(){
	const int SIZE=10;
	int a1[]={1,2,3,4,5,6,7,8,9,10};
	vector<int> v(a1,a1+SIZE);
	cout<<"1) ";PrintInterval(v.begin(),v.end());
	int result=accumulate(v.begin(),v.end(),0,sumSquares);
	cout<<"ƽ���ͣ� "<<result<<endl;
	result=accumulate(v.begin(),v.end(),0,sumPowers<int>(3));
	cout<<"�����ͣ� "<<result<<endl;
	result=accumulate(v.begin(),v.end(),0,sumPowers<int>(4));
	cout<<"�Ĵη��ͣ� "<<result<<endl;

}

list<int>& ith_list(vector<list<int> >& l_id,int id){

	vector<list<int> >::iterator s;
	s=l_id.begin();
	return *(s+id-1);
}


//vector�д洢���Ƕ���ָ����Զ�������
class A{
protected:
	int p;
public:
	int a;
	A(int a_):a(a_){if (a) p=100;else p=0;}
	void set_fa(int p_){p=p_;}
};
bool myLess(const A *A1, const A *A2){return (A1->a)%10<(A2->a)%10;}
int vector_cmp(){
	vector<A*> PA;
	A A1(12),A2(14),A3(21);
	PA.push_back(&A1);
	PA.push_back(&A2);
	PA.push_back(&A3);
	sort(PA.begin(),PA.end(),myLess);
	PA.erase(PA.begin()+2);
	for(vector<A*>::iterator i=PA.begin();i!=PA.end();i++)
		cout<<(*i)->a<<endl;

	return 0;

}

class son_A:public A{
private:
	int sa;
public:
	son_A(int a_,int s_):A(a_),sa(s_){}
	int get_sa(){return sa;}
	int get_both(){return this->a;}
	int get_father(){return this->p;}
	~son_A(){cout<<"kill"<<endl;}
};

void sons(int count){
	son_A sA(10,100);
	cout<<"create"<<endl;
	//~son_A();
	count--;
	cout<<count<<endl;

}
void ex8(){
	int n;
	cin>>n;
	vector<list<int> > A;
	for(int i=0;i<n;i++){
		string s;
		cin>>s;
		if(s=="new"){
			int id;
			cin>>id;
			A.push_back(list<int>());//create a new list head
		}
		else if (s=="add"){
			int id,num;
			cin>>id>>num;
			//find the entrance of ith list
			list<int>& ith_l=ith_list(A,id);
			ith_l.push_back(num);
			ith_l.sort();
		}
		else if (s=="merge"){
			int id1,id2;
			cin>>id1>>id2;
			list<int>& l1=ith_list(A,id1);
			list<int>& l2=ith_list(A,id2);
			l1.sort();
			l2.sort();
			l1.merge(l2);
		}
		else if (s=="unique"){
			int id;
			cin>>id;
			list<int>& ith_l=ith_list(A,id);
			ith_l.sort();
			ith_l.unique();
		}
		else if (s=="out"){
			int id;
			cin>>id;
			list<int>& ith_l=ith_list(A,id);
			if(ith_l.size()>0){
				list<int>::iterator i;
				for(i=ith_l.begin();i!=ith_l.end();i++)
					cout<<*i<<" ";
			}
			cout<<endl;
		}
	}
}
int main(){
	sons(10);
	return 0;
}