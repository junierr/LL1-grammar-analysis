#include<bits/stdc++.h>
using namespace std;

typedef struct words{
	int id;
	string value;
}word;

map<string,vector<vector<string> > >mapp;
/*
存文法
map[非终结符]=第一句{词语1，词语2，词语3}，第二句{词语1，...}
*/

map<string,vector<string> >FIRST,FOLLOW;

set<string> f_judge;//判断是否非终结符
set<string> t_judge;//判断是否终结符
set<string> jud;//判断非终结符是否可为空


//因为间接左递归时结果与输入规则有关，所以这里放表来定非终结符顺序而不是遍历map
string f_end[1005];//非终结符
string t_end[1005];//终结符
int ff=0,tt=0;

string all_code[1005];//输入文法
int tot=0;


string begin_="begin";
string end_="end";
string if_="if";
string then_="then";
string else_="else";
string for_="for";
string while_="while";
string do_="do";
string and_="and";
string or_="or";
string not_="not";

string table_mer[1005];//提取公共左因子后替换右部
int num_mer=0;//定义新变量


word s[500];

int k=0;
bool flag=0;//是否提前报错
bool flag1=0;//处理符号出错
bool flag2=0;//是否数字串



void ll1();
void save();//保存文法并分出非终结符和终结符
void cha();//左递归消除
void cha_();//间接左递归消除
void mer();//左公共因子提取
void mak();//构造FIRST和FOLLOW
void judge();//判断LL1,生成预测分析表

void yuce();


void fenxi(){
    string code;
	string words;
	char ch;
	int i,j,p,count,len;
	
	cout<<endl<<endl;
	printf("种别码：1 类别：关键字 begin\n");
	printf("种别码：2 类别：关键字 end\n");
	printf("种别码：3 类别：关键字 if\n");
	printf("种别码：4 类别：关键字 then\n");
	printf("种别码：5 类别：关键字 else\n");
	printf("种别码：6 类别：关键字 for\n");
	printf("种别码：7 类别：关键字 while\n");
	printf("种别码：8 类别：关键字 do\n");
	printf("种别码：9 类别：关键字 and\n");
	printf("种别码：10 类别：关键字 or\n");
	printf("种别码：11 类别：关键字 not\n");
	printf("种别码：12 类别：标识符\n");
	printf("种别码：13 类别：无符号数字串\n");
	printf("种别码：14 类别：运算符和分界符\n");


	//freopen("ll1_test.in","r",stdin);
	//while(getline(cin,code)){
		code="( a , a ) #";
		code+=' ';
		len=code.size();
		words="";
		
		for(int i=0;i<len;i++){
			if((code[i]>='a'&&code[i]<='z')||(code[i]>='A'&&code[i]<='Z')){
				words+=code[i];
				flag2=1;
			}
			else if(code[i]>='0'&&code[i]<='9'){
				words+=code[i];
			}
			else if(code[i]=='_'){
				words+=code[i];
				flag2=1;
			}
			else if(code[i]=='+'||code[i]=='-'||code[i]=='*'||code[i]=='/'){
				words+=code[i];
				flag1=1;
				flag2=1;
			}
			else if(code[i]=='>'||code[i]=='<'||code[i]=='='||code[i]==':'){
				words+=code[i];
				flag1=1;
				flag2=1;
			}
			else if(code[i]=='('||code[i]==')'||code[i]==';'||code[i]=='#'||code[i]==','){
				words+=code[i];
				flag1=1;
				flag2=1;
			}
			else if(code[i]==' '||code[i]=='	'||code[i]=='\n'){
				if(words.size()>1&&(words[0]>='0'&&words[0]<='9')&&flag2==1) {
					cout<<"run error! error:"<<words<<endl;
					flag=1;
					break;
				}
				else if(flag1==1&&words.size()>2){
					cout<<"run error! error:"<<words<<endl;
					flag=1;
					break;
				}
				else if(flag1==1&&words.size()==2){
					if(words==":="||words==">="||words=="<="||words=="<>"||words=="++"||words=="--"){
						s[k].id=14;
						s[k].value=words;
						k++;
					}
					else{
						cout<<"run error! error:"<<words<<endl;
						flag=1;
						break;
					}
				}
				else if(flag1==1&&words.size()==1){
					s[k].id=14;
					s[k].value=words;
					k++;
				}
				else if(flag2==0){
					s[k].id=13;
					s[k].value=words;
					k++;
				}
				else if(words==begin_){
					s[k].id=1;
					s[k].value=words;
					k++;
				}
				else if(words==end_){
					s[k].id=2;
					s[k].value=words;
					k++;
				}
				else if(words==if_){
					s[k].id=3;
					s[k].value=words;
					k++;
				}
				else if(words==then_){
					s[k].id=4;
					s[k].value=words;
					k++;
				}
				else if(words==else_){
					s[k].id=5;
					s[k].value=words;
					k++;
				}
				else if(words==for_){
					s[k].id=6;
					s[k].value=words;
					k++;
				}
				else if(words==while_){
					s[k].id=7;
					s[k].value=words;
					k++;
				}
				else if(words==do_){
					s[k].id=8;
					s[k].value=words;
					k++;
				}
				else if(words==and_){
					s[k].id=9;
					s[k].value=words;
					k++;
				}
				else if(words==or_){
					s[k].id=10;
					s[k].value=words;
					k++;
				}
				else if(words==not_){
					s[k].id=11;
					s[k].value=words;
					k++;
				}
				else {
					s[k].id=12;
					s[k].value=words;
					k++;
				}
				words="";
				flag1=0;
				flag2=0;
			}
			else{
				cout<<"run error! error:"<<code[i]<<endl;
				flag=1;
				break;
			}
		}
	//}
	if(!flag) 
		for(int i=0;i<k;i++){
			cout<<"["<<s[i].id<<","<<s[i].value<<"]"<<endl;
		}
	//fclose(stdin);
}

