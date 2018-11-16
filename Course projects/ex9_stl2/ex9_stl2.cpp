#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<set>
#include<iterator>
#include<string>
using namespace std;

int main(){
	int N;
	cin>>N;
	multiset<int> ms;
	set<int> s;
	for(int i=1;i<=N;i++){
		string com;
		int id;
		cin>>com>>id;
		if (com=="add"){
			ms.insert(id);
			s.insert(id);
			cout<<ms.count(id)<<endl;
		}
		else if(com=="ask"){
			if(s.find(id)==s.end()) cout<<"0 0"<<endl;
			else{
				cout<<"1 ";
				cout<<ms.count(id)<<endl;
			}
		}
		else if(com=="del"){
			if(s.find(id)==s.end())
				cout<<"0"<<endl;
			else{
				cout<<ms.count(id)<<endl;
				ms.erase(id);
			}
			}
		}
	return 0;
}
