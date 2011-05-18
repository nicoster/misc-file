/**///////////////////////////////////////////////////////////////////////////
//                      ExpressionCalculator
//                            Version 0.1
//                        Powered by nankezhishi
//                          All Right reserved.
//      本计算器支持带括号的四则、乘方运算。并可包含独立的负号。
/**///////////////////////////////////////////////////////////////////////////
#include "iostream"
#include "string"
#include "cmath"
using namespace std;

//用于kind的值
#define NUMBER 1000
#define MYERROR 1001
#define END    1002
//词法分析器的当前状态
int state;
//读取的内容
string input;
//字符串的长度
int inputlength;
//字符串读取的位置.
int char_index = 0;
//词法分析器的返回值
int token;
//读取到数字时的值
string strval;
double yylval = 0;


/**///////////////////////////////////////////////////////////////////////////
//词法分析器
/**///////////////////////////////////////////////////////////////////////////
bool isdigit(char c)
{
    return (c >= '0' && c <= '9')?true:false;
}

bool isoperator(char c)
{
    return (c == '+'||c == '-'||c == '*'||c == '/'||c == '^'||c == '('||c == ')'||c == '=')?true:false;
}

//识别数字的DFA的状态转移函数
int move(int state, char c)
{
    if (isdigit(c))
    {
        return (state==0)?1:state;
    }
    else if (state == 1 && c == '.')
    {
        return 2;
    }
    else if (( state == 2 || state == 1) && (c == ' ' || c == '\n' || c == 0 || isoperator(c)))
    {
        char_index--;                              //操作符
        return 3;                          //接受
    }
    else
        return 0;
}

int get_token()
{
    if (char_index == inputlength)
	{
		cout << "end\n";
        return END;
	}
    if (isoperator(input[char_index]))
    {
        char_index++;
		cout << "op:" << input[char_index-1] << endl;
        return input[char_index-1];        //返回非数字运算符
    }
    int start = char_index;
    for (;char_index <= inputlength;)
    {
        state = move(state,input[char_index++]);
        if (state == 0)
            return MYERROR;
        else if (state == 3)
        {
            strval = input.substr(start,char_index-start);
            cout << "num:" << strval << endl;
            yylval = atof(strval.c_str());
			state = 0;
            return NUMBER;
        }
    }
    return 0;
}


/**///////////////////////////////////////////////////////////////////////////
//语法分析器采用自上而下的分析方法.
/**///////////////////////////////////////////////////////////////////////////
void match(int t)
{
    if (token == t)
        token = get_token();
    else
    {
        cout << "EXPRESSION ERRON IN MATCH!" << endl;
    }
}

double E();

double M()
{
    double temp;
    switch (token)
    {
    case NUMBER:
        temp = yylval;
        match(NUMBER);
        return temp;
    case '(':
        match('(');
        temp = E();
        match(')');
        return temp;
    default:
        cout << "EXPRESSION ERROR IN M()!" << endl;
        return 0;
    }
}

double N();

double N_()
{
    switch (token)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case ')':
    case END:
        return 1;
    case '^':
        match('^');
        return N();
    default:
        cout << "EXPRESSION ERROR IN N_()!" << endl;
        return 0;
    }
}

double N()
{
    switch (token)
    {
    case NUMBER:
    case '(':
    {
        double m = M();
        return pow(m, N_());    //这里不可以写做pow(M(),N_())因为参数压栈的顺序是从右向左,这样就会先调用N_()而产生错误.
    }
    default:
        cout << "EXPRESSION ERROR IN N()!" << endl;
        return 0;
    }
}

double F()
{
    switch (token)
    {
    case '-':
        match('-');
        return -N();
    case NUMBER:
    case '(':
        return N();
    default:
        cout << "EXPRESSION ERROR IN F()!" << endl;
        return 0;
    }
}

double T_()
{
    switch (token)
    {
    case '+':
    case '-':
    case ')':
    case END:
        return 1;        //对于乘法,这里要返回1.
    case '*':
        match('*');
        return F() * T_();
    case '/':
        match('/');
        return 1/(F() / T_());
    default:
        cout << "EXPRESSION ERROR IN T_()!" << endl;
        return 0;
    }
}

double T()
{
    switch (token)
    {
    case NUMBER:
    case '-':
    case '(':
        return F() * T_();
    default:
        cout << "EXPRESSION ERROR IN T()!" << endl;
        return 0;
    }
}

double E_()
{
    switch (token)
    {
    case '+':
        match('+');
        return T() + E_();
    case ')':
    case END:
        return 0;
    case '-':
        match('-');
        return -(T() - E_());
    default:
        cout << "EXPRESSION ERROR IN E_()!" << endl;
        return 0;
    }
}

double E()
{
    switch (token)
    {
    case NUMBER:
    case '-':
    case '(':
        return T() + E_();
    default:
        cout << "EXPRESSION ERROR IN E()!" << endl;
        return 0;
    }
}

int main()
{
    while ((cin >> input) )
    {
//		input += '\n';
        inputlength = input.length();
        state = 0;
        char_index = 0;
        token = get_token();
        cout << E() << endl;
    }

    /**///////////////////////////////////////////////////////////////////////////
    //词法分析器测试程序
    /**///////////////////////////////////////////////////////////////////////////
    //~ while (char_index < inputlength)
    //~ while ((cin >> input) && (inputlength = input.length()) > 0)
    //~ {
    //~ token = get_token();
    //~ if (token == NUMBER)
    //~ {
    //~ cout << yylval << endl;
    //~ }
    //~ else if (token == MYERROR)
    //~ {
    //~ cout << "表达式错误" << endl;
    //~ }
    //~ else
    //~ cout << (char)token << endl;
    //~ }

    return 0;
}