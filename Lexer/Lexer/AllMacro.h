#pragma once
#pragma once
#define RESERVELEN    200
#define BUFFERLEN	  512
//编码表

//主体及类相关的
#define T_MAIN		1
#define T_CONST		2
#define T_GOTO		3
#define T_VOID		4
#define T_UNSIGNED	5
#define T_CLASS		6
#define T_RETURN	7
#define T_STATIC	8
#define T_STRUCT	9
#define T_INCLUDE   10





//条件关键字
#define T_IF		21
#define T_ELSE		22
#define T_SWITCH    23
#define T_CASE		24
#define T_DEFOULT   25


//循环关键字
#define T_WHILE		41
#define T_FOR		42
#define T_DO		43
#define T_IN		44
#define T_BREAK		45
#define T_CONTINUE	46


//数据类型
#define T_INT		61
#define T_CHAR		62
#define T_DOUBLE	63
#define T_BOOL		64
#define T_LIST		65
#define T_STRING	66


//操作符 + - * / 
#define T_PLUS		101
#define T_MINUS		102
#define T_MULTI		103
#define T_RDIV		104
//< <=
#define T_LT		105
#define T_LE		106
//> >= != == =
#define T_RT		107
#define T_RE		108
#define T_NEQ		109
#define T_IFEQ		110
#define T_EQ		111


//分界符 ( ) , ; { } # 
#define T_LPARISIS	131
#define T_RPARISIS	132
#define T_COMMA		133
#define T_SEMIC		134
#define T_LBRACE	135
#define T_RBRACE	136
#define T_HASH		137
//[ ]
#define T_LSQUBRA	138
#define T_RSQUBRA	139
//'
#define T_SINGQUO	140
//"
#define T_DOUQUE	141
// :
#define T_COLON		142
//.
#define T_DOT		143



//标识符
#define T_ID		200
#define T_INT_NUM   201
#define T_$         202


