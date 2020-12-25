#pragma once
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include "AllMacro.h"
using namespace std;

string Reserve[RESERVELEN];
char bufferA[BUFFERLEN];		//缓存区A；
char bufferB[BUFFERLEN];		//缓存区B；
int indexA;					//缓存区A当前处理的下标索引
char charProcess;			//缓冲区读出的需要处理的字符
string token;				//已经读入的字符序列
map<string, int> Symbol;	//标识符集
map<string, int> Digit;		//常数集
map<string, int>::iterator ite; //迭代器

ifstream ifs{ "../resouce/string.txt",ios::in };//全局文件读
ofstream ofs{ "../out/tokenList.txt" };//全局文件写token
ofstream ofSymbol{ "../out/symbol.txt" }; //输出标识符集
ofstream ofIntNum{ "../out/intNum.txt" }; //输出int数据表


bool isFinishRead = false;      //读文件完成标志
bool isUsedBufferB = false;     //用了BufferB？
int numBufferB = 0;				//bufferB的数量
int numBufferA = 0;				//bufferA的字符数量

void initReserve();
void initFirst();
bool isOpenFile();
void initReadToBuffer();
bool updateBufferA();
bool getChar();
void jumpNull();
void backChar();
void concat();
bool isLetter();
bool isDigit();
bool isConnector();
int isReserve();
void mainProcess();


struct Binary
{
	Binary(int argCategory, int argIndex, string argValue = "NULL") {
		category = argCategory;
		index = argIndex;
		value = argValue;
	}
	int category = 0;
	int index = 0;
	string value = "NULL";
};

void initFirst() {
	initReserve();
	indexA = 0;
	charProcess = ' ';
	token = "";
	if (isOpenFile()) printf("文件正常\n");
	initReadToBuffer();
}

//初始化编码表
void initReserve() {
	Reserve[1] = "main";
	Reserve[2] = "const";
	Reserve[3] = "goto";
	Reserve[4] = "void";
	Reserve[5] = "unsigned";
	Reserve[6] = "class";
	Reserve[7] = "return";
	Reserve[8] = "static";
	Reserve[9] = "struct";
	Reserve[10] = "include";

	Reserve[21] = "if";
	Reserve[22] = "else";
	Reserve[23] = "switch";
	Reserve[24] = "case";
	Reserve[25] = "default";

	Reserve[41] = "while";
	Reserve[42] = "for";
	Reserve[43] = "do";
	Reserve[44] = "in";
	Reserve[45] = "break";
	Reserve[46] = "continue";

	Reserve[61] = "int";
	Reserve[62] = "char";
	Reserve[63] = "double";
	Reserve[64] = "bool";
	Reserve[65] = "list";
	Reserve[66] = "string";

	Reserve[101] = "+";
	Reserve[102] = "-";
	Reserve[103] = "*";
	Reserve[104] = "/";
	Reserve[105] = "<";
	Reserve[106] = "<=";
	Reserve[107] = ">";
	Reserve[108] = ">=";
	Reserve[109] = "!=";
	Reserve[110] = "==";
	Reserve[111] = "=";

	Reserve[131] = "(";
	Reserve[132] = ")";
	Reserve[133] = ",";
	Reserve[134] = ";";
	Reserve[135] = "{";
	Reserve[136] = "}";
	Reserve[137] = "#";
	Reserve[138] = "[";
	Reserve[139] = "]";
	Reserve[140] = "'";
	Reserve[141] = "\"";
	Reserve[142] = ":";
	Reserve[143] = ".";

}

//打开文件
bool isOpenFile() {
	//ifs.open("../resouce/string.txt");
	//ofs.open( "../out/ans.txt" );
	bool ifsBool = ifs.is_open();
	bool ofsBool = ofs.is_open();
	if (ifsBool && ofsBool) {
		cout << "读写文件均打开正常\n" << endl;
		return true;
	}
	else if (!ifsBool && !ofsBool) {
		cout << "读写文件均打开失败\n" << endl;
	}
	else if(!ifsBool){
		cout << "写文件打开失败\n" << endl;
	}
	else {
		cout << "写文件打开失败\n" << endl;
	}
	return false;
}