int main(){
	system("chcp 65001");
    
    //ll1
    ll1();
    
    //词法分析
	fenxi();
    yuce();
	while(true);
	return 0;
}

void ll1(){
    save();
	cha();
	cha_();
	mer();
	mak();
	judge();
}


//大致思路是用map存文法，左部的非终结符作为索引，句子为第一层vector，词语为第二层vector
void save(){
    freopen("ll1_judge.in","r",stdin);
    //cout<<"请输入文法："<<endl;
    
    while(getline(cin,all_code[tot])){
        int len=all_code[tot].size();
		string temp=all_code[tot];
        string t1="";
        int p1;
        for(int j=0;j<len;j++){
            if(temp[j]=='-'&&temp[j+1]=='>'){
                p1=j-1;
            }
        }
        for(int j=0;j<p1;j++){
            t1+=temp[j];
        }
		if(f_judge.find(t1)==f_judge.end()){
			f_judge.insert(t1);
			f_end[ff++]=t1;
		} 
		tot++;
    }
	vector<string>ve;
	int p1,p2;
	for(int i=0;i<tot;i++){
		all_code[i]+=" |";
		int len=all_code[i].size();
		string temp=all_code[i];
		for(int j=0;j<len;j++){
            if(temp[j]=='-'&&temp[j+1]=='>'){
				p1=j-1;
                p2=j+2;
            }
        }
		string t1="";
		for(int j=0;j<p1;j++){
            t1+=temp[j];
        }
		string t3="";
		for(int j=p2;j<len;j++){
			if(temp[j]==' '){
				if(t3!=""){
					if(f_judge.find(t3)==f_judge.end()&&t_judge.find(t3)==t_judge.end()&&t3!="~"){
						t_judge.insert(t3);
						t_end[tt++]=t3;
					}
					ve.push_back(t3);
				}
				t3="";
			}
			else if(temp[j]=='|'){
				if(ve.size()!=0){
					mapp[t1].push_back(ve);
				}
				ve.clear();
			}
			else {
				t3+=temp[j];
			}
		}
	}
	fclose(stdin);
	/*cout<<"f_end:"<<endl;
	for(int i=0;i<ff;i++){
		cout<<f_end[i]<<" / ";
	}
	cout<<endl<<endl;

	cout<<"t_end:"<<endl;
	for(int i=0;i<tt;i++){
		cout<<t_end[i]<<" / ";
	}
	cout<<endl<<endl;

	for(auto p:mapp){
        int len1=mapp[p.first].size();
		cout<<p.first<<":";
        for(int i=0;i<len1;i++){
            int len2=mapp[p.first][i].size();
             for(int j=0;j<len2;j++){
                 cout<<p.second[i][j]<<" ";
             }
			 cout<<" | ";
        }
		cout<<endl;
    }*/
	
}


