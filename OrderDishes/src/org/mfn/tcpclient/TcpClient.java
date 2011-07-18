package org.mfn.tcpclient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.UnknownHostException;

import android.util.Log;

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
	
	public static void hexDump(byte[] buf)
	{
		String out = "";
		for (int i = 0; i < buf.length; i ++)
		{
			out += String.format("%02x ", buf[i]);
		}
		Log.d("conn/", out);
	}
	
	public boolean requestForOutputStream(String req, OutputStream outstream)
	{
		InputStream in = null;
		try {
			assert(mServer != null && mServer.length() > 0);
			assert(mPort != 0);
			
	        Socket s = new Socket(mServer, mPort);
	        s.setSoTimeout(5000);
	        
	        OutputStreamWriter output = new OutputStreamWriter(s.getOutputStream(), "GBK");
	        output.write(req, 0, req.length());
	        output.flush();
	        Log.d("conn/send/", req);
	        
	        in = s.getInputStream();

			byte[] buffer = new byte[1024 * 4];
			int n = 0; // count = 0;
			while (-1 != (n = in.read(buffer))) {
				outstream.write(buffer, 0, n);
				//count += n;
			}
	        s.close();
		} 
		catch (UnknownHostException e) {
			e.printStackTrace();
		} 
		catch (IOException e) {
			e.printStackTrace();
		}	
		
		return true;
	}

	public String request(String req)
	{
		InputStream in = null;
		String res = "";
		try {
			assert(mServer != null && mServer.length() > 0);
			assert(mPort != 0);
			
	        Socket s = new Socket(mServer, mPort);
	       
	        OutputStreamWriter output = new OutputStreamWriter(s.getOutputStream(), "GBK");
	        output.write(req, 0, req.length());
	        output.flush();
	        Log.d("conn/send/", req);
	        
	        in = s.getInputStream();
	        
	        // for debugging
	        String buf = null;
	        BufferedReader input = new BufferedReader(new InputStreamReader(in, "GBK"));
	        while ((buf = input.readLine()) != null) res += buf;
	        Log.d("conn/recv/", res);
	        
	        s.close();
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}	
		
		return res;
	}
}