//第一次读文件到bufferA bufferB
void initReadToBuffer() {
	for(int i = 0; i<BUFFERLEN;i++){//读到缓冲区A
		if (ifs.read(bufferA+i,1))  numBufferA++;
		else isFinishRead = true;
	}
	if (!isFinishRead) {//缓冲区A存不完，继续读给缓冲区B
		isUsedBufferB = true;
		for (int i = 0; i < BUFFERLEN; i++) {
			if (!(ifs.read(bufferB+i,1))) isFinishRead = true;
			else numBufferB++;
		}
	}
}

//将bufferB的内容复刻到bufferA
bool updateBufferA() {
	if (isUsedBufferB) {
		for (int i = 0; i < numBufferB; i++) {
			bufferA[i] = bufferB[i];
		}
		numBufferA = numBufferB;
		numBufferB = 0;
		indexA = 0;
		isUsedBufferB = false;
		if (!isFinishRead) {//未读完文件，继续读文件到bufferB
			for (int i = 0; i < BUFFERLEN; i++) {
				if (!(ifs.read(bufferB+i,1))) isFinishRead = true;
				else numBufferB++;
			}
			isUsedBufferB = true;
		}
		return true;
	}
	else return false;
}

//从缓冲区A读一个字符
bool getChar() {
	if (indexA < numBufferA) {//511
		charProcess = bufferA[indexA];
		indexA++;
		return true;
	}
	else{//更新A？
		if (updateBufferA()) {
			charProcess = bufferA[indexA];
			indexA++;
			return true;
		}
		else return false;
	}
}

//跳过空格
void jumpNull() { 
	while (charProcess == ' ') {
		getChar();
	}
}

//缓冲区回滚一个字符
void backChar() {
	charProcess = ' ';
	indexA--;
}

//连接token
void concat() {
	token += charProcess;
}

//是字母吗？
bool isLetter() {
	return ((charProcess >= 'A' && charProcess <= 'Z') || (charProcess >= 'a' && charProcess <= 'z')) ?true: false;
}

//是数字吗？
bool isDigit() {
	return (charProcess>='0'&& charProcess<='9') ? true : false;
} 

//是连接符_吗？
bool isConnector() {
	return (charProcess == '_') ? true : false;
}

//是保留字吗？是则返回种别码，不是则返回 T_ID 161标识符
int isReserve() {
	for (int i = 0; i < RESERVELEN; i++)
		if (Reserve[i] == token)return i;
	return T_ID;
}

//存在标识符？不存在就加入Symbol map
string isExistSymbol() {
	ite = Symbol.find(token);
	if (ite != Symbol.end()) return ite->first;//已经存在标识符
	else {
		Symbol[token] = Symbol.size();//插入标识符
		return token;
	}
}

//存在int常数？不存在就加入Digit map
string isExistConstant() {
	ite = Digit.find(token);
	if (ite != Digit.end()) {
		return ite->first;
	}
	else {
		Digit[token] = Digit.size();
		return token;
	}
}

Binary t_Erro( ){
	cout << token << "\t- = >单词符合不符合规范\n" << endl;
	return Binary(0, 0);
}

