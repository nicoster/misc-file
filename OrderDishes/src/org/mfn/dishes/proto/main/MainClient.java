package org.mfn.dishes.proto.main;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Date;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.mfn.dishes.vo.DeskDetailInfo;
import org.mfn.dishes.vo.DeskDishInfo;
import org.mfn.dishes.vo.DishCategoryInfo;
import org.mfn.dishes.vo.DishInfo;
import org.mfn.dishes.vo.FlavorInfo;
import org.mfn.dishes.vo.ServerImageInfo;
import org.mfn.dishes.vo.UserInfo;
import org.mfn.tcpclient.TcpClient;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NamedNodeMap;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;

import android.os.Handler;
import android.text.TextUtils;
import android.util.Log;

public class MainClient {

	private static MainClient mInstance = null;
	private String mUid, mDevice, mVersion, mWaiter;
	int mSeq = 0;

	public static MainClient getInstance() {
		if (mInstance == null) {
			mInstance = new MainClient();
		}
		return mInstance;
	}

	public class Event {
		/**
		 * This method gets called when finishing makeing an order
		 * @param error	0 for success. 
		 * @param errorStr 
		 * @param deskDetail
		 */
		public void onOrderDishes(int error, String errorStr, DeskDetailInfo deskDetail) {
		}

		public void onCancelDish(int error, String errorStr) {
		}
	}

	Handler mHandler;

	private TcpClient mConn = TcpClient.getInstance();

	private String request(String req) {
		return mConn.request(req);
	}

	private boolean requestForOutputStream(String req, OutputStream o) {
		return mConn.requestForOutputStream(req, o);
	}	

	synchronized int seq() {
		return ++mSeq;
	}

	/**
	 * Initialize this module. Make sure this method is called within main
	 * thread. As a Handler gets initialized inside, on which we depend to post
	 * notification for data is ready for asynchronous calls.
	 */
	public void init(String uid, String device, String server, int port, String version) {
		if (version == null || server.length() == 0) {
			version = "v1.0";
		}

		// mHandler = new Handler();

		mUid = uid;
		mWaiter = uid;
		mDevice = device;
		mVersion = version;

		if (server == null || server.length() == 0) {
			server = "fbsmart.cn";
		}

		if (port == 0) {
			port = 7990;
		}
		mConn.init(server, port);
	}

	public boolean post(Runnable r) {
		return mHandler.post(r);
	}

	private String getNodeValue(Node item) {
		if (item.getFirstChild() != null)
			return item.getFirstChild().getNodeValue();
		return null;
	}

	private String getNodeValue(Element root, String tag) {
		if (root == null)
			return "";

		NodeList items = root.getElementsByTagName(tag);
		if (items.getLength() > 0) {
			Node item = items.item(0);
			if (item.getNodeName() == tag) {
				return item.getNodeValue();
			}
		}

		return "";
	}

	private String getNodeAttribute(Node item, String attr) {
		if (item == null)
			return "";
		NamedNodeMap attrs = item.getAttributes();
		Node anAttr = attrs.getNamedItem(attr);
		if (anAttr != null) {
			return anAttr.getNodeValue();
		}

		return "";
	}

	private String getNodeAttribute(Element root, String tag, String attr) {
		if (root == null)
			return "";
		NodeList items = root.getElementsByTagName(tag);
		if (items.getLength() > 0) {
			Node item = items.item(0);
			NamedNodeMap attrs = item.getAttributes();
			Node anAttr = attrs.getNamedItem(attr);
			if (anAttr != null) {
				return anAttr.getNodeValue();
			}
		}
		return "";
	}

	/**
	 * Download the image <code>file</code> and save it to <code>dir</code>.
	 * 
	 * @param file
	 *            the file name to download, supposed to be something like
	 *            '000100063.bmp'
	 * @param dir
	 *            the directory to which the downloaded image saves
	 */
	public void downloadImage(String file, String dir) {
		String[] fields = file.split("\\.");
		assert (fields.length == 2);
		assert (!TextUtils.isEmpty(dir));
		// Log.d("client", "get " + file);

		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='getfile' seq='%d' dnt='1'><data>"
				+ "<waiterid>%s</waiterid><deskid/><consumeid/><param1>%s</param1>" + "<param2>%s</param2></data></fbsmart>", mUid,
				mDevice, seq(), mUid, file, fields[1].toLowerCase());

		try {
			FileOutputStream out = new FileOutputStream(new File(dir + "/" + file));
			requestForOutputStream(req, out);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/**
	 * get image infos
	 * @return
	 */
	public ServerImageInfo[] getImageInfo() {
		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='TreeData' seq='%d' dnt='1'><data>"
				+ "<waiterid>%s</waiterid><deskid/><consumeid/><param1>picdir</param1>" + "<param2/></data></fbsmart>", mUid, mDevice,
				seq(), mUid);

		String res = request(req);
		return parseImageInfo(res);
	}
	
