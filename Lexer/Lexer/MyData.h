#pragma once
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <fstream>
#include "AllMacro.h"
using namespace std;

string Reserve[RESERVELEN];
char bufferA[BUFFERLEN];		//������A��
char bufferB[BUFFERLEN];		//������B��
int indexA;					//������A��ǰ������±�����
char charProcess;			//��������������Ҫ������ַ�
string token;				//�Ѿ�������ַ�����
map<string, int> Symbol;	//��ʶ����
map<string, int> Digit;		//������
map<string, int>::iterator ite; //������

ifstream ifs{ "../resouce/string.txt",ios::in };//ȫ���ļ���
ofstream ofs{ "../out/tokenList.txt" };//ȫ���ļ�дtoken
ofstream ofSymbol{ "../out/symbol.txt" }; //�����ʶ����
ofstream ofIntNum{ "../out/intNum.txt" }; //���int���ݱ�


bool isFinishRead = false;      //���ļ���ɱ�־
bool isUsedBufferB = false;     //����BufferB��
int numBufferB = 0;				//bufferB������
int numBufferA = 0;				//bufferA���ַ�����

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
	if (isOpenFile()) printf("�ļ�����\n");
	initReadToBuffer();
}

//��ʼ�������
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

//���ļ�
bool isOpenFile() {
	//ifs.open("../resouce/string.txt");
	//ofs.open( "../out/ans.txt" );
	bool ifsBool = ifs.is_open();
	bool ofsBool = ofs.is_open();
	if (ifsBool && ofsBool) {
		cout << "��д�ļ���������\n" << endl;
		return true;
	}
	else if (!ifsBool && !ofsBool) {
		cout << "��д�ļ�����ʧ��\n" << endl;
	}
	else if(!ifsBool){
		cout << "д�ļ���ʧ��\n" << endl;
	}
	else {
		cout << "д�ļ���ʧ��\n" << endl;
	}
	return false;
}

//��һ�ζ��ļ���bufferA bufferB
void initReadToBuffer() {
	for(int i = 0; i<BUFFERLEN;i++){//����������A
		if (ifs.read(bufferA+i,1))  numBufferA++;
		else isFinishRead = true;
	}
	if (!isFinishRead) {//������A�治�꣬��������������B
		isUsedBufferB = true;
		for (int i = 0; i < BUFFERLEN; i++) {
			if (!(ifs.read(bufferB+i,1))) isFinishRead = true;
			else numBufferB++;
		}
	}
}

//��bufferB�����ݸ��̵�bufferA
bool updateBufferA() {
	if (isUsedBufferB) {
		for (int i = 0; i < numBufferB; i++) {
			bufferA[i] = bufferB[i];
		}
		numBufferA = numBufferB;
		numBufferB = 0;
		indexA = 0;
		isUsedBufferB = false;
		if (!isFinishRead) {//δ�����ļ����������ļ���bufferB
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

//�ӻ�����A��һ���ַ�
bool getChar() {
	if (indexA < numBufferA) {//511
		charProcess = bufferA[indexA];
		indexA++;
		return true;
	}
	else{//����A��
		if (updateBufferA()) {
			charProcess = bufferA[indexA];
			indexA++;
			return true;
		}
		else return false;
	}
}

//�����ո�
void jumpNull() { 
	while (charProcess == ' ') {
		getChar();
	}
}

//�������ع�һ���ַ�
void backChar() {
	charProcess = ' ';
	indexA--;
}

//����token
void concat() {
	token += charProcess;
}

//����ĸ��
bool isLetter() {
	return ((charProcess >= 'A' && charProcess <= 'Z') || (charProcess >= 'a' && charProcess <= 'z')) ?true: false;
}

//��������
bool isDigit() {
	return (charProcess>='0'&& charProcess<='9') ? true : false;
} 

//�����ӷ�_��
bool isConnector() {
	return (charProcess == '_') ? true : false;
}

//�Ǳ����������򷵻��ֱ��룬�����򷵻� T_ID 161��ʶ��
int isReserve() {
	for (int i = 0; i < RESERVELEN; i++)
		if (Reserve[i] == token)return i;
	return T_ID;
}

//���ڱ�ʶ���������ھͼ���Symbol map
string isExistSymbol() {
	ite = Symbol.find(token);
	if (ite != Symbol.end()) return ite->first;//�Ѿ����ڱ�ʶ��
	else {
		Symbol[token] = Symbol.size();//�����ʶ��
		return token;
	}
}

//����int�����������ھͼ���Digit map
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
	cout << token << "\t- = >���ʷ��ϲ����Ϲ淶\n" << endl;
	return Binary(0, 0);
}

//��������token��
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
			//��ĸ��ͷ���ִ�СдȻ��������ֻ����ӷ��� _ 
			while (isLetter() || isDigit() ||isConnector()) {
				concat();//����
				getChar();//ȡ����һ���ַ���������
			}
			backChar();//��һ��charProcess����������ķ���%
			reserveIndex = isReserve();//�鿴token�ǲ��Ǳ�����
			if (reserveIndex!=T_ID ) {
				return Binary(reserveIndex,-1,Reserve[reserveIndex]);
			}
			else {//��ʶ��
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
		case'<'://������<  <=
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
			if (charProcess == '=') return Binary(T_IFEQ, -1,"==");//����==����
			else {
				backChar();
				return Binary(T_EQ,-1,"=");//����=����
			}
		case'!'://��������
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

//�ļ�����
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

//������
void mainProcess() {
	initFirst();
	Binary temp(0,0);
	int count = 0;
	while (getChar()) {//�ܶ����ַ�
		temp = lexAnalyze();
		if (temp.category != 0) {
			cout << "(" << temp.category << ",\t" << temp.index << ",\t" << temp.value <<")\n"<< endl;
			string tokenText = "(" + to_string(temp.category)  + ",\t" + to_string(temp.index) + ",\t" + temp.value + ")\n";
			ofs.write(&tokenText[0],tokenText.size());
		}
		count++;
	}
	cout << "������" << count<<endl;
	writeFile();
	closeFile();
}