//每个非终结符有左递归的话消一次肯定无了，所以先找该非终结符有无左递归，有的话把新非终结符加入集合，然后把左递归句子的后面项存到ve中
//ve就是新非终结符推出的句子，然后把无递归项的句子用more_ve[]存起来，这就是原递归项的新句子
void cha(){
	for(int i=0;i<ff;i++){
		int len1=mapp[f_end[i]].size();
		int flag_cha=0;
		string n1=f_end[i]+to_string(num_mer);
		for(int j=0;j<len1;j++){
			if(f_end[i]==mapp[f_end[i]][j][0]){
				flag_cha=1;
				break;
			}
		}
		if(flag_cha==0) continue;
		num_mer++;
		if(f_judge.find(n1)==f_judge.end()){
			f_judge.insert(n1);
			f_end[ff++]=n1;
		}
		vector<string>ve;
		vector<string>more_ve[1005];
		int num_ve=0;
		for(int j=0;j<len1;j++){
			ve.clear();
			if(f_end[i]==mapp[f_end[i]][j][0]){
				for(int l=1;l<mapp[f_end[i]][j].size();l++){
					ve.push_back(mapp[f_end[i]][j][l]);
				}
				ve.push_back(n1);
				mapp[n1].push_back(ve);
				ve.clear();
			}
			else{
				for(int l=0;l<mapp[f_end[i]][j].size();l++){
					more_ve[num_ve].push_back(mapp[f_end[i]][j][l]);
				}
				more_ve[num_ve].push_back(n1);
				num_ve++;
			}
		}
		ve.clear();
		ve.push_back("~");
		mapp[n1].push_back(ve);
		ve.clear();
		mapp.erase(f_end[i]);
		for(int j=0;j<num_ve;j++){
			mapp[f_end[i]].push_back(more_ve[j]);
		}
	}
	
	cout<<endl<<endl<<"消除左递归后："<<endl;
	cout<<"f_end:"<<endl;
	for(int i=0;i<ff;i++){
		cout<<f_end[i]<<" / ";
	}
	cout<<endl<<endl;

	cout<<"t_end:"<<endl;
	for(int i=0;i<tt;i++){
		cout<<t_end[i]<<" / ";
	}
	cout<<endl<<endl;

	for(int i=0;i<ff;i++){
        int len1=mapp[f_end[i]].size();
		cout<<f_end[i]<<":";
        for(int j=0;j<len1;j++){
            int len2=mapp[f_end[i]][j].size();
             for(int l=0;l<len2;l++){
                 cout<<mapp[f_end[i]][j][l]<<" ";
             }
			 cout<<" | ";
        }
		cout<<endl;
    }
}

int compare(vector<string> A,vector<string> B){
	if(A[0]==B[0]) return 1;
	else return 0;
}

