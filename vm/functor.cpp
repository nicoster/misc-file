#include <iostream.h>
#include <string>
#include <list>
#include <algorithm>

class IsAToothbrush 
{
public:
  IsAToothbrush(string& InToothbrushCode) : 
      ToothbrushCode(InToothbrushCode) {}
  bool operator() (string& SalesRecord) 
  {
    return SalesRecord.substr(0,4)==ToothbrushCode;
  }       
private:
  string ToothbrushCode;        
};

int main (void) 
{
  list<string> SalesRecords;

  SalesRecords.push_back("0001 Soap");
  SalesRecords.push_back("0002 Shampoo");
  SalesRecords.push_back("0003 Toothbrush");
  SalesRecords.push_back("0004 Toothpaste");
  SalesRecords.push_back("0003 Toothbrush");
  
  string VariableToothbrushCode("0003");

  int NumberOfToothbrushes(0);  
  count_if (SalesRecords.begin(), SalesRecords.end(), 
              IsAToothbrush(VariableToothbrushCode),
                 NumberOfToothbrushes);
  cout << "There were  "
       << NumberOfToothbrushes 
       << " toothbrushes matching code "
       << VariableToothbrushCode
       << " sold" 
       << endl;
}
