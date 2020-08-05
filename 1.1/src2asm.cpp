#include<bits/stdc++.h>
using namespace std;
#define elif else if
ifstream fin;
string getword(){
	char c,tmp=0;
	string ret;
	fin>>c;
	if(c=='\'' or c=='\"'){
		while(!fin.eof()){
			if((tmp=fin.get())==c)break;
			ret+=tmp;
		}
	}else{
		fin.putback(c);
		fin>>ret;
	}
	return ret;
}
#define cout fout
ofstream fout;
int main(int argc,char** argv){
	if(argc<3)return 1;
	fin.open(argv[1]);
	fout.open(argv[2]);
	int bits=32,adr=0;
	map<string,int> label;
	auto jump=[&label,bits]()->int{
		string dst=getword();
		cout<<"\n\t"<<(bits==32?"dd ":"dw ")<<dst<<endl;
		return bits==32?5:3;
	};
	auto calcs=[bits,&adr](int c){
		int n=0x57;
		if(bits==32)n+=0x0c;
		int src;fin>>src;
		string dst=getword();
		string b=(bits==32?(adr+=4,"dd "):(adr+=2,"dw "));
		if(dst[0]=='*'){
			n-=0x30;
			dst=dst.substr(1);
			b="db ";
			adr--;
		}
		int code=n+c;
		//clog<<"db 0x"<<hex<<code<<dec<<","<<src<<"\n\t"<<(bits==32?"dd ":"dw ")<<dst<<endl;
		cout<<"db 0x"<<hex<<code<<dec<<","<<src<<"\n\t"<<b<<dst<<endl;
		adr++;
		return;
	};
	bool pkg=false;
	while(1){
		string cmd;
		fin>>cmd;
		if(cmd=="")break;
		if(cmd[0]==';')continue;
		string s;
		if(cmd=="exit")cout<<"db 0x09"<<endl,adr++;
		elif(cmd=="bits")fin>>bits;
		elif(cmd=="nop")cout<<"db 0x0a"<<endl,adr++;
		elif(cmd=="forever$")cout<<"db 0x0b"<<endl,adr++;
		elif(cmd=="pause")cout<<"db 0x0c"<<endl,adr++;
		elif(cmd=="script"){
			string type=getword();
			if(type=="python")cout<<"db 0x11,0"<<endl,adr+=2;
			elif(type=="java")cout<<"db 0x10,0"<<endl,adr+=2;
			elif(type=="text")cout<<"db 0x12,0"<<endl,adr+=2;
			elif(type=="norun")cout<<"db 0x0d"<<endl,adr++;
			string name=getword();
			string cont=getword();
			cout<<"\tdb "<<name.length()<<
				", \""<<name<<"\"\n\t"<<
				"dd "<<cont.length()<<
				"\n\tdb \""<<cont<<"\""<<endl;
			adr=adr+name.length()+1+cont.length()+4;
		}elif(cmd=="cls" or cmd=="clear")cout<<"db 0x0f"<<endl,adr++;
		elif(cmd=="shell"){
			string shd=getword();
			cout<<"db 0x13\n\t"<<
				"db "<<shd.length()<<
				", \""<<shd<<"\""<<endl;
		}elif(cmd=="exits")cout<<"db 0x14,"<<getword()<<endl;
		elif(cmd=="input")cout<<(bits==32?"db 0x15,":"db 0x17")<<getword()<<endl,adr+=2;
		elif(cmd=="print")cout<<(bits==32?"db 0x16,":"db 0x18")<<getword()<<endl,adr+=2;
		elif(cmd=="getch")cout<<"db 0x19,"<<getword()<<endl,adr+=2;
		elif(cmd=="getchar")cout<<"db 0x1a,"<<getword()<<endl,adr+=2;
		elif(cmd=="set"){
			string str=getword();
			cout<<(bits==32?"db 0x1c,":"db 0x1b")<<str<<(bits==32?"\n\tdd ":"\n\tdw ")<<getword()<<endl;
		}
		elif(cmd=="mov"){
			string dst=getword();string src=getword();
			if(src==".text"){
				src=getword();
				cout<<"db "<<(bits==32?"0x22,":"0x21,")<<dst<<"\n\tdw "<<src<<endl;
			}else cout<<"db "<<(bits==32?"0x1e,":"0x1d,")<<dst<<","<<src<<endl;
			adr+=4;
		}elif(cmd=="movs"){
			string dst=getword();string src=getword();
			if(src==".text"){
				src=getword();
				cout<<"db 0x23,"<<dst<<"\n\tdw "<<src<<endl;
			}else cout<<"db 0x1f,"<<dst<<","<<src<<endl;
			adr+=4;
		}elif(cmd=="movsl"){
			string dst=getword();string src=getword();string len=getword();
			if(src==".text"){
				src=getword();
				cout<<"db 0x24,"<<dst<<"\n\tdw "<<src<<","<<len<<endl;
			}else cout<<"db 0x20,"<<dst<<","<<src<<","<<len<<endl;
			adr+=6;
		}elif(cmd=="jmp")cout<<"db "<<(bits==32?"0x26":"0x25")<<"\n\t",adr+=jump();
		elif(cmd=="int")cout<<"db 0x70,"<<getword()<<endl,adr+=2;
		elif(cmd=="seted")cout<<"db 0x71\n\tdd "<<getword()<<endl,adr+=2;
		elif(cmd=="rep")cout<<"db 0x74,"<<getword()<<"\n\t",adr+=2;
		elif(cmd=="inc")cout<<"db 0x76,"<<getword()<<endl,adr+=2;
		elif(cmd=="dec")cout<<"db 0x77,"<<getword()<<endl,adr+=2;
		elif(cmd=="jz")cout<<"db "<<(bits==32?"0x78,":"0x79,")<<getword(),adr+=jump();
		elif(cmd=="jn")cout<<"db "<<(bits==32?"0x7a,":"0x7b,")<<getword(),adr+=jump();
		elif(cmd=="jp")cout<<"db "<<(bits==32?"0x7c,":"0x7d,")<<getword(),adr+=jump();
		elif(cmd=="jnz")cout<<"db "<<(bits==32?"0x7e,":"0x7f,")<<getword(),adr+=jump();
		elif(cmd=="add")calcs(1);
		elif(cmd=="sub")calcs(2);
		elif(cmd=="mul")calcs(3);
		elif(cmd=="div")calcs(4);
		elif(cmd=="mod")calcs(5);
		elif(cmd=="shl")calcs(6);
		elif(cmd=="shr")calcs(7);
		elif(cmd=="or")calcs(8);
		elif(cmd=="and")calcs(9);
		elif(cmd=="not")calcs(10);
		elif(cmd=="xor")calcs(11);
		elif(cmd=="puts")cout<<"db 0x88,"<<getword()<<endl,adr+=2;
		elif(cmd=="putsl"){
			string cont=getword();
			cout<<"db 0x89,"<<cont.length()<<"\n\tdb \""<<cont<<"\""<<endl;
			adr=adr+2+cont.length();
		}
		elif(cmd=="call")cout<<"db "<<(bits==32?"0x95":"0x94")<<"\n\t"<<(bits==32?"dd ":"dw ")<<getword()<<endl,adr+=(bits==32?5:3);
		elif(cmd=="ret" or cmd=="return")cout<<"db 0x96"<<endl,adr++;
		elif(cmd=="push")cout<<"db "<<(bits==32?"0x8c":"0x8b")<<"\n\t"<<(bits==32?"dd ":"dw ")<<getword()<<endl,adr+=(bits==32?5:3);
		elif(cmd=="pop")cout<<"db "<<(bits==32?"0x8f,":"0x8e,")<<getword()<<endl,adr+=2;
		elif(cmd=="pushm")cout<<"db "<<(bits==32?"0x98,":"0x97,")<<getword()<<endl,adr+=2;
		elif(cmd=="putsp"){
			s=getword();
			cout<<"db "<<(bits==32?"0x91,":"0x87,")<<s<<"\n\t"<<(bits==32?"dd ":"dw ")<<getword()<<endl;
			adr+=(bits==32?6:4);
		}
		elif(cmd=="putspm"){
			s=getword();
			cout<<"db "<<(bits==32?"0x93,":"0x92,")<<s<<","<<getword()<<endl;
			adr+=3;
		}
		elif(cmd=="getsp"){
			s=getword();
			cout<<"db "<<(bits==32?"0x9a,":"0x99,")<<s<<","<<getword()<<endl;
			adr+=3;
		}
		elif(cmd=="sqrt"){
			s=getword();cout<<"db 0x9b,"<<s<<"\n\tdd "<<getword()<<endl;adr+=6;
		}
		elif(cmd=="sqrtm"){
			s=getword();cout<<"db 0x9c,"<<s<<","<<getword()<<endl;adr+=3;
		}
		elif(cmd=="je"){
			s=getword();cout<<"db 0xa3,"<<s<<"\n\tdd "<<getword(),adr+=jump();
		}
		elif(cmd=="jl"){
			s=getword();cout<<"db 0xa4,"<<s<<"\n\tdd "<<getword(),adr+=jump();
		}
		elif(cmd=="jg"){
			s=getword();cout<<"db 0xa5,"<<s<<"\n\tdd "<<getword(),adr+=jump();
		}
		elif(cmd=="jne"){
			s=getword();cout<<"db 0xa6,"<<s<<"\n\tdd "<<getword(),adr+=jump();
		}
		elif(cmd=="jng" or cmd=="jle"){
			s=getword();cout<<"db 0xa7,"<<s<<"\n\tdd "<<getword(),adr+=jump();
		}
		elif(cmd=="jnl" or cmd=="jge"){
			s=getword();cout<<"db 0xa8,"<<s<<"\n\tdd "<<getword(),adr+=jump();
		}
		elif(cmd=="jem"){
			s=getword();cout<<"db 0x9d,"<<s<<","<<getword(),adr+=jump();
		}
		elif(cmd=="jlm"){
			s=getword();cout<<"db 0x9e,"<<s<<","<<getword(),adr+=jump();
		}
		elif(cmd=="jgm"){
			s=getword();cout<<"db 0x9f,"<<s<<","<<getword(),adr+=jump();
		}
		elif(cmd=="jnem"){
			s=getword();cout<<"db 0xa0,"<<s<<","<<getword(),adr+=jump();
		}
		elif(cmd=="jngm" or cmd=="jlem"){
			s=getword();cout<<"db 0xa1,"<<s<<","<<getword(),adr+=jump();
		}
		elif(cmd=="jnlm" or cmd=="jgem"){
			s=getword();cout<<"db 0xa2,"<<s<<","<<getword(),adr+=jump();
		}elif(cmd=="import"){
			s=getword();
			cout<<"db 0xa9,"<<s.length()<<",\""<<s<<"\""<<endl;
			adr=adr+2+s.length();
		}elif(cmd=="callpkg"){
			s=getword();
			cout<<"db 0xab,"<<s<<"\n\tdw "<<getword()<<endl,adr+=6;
		}elif(cmd=="package")cout<<"db 0x08\n\tdw 0000"<<endl,adr+=3,pkg=true;
		elif(cmd=="importn")cout<<"db 0xaa\n\tdd "<<getword()<<endl,adr+=5;
		elif(cmd=="align"){
			int a;
			fin>>a;
			cout<<"align "<<a<<endl;
			adr=adr+(a-adr%a);
		}elif(cmd=="global"){
			label[getword()]=adr;
		}
		else cout<<cmd<<endl;
	}
	fin.close();
	if(pkg){
		fout.seekp(13);
		char s[8];
		sprintf(s,"%4d",adr);
		fout.write(s,4);
		fout.seekp(0,ios::end);
		fout<<"dw "<<label.size()<<endl; 
		for(auto b:label){
			cout<<"dw "<<b.second<<endl;
		}
	}
	return 0;
}
#undef cout
