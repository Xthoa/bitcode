#define proj_ver 1.0

#include<bits/stdc++.h>
using namespace std;
#include<stdio.h>
#include<conio.h>
#define elif else if
vector<string> pkg={"prime.pkg"};
class err{
	public:
	string s;
	err(string r){
		s=r;
	}
};
class ecp{
	public:
	string s;
	ecp(string r){
		s=r;
	}
};
char *cs,*ds,*pc,*ss,*esp;
int len;
inline char read1(){return *(pc++);}
inline short read2(){
	short ret=*(short*)pc;
	pc+=2;
	return ret;
}
inline int read4(){
	int ret=*(int*)pc;
	pc+=4;
	return ret;
}
inline string read(int len){
	string ret=string(pc,len);
	pc+=len;
	return ret;
}
inline char& data1(int idx){return ds[idx];}
inline short& data2(int idx){return *(short*)(ds+idx);}
inline int& data4(int idx){return *(int*)(ds+idx);}
inline char text1(int idx){return cs[idx];}
inline short text2(int idx){return *(short*)(cs+idx);}
inline int text4(int idx){return *(int*)(cs+idx);}
inline string text(int idx,int len=0){
	string ret;
	if(len)ret=string(cs+idx,len);
	else ret=string(cs+idx);
	return ret;
}
inline void push1(char c){*(esp++)=c;}
inline void push2(short s){*(short*)esp=s;esp+=2;}
inline void push4(int i){*(int*)esp=i;esp+=4;}
inline char pop1(){return *(--esp);}
inline short pop2(){return *(short*)(esp-=2);}
inline int pop4(){return *(int*)(esp-=4);}
bool clocks=true;
struct package{
	int no;
	string name;
	char* buf;
	int len;
};
vector<package> packs;
int curpack;
void idt(char code){
	if(code==3)throw ecp("Int3");
}
void seted(int code){
	if(code==1)clocks=!clocks;
	elif(code==2)cout<<"Hello world!"<<endl;
	elif(code==3)cout<<hex;
	elif(code==4)cout<<dec;
	elif(code==5)cout<<oct;
}
void calc(int& dst,int src,char opr){
	if(opr==0x00)dst=src;
	elif(opr==0x01)dst+=src;
	elif(opr==0x02)dst-=src;
	elif(opr==0x03)dst*=src;
	elif(opr==0x04){
		if(src==0)throw err("ZeroDivisionError");
		dst/=src;
	}elif(opr==0x05){
		if(src==0)throw err("ZeroDivisionError");
		dst%=src;
	}
	elif(opr==0x06)dst<<=src;
	elif(opr==0x07)dst>>=src;
	elif(opr==0x08)dst|=src;
	elif(opr==0x09)dst&=src;
	elif(opr==0x0a)dst=~src;
	elif(opr==0x0b)dst^=src;
}
bool runcode(char code);
bool runcmd(){
	char code=read1();
	return runcode(code);
}
string fname;
int fact(int x){
	return x==1?1:fact(x-1)*x; 
}
void condjmp(bool cond,int bts){
	if(cond)runcode(bts==32?0x26:0x25);
	else pc+=(bts/8);
}
bool existpack(string pack){
	for(auto p:packs){
		if(p.name==pack)return true;
	}
	return false;
}
void import(string str){
	if(existpack(str))throw ecp("Package Already Exist"); 
	ifstream fin(str,ios::ate);
	if(!fin)throw err("Package Not Found");
	package p;
	p.name=str;
	auto pi=find(pkg.begin(),pkg.end(),str);
	if(pi==pkg.end()){
		cout<<"Package Global Temporary Identifier : "<<pkg.size()<<endl;
		pkg.push_back(str);
	}
	p.no=pi-pkg.begin();
	p.buf=new char[p.len=fin.tellg()];
	fin.seekg(0);
	fin.read(p.buf,p.len);
	if(p.buf[0]!=0x08)throw err("<"+str+"> is not a package");
	cout<<"Package Local Identifier : "<<packs.size()<<endl;
	packs.push_back(p);
}
bool compare(int dst,int src,int opr){
	if(opr==0)return dst==src;
	if(opr==1)return dst<src;
	if(opr==2)return dst>src;
	if(opr==3)return dst!=src;
	if(opr==4)return dst<=src;
	if(opr==5)return dst>=src;
}
bool runcode(char c){
	int r,r1,r2;
	unsigned char code=c;
	//cout<<hex<<(int)code<<endl;
	if(code==0x09)return false;
	elif(code==0x0a)asm("nop");
	elif(code==0x0b)while(1);
	elif(code==0x0c)system("pause");
	elif(code==0x0d){
		int slen=read1();
		cout<<slen<<endl;
		ofstream fout(fname=read(slen));
		cout<<fname<<endl;
		slen=read4();
		cout<<slen<<endl;
		fout.write(pc,slen);
		pc+=slen;
		fout.close();
	}elif(code==0x0e){
		int slen=read1();
		if(slen==0x00)return runcode(0x0d);
		ofstream fout(fname=read(slen));
		int ofst=read4();
		slen=read4();
		fout.write(cs+ofst,slen);
		fout.close();
	}elif(code==0x0f)system("cls");
	elif(code==0x10){
		runcode(0x0e);
		system(("java "+fname).c_str());
	}elif(code==0x11){
		runcode(0x0e);
		system(("python "+fname).c_str());
	}elif(code==0x12){
		runcode(0x0e);
		system(fname.c_str());
	}elif(code==0x13)system(string(pc,r=read1()).c_str()),pc+=r;
	elif(code==0x14)exit(read2());
	elif(code==0x15)cin>>data4(read1());
	elif(code==0x16)cout<<data4(read1())<<endl;
	elif(code==0x17)cin>>data2(read1());
	elif(code==0x18)cout<<data2(read1())<<endl;
	elif(code==0x19)data1(read1())=getch();
	elif(code==0x1a)data1(read1())=getchar();
	elif(code==0x1b)data2(read1())=read2();
	elif(code==0x1c)data4(read1())=read4();
	elif(code==0x1d){
		r=read1();
		data2(r)=data2(read1());
	}elif(code==0x1e){
		r=read1();
		data4(r)=data4(read1());
	}elif(code==0x1f){
		r=read1();
		strcpy(ds+r,ds+read1());
	}elif(code==0x20){
		r=read1();
		r1=read1();
		memcpy(ds+r,ds+r1,read2());
	}elif(code==0x21){
		r=read1();
		data2(r)=text2(read2());
	}elif(code==0x22){
		r=read1();
		data4(r)=text4(read2());
	}elif(code==0x23){
		r=read1();
		strcpy(ds+r,cs+read2());
	}elif(code==0x24){
		r=read1();
		r1=read2();
		memcpy(ds+r,cs+r1,read2());
	}elif(code==0x25)pc=cs+read2();
	elif(code==0x26)pc=cs+read4();
	elif(0x27<=code and code<0x33){
		r=read1();
		calc((int&)data2(r),data2(read1()),code-0x27);
	}elif(0x33<=code and code<0x3f){
		r=read1();
		calc(data4(r),data4(read1()),code-0x33);
	}elif(0x57<=code and code<0x63){
		r=read1();
		calc((int&)data2(r),read2(),code-0x57);
	}elif(0x63<=code and code<0x6f){
		r=read1();
		calc(data4(r),read4(),code-0x63);
	}elif(code==0x70)idt(read1());
	elif(code==0x71)seted(read4());
	elif(code==0x74){
		r=read1();data4(r)=fact(read2());
	}
	elif(code==0x75){
		r=read1();
		r1=pc-cs;
		while(r--){if(!runcode(r))return false;}
		pc=r1+cs;
	}elif(code==0x76)data4(read1())++;
	elif(code==0x77)data4(read1())--;
	elif(code==0x78)condjmp(data4(read1())==0,32);
	elif(code==0x79)condjmp(data2(read1())==0,16);
	elif(code==0x7a)condjmp(data4(read1())<0,32);
	elif(code==0x7b)condjmp(data2(read1())<0,16);
	elif(code==0x7c)condjmp(data4(read1())>0,32);
	elif(code==0x7d)condjmp(data2(read1())>0,16);
	elif(code==0x7e)condjmp(data4(read1())!=0,32);
	elif(code==0x7f)condjmp(data2(read1())!=0,16);
	elif(code==0x88)cout<<(char*)(ds+read1())<<endl;
	elif(code==0x89){
		r=read1();
		while(r--)cout<<read1();
		cout<<endl;
	}elif(code==0x8b)push2(read2());
	elif(code==0x8c)push4(read4());
	elif(code==0x8e)data2(read1())=pop2();
	elif(code==0x8f)data4(read1())=pop4();
	elif(code==0x90){
		r=read1();
		*(short*)(esp+r)=read2();
	}elif(code==0x91){
		r=read1();
		*(int*)(esp+r)=read4();
	}elif(code==0x92){
		r=read1();
		*(short*)(esp+r)=data2(read1());
	}elif(code==0x93){
		r=read1();
		*(int*)(esp+r)=data4(read1());
	}elif(code==0x94){
		push4(pc-cs+2);
		pc=cs+read2();
	}elif(code==0x95){
		push4(pc-cs+4);
		pc=cs+read4();
	}elif(code==0x96){
		r=pop4();
		//cout<<r<<endl;
		if(r>len){
			//printf("%x %x %d %d\n",cs,pc,curpack,len);
			pc=(char*)r;
			curpack=r1=pop4();
			cs=packs[r1].buf;
			len=packs[r1].len;
			//printf("%x %x %d %d\n",cs,pc,curpack,len);
		}
		else pc=cs+r;
	}
	elif(code==0x97)push2(data2(read1()));
	elif(code==0x98)push4(data4(read1()));
	elif(code==0x99){
		r=read1();
		data2(r)=*(short*)(esp+read1());
	}elif(code==0x9a){
		r=read1();
		data4(r)=*(int*)(esp+read1());
	}elif(code==0x9b){
		r=read1();
		data4(r)=sqrt(read4());
	}elif(code==0x9c){
		r=read1();
		data4(r)=sqrt(data4(read1()));
	}elif(code>=0x9d and code<0xa9){
		r=read1();
		if(code>=0x9d and code<0xa3)condjmp(compare(data4(r),data4(read1()),code-0x9d),32);
		else if(code>=0xa3 and code<0xa9)condjmp(compare(data4(r),read4(),code-0xa3),32);
	}elif(code==0xa9){
		r=read1();
		string str=read(r);
		import(str);
	}elif(code==0xaa)import(pkg[read4()]);
	elif(code==0xab){
		//printf("%x %x %d %d\n",cs,pc,curpack,len);
		push4(curpack);
		push4((int)(pc+5));
		curpack=r=read1();
		cs=packs[r].buf;
		pc=cs+read4();
		len=packs[r].len;
		//printf("%x %x %d %d\n",cs,pc,curpack,len);
	} 
	return true;
}
void tellerr(string err){
	cout<<"At 0x"<<hex<<(pc-cs)<<" :\n  "<<err<<dec<<endl;
}
int main(int argc,char** argv){
	if(argc<2)return 1;
	clock_t pst=clock();
	ifstream fin(argv[1]);
	fin.seekg(0,ios::end);
	len=fin.tellg();
	fin.seekg(0);
	pc=cs=new char[len];
	package cur;
	cur.no=-1;
	cur.buf=cs;
	cur.name="__main__";
	cur.len=len;
	packs.push_back(cur);
	curpack=0;
	fin.read(cs,len);
	if(cs[0]==0x08){
		cout<<"File is a package and is not executable"<<endl;
		return 0;
	}
	ds=new char[256];
	esp=ss=new char[4096];
	clock_t ust=clock();
	clock_t end;
	try{
		while(1){
			bool res;
			try{
				res=runcmd();
			}catch(ecp e){
				tellerr(e.s);
			}
			if(res==false)break;
		}
	}catch(err e){
		tellerr(e.s);
	}
	end=clock();
	if(clocks)cout<<"Execute Time : "<<dec<<(end-ust)<<" ms"<<endl;
	return 0;
}