//因为map的索引是string，所以每次合并一个词
void mer(){
	int flag_mer=0;
	for(int i=0;i<ff;i++){  //所有非终结符
		flag_mer=0;
		for(int j=0;j<mapp[f_end[i]].size();j++){  //对该终结符推出的所有句子
			flag_mer=0;
			int minlen=0x3f3f3f3f;
			for(int l=j+1;l<mapp[f_end[i]].size();l++){  //对之后的所有句子
				int pub=compare(mapp[f_end[i]][j],mapp[f_end[i]][l]);  //是否存在可合并句子
				if(pub!=0&&pub<minlen){
					minlen=pub;
					flag_mer=1;
				}
			}
			if(flag_mer==0) continue;
			string n1=f_end[i]+to_string(num_mer);  //构造新符号
			if(f_judge.find(n1)==f_judge.end()){  //加入非终结符号集
				f_judge.insert(n1);
				f_end[ff++]=n1;
			}
			vector<string>ve1,ve2;
			ve1.clear();
			ve1.push_back(mapp[f_end[i]][j][0]);
			ve1.push_back(n1);    //构造原非终结符的新句子
			for(int l=j;l<mapp[f_end[i]].size();l++){  //找到所有可合并该左公共因子的，合并
				ve2.clear();
				int pub=compare(mapp[f_end[i]][j],mapp[f_end[i]][l]);
				if(pub==minlen){
					int len2=mapp[f_end[i]][l].size();
					if(len2==1){  //整个句子就是合并项，补空集
						ve2.push_back("~");
					}
					else{
						for(int o=1;o<len2;o++){  //除相同项外加入到新句子中
							ve2.push_back(mapp[f_end[i]][l][o]);
						}
					}
					mapp[n1].push_back(ve2);	
				}  
			}
			string oldmap=mapp[f_end[i]][j][0];
			for(int l=j;l<mapp[f_end[i]].size();l++){ //删去原句子
				if(mapp[f_end[i]][l][0]==oldmap){
					mapp[f_end[i]].erase(mapp[f_end[i]].begin()+l);
					l--;
				}
			}
			mapp[f_end[i]].push_back(ve1);  //加入新句子
			if(flag_mer==1) {  
				num_mer++;  //构造新符号用
				j--;
			}
		}
	}

	cout<<endl<<endl<<"合并左公共因子后："<<endl;
	cout<<"f_end:"<<endl;
	for(int i=0;i<ff;i++){
		cout<<f_end[i]<<" / ";
	}
	cout<<endl<<endl;

	cout<<"t_end:"<<endl;
	for(int i=0;i<tt;i++){
		cout<<t_end[i]<<" / ";
	}
	cout<<endl<<endl;

	for(int i=0;i<ff;i++){
        int len1=mapp[f_end[i]].size();
		cout<<f_end[i]<<":";
        for(int j=0;j<len1;j++){
            int len2=mapp[f_end[i]][j].size();
             for(int l=0;l<len2;l++){
                 cout<<mapp[f_end[i]][j][l]<<" ";
             }
			 cout<<" | ";
        }
		cout<<endl;
    }
}


