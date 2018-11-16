/*
 * ex5.cpp
 *
 *  Created on: 2018年9月17日
 *      Author: yyiust
 *
 *  ch5:继承与派生
 */


#include <cstdio>
#include <iostream>
#include <string>
using namespace std;


//red: iceman,lion,wolf,ninja,dragon
//blue:lion, dragon,ninja,iceman,wolf
//input:dragon,ninja,iceman,lion,wolf
class tribe;
class warrior{
private:
	tribe *ptribe;//this warrior belongs to which tribe?
	int wIdx;
	int wNum;//the total warrior number in the tribe
public:
	static string names[5];
	static int life[5];
	warrior(tribe * p,int idx,int n):ptribe(p),wIdx(idx),wNum(n){};
	void print(int time);
};

class tribe{
private:
	int color;
	int tLife;
	int tWarNum;
	int warNum[5];//the number of each kind of warriors in the tribe
	int curIdx;
	bool stop;
	warrior *pw[1000];//point to warriors in each tribe

public:
	friend class warrior;
	static int proseq[2][5];
	void init(int color_,int tLife);
	string getColor(){
		if(color) return "blue";
		else return "red";
	}
	int proWar(int time);
	~tribe(){
		for (int i=0;i<tWarNum;i++)
			delete pw[i];
	}
};
void tribe::init(int color_,int tLife_){
	color=color_;
	tLife=tLife_;
	tWarNum=0;//the number of total warrior in this tribe
	curIdx=0;
	stop=false;
	for(int i=0;i<5;i++)
		warNum[i]=0;
}
int tribe::proWar(int time){
	if(stop) return 0;
	//if power is not enough
	int searchNum=0;
	while(warrior::life[proseq[color][curIdx]]>tLife && searchNum<5){
		curIdx=(curIdx+1)%5;
		searchNum++;
	}
	int wIdx=proseq[color][curIdx];//find current warrior
	if(warrior::life[wIdx]>tLife){//if the power needed to produce this warrior is larger than the remain value
		stop=true;
		if(color==0)
			printf("%03d red headquarter stops making warriors\n",time);
		if(color==1)
			printf("%03d blue headquarter stops making warriors\n",time);
		return 0;
	}
	//produce a warrior
	tLife=tLife-(warrior::life[wIdx]);
	curIdx=(curIdx+1)%5;
	warNum[wIdx]++;
	//create a new pointer pointing to a the newly created warrior
	//the "wIdx" is the warrior index
	pw[tWarNum] = new warrior(this,wIdx,tWarNum+1);
	pw[tWarNum]->print(time);
	tWarNum++;
	return 1;
}

void warrior::print(int time){
	string color=ptribe->getColor();
	printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
			time,color.c_str(),names[wIdx].c_str(),wNum,life[wIdx],ptribe->warNum[wIdx],
			names[wIdx].c_str(),color.c_str());
}

string warrior::names[5]={"dragon","ninja","iceman","lion","wolf"};
int tribe::proseq[2][5]={{ 2,3,4,1,0 },{3,0,1,2,4}};
int warrior::life[5]={0,0,0,0,0};

int main(){
	int testnum;
	cin>>testnum;
	int caseNum=1;
	int totalLife;

	tribe redTribe,blueTribe;
	while(testnum--){

		cin>>totalLife;
		for(int i=0;i<5;i++)
			cin>>warrior::life[i];
		printf("Case:%d\n",caseNum++);
		redTribe.init(0,totalLife);
		blueTribe.init(1,totalLife);
		int time=0;
		while(true){
			int tmp1=redTribe.proWar(time);
			int tmp2=blueTribe.proWar(time);
			if (tmp1==0 && tmp2==0) break;
			time++;
		}
	}
	return 0;

}
