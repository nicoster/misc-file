package org.mfn.dishes.proto;

import org.mfn.tcpclient.TcpClient;

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
		mUid = uid;
		mDevice = device;
		mVersion = version;
		
		if (server == null || server.length() == 0)
		{
			server = "fbsmart.cn";
		}
		
		if (port == 0)
		{
			port = 7992;
		}
		mConn.init(server, port);
	}
	
	Boolean login(String name, String passwd)
	{
		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='login' seq='%d'><data><waiterid>%s</waiterid><password>%s</password><lostdish></lostdish><maxdishid>-1</maxdishid><clientver>%s</clientver></data></fbsmart>'", 
				mUid, mDevice, seq(), name, passwd, mVersion);
		
		String res = request(req);
		if (res.length() > 0)
		{
			
		}
		return false;
	}
}