	/**
	 * resolve image infos
	 * @param res
	 * @return
	 */
	private ServerImageInfo[] parseImageInfo(String res) {
		ServerImageInfo serverImageInfos[] = null;
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(
					new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			NodeList items = root.getElementsByTagName("row");
			serverImageInfos = new ServerImageInfo[items.getLength()];
			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				long time = parseInt(getNodeAttribute(item, "stat"));
				ServerImageInfo serverImageInfo = new ServerImageInfo(getNodeValue(item),parseInt(getNodeAttribute(item, "code")),new Date(time * 1000));
				serverImageInfos[i] = serverImageInfo;
			}
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return serverImageInfos;
	}

	/**
	 * get flavor info
	 * @return
	 */
	public FlavorInfo[] getFlavorInfos() {
		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='query' seq='%d' dnt='1'><data>"
				+ "<table field='kouw_id,kouw_neir,kouw_bz'>kouw</table></data></fbsmart>", mUid, mDevice, seq());
		String res = request(req);
		return parseFlavorInfo(res);
	}
	
	/**
	 * resolve flavor info
	 * @param res
	 * @return
	 */
	private FlavorInfo[] parseFlavorInfo(String res) {
		FlavorInfo flavorInfo[] = null;
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			NodeList items = root.getElementsByTagName("record");
			flavorInfo = new FlavorInfo[items.getLength()];
			
			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				FlavorInfo obj = new FlavorInfo(getNodeAttribute(item, "f1"), getNodeAttribute(item, "f2"), parseBoolean(getNodeAttribute(item, "f3")));
				flavorInfo[i] = obj;
			}
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return flavorInfo;
	}
	

	/**
	 * get dish category info
	 * @return
	 */
	public DishCategoryInfo[] getDishCategoryInfos() {
		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='query' seq='%d' dnt='1'><data>"
				+ "<table field='uid,ctname,ctparentid,ctorder'>stCategory</table></data></fbsmart>", mUid, mDevice, seq());
		String res = request(req);
		return parseDishCategoryInfo(res);
	}
	
	/**
	 * resolve dish category info
	 * @param res
	 * @return
	 */
	private DishCategoryInfo[] parseDishCategoryInfo(String res) {
		DishCategoryInfo dishCategoryInfos[] = null;
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(
					new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			NodeList items = root.getElementsByTagName("record");
			dishCategoryInfos = new DishCategoryInfo[items.getLength()];
			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				DishCategoryInfo dishCategoryInfo = new DishCategoryInfo(getNodeAttribute(item, "f1"), getNodeAttribute(item, "f2"), getNodeAttribute(item, "f3"), parseInt(getNodeAttribute(item, "f4")));
				dishCategoryInfos[i] = dishCategoryInfo;
			}
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return dishCategoryInfos;
	}


	public static float parseFloat(String s) {
		if (TextUtils.isEmpty(s))
			return 0.0f;

		return Float.parseFloat(s);
	}

	public static int parseInt(String s) {
		if (TextUtils.isEmpty(s))
			return 0;

		return Integer.parseInt(s);
	}

	public static boolean parseBoolean(String s) {
		if (TextUtils.isEmpty(s))
			return false;

		return Boolean.parseBoolean(s);
	}
	

	/**
	 * get dish infos
	 * @return
	 */
	public DishInfo[] getDishInfos() {
		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='query' seq='%d' dnt='1'><data>"
				+ "<table field='cp_id,cp_code,cp_qcode,cp_name,cp_size,cp_unit,cp_price,cp_cate,cp_var,cp_mzuof,cp_azuof'>caip</table>"
				+ "</data></fbsmart>", mUid, mDevice, seq());
		String res = request(req);
		return parseDishInfo(res);
	}

	// <row f1="000100131" f2="000100131" f3="HHXJCDQXL" f4="DishName" f5="" f6="unit"
	// f7="128" f8="00010009" f9="0"
	// f10="1" f11="00010004,00010005,00010006" f12="72" f13=",," f14="0"
	// f15="100"/>
	private DishInfo[] parseDishInfo(String res) {
		Log.d("MainClient", "DishInfo Msg = " + res);
		DishInfo[] dishInfos = null;
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			NodeList items = root.getElementsByTagName("row");
			dishInfos = new DishInfo[items.getLength()];
			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				DishInfo dishInfo = new DishInfo(getNodeAttribute(item, "f1"), 
							getNodeAttribute(item, "f2"), 
							getNodeAttribute(item, "f3"), 
							getNodeAttribute(item, "f4"), 
							parseInt(getNodeAttribute(item, "f5")), 
							getNodeAttribute(item, "f6"), 
							parseFloat(getNodeAttribute(item, "f7")), 
							parseBoolean(getNodeAttribute(item, "f9")), 
							parseFloat(getNodeAttribute(item, "f14")), 
							parseFloat(getNodeAttribute(item, "f15")), 
							getNodeAttribute(item, "f16"), 
							getNodeAttribute(item, "f17"), 
							parseInt(getNodeAttribute(item, "f12")));
				dishInfo.addCategory(getNodeAttribute(item, "f8"));
				//f11 can be null or "00010005,00010007,00010004,00010016,00010002,00010008,00010013,00010029,20.00,20.00,00010003,00010001,00010006,00010017,00010009,00010014,00010010,00010011"
				//f13 can be null or ",,,,,,,,,,,,,,,,,20.00;1"
//				dishInfo.addCookInfo(getNodeAttribute(item, "f11"), parseFloat(getNodeAttribute(item, "f13")));
				// if (dish.hasMultiCookingStyle() !=
				// parseBoolean(getNodeAttribute(item, "f10")))
				// {
				// Log.e("client", "multi-cooking-style inconsistent:" +
				// getNodeAttribute(item, "f11") + " f9:" +
				// getNodeAttribute(item, "f9"));
				// }
				dishInfos[i] = dishInfo;
			}

			return dishInfos;
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return dishInfos;
	}
	
	/**
	 * check the login result
	 * @param res
	 * @return
	 */
	private Boolean parseLogin(String res) {
		if (res.length() == 0){
			return false;
		}			

		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(new ByteArrayInputStream(res.getBytes())));
			String cmd = getNodeAttribute(dom.getDocumentElement(), "fbsmart", "cmd");
			return "login" == cmd;
		} catch (Exception e) {
			Log.e("client", e.toString());
		}
		return false;
	}

	/**
	 * login to server
	 * @param name
	 * @param passwd
	 * @return
	 */
	public boolean login(String name, String passwd) {
		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='login' seq='%d'><data><waiterid>%s</waiterid>"
				+ "<password>%s</password><lostdish></lostdish><maxdishid>-1</maxdishid><clientver>%s</clientver></data></fbsmart>", mUid,
				mDevice, seq(), name, passwd, mVersion);

		String res = request(req);
		return parseLogin(res);
	}

	/**
	 * get user infos
	 * @return
	 */
	public UserInfo[] getUserInfos() {
		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='query' seq='%d' dnt='1'>"
				+ "<data><table field='yonghxx_yhm,yonghxx_qm,yonghxx_ms,yonghxx_mm'>yonghxx</table></data></fbsmart>", mUid, mDevice, seq());

		String res = request(req);
		return parseUserInfo(res);
	}
	
	/**
	 * resolve the user result
	 * @param res
	 * @return
	 */
	private UserInfo[] parseUserInfo(String res) {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			NodeList items = root.getElementsByTagName("record");
			UserInfo users[] = new UserInfo[items.getLength()];

			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				UserInfo user = new UserInfo(getNodeAttribute(item, "f1"), getNodeAttribute(item, "f2"), getNodeAttribute(item, "f3"));
				if (TextUtils.isEmpty(user.getId())) {
					Log.e("client", "invalid user, dropped:" + user.toString());
				} else {
					users[i] = user;
				}
			}
			return users;
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return null;
	}
	
	private String parseSelectDeskResp(String res) {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			return getNodeValue(root, "consumeid");
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return null;
	}

	/**
	 * Select a desk before making an order.
	 * @param deskId
	 * @param headcount
	 * @return the orderid if success, or null otherwise.
	 */
	private String selectDesk(String deskId, int headcount) {
		assert !TextUtils.isEmpty(deskId);
		assert headcount > 0;

		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='opendesk' seq='%d' dnt='1'>"
				+ "<data><type>1</type><desk><deskid>%s</deskid><rens>%d</rens><waiterid>%s</waiterid></desk></data></fbsmart>", mUid,
				mDevice, seq(), deskId, headcount, mWaiter);

		String res = request(req);
		return parseSelectDeskResp(res);
	}

	/**
	 * 
	 * @param res
	 * @return
	 */
	private boolean parseNewOrderResp(String res) {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			return !TextUtils.isEmpty(getNodeAttribute(root, "desk", "billid"));
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return false;
	}
	
	/**
	 * 
	 * @param orderId
	 * @param deskId
	 * @param headcount
	 * @param dishes
	 * @return
	 */
	private boolean newOrder(String orderId, String deskId, int headcount, DeskDishInfo[] dishes) {
		assert dishes.length > 0;
		assert !TextUtils.isEmpty(orderId);
		assert !TextUtils.isEmpty(deskId);
		assert headcount > 0;

		String rows = "";
		for (int i = 0; i < dishes.length; i++) {
			DeskDishInfo dish = dishes[i];
			rows += String.format("<row uid='%d' gds='%s' qty='%f' tasteid='%s' chucfs='%d' price='%f' danw='%s' />", i, dish.getId(),
					dish.getCount(), dish.getFlavorIds(), dish.getServingMode(), dish.getPrice(), dish.getUnit());
		}

		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='adddish' seq='%d' dnt='1'>"
				+ "<data><deskid>%s</deskid><rens>%d</rens><waiterid>%s</waiterid>"
				+ "<consumeid>%s</consumeid><detail>%s</detail></data></fbsmart>", mUid, mDevice, seq(), deskId, headcount, mWaiter,
				orderId, rows);

		String res = request(req);
		return parseNewOrderResp(res);
	}
	
	/**
	 * 
	 * @param res
	 * @return
	 */
	private DeskDetailInfo parseDeskDetail(String res) {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			DeskDetailInfo deskDetailInfo = new DeskDetailInfo(getNodeValue(root, "desk"), parseInt(getNodeAttribute(root, "desk", "rens")), getNodeAttribute(root, "desk", "bill"), getNodeAttribute(root, "desk", "waiter"));

			NodeList items = root.getElementsByTagName("row");
			deskDetailInfo.setDeskDishInfos(new DeskDishInfo[items.getLength()]);
			
			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				DeskDishInfo dish = new DeskDishInfo(getNodeAttribute(item, "id"), 
													 getNodeAttribute(item, "id"), 
													 getNodeAttribute(item, "state"), 
													 parseFloat(getNodeAttribute(item, "qty")), 
													 new Date(getNodeAttribute(item, "time")), 
													 parseFloat(getNodeAttribute(item, "prc")), 
													 getNodeAttribute(item, "usr"), 
													 getNodeAttribute(item, "dw"), 
													 getNodeAttribute(item, "cz"));

				deskDetailInfo.getDeskDishInfos()[i] = dish;
			}

			return deskDetailInfo;
		} catch (Exception e) {
			Log.e("client", e.toString());
		}
		return null;
	}
	
	/**
	 * 
	 * @param deskId
	 * @param headcount
	 * @param orderId
	 * @return
	 */
	private DeskDetailInfo getDeskDetail(String deskId, int headcount, String orderId) {
		assert !TextUtils.isEmpty(orderId);
		assert !TextUtils.isEmpty(deskId);
		assert headcount > 0;

		String req = String.format("<fbsmart UID='%s' dev='%s' cmd='updatemenu' seq='%d' dnt='1'><data>"
				+ "<deskid>%s</deskid><rens>%d</rens><waiterid>%s</waiterid>" + "<consumeid>%s</consumeid></data></fbsmart>", mUid,
				mDevice, seq(), deskId, headcount, mWaiter, orderId);
		String res = request(req);
		return parseDeskDetail(res);
	}
	
	/**
	 * 
	 * @param err
	 * @param errString
	 * @param dd
	 * @param cb
	 */
	private void postOrderNotification(final int err, final String errString, final DeskDetailInfo dd, final MainClient.Event cb) {
		mHandler.post(new Runnable() {
			public void run() {
				cb.onOrderDishes(err, errString, dd);
			}
		});
	}
	
	/**
	 * order a dish
	 * @param deskId
	 * @param headcount
	 * @param dishes
	 * @param callback
	 * @param async
	 * @return
	 */
	public boolean order(final String deskId, final int headcount, final DeskDishInfo[] dishes, final MainClient.Event callback, boolean async) {
		assert !TextUtils.isEmpty(deskId);
		assert headcount > 0;
		assert dishes != null;
		assert callback != null;

		if (async != false) {
			final Thread t = new Thread() {
				public void run() {
					try {
						order(deskId, headcount, dishes, callback, false);
					} finally {

					}
				}
			};
			t.start();
			return true;
		}

		String orderId = selectDesk(deskId, headcount);
		if (TextUtils.isEmpty(orderId)) {
			postOrderNotification(1, null, null, callback);
			return false;
		}

		boolean order = newOrder(orderId, deskId, headcount, dishes);
		if (order == false) {
			postOrderNotification(2, null, null, callback);
			return false;
		}

		DeskDetailInfo dd = getDeskDetail(deskId, headcount, orderId);
		postOrderNotification(dd == null ? 3 : 0, "", dd, callback);
		return false;
	}
}
