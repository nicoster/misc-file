package org.mfn.dishes.proto.main;


import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.mfn.tcpclient.TcpClient;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class MainClient {
	
	private static MainClient mInstance = null;
	public static MainClient getInstance() {
		if (mInstance == null) {
			mInstance = new MainClient();
		}
		return mInstance;
	}
	
	private
	TcpClient mConn = TcpClient.getInstance();
	
	String request(String req)
	{
		return mConn.request(req);
	}
	
	String mUid, mDevice, mVersion;
	int mSeq = 0;
	
	int seq()
	{
		return ++ mSeq;
	}
	
	public
	void init(String uid, String device, String server, int port, String version)
	{
		if (version == null || server.length() == 0)
		{
			version = "v1.0";
		}

		mUid = uid;
		mDevice = device;
		mVersion = version;		
		
		if (server == null || server.length() == 0)
		{
			server = "fbsmart.cn";
		}
		
		if (port == 0)
		{
			port = 7990;
		}
		mConn.init(server, port);
	}
	
	String getNodeValue(Document dom, String tag)
	{
		Element root = dom.getDocumentElement();
		NodeList items = root.getElementsByTagName(tag);
		if (items.getLength() > 0) {
			Node item = items.item(0);
			if (item.getNodeName() == tag) {
				return item.getNodeValue();
			}
		}
		
		return "";
	}
	
	String getNodeAttribute(Document dom, String tag, String attr)
	{
		Element root = dom.getDocumentElement();
		NodeList items = root.getElementsByTagName(tag);
		if (items.getLength() > 0) {
			Node item = items.item(0);
			NamedNodeMap attrs = item.getAttributes();
			Node anAttr = attrs.getNamedItem(attr);
			if (anAttr != null)
			{
				return anAttr.getNodeName();
			}
		}
		
		return "";
	
	}
	
	Boolean parseLogin(String res)
	{
		if (res.length() == 0)
			return false;
		
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        try {
            DocumentBuilder builder = factory.newDocumentBuilder();
            Document dom = builder.parse(res);
            return "login" == getNodeAttribute(dom, "fbsmart", "cmd");
        } catch (Exception e) {
//            throw new RuntimeException(e);
        }
		return false; 		
	}
	
	public Boolean login(String name, String passwd)
	{
		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='login' seq='%d'><data><waiterid>%s</waiterid><password>%s</password><lostdish></lostdish><maxdishid>-1</maxdishid><clientver>%s</clientver></data></fbsmart>", 
				mUid, mDevice, seq(), name, passwd, mVersion);
		
		String res = request(req);
		
		return parseLogin(res);
	}
}
