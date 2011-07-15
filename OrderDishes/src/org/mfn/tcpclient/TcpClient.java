package org.mfn.tcpclient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.UnknownHostException;

public class TcpClient {
	private static TcpClient mInstance = null;
	public static TcpClient getInstance() {
		if (mInstance == null) {
			mInstance = new TcpClient();
		}
		return mInstance;
	}
	
	String mServer;
	int mPort;
	
	public void init(String server, int port)
	{
		mServer = server;
		mPort = port;
	}

	public String request(String req)
	{
		String res = null;
		try {
			assert(mServer != null && mServer.length() > 0);
			assert(mPort != 0);
			
	        Socket s = new Socket(mServer, mPort);
	       
	        //outgoing stream redirect to socket
	        OutputStream out = s.getOutputStream();
	       
	        PrintWriter output = new PrintWriter(out);
	        output.println("Hello Android!");
	        
	        BufferedReader input = new BufferedReader(new InputStreamReader(s.getInputStream()));
	       
	        //read line(s)
	        res = input.readLine();

	        //Close connection
	        s.close();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}	
		
		return res;
	}
}