// 先找到可推出空集的项，后面多处会用到
//FIRST：对于右部首个是终结符的，直接加入，是非终结符的，将其first集加入，如果该非终结符可以为空，将后一个first加入，直到右部加完或不可为空
//死循环到不再变化为止
//FOLLOW：从后往前，把最后是非终结符的和当前最后可以为空的非终结符前面那个非终结符的FOLLOW加上左部的FOLLOW
//然后在所有右部找非终结符，将其右部第一个词语的FIRST集加入该非终结符的FOLLOW
//死循环到不再变化为止
void mak(){

	//FIRST
	for(int i=0;i<ff;i++){
			for(int j=0;j<mapp[f_end[i]].size();j++){
				if(mapp[f_end[i]][j][0]=="~"&&jud.find(f_end[i])==jud.end()){
					jud.insert(f_end[i]);
				}
			}
		}
	int flag_change=1;
	//找所有可能为空的非终结符
	while(flag_change){  
		flag_change=0;
		for(int i=0;i<ff;i++){
			if(jud.find(f_end[i])!=jud.end()) continue;
			for(int j=0;j<mapp[f_end[i]].size();j++){
				int flag_kong=0;
				for(int l=0;l<mapp[f_end[i]][j].size();l++){
					string str=mapp[f_end[i]][j][l];
					if(str!="~"&&t_judge.find(str)!=t_judge.end()){
						flag_kong=1;
						break;
					}
					else if(jud.find(str)==jud.end()){
						flag_kong=1;
						break;
					}
				}
				if(flag_kong==0){
					jud.insert(f_end[i]);
					flag_change=1;
				}
				if(flag_change==1) break;
			}
		}
	}
	for(int i=0;i<ff;i++){
		if(jud.find(f_end[i])!=jud.end()){
			FIRST[f_end[i]].push_back("~");
		}
	}

	int flag_first=1;
	while(flag_first){
		flag_first=0;
		for(int i=0;i<ff;i++){
			for(int j=0;j<mapp[f_end[i]].size();j++){
				string fir=mapp[f_end[i]][j][0];
				if(t_judge.find(fir)!=t_judge.end()||fir=="~"){ //是终结符并且没有加入
					vector<string>::iterator result=find(FIRST[f_end[i]].begin(),FIRST[f_end[i]].end(),fir);
					if(result==FIRST[f_end[i]].end()){
						FIRST[f_end[i]].push_back(fir);
						flag_first=1;
					}
				}
				else{ //是非终结符
					for(int l=0;l<FIRST[fir].size();l++){    //将fir的FIRST集加入到当前非终结符的FIRST集中
						vector<string>::iterator result=find(FIRST[f_end[i]].begin(),FIRST[f_end[i]].end(),FIRST[fir][l]);
						if(result==FIRST[f_end[i]].end()){
							FIRST[f_end[i]].push_back(FIRST[fir][l]);
							flag_first=1;
						}
					}
					if(jud.find(fir)!=jud.end()){  //可为空
					int pre=0;
					for(int l=1;l<mapp[f_end[i]][j].size();l++){  //当前可为空则往后面推
						if(pre==1) break;
						fir=mapp[f_end[i]][j][l];
						if(jud.find(fir)==jud.end()) pre=1;  
						if(t_judge.find(fir)!=t_judge.end()){  //是终结符
							vector<string>::iterator result=find(FIRST[f_end[i]].begin(),FIRST[f_end[i]].end(),fir);
							if(result==FIRST[f_end[i]].end()){
								FIRST[f_end[i]].push_back(fir);
								flag_first=1;
							}
							continue;
						}
						for(int o=0;o<FIRST[fir].size();o++){  //是非终结符
							vector<string>::iterator result=find(FIRST[f_end[i]].begin(),FIRST[f_end[i]].end(),FIRST[fir][o]);
							if(result==FIRST[f_end[i]].end()){
								FIRST[f_end[i]].push_back(FIRST[fir][o]);
								flag_first=1;
							}
						}
					}
					}
				}
			}
		}
	}
	for(int i=0;i<tt;i++){
		FIRST[t_end[i]].push_back(t_end[i]);
	}
	cout<<endl<<endl<<"FIRST:"<<endl;
	for(auto p:FIRST){
		cout<<p.first<<":";
		for(int i=0;i<p.second.size();i++){
			cout<<p.second[i]<<" | ";
		}
		cout<<endl;
	}

	//FOLLOW
	FOLLOW[f_end[0]].push_back("#");
	int flag_follow=1;
	while(flag_follow){
		flag_follow=0;
		for(int i=0;i<ff;i++){
			for(int j=0;j<mapp[f_end[i]].size();j++){
				int pre=0;
				for(int l=mapp[f_end[i]][j].size()-1;l>=0;l--){
					if(pre==0){
						if(f_judge.find(mapp[f_end[i]][j][l])!=f_judge.end()){ //如果最后一个是非终结符
						for(int o=0;o<FOLLOW[f_end[i]].size();o++){
							vector<string>::iterator result=find(FOLLOW[mapp[f_end[i]][j][l]].begin(),FOLLOW[mapp[f_end[i]][j][l]].end(),FOLLOW[f_end[i]][o]);
							if(result==FOLLOW[mapp[f_end[i]][j][l]].end()){
								FOLLOW[mapp[f_end[i]][j][l]].push_back(FOLLOW[f_end[i]][o]);
								flag_follow=1;
							}
						}
						}
					}
					if(jud.find(mapp[f_end[i]][j][l])==jud.end()) pre=1;
					if(l==0) continue;
					if(f_judge.find(mapp[f_end[i]][j][l-1])!=f_judge.end()){
						for(int o=0;o<FIRST[mapp[f_end[i]][j][l]].size();o++){
							if(FIRST[mapp[f_end[i]][j][l]][o]=="~") continue;
							vector<string>::iterator result=find(FOLLOW[mapp[f_end[i]][j][l-1]].begin(),FOLLOW[mapp[f_end[i]][j][l-1]].end(),FIRST[mapp[f_end[i]][j][l]][o]);
							if(result==FOLLOW[mapp[f_end[i]][j][l-1]].end()){
								FOLLOW[mapp[f_end[i]][j][l-1]].push_back(FIRST[mapp[f_end[i]][j][l]][o]);
								flag_follow=1;
							}
						}
					}
				}
			}
		}
	}
	cout<<endl<<endl<<"FOLLOW:"<<endl;
	for(auto p:FOLLOW){
		cout<<p.first<<":";
		for(int i=0;i<p.second.size();i++){
			cout<<p.second[i]<<" | ";
		}
		cout<<endl;
	}

} 

