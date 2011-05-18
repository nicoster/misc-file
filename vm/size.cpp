#include <iostream>
#include <string>
using namespace std;

void main()
{
	string temp = "<?xml version=""1.0"" encoding=""UTF-8""?>\
<Message version=""1.0"">\
   <Header Message_Type=""PU_Register_Rsp"" Session_ID=""4759ac8d3""\ Sequence_Number=""1"" />\
	<result code=""0""/>\
	<parameters>\
		<expires></expires>\
		<sipRegIPAddr>192.168.1.2</sipRegIPAddr>\
		< sipRegPort >5060</ sipRegPort>\
	</parameters>\
</Message>";
	
	string cs = "<?xml version=""1.0"" encoding=""UTF-8""?>\
<Message version=""1.0"">\
<Header Message_Type=""Heart_Beat"" Session_ID=""4759ac8d3"" Sequence_Number=""2"" />\
</Message>\
<expires/>\
<sipRegIPAddr>192.168.1.2</sipRegIPAddr>\
<sipRegPort >5060</sipRegPort>\
</parameters>\
</Message>";

	cout<<temp.size()<<endl;
	cout << cs.size()<<endl;
}