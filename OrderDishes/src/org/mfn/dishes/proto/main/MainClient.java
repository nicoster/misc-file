package org.mfn.dishes.proto.main;

import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Date;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.mfn.dishes.vo.DeskDetail;
import org.mfn.dishes.vo.DishInfoObj;
import org.mfn.dishes.vo.DishObj;
import org.mfn.dishes.vo.DishTypeObj;
import org.mfn.dishes.vo.FlavorInfoObj;
import org.mfn.dishes.vo.ImageInfoObj;
import org.mfn.dishes.vo.UserInfoObj;
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
		public void onOrderDishes(int error, String errorStr, DeskDetail deskDetail) {
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

	String mUid, mDevice, mVersion, mWaiter;
	int mSeq = 0;

	synchronized int seq() {
		return ++mSeq;
	}

	/**
	 * Initialize this module. Make sure this method is called within main
	 * thread. As a Handler gets initialized inside, on which we depend to post
	 * notification for data is ready for asynchronous calls.
	 */
	public void init(String uid, String device, String server, int port,
			String version) {
		if (version == null || server.length() == 0) {
			version = "v1.0";
		}

//		mHandler = new Handler();

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

	@SuppressWarnings("unused")
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

		String req = String
				.format(
						"<fbsmart UID='%s' dev='%s' cmd='getfile' seq='%d' dnt='1'><data>"
								+ "<waiterid>%s</waiterid><deskid/><consumeid/><param1>%s</param1>"
								+ "<param2>%s</param2></data></fbsmart>", mUid,
						mDevice, seq(), mUid, file, fields[1].toLowerCase());

		try {
			FileOutputStream out = new FileOutputStream(new File(dir + "/"
					+ file));
			requestForOutputStream(req, out);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private ImageInfoObj[] parseImageInfo(String res) {
		ImageInfoObj objs[] = null;
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(
					new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			NodeList items = root.getElementsByTagName("row");
			objs = new ImageInfoObj[items.getLength()];
			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				ImageInfoObj obj = new ImageInfoObj();
				obj.name = getNodeValue(item);
				obj.size = parseInt(getNodeAttribute(item, "code"));
				long time = parseInt(getNodeAttribute(item, "stat"));
				obj.modified_time = new Date(time * 1000);

				objs[i] = obj;
			}
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return objs;
	}

	public ImageInfoObj[] getImageInfo() {
		String req = String
				.format(
						"<fbsmart UID='%s' dev='%s' cmd='TreeData' seq='%d' dnt='1'><data>"
								+ "<waiterid>%s</waiterid><deskid/><consumeid/><param1>picdir</param1>"
								+ "<param2/></data></fbsmart>", mUid, mDevice,
						seq(), mUid);

		String res = request(req);
		return parseImageInfo(res);
	}

	// <record f1="00010001" f2="鐩愭按" f3="1"/>
	private FlavorInfoObj[] parseFlavorInfo(String res) {
		FlavorInfoObj objs[] = null;
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(
					new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			NodeList items = root.getElementsByTagName("record");
			objs = new FlavorInfoObj[items.getLength()];
			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				FlavorInfoObj obj = new FlavorInfoObj();
				obj.id = getNodeAttribute(item, "f1");
				obj.name = getNodeAttribute(item, "f2");
				obj.is_cook_style = parseBoolean(getNodeAttribute(item, "f3"));

				objs[i] = obj;
			}
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return objs;
	}

	public FlavorInfoObj[] getFlavorInfo() {
		String req = String
				.format(
						"<fbsmart UID='%s' dev='%s' cmd='query' seq='%d' dnt='1'><data>"
								+ "<table field='kouw_id,kouw_neir,kouw_bz'>kouw</table></data></fbsmart>",
						mUid, mDevice, seq());
		String res = request(req);
		return parseFlavorInfo(res);
	}

	private DishTypeObj[] parseDishTypeInfo(String res) {
		DishTypeObj dishtypes[] = null;
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(
					new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			NodeList items = root.getElementsByTagName("record");
			dishtypes = new DishTypeObj[items.getLength()];
			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				DishTypeObj dishtype = new DishTypeObj();
				dishtype.id = getNodeAttribute(item, "f1");
				dishtype.name = getNodeAttribute(item, "f2");
				dishtype.parentId = getNodeAttribute(item, "f3");
				dishtype.index = parseInt(getNodeAttribute(item, "f4"));

				dishtypes[i] = dishtype;
			}
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return dishtypes;
	}

	public DishTypeObj[] getDishTypeInfo() {
		String req = String
				.format(
						"<fbsmart UID='%s' dev='%s' cmd='query' seq='%d' dnt='1'><data>"
								+ "<table field='uid,ctname,ctparentid,ctorder'>stCategory</table></data></fbsmart>",
						mUid, mDevice, seq());
		String res = request(req);
		return parseDishTypeInfo(res);
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

	// <row f1="000100131" f2="000100131" f3="HHXJCDQXL" f4="绾㈣姳锜� f5="" f6="渚�
	// f7="128" f8="00010009" f9="0"
	// f10="1" f11="00010004,00010005,00010006" f12="72" f13=",," f14="0"
	// f15="100"/>
	private DishInfoObj[] parseDishInfo(String res) {
		DishInfoObj dishes[] = null;
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(
					new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			NodeList items = root.getElementsByTagName("row");
			dishes = new DishInfoObj[items.getLength()];
			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				DishInfoObj dish = new DishInfoObj();
				dish.id = getNodeAttribute(item, "f1");
				dish.query_code = getNodeAttribute(item, "f2");
				dish.query_code2 = getNodeAttribute(item, "f3");
				dish.name = getNodeAttribute(item, "f4");
				dish.size = getNodeAttribute(item, "f5");
				dish.unit = getNodeAttribute(item, "f6");
				dish.price = parseFloat(getNodeAttribute(item, "f7"));
				dish.type = getNodeAttribute(item, "f8");
				dish.variable_price = parseBoolean(getNodeAttribute(item, "f9"));
				dish.setCookingInfo(getNodeAttribute(item, "f11"),
						getNodeAttribute(item, "f13"));
				// if (dish.hasMultiCookingStyle() !=
				// parseBoolean(getNodeAttribute(item, "f10")))
				// {
				// Log.e("client", "multi-cooking-style inconsistent:" +
				// getNodeAttribute(item, "f11") + " f9:" +
				// getNodeAttribute(item, "f9"));
				// }
				dish.flag = parseInt(getNodeAttribute(item, "f12"));
				dish.cost = parseFloat(getNodeAttribute(item, "f14"));
				dish.gross_profit = parseFloat(getNodeAttribute(item, "f15"));
				dish.name_en = getNodeAttribute(item, "f16");
				dish.name_jp = getNodeAttribute(item, "f17");
				dishes[i] = dish;
			}

			return dishes;
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return dishes;
	}

	public DishInfoObj[] getDishInfo() {
		String req = String
				.format(
						"<fbsmart UID='%s' dev='%s' cmd='query' seq='%d' dnt='1'><data>"
								+ "<table field='cp_id,cp_code,cp_qcode,cp_name,cp_size,cp_unit,cp_price,cp_cate,cp_var,cp_mzuof,cp_azuof'>caip</table>"
								+ "</data></fbsmart>", mUid, mDevice, seq());
		String res = request(req);
		return parseDishInfo(res);
	}

	private UserInfoObj[] parseUserInfo(String res) {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(
					new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			NodeList items = root.getElementsByTagName("record");
			UserInfoObj users[] = new UserInfoObj[items.getLength()];
			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				UserInfoObj user = new UserInfoObj();
				user.id = getNodeAttribute(item, "f1");
				user.name = getNodeAttribute(item, "f2");
				user.level = getNodeAttribute(item, "f3");

				if (TextUtils.isEmpty(user.id)) {
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

	private Boolean parseLogin(String res) {
		if (res.length() == 0)
			return false;

		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(
					new ByteArrayInputStream(res.getBytes())));
			String cmd = getNodeAttribute(dom.getDocumentElement(), "fbsmart",
					"cmd");
			return "login" == cmd;
		} catch (Exception e) {
			Log.e("client", e.toString());
		}
		return false;
	}

	public boolean login(String name, String passwd) {
		String req = String
				.format(
						"<fbsmart UID='%s' dev='%s' cmd='login' seq='%d'><data><waiterid>%s</waiterid>"
								+ "<password>%s</password><lostdish></lostdish><maxdishid>-1</maxdishid><clientver>%s</clientver></data></fbsmart>",
						mUid, mDevice, seq(), name, passwd, mVersion);

		String res = request(req);

		return parseLogin(res);
	}

	public UserInfoObj[] getUserInfo() {
		String req = String
				.format(
						"<fbsmart UID='%s' dev='%s' cmd='query' seq='%d' dnt='1'>"
								+ "<data><table field='yonghxx_yhm,yonghxx_qm,yonghxx_ms,yonghxx_mm'>yonghxx</table></data></fbsmart>",
						mUid, mDevice, seq());

		String res = request(req);

		return parseUserInfo(res);
	}
	
	private String parseSelectDeskResp(String res) {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(
					new ByteArrayInputStream(res.getBytes("GBK"))));
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
	private String selectDesk(String deskId, int headcount)
	{
		assert !TextUtils.isEmpty(deskId);
		assert headcount > 0;

		String req = String.format(
						"<fbsmart UID='%s' dev='%s' cmd='opendesk' seq='%d' dnt='1'>"
						+ "<data><type>1</type><desk><deskid>%s</deskid><rens>%d</rens><waiterid>%s</waiterid></desk></data></fbsmart>",
						mUid, mDevice, seq(), deskId, headcount, mWaiter);

		String res = request(req);
		return parseSelectDeskResp(res);
	}

	private boolean parseNewOrderResp(String res) {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(
					new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			return !TextUtils.isEmpty(getNodeAttribute(root, "desk", "billid"));
		} catch (Exception e) {
			Log.e("client", e.toString());
		}

		return false;
	}
	
	private boolean newOrder(String orderId, String deskId, int headcount, DishObj[] dishes)
	{
		assert dishes.length > 0;
		assert !TextUtils.isEmpty(orderId);
		assert !TextUtils.isEmpty(deskId);
		assert headcount > 0;
		
		String rows = "";
		for (int i = 0; i < dishes.length; i ++)
		{
			DishObj dish = dishes[i];
			rows += String.format("<row uid='%d' gds='%s' qty='%f' tasteid='%s' chucfs='%d' price='%f' danw='%s' />",
					i, dish.id, dish.count, dish.flavorIds, dish.servingMode, dish.price, dish.unit);
		}
		
		String req = String.format(
						"<fbsmart UID='%s' dev='%s' cmd='adddish' seq='%d' dnt='1'>" +
						"<data><deskid>%s</deskid><rens>%d</rens><waiterid>%s</waiterid>" +
						"<consumeid>%s</consumeid><detail>%s</detail></data></fbsmart>",
						mUid, mDevice, seq(), deskId, headcount, mWaiter, orderId, rows);

		String res = request(req);
		return parseNewOrderResp(res);
	}
	
	private DeskDetail parseDeskDetail(String res)
	{
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		try {
			DocumentBuilder builder = factory.newDocumentBuilder();

			Document dom = builder.parse(new InputSource(
					new ByteArrayInputStream(res.getBytes("GBK"))));
			Element root = dom.getDocumentElement();
			DeskDetail dd = new DeskDetail();
			dd.headcount = parseInt(getNodeAttribute(root, "desk", "rens"));
			dd.waiter = getNodeAttribute(root, "desk", "waiter");
			dd.orderId = getNodeAttribute(root, "desk", "bill");
			dd.id = getNodeValue(root, "desk");
			
			NodeList items = root.getElementsByTagName("row");
			dd.dishes = new DishObj[items.getLength()];
			for (int i = 0; i < items.getLength(); i++) {
				Node item = items.item(i);
				DishObj dish = new DishObj();
				dish.id = getNodeAttribute(item, "id");
				dish.dishInfoId = getNodeAttribute(item, "gds");
				dish.count = parseFloat(getNodeAttribute(item, "qty"));
				dish.state = getNodeAttribute(item, "state");
				dish.start = new Date(getNodeAttribute(item, "time"));
				dish.price = parseFloat(getNodeAttribute(item, "prc"));
				dish.waiter = getNodeAttribute(item, "usr");
				dish.unit = getNodeAttribute(item, "dw");
				dish.operator = getNodeAttribute(item, "cz");

				dd.dishes[i] = dish;
			}

			return dd;
		} 
		catch (Exception e) {
			Log.e("client", e.toString());
		}
		return null;
	}
	
	private DeskDetail getDeskDetail(String deskId, int headcount, String orderId)
	{
		assert !TextUtils.isEmpty(orderId);
		assert !TextUtils.isEmpty(deskId);
		assert headcount > 0;

		String req = String.format(
				"<fbsmart UID='%s' dev='%s' cmd='updatemenu' seq='%d' dnt='1'><data>" +
				"<deskid>%s</deskid><rens>%d</rens><waiterid>%s</waiterid>" +
				"<consumeid>%s</consumeid></data></fbsmart>", 
				mUid, mDevice, seq(), deskId, headcount, mWaiter, orderId);
		String res = request(req);
		return parseDeskDetail(res);
	}
	
	private void postOrderNotification(final int err, final String errString, final DeskDetail dd, final MainClient.Event cb)
	{
		mHandler.post(new Runnable(){
			public void run()
			{
				cb.onOrderDishes(err, errString, dd);
			}
		});
	}
	
	public boolean order(final String deskId, final int headcount, final DishObj[] dishes, final MainClient.Event callback, boolean async)
	{
		assert !TextUtils.isEmpty(deskId);
		assert headcount > 0;
		assert dishes != null;
		assert callback != null;

		if (async != false)
		{
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
		if (TextUtils.isEmpty(orderId))
		{
			postOrderNotification(1, null, null, callback);
			return false;
		}
		
		boolean order = newOrder(orderId, deskId, headcount, dishes);
		if (order == false)
		{
			postOrderNotification(2, null, null, callback);
			return false;
		}
		
		DeskDetail dd = getDeskDetail(deskId, headcount, orderId);
		postOrderNotification(dd == null ? 3 : 0, "", dd, callback);
        return false;
	}
}