vector<string> map_a[105][105];//预测分析表
//非终结符即对应f_end下标
map<string,int> tt_end;//终结符对应下标
map<string,int> ff_end;//非终结符对应下标


//老老实实构造预测分析表（处理空集的情况）
//把右部的FIRST集全部填上，如果右部可为空，将左部的FOLLOW填上
void judge(){
	int flag_judge=0;
	for(int i=0;i<ff;i++){
		for(int j=0;j<tt;j++){
			map_a[i][j].clear();
		}
	}
	t_end[tt++]="#";
	for(int i=0;i<tt;i++){
		tt_end[t_end[i]]=i;
	}
	for(int i=0;i<ff;i++){
		ff_end[f_end[i]]=i;
	}
	for(int i=0;i<ff;i++){
		for(int j=0;j<mapp[f_end[i]].size();j++){
			int pre=1;
			for(int l=0;l<mapp[f_end[i]][j].size();j++){
				if(pre==1){  //是空集，取下一个非终结符的first
					pre=0;
					if(mapp[f_end[i]][j].size()==1&&mapp[f_end[i]][j][0]=="~"){
						for(int oo=0;oo<FOLLOW[f_end[i]].size();oo++){
									if(map_a[i][tt_end[FOLLOW[f_end[i]][oo]]].size()!=0){
										flag_judge=1;
										break;
									}
									else{
										map_a[i][tt_end[FOLLOW[f_end[i]][oo]]].push_back("~");
									}
								}
					}
					for(int o=0;o<FIRST[mapp[f_end[i]][j][l]].size();o++){
						if(FIRST[mapp[f_end[i]][j][l]][o]=="~"){
							pre=1;
							if(l==mapp[f_end[i]][j].size()-1){  //如果全是空集
								for(int oo=0;oo<FOLLOW[f_end[i]].size();oo++){
									if(map_a[i][tt_end[FOLLOW[f_end[i]][oo]]].size()!=0){
										flag_judge=1;
										break;
									}
									else{
										map_a[i][tt_end[FOLLOW[f_end[i]][oo]]].push_back("~");
									}
								}
							}
							continue;
						}
						if(map_a[i][tt_end[FIRST[mapp[f_end[i]][j][l]][o]]].size()!=0){
							flag_judge=1;
							break;
						}
						for(int oo=0;oo<mapp[f_end[i]][j].size();oo++){
							map_a[i][tt_end[FIRST[mapp[f_end[i]][j][l]][o]]].push_back(mapp[f_end[i]][j][oo]);
						}
					}
				}
				if(pre==0) break;
				if(flag_judge==1) break;
			}
			if(flag_judge==1) break;
		}
		if(flag_judge==1) break;
	}

	cout<<endl<<endl;
	if(flag_judge) cout<<"no"<<endl;
	else {
		cout<<"预测分析表："<<endl;
		for(int i=0;i<ff;i++){
			for(int j=0;j<tt;j++){
				if(map_a[i][j].size()!=0){
					cout<<"["<<f_end[i]<<","<<t_end[j]<<"]=";
					for(int l=0;l<map_a[i][j].size();l++) cout<<map_a[i][j][l]<<" ";
					cout<<endl;
				}
			}
		}
	}
}

stack<string> sta;//栈
stack<string> sta_;//用来暂存输出
string ch;//当前输入
queue<string> q;//剩余输入
queue<string> q_;//用来暂存输出

