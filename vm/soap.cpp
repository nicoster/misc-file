#include <stdio.h>

#import "msxml3.dll"
using namespace MSXML2;

#import "C:\Program Files\Common Files\MSSoap\Binaries\MSSOAP1.dll" \
exclude("IStream", "ISequentialStream", "_LARGE_INTEGER", \
"_ULARGE_INTEGER", "tagSTATSTG", "_FILETIME")
using namespace MSSOAPLib;

void main()
{
  CoInitialize(NULL);

  ISoapSerializerPtr Serializer;
  ISoapReaderPtr Reader;
  ISoapConnectorPtr Connector;

  // Connect to the service
  Connector.CreateInstance(__uuidof(HttpConnector));
  Connector->Property["EndPointURL"] =
  "http://www.allesta.net:51110/webservices/soapx4/isuseronline.php";
  Connector->Connect();

  // Begin message
  Connector->Property["SoapAction"] = "uri:allesta-YahooUserPing";
  Connector->BeginMessage();

  // Create the SoapSerializer
  Serializer.CreateInstance(__uuidof(SoapSerializer));

  // Connect the serializer to the input stream of the connector
  Serializer->Init(_variant_t((IUnknown*)Connector->InputStream));

  // Build the SOAP Message
  Serializer->startEnvelope("","","");
  Serializer->startBody("");
  Serializer->startElement("isuseronline",
                              "uri:allesta-YahooUserPing",
                              "",
                              "m");
 Serializer->startElement("username","","","");
  Serializer->writeString("laghari78");
  Serializer->endElement();
  Serializer->endElement();
  Serializer->endBody();
  Serializer->endEnvelope();

  // Send the message to the web service
  Connector->EndMessage();

  // Read the response
  Reader.CreateInstance(__uuidof(SoapReader));

  // Connect the reader to the output stream of the connector
  Reader->Load(_variant_t((IUnknown*)Connector->OutputStream),
                  "");

  // Display the result
  printf("Answer: %s\n", (const char *)Reader->RPCResult->text);
    CoUninitialize();

}