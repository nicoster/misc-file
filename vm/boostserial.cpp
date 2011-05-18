#include <fstream>
#include <iostream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class A

{

private:

    //Ϊ�����ô��л�����ܹ�����˽�г�Ա������Ҫ����һ����Ԫ��

    friend class boost::serialization::access;

    //���������

    int a;

    double b;

    //���л��ĺ�������һ��������ɶ���ı�����ָ�

    template<class Archive>

    void serialize(Archive & ar, const unsigned int version)

    {

        ar & a;   //������ô�򵥣�Ҳ����ʹ�� ar<<a �������﷨

        ar & b;

    }

public:

    A(int aa,double bb):a(aa),b(bb){}

    A(){}

    void print(){std::cout<<a<<' '<<b<<std::endl;}

};    

int main() 

{

   std::ofstream fout("file.txt");//�Ѷ���д��file.txt�ļ���

   boost::archive::text_oarchive oa(fout);//�ı�������鵵�࣬ʹ��һ��ostream������

   A obj(1,2.5);

   oa<<obj;//����obj����

   fout.close();//�ر��ļ�

   

   std::ifstream fin("file.txt");

   boost::archive::text_iarchive ia(fin);//�ı�������鵵��

   A newobj;

   ia>>newobj;//�ָ���newobj����

   newobj.print();

   fin.close();

   system("pause");

   return 0;

}