//老老实实预测
//没啥好讲的，归约-移进两种操作，碰到不匹配就弹出，主要是栈和队列的操作
void yuce(){
	while(!q.empty()) q.pop(),q_.pop();
	while(!sta.empty()) sta.pop(),sta_.pop();
	sta.push("#");
	sta.push(f_end[0]);
	for(int i=0;i<k;i++) q.push(s[i].value);
	int flag_yuce=0;
	int flag_ch=1;
	while(!q.empty()){
		if(sta.top()=="~"){
			sta.pop();
			continue;
		}
		if(flag_ch==1) ch=q.front();
		if(flag_ch==1) q.pop();
		flag_ch=0;
		cout<<"栈：";
		while(!sta.empty()){
			cout<<sta.top()<<" ";
			sta_.push(sta.top());
			sta.pop();
		}
		cout<<"; ";
		while(!sta_.empty()){sta.push(sta_.top());sta_.pop();}
		cout<<"当前输入:"<<ch<<"; ";
		cout<<"剩余输入：";
		while(!q.empty()){
			cout<<q.front()<<" ";
			q_.push(q.front());
			q.pop();
		}
		cout<<"; ";
		while(!q_.empty()){q.push(q_.front());q_.pop();}
		if(ch!=sta.top()){
			if(t_judge.find(sta.top())!=t_judge.end()){  //是终结符且不相等
				flag_yuce=1;
				break;
			}
			else{
				if(map_a[ff_end[sta.top()]][tt_end[ch]].size()==0){flag_yuce=1;break;}
				else{
					string t1=sta.top();
					sta.pop();
					for(int i=map_a[ff_end[t1]][tt_end[ch]].size()-1;i>=0;i--){
						sta.push(map_a[ff_end[t1]][tt_end[ch]][i]);
					}
					cout<<"所用产生式："<<t1<<" -> ";
					for(int i=0;i<map_a[ff_end[t1]][tt_end[ch]].size();i++){
						cout<<map_a[ff_end[t1]][tt_end[ch]][i]<<" ";
					}
					cout<<endl;
				}
			}
		}
		else{
			flag_ch=1;
			sta.pop();
			cout<<"所用产生式：空"<<endl;
		}
	}
	if(flag_yuce) cout<<"式子错误！"<<endl;
	else if(sta.size()!=0) cout<<"式子错误！"<<endl;
	else cout<<"成功！"<<endl;
	//else if(sta.top()!="#"||ch!="#") cout<<"式子错误！"<<endl;
}



//消除间接左递归
/*
for （i＝1；i<=n；i++）
   for （j＝1；j<=i－1；j++）
   { 把形如Ai→Ajγ的产生式改写成Ai→δ1γ /δ2γ /…/δkγ 
       其中Aj→δ1 /δ2 /…/δk是关于的Aj全部规则；
       消除Ai规则中的直接左递归；
   }
去掉多余的规则。
*/
void cha_(){
	for(int i=0;i<ff;i++){
		for(int j=0;j<i;j++){
			for(int l=0;l<mapp[f_end[i]].size();l++){
				int num=0;
				while(num<mapp[f_end[i]][l].size()&&mapp[f_end[i]][l][num]=="~") num++;//处理前面推出空的情况
				if(num==mapp[f_end[i]][l].size()) continue;

				if(mapp[f_end[i]][l][num]==f_end[j]){
					//cout<<"~~~~~~~~~~~~~~~~~:"<<f_end[j]<<endl;
					for(int o=0;o<mapp[f_end[j]].size();o++){
						vector<string> r1;
						r1.clear();
						for(int oo=0;oo<mapp[f_end[j]][o].size();oo++){
							r1.push_back(mapp[f_end[j]][o][oo]);
						}
						for(int oo=1;oo<mapp[f_end[i]][l].size();oo++){
							r1.push_back(mapp[f_end[i]][l][oo]);
						}
						mapp[f_end[i]].push_back(r1);
					}
					vector<vector<string> >::iterator it=find(mapp[f_end[i]].begin(),mapp[f_end[i]].end(),mapp[f_end[i]][l]);
					mapp[f_end[i]].erase(it);
					l--;
					cha();//消除直接左递归
				}
			}
		}
	}
	//化简文法
	for(int i=0;i<ff;i++){		
		set<vector<string> > s(mapp[f_end[i]].begin(),mapp[f_end[i]].end());
		mapp[f_end[i]].clear();
		mapp[f_end[i]].assign(s.begin(),s.end());
	}
}