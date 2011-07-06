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
int i = 0;
//�ʷ��������ķ���ֵ
int returnvalue;
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
        i--;                              //������
        return 3;                          //����
    }
    else
        return 0;
}

int lexer()
{
    if (i == inputlength)
        return END;
    if (isoperator(input[i]))
    {
        i++;
        return input[i-1];        //���ط����������
    }
    int start = i;
    for (;i < inputlength;)
    {
        state = move(state,input[i++]);
        if (state == 0)
            return MYERROR;
        else if (state == 3)
        {
            strval = input.substr(start,i-start);
            yylval = atof(strval.c_str());
            return NUMBER;
        }
    }
    return MYERROR;
}


/**///////////////////////////////////////////////////////////////////////////
//�﷨�������������϶��µķ�������.
/**///////////////////////////////////////////////////////////////////////////
void match(int t)
{
    if (returnvalue == t)
        returnvalue = lexer();
    else
    {
        cout << "EXPRESSION ERRON IN MATCH!" << endl;
    }
}

double E();

double M()
{
    double temp;
    switch (returnvalue)
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
    switch (returnvalue)
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
    double m,n_;
    switch (returnvalue)
    {
    case NUMBER:
    case '(':
        m = M();
        n_ = N_();
        return pow(m,n_);    //���ﲻ����д��pow(M(),N_())��Ϊ����ѹջ��˳���Ǵ�������,�����ͻ��ȵ���N_()����������.
    default:
        cout << "EXPRESSION ERROR IN N()!" << endl;
        return 0;
    }
}

double F()
{
    switch (returnvalue)
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
    switch (returnvalue)
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
    switch (returnvalue)
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
    switch (returnvalue)
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
    switch (returnvalue)
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
    while ((cin >> input) && (inputlength = input.length()) > 0)
    {
        state = 0;
        i = 0;
        returnvalue = lexer();
        cout << E() << endl;
    }

    /**///////////////////////////////////////////////////////////////////////////
    //�ʷ����������Գ���
    /**///////////////////////////////////////////////////////////////////////////
    //while (i < inputlength)
    //{
    //    returnvalue = lexer();
    //    if (returnvalue == NUMBER)
    //    {
    //        cout << yylval << endl;
    //    }
    //    else if (returnvalue == MYERROR)
    //    {
    //        cout << "����ʽ����" << endl;
    //    }
    //    else
    //        cout << (char)returnvalue << endl;
    //}
    return 0;
}