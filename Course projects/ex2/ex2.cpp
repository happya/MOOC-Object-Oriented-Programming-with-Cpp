/*
 * ex2.cpp
 *
 *  Created on: 2018年9月11日
 *      Author: pc39
 */
/*
 * ch4:运算符重载
 * */
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


//"[]""="运算符重载,实现可变长整型数组
class CArray{
private:
	int size;
	int *ptr;
public:
	CArray(int s=0);
	CArray(CArray & a);//复制构造函数
	~CArray();//析构函数
	void push_back(int v);//在数组后添加一个元素
	int length(){return size;}//返回数组大小，即元素个数
	CArray & operator=(const CArray & a);//“=”赋值重载
	int & operator[](int i){return ptr[i];}//"[]"下标重载
};

//构造函数
CArray::CArray(int s){
	size=s;
	if(s==0)
		ptr=NULL;
	else
		ptr=new int[s];
}
//复制构造函数
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
//析构函数
CArray::~CArray(){
	if(ptr)
		delete [] ptr;
}
//"="重载
CArray & CArray::operator =(const CArray & a){//将a里的数组赋值给其他对象
	if (ptr==a.ptr){return *this;}//防止a=a这类的赋值出错
	if (!a.ptr){//如果a里的赋值是空的
		if(ptr) delete [] ptr;
		ptr=NULL;
		size=0;
		return *this;
	}
	if(size<a.size){//如果原有空间足够大，就不用分配新的空间；反之delete掉原有空间，开辟a.size大小的空间
		if(ptr) delete [] ptr;
		ptr = new int[a.size];
	}
	memcpy(ptr,a.ptr,sizeof(int)*a.size);
	size=a.size;
	return *this;
}
//成员函数，在数组后添加一个元素，效率低
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

//输入输出运算符重载
class Complex{
private:
	double real,imag;
public:
	Complex(double r=0,double i=0):real(r),imag(i){}
	friend ostream & operator<<(ostream & os, const Complex & c);
	friend istream & operator>>(istream & is, Complex & c);
};
//不能重载为成员函数，但因为需要访问私有变量，所以为Complex类的友元
ostream & operator<<(ostream & os, const Complex & c){
	os<<c.real<<"+"<<c.imag<<"i";
	return os;
}
istream & operator>>(istream & is, Complex & c){
	string s;
	is>>s;
	int pos=s.find("+",0);
	string stmp=s.substr(0,pos);
	//c_str()：生成一个const char*指针，它返回当前字符串的首字符地址
	c.real = atof(stmp.c_str());//atof库函数，能将const *char指向的内容转换为float类型
	stmp = s.substr(pos+1,s.length()-pos-2);
	c.imag=atof(stmp.c_str());
	return is;

}

//自增自减运算符重载
class CDemo{
private:
	int n;
public:
	CDemo(int i=0):n(i){}
	CDemo & operator++();//前置++
	CDemo operator++(int);//后置
	operator int (){return n;}//int 作为类型强制转换运算符被重载
	friend CDemo & operator--(CDemo &);
	friend CDemo operator--(CDemo &,int);
};
CDemo & CDemo::operator++(){//前置++
	++n;
	return *this;
}//++s即为s.operator++()
CDemo CDemo::operator++(int k){
	//后置++
	CDemo tmp(*this);//记录修改前的对象
	++n;
	return tmp;//返回修改前的对象；
}
CDemo & operator--(CDemo & d){//前置--
	--(d.n);
	return d;
}//--s即为operator--(s)
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
