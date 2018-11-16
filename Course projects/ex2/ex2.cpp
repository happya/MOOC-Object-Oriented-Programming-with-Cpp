/*
 * ex2.cpp
 *
 *  Created on: 2018��9��11��
 *      Author: pc39
 */
/*
 * ch4:���������
 * */
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


//"[]""="���������,ʵ�ֿɱ䳤��������
class CArray{
private:
	int size;
	int *ptr;
public:
	CArray(int s=0);
	CArray(CArray & a);//���ƹ��캯��
	~CArray();//��������
	void push_back(int v);//����������һ��Ԫ��
	int length(){return size;}//���������С����Ԫ�ظ���
	CArray & operator=(const CArray & a);//��=����ֵ����
	int & operator[](int i){return ptr[i];}//"[]"�±�����
};

//���캯��
CArray::CArray(int s){
	size=s;
	if(s==0)
		ptr=NULL;
	else
		ptr=new int[s];
}
//���ƹ��캯��
CArray::CArray(CArray & a){
	if(!a.ptr){
		ptr=NULL;
		size=0;
		return;
	}
	size=a.size;
	ptr = new int[a.size];
	memcpy(ptr,a.ptr,sizeof(int)*size);
	return;
}
//��������
CArray::~CArray(){
	if(ptr)
		delete [] ptr;
}
//"="����
CArray & CArray::operator =(const CArray & a){//��a������鸳ֵ����������
	if (ptr==a.ptr){return *this;}//��ֹa=a����ĸ�ֵ����
	if (!a.ptr){//���a��ĸ�ֵ�ǿյ�
		if(ptr) delete [] ptr;
		ptr=NULL;
		size=0;
		return *this;
	}
	if(size<a.size){//���ԭ�пռ��㹻�󣬾Ͳ��÷����µĿռ䣻��֮delete��ԭ�пռ䣬����a.size��С�Ŀռ�
		if(ptr) delete [] ptr;
		ptr = new int[a.size];
	}
	memcpy(ptr,a.ptr,sizeof(int)*a.size);
	size=a.size;
	return *this;
}
//��Ա����������������һ��Ԫ�أ�Ч�ʵ�
void CArray::push_back(int v){
	if(ptr){
		int * tmpptr=new int[size+1];
		memcpy(tmpptr,ptr,sizeof(int)*size);
		delete [] ptr;
		ptr = tmpptr;

	}
	else
		ptr = new int[1];
	ptr[size++] = v;

}

//����������������
class Complex{
private:
	double real,imag;
public:
	Complex(double r=0,double i=0):real(r),imag(i){}
	friend ostream & operator<<(ostream & os, const Complex & c);
	friend istream & operator>>(istream & is, Complex & c);
};
//��������Ϊ��Ա����������Ϊ��Ҫ����˽�б���������ΪComplex�����Ԫ
ostream & operator<<(ostream & os, const Complex & c){
	os<<c.real<<"+"<<c.imag<<"i";
	return os;
}
istream & operator>>(istream & is, Complex & c){
	string s;
	is>>s;
	int pos=s.find("+",0);
	string stmp=s.substr(0,pos);
	//c_str()������һ��const char*ָ�룬�����ص�ǰ�ַ��������ַ���ַ
	c.real = atof(stmp.c_str());//atof�⺯�����ܽ�const *charָ�������ת��Ϊfloat����
	stmp = s.substr(pos+1,s.length()-pos-2);
	c.imag=atof(stmp.c_str());
	return is;

}

//�����Լ����������
class CDemo{
private:
	int n;
public:
	CDemo(int i=0):n(i){}
	CDemo & operator++();//ǰ��++
	CDemo operator++(int);//����
	operator int (){return n;}//int ��Ϊ����ǿ��ת�������������
	friend CDemo & operator--(CDemo &);
	friend CDemo operator--(CDemo &,int);
};
CDemo & CDemo::operator++(){//ǰ��++
	++n;
	return *this;
}//++s��Ϊs.operator++()
CDemo CDemo::operator++(int k){
	//����++
	CDemo tmp(*this);//��¼�޸�ǰ�Ķ���
	++n;
	return tmp;//�����޸�ǰ�Ķ���
}
CDemo & operator--(CDemo & d){//ǰ��--
	--(d.n);
	return d;
}//--s��Ϊoperator--(s)
CDemo operator--(CDemo & d, int k){
	CDemo tmp(d);
	--(d.n);
	return tmp;
}


int main(){
	/*
	CArray a1;
	a1.push_back(2);
	a1.push_back(3);
	cout<<a1.length()<<endl;
	CArray a2;
	a2=a1;
	a2.push_back(4);
	a2[0]=100;
	cout<<a2.length()<<endl;
	cout<<a2[0]<<' '<<a2[1]<<' '<<a2[2]<<endl;
	*/
	/*
	Complex c;
	int n;
	cin>>c>>n;
	cout<<c<<","<<n;
	*/
	CDemo d(5);
	cout<<"d++: "<<d++<<endl;
	cout<<"d: "<<d<<endl;
	cout<<"++d: "<<++d<<endl;
	cout<<"d: "<<d<<endl;
	cout<<"d--: "<<d--<<endl;
	cout<<"d: "<<d<<endl;
	cout<<"--d: "<<--d<<endl;
	cout<<"d: "<<d<<endl;
	return 0;
}
