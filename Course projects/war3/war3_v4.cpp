/*
author: yyiust
date: 13/11/2018
openjudge: "http://cxsjsxmooc.openjudge.cn/2018t3fallwar/1/"
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class tribe;
class warrior;
class weapon;
class fields;
const int WEAPON_NUM=3;
const int WARR_NUM=5;
const int MAX_WEAPON=10;
int CITY_NUM;
vector<fields*> fields_all;
int M=0,K=0,T=0;
bool gameover=false;




class weapon{
private:
    int weapon_idx; //武器编号
    //warrior *owner; //拥有武器的武士
    int weapon_life;
    bool is_weapon_ok; //武器是否还能用

public:
    friend class cmp_battle;
    friend bool cmp_snatch(const weapon &w1, const weapon &w2);
    friend class warrior;
    weapon(int w_idx);

    void update_weapon(){
        weapon_life--;
        if(weapon_idx==1 && weapon_life<=0)
            is_weapon_ok=false;
        else if(weapon_idx==2 && weapon_life<=0)
            is_weapon_ok=false;
        return;
        }
};
class cmp_battle{
public:
bool operator()(const weapon &w1, const weapon &w2){
        if(w1.weapon_idx!=w2.weapon_idx) return w1.weapon_idx<w2.weapon_idx;//编号小的优先
        else return w1.weapon_life<w2.weapon_life;//用过的优先
    }
};


bool cmp_snatch(const weapon &w1, const weapon &w2){
        if(w1.weapon_idx!=w2.weapon_idx) return w1.weapon_idx<w2.weapon_idx;//编号小的优先
        else return w1.weapon_life<w2.weapon_life; //没用过的优先
    }

class warrior{
private:
    tribe *ptribe;    //武士属于哪个部落
    int warr_idx;     //武士种类编号
    int warr_no;      //武士编号n
    int HP, ATK,loyalty;      //武士生命值，攻击力
    int weapon_n[3];    //武士的武器数目
    vector<weapon> own_weapon; //武士拥有哪些武器
    bool alive;
public:
    friend class weapon;
    friend class tribe;
    friend class fields;
    int city_n;      //武士走到的城市
    int weapon_total;
    static string names[WARR_NUM];
    static int initHP[WARR_NUM];
    static int initATK[WARR_NUM];
    static string weapons[WEAPON_NUM];

    friend class weapon;
    friend class tribe;
    friend class fields;


    //成员函数
    warrior(tribe * p,int idx,int w_no, int hp_,int atk_);

    void print_born_info(int nHour);

    void init_my_weapon();
    bool isalive(){return alive;}
    void update_alive(){if(HP<=0) alive=false;}



    //特殊武士的事件
    void yell(int nHour);
    bool escape(int nHour);


    void get_weapons(warrior *w,int num);
    void lose_weapons(int num);
    void win_weapons(warrior *enemy);
    int find_weapon(int id);
    void attack(warrior *enemy);
    int get_AP(int id);
    int check_weapon();
    void wolf_snatch(warrior *enemy,int nHour);
    void print_wolf_snatch(int nHour,int no,int w_idx,warrior *enemy);
    void march(); //前进一步
    void report_fight(int nHour);
    void report_battle(int nHour,int n);
    void report_status(int nHour);
    ~warrior(){
        own_weapon.clear();
    }
};

class tribe{
private:
    int elements; //生命元
    //int warr_n[WARR_NUM];//每种战士数
    int warr_total;
    int color;
    int cur_idx;
    //bool win;
    vector<warrior*> own_warriors;
public:
    static int sequence[2][5];
    friend class warrior;
    tribe(int M,int col){
        elements=M;
        color=col;
        cur_idx=0;
        warr_total=0;
    }
    string get_color(){if(color) return "blue";else return "red";}
    void produce(int nHour);
    void update_my_warriors(warrior *w);

    void tribe_march(int color);
    void report_M(int nHour);
    ~tribe(){
        for (int i=0;i<warr_total;i++)
            delete own_warriors[i];
        own_warriors.clear();
    }
};

class fields{//一个城市
private:
    warrior *wR, *wB;
public:
    fields():wR(NULL),wB(NULL){}
    fields(warrior *w1,warrior *w2):wR(w1),wB(w2){}
    friend class warrior;
    friend class tribe;
    void city_escape(int nHour,int n);
    void city_snatch(int nHour);
    void print_march(int nHour);
    void print_takeover(int nHour,int color);

    void city_report(int nHour);
    void city_battle(int nHour,int n);
    void city_win_weapons(int result);
    void report_fight(int nHour,int result,int n);
    void city_yell(int nHour,int result);

    ~fields(){
        for(int i=0;i<=CITY_NUM+1;i++)
            delete fields_all[i];
        fields_all.clear();
    }
};

weapon::weapon(int w_idx):weapon_idx(w_idx){
        is_weapon_ok=true;
        switch(w_idx){
        case 0: weapon_life=0xffff; break;
        case 1: weapon_life=1;break;
        case 2: weapon_life=2;break;
        default: break;
        }
}
warrior::warrior(tribe * p,int idx,int w_no, int hp_,int atk_){
        ptribe=p;
        warr_idx=idx;
        warr_no=w_no;
        HP=hp_; ATK=atk_;loyalty=ptribe->elements;
        alive=true;
        if(ptribe->color) city_n=CITY_NUM+1;
        else city_n=0;
        weapon_total=0;
        weapon_n[3]={0};
}

void tribe::produce(int nHour){
    //看生命元是否足够
    int wIdx=sequence[color][cur_idx];//现在要制造武士的编号
    if(warrior::initHP[wIdx]<=elements){
        //制造武士
        int w_HP=warrior::initHP[wIdx];
        int w_ATK=warrior::initATK[wIdx];
        elements -= w_HP;                          //司令部生命元减少
        cur_idx=(cur_idx+1)%5;                    //下次要制造的武士在数组中的序列号
        //制造武士所需信息：所属部落，武士种类编号，武士id，HP,ATK
        warrior *s;
        s = new warrior(this,wIdx,warr_total+1,w_HP,w_ATK);
        s->init_my_weapon();
        update_my_warriors(s);
        s->print_born_info(nHour);

        if(color==0) fields_all[0]->wR=s;
        if(color==1) fields_all[CITY_NUM+1]->wB=s;
    }
}
void warrior::init_my_weapon(){
    for(int i=0;i<=2;i++) weapon_n[i]=0;
    if(warr_idx==4) weapon_total=0;//wolf
    else if(warr_idx==1){//ninja
        weapon_n[warr_no%3]=1;
        weapon w1=weapon(warr_no%3);
        own_weapon.push_back(w1);
        weapon_n[(warr_no+1)%3]=1;
        weapon w2=weapon((warr_no+1)%3);
        own_weapon.push_back(w2);
        weapon_total=2;
    }
    else{//dragon,iceman,lion
        weapon_n[warr_no%3]=1;
        weapon w=weapon(warr_no%3);
        own_weapon.push_back(w);
        weapon_total=1;
    }
}
void tribe::update_my_warriors(warrior *w){
    if (w->alive){
        //武士降生时调用
        own_warriors.push_back(w);
        warr_total++;
        //warr_n[w->warr_idx]++;
    }
}


//5min:lion escape
bool warrior::escape(int nHour){
    if(warr_idx!=3) return false;
    else if(loyalty<=0){
        //输出逃跑信息
        if(ptribe->color==0 && city_n<CITY_NUM+1){
            alive=false;
            printf("%03d:05 red lion %d ran away\n",nHour,warr_no);
        }
        if(ptribe->color && city_n>0){
            alive=false;
            printf("%03d:05 blue lion %d ran away\n",nHour,warr_no);
        }
        return true;
    }
    else return false;
}

//10min:march
//march 方法从让tribe的每一个武士移动

void warrior::march(){
    if(ptribe->color==0){//编号0到CITY_NUM的武士
        if(city_n<CITY_NUM+1) city_n++;
    }
    if(ptribe->color==1){//编号CITY_NUM+1到1的武士
        if(city_n>0) city_n--;
    }
    if(warr_idx==2) {HP = HP-HP/10;update_alive();} //iceman越走越弱
    if(warr_idx==3) loyalty = loyalty-K;//lion越走越胆小
    //对于lion，不判断是否活着，因为不管它忠诚度多少，接下来的march信息都要输出
}
void tribe::tribe_march(int color){
    for(int i=0;i<=CITY_NUM+1;i++){
        if(color==0)
            fields_all[i]->wR=NULL;
        else
            fields_all[i]->wB=NULL;
    }
    for(int i=0;i<warr_total;i++){
        warrior *w = own_warriors[i];
        if (w->isalive()) {
            w->march();//march结束状态发生变化的是iceman
            if(w->isalive()){
                int num = w->city_n;
                if(color==0) fields_all[num]->wR = w;
                if(color==1) fields_all[num]->wB = w;
            }
        }
    }
}

//35min
//战前：武器抢夺

void warrior::wolf_snatch(warrior *enemy,int nHour){
    if(enemy->warr_idx==4) return;
    else if (enemy->weapon_total==0|| weapon_total==10) return;
    sort(enemy->own_weapon.begin(),enemy->own_weapon.end(),cmp_snatch);
    int w0=enemy->weapon_n[0];
    int w1=enemy->weapon_n[1];
    int w2=enemy->weapon_n[2];

            //cout<<w0<<" "<<w1<<" "<<w2<<endl;
            //for(int i=0;i<enemy->weapon_total;i++)
            //  cout<<enemy->own_weapon[i].weapon_idx<<" ";
            //cout<<endl;

    int rob_num=0,rob_idx=0;
    if(w0) rob_num=w0;    //有sword抢sword
    else if(w1) {rob_num=w1;rob_idx=1;}//没有sword抢bomb
    else if(w2) {rob_num=w2;rob_idx=2;}//都没有抢arrow

    if(rob_num>10-weapon_total) rob_num=10-weapon_total;
    if(rob_num==0) return;
    get_weapons(enemy,rob_num);
    enemy->lose_weapons(rob_num);
    print_wolf_snatch(nHour,rob_num,rob_idx,enemy);


}
//抢来武器更新
void warrior::get_weapons(warrior *w,int num){
    if(num==0) return;
    for(int i=0;i<num;i++){
        int id=w->own_weapon[i].weapon_idx;
        weapon_n[id]++;
        own_weapon.push_back(w->own_weapon[i]);
    }
    weapon_total=own_weapon.size();
    return;
}

//失去武器更新：武器被抢走
void warrior::lose_weapons(int num){
    if(num==0) return;
    for(int i=0;i<num;i++){
        int id=own_weapon[i].weapon_idx;
        weapon_n[id]--; //该种武器减1
    }

    own_weapon.erase(own_weapon.begin(),own_weapon.begin()+num);
    weapon_total=own_weapon.size();

    return;
}


//抢一批武器
void warrior::win_weapons(warrior *enemy){
        if (enemy->weapon_total==0|| weapon_total==10) return;
        else{

            sort(enemy->own_weapon.begin(),enemy->own_weapon.end(),cmp_snatch);
            int rob_num=enemy->weapon_total;
            if(rob_num>10-weapon_total) rob_num=10-weapon_total;
            if(rob_num==0) return;

            get_weapons(enemy,rob_num);
            enemy->own_weapon.clear();enemy->weapon_total=0;

        }
}


int warrior::find_weapon(int id){
    if(id<0) return -1;
    if(weapon_total==0) return -1;
    int search=1;
    while(search<=weapon_total){
        if(own_weapon[id].is_weapon_ok) break;
        else {id=(id+1)%weapon_total; search++;}
    }
    if(own_weapon[id].is_weapon_ok)
        return id;
    else return -1;
}


//战斗事件


int warrior::check_weapon(){
    int count=0;
    for(int i=0;i<weapon_total;i++)
        if(own_weapon[i].is_weapon_ok)
            count++;
    return count;
}
int warrior::get_AP(int id){
    if(id==0) return ATK/5;
    if(id==1) return ATK*4/10;
    if(id==2) return ATK*3/10;
    else return 0;
}
void warrior::attack(warrior *enemy){
    sort(own_weapon.begin(),own_weapon.end(),cmp_battle());
    sort(enemy->own_weapon.begin(),enemy->own_weapon.end(),cmp_battle());

    int w1_id=0,w2_id=0,power=0,w_idx=0;

    //如果任意一方战死，或者双方都没有可以用的武器
    while(isalive() && enemy->isalive() && (weapon_total || enemy->weapon_total) ){
        //双方都活着
        //寻找可用的武器
        //printf("HP: %d , %d and weapon: %d , %d\n",w1_HP,w2_HP,w1_weapon,w2_weapon);
        power=0;
        w1_id=find_weapon(w1_id);
        //cout<<"weapon No. "<<w1_id<<endl;
        if(w1_id!=-1 && isalive()){//武器可用，则进攻
        //  cout<<" "<<ptribe->get_color()<<" attack! "<<"It's HP is "<<HP;
            w_idx=own_weapon[w1_id].weapon_idx;
            power=get_AP(own_weapon[w1_id].weapon_idx);
            //cout<<" the weapon id: "<<w_idx<<" and its power is "<<power<<endl;
            enemy->HP=enemy->HP-power;
            if(own_weapon[w1_id].weapon_idx==1) //如果武器是bomb且自己不是ninja，伤害回弹
                if(warr_idx!=1) HP=HP-power/2;
            own_weapon[w1_id].update_weapon();//更新使用的武器的寿命和是否还能用

            update_alive(); enemy->update_alive();
            if(own_weapon[w1_id].is_weapon_ok)
                w1_id=(w1_id+1)%weapon_total;
            else{

                weapon_total--;
                weapon_n[w_idx]--;
                own_weapon.erase(own_weapon.begin()+w1_id);
            }
        }
        w2_id=enemy->find_weapon(w2_id);
        if(w2_id!=-1 && enemy->isalive()){
            w_idx=enemy->own_weapon[w2_id].weapon_idx;
            power=enemy->get_AP(w_idx);
            //cout<<" the weapon id: "<<w_idx<<" and its power is "<<power<<endl;
            HP = HP-power;
            if(w_idx==1) //如果武器是bomb且自己不是ninja，伤害回弹
                if(enemy->warr_idx!=1) enemy->HP=enemy->HP-power/2;

            enemy->own_weapon[w2_id].update_weapon();//更新使用的武器的状态
            enemy->update_alive(); update_alive();

            if(enemy->own_weapon[w2_id].is_weapon_ok)
                w2_id=(w2_id+1)%(enemy->weapon_total);
            else{
                enemy->weapon_total--;
                enemy->weapon_n[w_idx]--;
                enemy->own_weapon.erase(enemy->own_weapon.begin()+w2_id);

            }
        }
        //一个回合结束
        if(isalive() && enemy->isalive()){
            int m1=weapon_n[1],m2=weapon_n[2];
            int w1=enemy->weapon_n[1],w2=enemy->weapon_n[2];
            if(m1==0 && m2==0 && w1==0 && w2==0 && get_AP(0)==0 && enemy->get_AP(1)==0)
                break;
        }
    }
}
void fields::city_battle(int nHour,int n){
    //发生在城市n的battle
    if(wR==NULL || wB==NULL) return;
    int result=0;
    if(n%2==1){
        //奇数城市，红先动手
        wR->attack(wB);
    }
    if(n%2==0){
        //偶数城市，蓝先动手
        wB->attack(wR);
    }

    if(wR->isalive() && wB->isalive())
        result=1;
    else if(!wR->isalive() && !wB->isalive())
        result=2;
    else if(wR->isalive())
        result=3;
    else if(wB->isalive())
        result=4;
    //cout<<"good game and the result is "<<result<<endl;
    city_win_weapons(result);
    report_fight(nHour,result,n);
    city_yell(nHour,result);
}
void fields::city_win_weapons(int result){
    if(result==3){//红的赢了
        if(wB->weapon_total==0) return;
        wR->win_weapons(wB);
    }
    if(result==4){//蓝的赢了
        if(wR->weapon_total==0) return;
        wB->win_weapons(wR);
    }
    //cout<<"after fight: "<<endl;
    //cout<<"red has "<<wR->own_weapon.size()<<" blue has "<<wB->own_weapon.size()<<endl;
}



//print输出
//0 min
void warrior::print_born_info(int nHour){
    string warr_type=warrior::names[warr_idx];
    if(ptribe->color==0)
        printf("%03d:00 red %s %d born\n",nHour,warr_type.c_str(),warr_no);
    if(ptribe->color==1)
        printf("%03d:00 blue %s %d born\n",nHour,warr_type.c_str(),warr_no);
    if(warr_idx==3)
        printf("Its loyalty is %d\n",loyalty);

}
//5min escape
void fields::city_escape(int nHour,int n){
    bool is_escape=false;
    if(wR!=NULL && wR->warr_idx==3){
        is_escape = wR->escape(nHour);//判断和输出逃跑信息
        if (is_escape) {wR=NULL;}
    }

    if(wB!=NULL && wB->warr_idx==3){
        is_escape = wB->escape(nHour);//判断和输出逃跑信息
        if (is_escape) {wB=NULL;}
    }

}
//10 min
void fields::print_march(int nHour){
        if (wR){
            string red_type = warrior::names[wR->warr_idx];
            printf("%03d:10 red %s %d marched to city %d with %d elements and force %d\n",
                    nHour, red_type.c_str(),wR->warr_no,wR->city_n,wR->HP,wR->ATK);
        }
        if (wB){
                    string blue_type = warrior::names[wB->warr_idx];
                    printf("%03d:10 blue %s %d marched to city %d with %d elements and force %d\n",
                            nHour, blue_type.c_str(),wB->warr_no,wB->city_n,wB->HP,wB->ATK);
                }

}
//10min 司令部攻占情况
void fields::print_takeover(int nHour,int color){
    if(color==0){
        if (wB){
            string hero=warrior::names[wB->warr_idx];
            printf("%03d:10 blue %s %d reached red headquarter with %d elements and force %d\n",
                    nHour,hero.c_str(),wB->warr_no,wB->HP,wB->ATK);
            printf("%03d:10 red headquarter was taken\n",nHour);
            gameover=true;
        }
    }
    if(color==1){
        if(wR){
            string hero=warrior::names[wR->warr_idx];
            printf("%03d:10 red %s %d reached blue headquarter with %d elements and force %d\n",
                    nHour,hero.c_str(),wR->warr_no,wR->HP,wR->ATK);
            printf("%03d:10 blue headquarter was taken\n",nHour);
            gameover=true;
        }
    }

}
//35 min wolf抢武器
void warrior::print_wolf_snatch(int nHour,int no,int w_idx,warrior *enemy){
    string pk=names[enemy->warr_idx];
    string bonus=weapons[w_idx];
    int id = enemy->warr_no;
    if(ptribe->color==0)
            printf("%03d:35 red wolf %d took %d %s from blue %s %d in city %d\n",
                    nHour,warr_no,no,bonus.c_str(),pk.c_str(),id,city_n);
    if(ptribe->color==1)
        printf("%03d:35 blue wolf %d took %d %s from red %s %d in city %d\n",
                nHour,warr_no,no,bonus.c_str(),pk.c_str(),id,city_n);
}


void fields::city_snatch(int nHour){

        if(wR==NULL || wB==NULL) return;
        else {
            if(wR->warr_idx==4 && wB->warr_idx!=4)
                wR->wolf_snatch(wB,nHour);
            else if(wR->warr_idx!=4 && wB->warr_idx==4)
                wB->wolf_snatch(wR,nHour);
            else return;
        }
        return;
}
//35min 报告战斗情况
void fields::report_fight(int nHour,int result,int n){
    string red_w=warrior::names[wR->warr_idx];
    string blue_w=warrior::names[wB->warr_idx];
    int red_id=wR->warr_no;
    int blue_id=wB->warr_no;

    if(result==1){//双方活着的平局
        printf("%03d:40 both red %s %d and blue %s %d were alive in city %d\n",
                nHour, red_w.c_str(),red_id,blue_w.c_str(),blue_id,n);
    }
    else if(result==2){//双方都死了的平局
        printf("%03d:40 both red %s %d and blue %s %d died in city %d\n",
                nHour, red_w.c_str(),red_id,blue_w.c_str(),blue_id,n);
        wR=NULL;wB=NULL;
    }
    else if(result==3){//红的赢了
        printf("%03d:40 red %s %d killed blue %s %d in city %d remaining %d elements\n",
                nHour, red_w.c_str(),red_id,blue_w.c_str(),blue_id,n,wR->HP);
        wB=NULL;
    }
    else if(result==4){//蓝的赢了
        printf("%03d:40 blue %s %d killed red %s %d in city %d remaining %d elements\n",
                nHour, blue_w.c_str(),blue_id,red_w.c_str(),red_id,n,wB->HP);
        wR=NULL;
    }
}
//35min dragon 欢呼
void fields::city_yell(int nHour, int result){
    if(result==1 || result==3){
        if(wR->warr_idx==0) wR->yell(nHour);
    }
    if(result==1 || result==4){
        if(wB->warr_idx==0) wB->yell(nHour);
    }
}
void warrior::yell(int nHour){
    if(warr_idx==0){
        if(ptribe->color==0)
            printf("%03d:40 red dragon %d yelled in city %d\n",nHour,warr_no,city_n);
        if(ptribe->color==1)
            printf("%03d:40 blue dragon %d yelled in city %d\n",nHour,warr_no,city_n);
    }
}

//50min 司令部汇报
void tribe::report_M(int nHour){
    if(color==0)
        printf("%03d:50 %d elements in red headquarter\n",nHour,elements);
    if(color==1)
        printf("%03d:50 %d elements in blue headquarter\n",nHour,elements);
}

//55 min
void warrior::report_status(int nHour){
    int w0 = weapon_n[0];
    int w1 = weapon_n[1];
    int w2 = weapon_n[2];
    if(ptribe->color==0){
        printf("%03d:55 red %s %d has %d sword %d bomb %d arrow and %d elements\n",
                nHour,names[warr_idx].c_str(),warr_no,w0,w1,w2,HP);
    }
    if(ptribe->color==1){
        printf("%03d:55 blue %s %d has %d sword %d bomb %d arrow and %d elements\n",
                nHour,names[warr_idx].c_str(),warr_no,w0,w1,w2,HP);
    }
}
void fields::city_report(int nHour){
    if(wR!=NULL && wR->isalive())
        wR->report_status(nHour);
    if(wB!=NULL && wB->isalive())
        wB->report_status(nHour);
}

string warrior::names[WARR_NUM]={"dragon","ninja","iceman","lion","wolf"};
string warrior::weapons[WEAPON_NUM]={"sword","bomb","arrow"};
int tribe::sequence[2][5]={{ 2,3,4,1,0 },{3,0,1,2,4}};
int warrior::initHP[5]={0,0,0,0,0};
int warrior::initATK[5]={0,0,0,0,0};



int main(){
    //freopen("datapub2.in","r",stdin);
    //freopen("my_out.out","w",stdout);
    int t;
    int counts=1;
    int nHour;
    bool end=false;
    cin>>t;
    while(t--){

        //接受输入
        cin>>M>>CITY_NUM>>K>>T;
        for(int i=0;i<WARR_NUM;i++)
            cin>>warrior::initHP[i];
        for(int i=0;i<WARR_NUM;i++)
            cin>>warrior::initATK[i];

        if(!fields_all.empty()) fields_all.clear();
        for(int i=0;i<=CITY_NUM+1;i++){
            fields_all.push_back(new fields(NULL,NULL));
        }
        gameover=false;end=false;nHour=0;
        tribe Red(M,0),Blue(M,1);
        cout<<"Case "<<counts<<":"<<endl;
        counts++;
        while(!gameover && !end){
            end = (nHour*60>T);
            if(!end){//1武士降生
                Red.produce(nHour);
                Blue.produce(nHour);
                end = (nHour*60+5>T);
                //cout<<"warriors are created"<<endl;
            }
            if(!end && !gameover){
                //2.lion逃跑 5min
                for(int i=1;i<=CITY_NUM;i++)
                    fields_all[i]->city_escape(nHour,i);
                end = (nHour*60+10>T);

                //cout<<"5 min happened"<<endl;
            }
            if(!end && !gameover){//nMin==10
                //3.武士行军，march
                //7.武士抵达敌军司令部
                //8.司令部被占领
                Red.tribe_march(0);
                Blue.tribe_march(1);
                fields_all[0]->print_takeover(nHour,0);
                for(int i=1;i<=CITY_NUM;i++)
                    fields_all[i]->print_march(nHour);
                fields_all[CITY_NUM+1]->print_takeover(nHour,1);

                end=(nHour*60+35>T);
                //cout<<"10 min happened"<<endl;
            }
            if(!end && !gameover){//nMin==35
                //4.wolf抢武器
                for(int i=1;i<=CITY_NUM;i++)
                    fields_all[i]->city_snatch(nHour);

                end=(nHour*60+40>T);
                //cout<<"35 min happened"<<endl;
            }
            if(!end && !gameover){//nMin==40
                //5.报告战斗情况
                //6.dragon欢呼

                for(int i=1;i<=CITY_NUM;i++)
                    fields_all[i]->city_battle(nHour,i);

                end=(nHour*60+50>T);
                //cout<<"40 min happened"<<endl;
            }
            if(!end && !gameover){//nMin==50
                //9.司令部报告生命元数量
                Red.report_M(nHour);
                Blue.report_M(nHour);
                end=(nHour*60+55>T);
                //cout<<"50 min happened"<<endl;
            }
            if(!end && !gameover){//nMin==55
                //10.武士报告情况
                for(int i=0;i<=CITY_NUM+1;i++)
                    fields_all[i]->city_report(nHour);
                //cout<<"55 min happened"<<endl;
            }
            nHour++;
            end=(nHour*60>T);
        }
    }

    return 0;
}