//分析产生token串
Binary lexAnalyze() {
	token = "";
	int reserveIndex;
	jumpNull();
	string val;
	switch(charProcess)
	{
		case'a':
		case'b':
		case'c':
		case'd':
		case'e':
		case'f':
		case'g':
		case'h':
		case'i':
		case'j':
		case'k':
		case'l':
		case'm':
		case'n':
		case'o':
		case'p':
		case'q':
		case'r':
		case's':
		case't':
		case'u':
		case'v':
		case'w':
		case'x':
		case'y':
		case'z':
		case'A':
		case'B':
		case'C':
		case'D':
		case'E':
		case'F':
		case'G':
		case'H':
		case'I':
		case'J':
		case'K':
		case'L':
		case'M':
		case'N':
		case'O':
		case'P':
		case'Q':
		case'R':
		case'S':
		case'T':
		case'U':
		case'V':
		case'W':
		case'X':
		case'Y':
		case'Z':
			//字母打头不分大小写然后可用数字或连接符号 _ 
			while (isLetter() || isDigit() ||isConnector()) {
				concat();//连接
				getChar();//取得下一个字符继续连接
			}
			backChar();//下一个charProcess是其他怪异的符号%
			reserveIndex = isReserve();//查看token是不是保留字
			if (reserveIndex!=T_ID ) {
				return Binary(reserveIndex,-1,Reserve[reserveIndex]);
			}
			else {//标识符
				val = isExistSymbol();
				return Binary(T_ID,Symbol[val],val);
			}
		case'0':
		case'1':
		case'2':
		case'3':
		case'4':
		case'5':
		case'6':
		case'7':
		case'8':
		case'9':
			while (isDigit()) {
				concat();
				getChar();
			}
			backChar();
			val = isExistConstant();
			return Binary(T_INT_NUM, Digit[val], val);
		case'<'://处理了<  <=
			getChar();
			if (charProcess == '=')return Binary(T_LE, -1, "<=");
			else
			{
				backChar();
				return Binary(T_LT, -1, "<");
			}
		case'>':
			getChar();
			if (charProcess == '=')return Binary(T_RE, -1, ">=");
			else
			{
				backChar();
				return Binary(T_RT, -1, ">");
			}
		case'=':
			getChar();
			if (charProcess == '=') return Binary(T_IFEQ, -1,"==");//返回==符号
			else {
				backChar();
				return Binary(T_EQ,-1,"=");//返回=符号
			}
		case'!'://待出错处理
			getChar();
			if (charProcess == '=')return Binary(T_NEQ, -1, "!=");
			else return t_Erro();
		case'+':
			return Binary(T_PLUS, -1, "+");
		case'-':
			return Binary(T_MINUS, -1, "-");
		case'*':
			return Binary(T_MULTI, -1, "*");
		case'/':
			return Binary(T_RDIV, -1, "/");
		case'(':
			return Binary(T_LPARISIS,-1,"(");
		case')':
			return Binary(T_RPARISIS,-1,")");
		case',':
			return Binary(T_COMMA, -1, ",");
		case';':
			return Binary(T_SEMIC, -1, ";");
		case'{':
			return Binary(T_LBRACE, -1, "{");
		case'}':
			return Binary(T_RBRACE, -1, "}");
		case'#':
			return Binary(T_HASH, -1, "#");
		case'[':
			return Binary(T_LSQUBRA, -1, "[");
		case']':
			return Binary(T_RSQUBRA, -1, "]");
		case'\'':
			return Binary(T_SINGQUO, -1, "'");
		case'\"':
			return Binary(T_DOUQUE, -1, "\"");
		case':':
			return Binary(T_COLON, -1, ":");
		case'.':
			return Binary(T_DOT, -1, ".");
		default:
			return t_Erro();
	}
}

//文件操作
void closeFile() {
	ifs.close();
	ofs.close();
	ofSymbol.close();
	ofIntNum.close();

}
void writeFile() {
	for (ite = Symbol.begin(); ite != Symbol.end(); ite++) {
		string value = "( "+ite->first+",\t"+to_string(ite->second)+")\n";
		ofSymbol.write(&value[0], value.size());
	}
	for (ite = Digit.begin(); ite != Digit.end(); ite++) {
		string value = "( " + ite->first + ",\t" + to_string(ite->second) + ")\n";
		ofIntNum.write(&value[0], value.size());
	}
}

//主流程
void mainProcess() {
	initFirst();
	Binary temp(0,0);
	int count = 0;
	while (getChar()) {//能读出字符
		temp = lexAnalyze();
		if (temp.category != 0) {
			cout << "(" << temp.category << ",\t" << temp.index << ",\t" << temp.value <<")\n"<< endl;
			string tokenText = "(" + to_string(temp.category)  + ",\t" + to_string(temp.index) + ",\t" + temp.value + ")\n";
			ofs.write(&tokenText[0],tokenText.size());
		}
		count++;
	}
	cout << "数量是" << count<<endl;
	writeFile();
	closeFile();
}