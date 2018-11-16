/*
 * rhombus.cpp
 *
 *  Created on: 2018��9��5��
 *      Author: yyi
 */
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class A{
public:
	int x;
	A(int x_):x(x_)
		{cout<<x<<" constructed called"<<endl;}
	A(const A & a){
		x=a.x+2;
		cout<<"copy called"<<endl;
	}
	~A(){cout<<x<<" destructed called"<<endl;}

};

A func(){
	A b(10);
	return b;
}
void swap(int &a,int &b);// ������Ϊ����������ʵ�ֽ�����������ֵ
void swap(int *&a,int *&b);// ָ�������
void arrange();


// ������Ϊ����������ʵ�ֽ�����������ֵ
void swap(int &a,int &b){
	int tmp = a;
	a=b;
	b=tmp;
}

// ָ�������
void swap(int *&a,int *&b){
	int *tmp=a;
	a=b;
	b=tmp;
}

void arrange(){

	string str;
	getline(cin,str);
	//int len = str.length();

}

class Student{
private:
	char name[20];
	int age;
	char id[20];
	float y1,y2,y3,y4;
	float average;
public:
	void input(){
		char c;
		cin.getline(name,20,',');
		cin>>age;cin.ignore(1,',');
		cin.getline(id,20,',');
		cin>>y1>>c>>y2>>c>>y3>>c>>y4;
	};
	float calculate(){
		average=(y1+y2+y3+y4)/4.0;
		return average;
	};
	void output(){
		cout<<name<<','<<age<<','<<id<<','<<average<<endl;
	};

};


int main(){
	Student student;        // ������Ķ���
	student.input();        // ��������
	student.calculate();    // ����ƽ���ɼ�
	student.output();       // �������
	return 0;
}



