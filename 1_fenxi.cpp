#include<bits/stdc++.h>
using namespace std;

typedef struct words{
	int id;
	string value;
}word;


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

int main(){
	system("chcp 65001");
	string code;
	string words;
	char ch;
	int i,j,p,count,len;
	word s[500];
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

	int k=0;
	bool flag=0;//是否提前报错
	bool flag1=0;//处理符号出错
	bool flag2=0;//是否数字串
	freopen("fenxi.in","r",stdin);
	while(getline(cin,code)){
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
			else if(code[i]=='('||code[i]==')'||code[i]==';'||code[i]=='#'){
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
	}
	if(!flag) 
		for(int i=0;i<k;i++){
			cout<<"["<<s[i].id<<","<<s[i].value<<"]"<<endl;
		}
	while(true);
	return 0;
}

/*
121 * 1 = 121 ;
1 <> 2 ;
begin a := 1 ; b := 2 ; a ++ ; a + b = 4 ; end ;
*/