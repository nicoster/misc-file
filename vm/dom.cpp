#include "common.h"
#import "msxml3.dll"
using namespace MSXML2;

inline void TESTHR( HRESULT _hr ) 
   { if FAILED(_hr) throw(_hr); }

void main()
{
	string str;
	str = "123456";
	UINT pos = str.find("1");
	if (pos != -1)
	cout << pos << "," << str.substr(pos) << endl;
	return;
   try {
      IXMLDOMDocumentPtr docPtr;
      IXMLDOMNodePtr DOMNodePtr;
      IXMLDOMNamedNodeMapPtr attrs;

      //init
      TESTHR(CoInitialize(NULL)); 
      TESTHR(docPtr.CreateInstance("msxml2.domdocument"));
      
      VARIANT vtTemp;

      vtTemp.vt=VT_I2;
      vtTemp.iVal = MSXML2::NODE_ATTRIBUTE;

      // load a document
      _variant_t varXml("d:\\soap.xml");
      _variant_t varOut((bool)TRUE);
      varOut = docPtr->load(varXml);
      if ((bool)varOut == FALSE)
         throw(0);

	IXMLDOMNodePtr node = docPtr->selectSingleNode("//responseCode");
      attrs = node->attributes;

//      MessageBox(NULL, _bstr_t(node->xml), _T("New Document"), MB_OK);
		cout << attrs->length << endl;
	  
	  IXMLDOMNodePtr attr;
	  attr = attrs->getNamedItem("href");
	  wstring strAttr;
	  if (attr)
		  strAttr = (wchar_t*)_bstr_t(attr->nodeValue) ;
	  strAttr = strAttr.substr(1);
	  wcout << strAttr << endl;
   } catch(...)
   {
      MessageBox(NULL, _T("Exception occurred"), _T("Error"), MB_OK);
   }
   CoUninitialize();
}
