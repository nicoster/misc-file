/**///////////////////////////////////////////////////////////////////////////
//                      ExpressionCalculator
//                            Version 0.1
//                        Powered by nankezhishi
//                          All Right reserved.
//      ��������֧�ִ����ŵ����򡢳˷����㡣���ɰ��������ĸ��š�
/**///////////////////////////////////////////////////////////////////////////
#include "iostream"
#include "string"
#include "cmath"
using namespace std;

//����kind��ֵ
#define NUMBER 1000
#define MYERROR 1001
#define END    1002
//�ʷ��������ĵ�ǰ״̬
int state;
//��ȡ������
string input;
//�ַ����ĳ���
int inputlength;
//�ַ�����ȡ��λ��.
int char_index = 0;
//�ʷ��������ķ���ֵ
int token;
//��ȡ������ʱ��ֵ
string strval;
double yylval = 0;


/**///////////////////////////////////////////////////////////////////////////
//�ʷ�������
/**///////////////////////////////////////////////////////////////////////////
bool isdigit(char c)
{
    return (c >= '0' && c <= '9')?true:false;
}

bool isoperator(char c)
{
    return (c == '+'||c == '-'||c == '*'||c == '/'||c == '^'||c == '('||c == ')'||c == '=')?true:false;
}

//ʶ�����ֵ�DFA��״̬ת�ƺ���
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
        char_index--;                              //������
        return 3;                          //����
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
        return input[char_index-1];        //���ط����������
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
//�﷨�������������϶��µķ�������.
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
        return pow(m, N_());    //���ﲻ����д��pow(M(),N_())��Ϊ����ѹջ��˳���Ǵ�������,�����ͻ��ȵ���N_()����������.
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
        return 1;        //���ڳ˷�,����Ҫ����1.
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
    //�ʷ����������Գ���
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
    //~ cout << "���ʽ����" << endl;
    //~ }
    //~ else
    //~ cout << (char)token << endl;
    //~ }

    return 0;
}