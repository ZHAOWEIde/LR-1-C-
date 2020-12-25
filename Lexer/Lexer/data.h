//#pragma once
//#include <iostream>
//#include <map>
//#include <algorithm>
//#include <string>
//
//using namespace std;
//
//string instr;//������Ŵ�
//int index;//��ǰ������Ŷ����ַ���λ��
//char character;//ȫ�ֱ����ַ���������¶�����ַ�
//string token;//�ַ����飬����Ѷ�����ַ�����
//map<string, int> Symbol;//��ʶ����
//map<string, int> Digit;//������
//map<string, int>::iterator ite;
//const int len = 100;
//string Reserve[len];//�����ֱ�
//string Boundary[2 * len];//���
//string Operator[3 * len];//�����
//struct Binary {
//	Binary(int c, int i, string v = "-") {
//		category = c;
//		index = i;
//		value = v;
//	}
//	int category = 0;
//	int index = 0;
//	string value = "-";
//};
//
// 
//
//void init_Reserve() {//���챣���ֱ�ĺ���
//	Reserve[1] = "main";
//	Reserve[2] = "int";
//	Reserve[3] = "if";
//	Reserve[4] = "else";
//	Reserve[5] = "while";
//	Reserve[6] = "for";
//	Reserve[7] = "read";
//	Reserve[8] = "write";
//	Reserve[9] = "bool";
//	Reserve[10] = "break";
//	Reserve[11] = "case";
//	Reserve[12] = "catch";
//	Reserve[13] = "char";
//	Reserve[14] = "class";
//	Reserve[15] = "const";
//	Reserve[16] = "continue";
//	Reserve[17] = "default";
//	Reserve[18] = "delete";
//	Reserve[19] = "do";
//	Reserve[20] = "double";
//	Reserve[21] = "enum";
//	Reserve[22] = "false";
//	Reserve[23] = "true";
//	Reserve[24] = "float";
//	Reserve[25] = "friend";
//	Reserve[26] = "goto";
//	Reserve[27] = "inline";
//	Reserve[28] = "long";
//	Reserve[29] = "new";
//	Reserve[30] = "private";
//	Reserve[31] = "protected";
//	Reserve[32] = "public";
//	Reserve[33] = "return";
//	Reserve[34] = "short";
//	Reserve[35] = "signed";
//	Reserve[36] = "sizeof";
//	Reserve[37] = "static";
//	Reserve[38] = "struct";
//	Reserve[39] = "switch";
//	Reserve[40] = "this";
//	Reserve[41] = "try";
//	Reserve[42] = "typedef";
//	Reserve[43] = "unsigned";
//	Reserve[44] = "using";
//	Reserve[45] = "virtual";
//	Reserve[46] = "void";
//	Reserve[47] = "include";
//	Reserve[48] = "iostream";
//	Reserve[49] = "namespace";
//	Reserve[50] = "std";
//
//	Reserve[51] = "print";
//}
//void init_Operator() {//��ʼ���������
//	Operator[210] = "+";
//	Operator[211] = "-";
//	Operator[212] = "*";
//	Operator[213] = "/";
//	Operator[214] = "<";
//	Operator[215] = "<=";
//	Operator[216] = ">";
//	Operator[217] = ">=";
//	Operator[218] = "!=";
//	Operator[219] = "==";
//	Operator[220] = "=";
//}
//void init_Boundary() {//������ʼ��
//
//	Boundary[121] = "(";
//	Boundary[122] = ")";
//	Boundary[123] = ",";
//	Boundary[124] = ";";
//	Boundary[125] = "{";
//	Boundary[126] = "}";
//	Boundary[127] = "#";
//}
//
//void getChar() {//����һ���ַ�
//	character = instr[index++];
//}
//void getnbc() {//����ǿհ��ַ�
//	while (character == ' ') {
//		getChar();
//	}
//}
//void concat() {//�����ַ���
//	token = token + character;
//}
//bool letter() {//�ж��Ƿ�Ϊ��ĸ
//	if ((character >= 'A' && character <= 'Z') || (character >= 'a' && character <= 'z'))
//		return true;
//	return false;
//}
//bool digit() {//�ж��Ƿ�Ϊ����
//	if (character >= '0' && character <= '9')
//		return true;
//	return false;
//}
//void retract() {//�����ַ��ĺ���
//	character = ' ';
//	index--;
//}
//int reserve() {//ƥ�䱣���ַ�
//	for (int i = 0; i < len; i++)
//		if (Reserve[i] == token)return i;
//	return -1;
//}
//string symbol() {
//	ite = Symbol.find(token);
//	if (ite != Symbol.end()) {
//		return ite->first;
//	}
//	else {
//		Symbol[token] = Symbol.size();
//		return token;
//	}
//}
//string constant() {
//	ite = Digit.find(token);
//	if (ite != Digit.end()) {
//		return ite->first;
//	}
//	else {
//		Digit[token] = Digit.size();
//		return token;
//	}
//}
//Binary error() {
//	cout << token << "\t-->\t�õ��ʲ�����" << endl;
//	return Binary(0, 0);
//}
////�ʷ��������������ʶ�𵥴�
//Binary LexAnalyze() {
//	token = "";
//	getChar();
//	getnbc();
//	string val;
//	int num = -1;
//	switch (character) {
//	case'a':
//	case'b':
//	case'c':
//	case'd':
//	case'e':
//	case'f':
//	case'g':
//	case'h':
//	case'i':
//	case'j':
//	case'k':
//	case'l':
//	case'm':
//	case'n':
//	case'o':
//	case'p':
//	case'q':
//	case'r':
//	case's':
//	case't':
//	case'u':
//	case'v':
//	case'w':
//	case'x':
//	case'y':
//	case'z':
//	case'A':
//	case'B':
//	case'C':
//	case'D':
//	case'E':
//	case'F':
//	case'G':
//	case'H':
//	case'I':
//	case'J':
//	case'K':
//	case'L':
//	case'M':
//	case'N':
//	case'O':
//	case'P':
//	case'Q':
//	case'R':
//	case'S':
//	case'T':
//	case'U':
//	case'V':
//	case'W':
//	case'X':
//	case'Y':
//	case'Z':
//		while (letter() || digit()) {//Ϊ��ĸ������
//			concat();//׷�ӵ�tokenĩβ
//			getChar();//��ȡ��һ���ַ�
//		}
//		retract();//����һ���ַ�
//		num = reserve();//�鿴�����ֱ�
//		if (num != -1) {
//			return Binary(num, 0);
//		}
//		else {
//			val = symbol();//�鿴��ʶ����
//			return Binary(1, Symbol[val], val);
//		}
//		break;
//	case'0':
//	case'1':
//	case'2':
//	case'3':
//	case'4':
//	case'5':
//	case'6':
//	case'7':
//	case'8':
//	case'9':
//		while (digit()) {//Ϊ����
//			concat();
//			getChar();
//		}
//		retract();
//		val = constant();//�鿴������
//		return Binary(2, Digit[val], val);
//		break;
//	case'<':
//		getChar();
//		if (character == '=') return Binary(215, 0);//����<=����
//		else {
//			retract();
//			return Binary(214, 0);//����<����
//		}
//		break;
//	case'>':
//		getChar();
//		if (character == '=')return Binary(217, 0);//����>=����
//		else {
//			retract();
//			return Binary(216, 0);//����>����
//		}
//		break;
//	case'=':
//		getChar();
//		if (character == '=') return Binary(219, 0);//����==����
//		else {
//			retract();
//			return Binary(220, 0);//����=����
//		}
//		break;
//	case'!':
//		getChar();
//		if (character == '=')return Binary(218, 0);
//		else return error();
//		break;
//	case'+':
//		return Binary(210, 0);
//		break;
//	case'-':
//		return Binary(211, 0);
//		break;
//	case'*':
//		return Binary(212, 0);
//		break;
//	case'/':
//		return Binary(213, 0);
//		break;
//	case'(':
//		return Binary(121, 0);
//		break;
//	case')':
//		return Binary(122, 0);
//		break;
//	case',':
//		return Binary(123, 0);
//		break;
//	case';':
//		return Binary(124, 0);
//		break;
//	case'{':
//		return Binary(125, 0);
//		break;
//	case'}':
//		return Binary(126, 0);
//		break;
//	case'#':
//		return Binary(127, 0);
//		break;
//	default:
//		return error();
//	}
//}
//void show_table() {
//	cout << "==================" << "������" << "==================" << endl;
//	cout << "�����ַ�\t������" << endl;
//	for (int i = 0; i < len; i++) {
//		if (Reserve[i] != "") {
//			if (Reserve[i].size() >= 8)
//				cout << Reserve[i] << "\t" << i << endl;
//			else
//				cout << Reserve[i] << "\t\t" << i << endl;
//		}
//	}
//	cout << "\n==================" << "���" << "==================" << endl;
//	cout << "���\t\t������" << endl;
//	for (int i = 0; i < 2 * len; i++) {
//		if (Boundary[i] != "") {
//			cout << Boundary[i] << "\t\t" << i << endl;
//		}
//	}
//	cout << "\n==================" << "�����" << "==================" << endl;
//	cout << "�����\t\t������" << endl;
//	for (int i = 0; i < 3 * len; i++) {
//		if (Operator[i] != "") {
//			cout << Operator[i] << "\t\t" << i << endl;
//		}
//	}
//	cout << "\n==================" << "��ʶ��" << "==================" << endl;
//	cout << "��ʶ��\t\t������\t����λ��" << endl;
//	for (ite = Symbol.begin(); ite != Symbol.end(); ite++) {
//		if (ite->first.size() >= 8)
//			cout << ite->first << "\t1\t\t" << ite->second << endl;
//		else
//			cout << ite->first << "\t\t1\t\t" << ite->second << endl;
//	}
//	cout << "\n==================" << "������" << "==================" << endl;
//	cout << "����ֵ\t\t������\t����λ��" << endl;
//	for (ite = Digit.begin(); ite != Digit.end(); ite++) {
//		cout << ite->first << "\t\t2\t\t" << ite->second << endl;
//	}
//}
//
//void Data() {
//	init_Reserve();//�����ֱ��ʼ��
//	init_Boundary();//������ʼ��
//	init_Operator();//��������ʼ��
//	Symbol.clear();//��ʶ������ʼ��
//	Digit.clear();//��������ʼ��
//	index = 0;
//	character = ' ';
//	token = "";
//	cout << "��������ʷ�������Դ������룺����@�����������\n" << endl;
//	//Դ����������봦��
//	string in;
//	ifstream ifs{ "../resouce/string.txt" };
//
//	while (ifs >> in && in != "@") {
//		instr = instr + " " + in;
//	}
//
//
//	//ʶ���Ԫ���ʼ��
//	Binary word(0, 0, "-");
//	//ѭ�����дʷ�����ֱ��ʶ�����е��ʷ���
//	cout << "\n------------------------ʶ����------------------------" << endl;
//	while (index < instr.size()) {
//		word = LexAnalyze();
//		if (word.category != 0) {
//			cout << "ʶ�𵥴�:\t(" << word.category << "," << word.value << ")" << endl;
//		}
//	}
//	//չʾ����ĸ��ִʻ��
//	cout << "\n------------------------�ʻ��չʾ------------------------\n" << endl;
//	show_table();
//
//	//system("pause");
//}