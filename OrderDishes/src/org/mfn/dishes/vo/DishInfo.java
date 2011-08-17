package org.mfn.dishes.vo;

import java.util.ArrayList;
import java.util.List;

public class DishInfo {
	private String 	mId;
	private String 	mCode;
	private String 	mPinyinCode;
	private String 	mName;
	private int 	mSize;
	private String 	mUnit;
	private float  	mPrice;
	private boolean mVariablePrice;
	private float	mCost;
	private float	mGrossProfit;
	private String	mNameEn;
	private String	mNameJp;
	private int		mFlag;
	private ImageInfo mImageInfo;
	private ArrayList<String> mCategoryList; //which category this dish belong to, may be multiple
	private ArrayList<CookInfo> mCookInfos; //cook style and it's price
	
	public DishInfo(){
		this.mCategoryList = new ArrayList<String>();
		this.mCookInfos = new ArrayList<DishInfo.CookInfo>();
	}
	
	public DishInfo(String id, String code, String pinyinCode, String name, int size, String unit, float price, boolean variablePrice,
				float cost, int flag, ImageInfo imageInfo){
		this.mId = id;
		this.mCode = code;
		this.mPinyinCode = pinyinCode;
		this.mName = name;
		this.mSize = size;
		this.mUnit = unit;
		this.mPrice = price;
		this.mVariablePrice = variablePrice;
		this.mCost = cost;
		this.mFlag = flag;
		this.mImageInfo = imageInfo;
		this.mCategoryList = new ArrayList<String>();
		this.mCookInfos = new ArrayList<DishInfo.CookInfo>();
	}
	
	public DishInfo(String id, String code, String pinyinCode, String name, int size, String unit, float price, boolean variablePrice,
				float cost, float grossProfit, String nameEn, String nameJp, int flag){
		this.mId = id;
		this.mCode = code;
		this.mPinyinCode = pinyinCode;
		this.mName = name;
		this.mSize = size;
		this.mUnit = unit;
		this.mPrice = price;
		this.mVariablePrice = variablePrice;
		this.mCost = cost;
		this.mGrossProfit = grossProfit;
		this.mNameEn = nameEn;
		this.mNameJp = nameJp;
		this.mFlag = flag;
		this.mCategoryList = new ArrayList<String>();
		this.mCookInfos = new ArrayList<DishInfo.CookInfo>();
	}
	
	// 是否套餐
	public boolean isPackage() {
		return (mFlag & 0x0001) != 0;
	} 
	
	// 自定义菜品
	public boolean isCustom() {
		return (mFlag & 0x0002) != 0;
	} 
	
	// 称重菜品
	public boolean isByQuantity() {
		return (mFlag & 0x0004) != 0;
	} 
	
	// 200904 拼菜套餐标志. 不是很确定这个标志位的意思. 先用这个函数名
	public boolean isPackage2() {
		return (mFlag & 0x0020) != 0;
	} 

	// Note: 该函数的定义是 是否可打折, 和协议中的定义相反. 协议中的定义是 "不可打折标志" true 表示不可打折
	// 2010 可打折标志 true 表示可打折
	public boolean isDiscountable() {
		return (mFlag & 0x0040) == 0;
	} 
	
	// 新菜
	public boolean isNew() {
		return (mFlag & 0x0080) != 0;
	}
	
	// 特色菜
	public boolean isSpecial() {
		return (mFlag & 0x0100) != 0;
	} 
	
	// 是否多做法
	public boolean hasMultiCookingStyle() {
		return this.mCookInfos != null && this.mCookInfos.size() > 1;
	} 
	
	public void addCategory(String categoryCode){
		if(this.mCategoryList.contains(categoryCode)){
			return;
		}
		this.mCategoryList.add(categoryCode);
	}
	
	public void delCategory(String categoryCode){
		if(this.mCategoryList.contains(categoryCode)){
			this.mCategoryList.remove(categoryCode);
		}
	}
	
	public void editCategory(String oldCategoryCode, String newCategoryCode){
		if(this.mCategoryList.contains(oldCategoryCode) && !this.mCategoryList.contains(newCategoryCode)){
			this.mCategoryList.remove(oldCategoryCode);
			this.mCategoryList.add(newCategoryCode);
		}
	}
	
	public List<String> getCategoryCodes(){
		return this.mCategoryList;
	}
	
	public boolean isInCategory(String categoryCode){
		if(this.mCategoryList.contains(categoryCode)){
			return true;
		}
		return false;		
	}
	
	/**
	 * add a cook info
	 * @param style
	 * @param price
	 */
	public void addCookInfo(String style, float price){
		CookInfo cookInfo = getCookInfo(style);
		if(cookInfo == null){
			cookInfo = new CookInfo(style, price);
			this.mCookInfos.add(cookInfo);
		}		
	}
	
	public void delCookInfo(String style){
		CookInfo cookInfo = getCookInfo(style);
		if(cookInfo != null){
			this.mCookInfos.remove(cookInfo);
		}
	}
	
	public void editCookInfo(String style, float price){
		CookInfo cookInfo = getCookInfo(style);
		if(cookInfo != null){
			cookInfo.setPrice(price);
		}
	}
	
	public CookInfo getCookInfo(String style){
		CookInfo cookInfo = null;
		for(int i = 0; i < this.mCookInfos.size(); i++){
			cookInfo = this.mCookInfos.get(i);
			if(style.equalsIgnoreCase(cookInfo.getStyle())){
				return cookInfo;
			}
		}
		return null;
	}	
	
	public String getId() {
		return mId;
	}

	public void setId(String mId) {
		this.mId = mId;
	}

	public String getCode() {
		return mCode;
	}

	public void setCode(String mCode) {
		this.mCode = mCode;
	}

	public String getPinyinCode() {
		return mPinyinCode;
	}

	public void setPinyinCode(String mPinyinCode) {
		this.mPinyinCode = mPinyinCode;
	}

	public String getName() {
		return mName;
	}

	public void setName(String mName) {
		this.mName = mName;
	}

	public int getSize() {
		return mSize;
	}

	public void setSize(int mSize) {
		this.mSize = mSize;
	}

	public String getUnit() {
		return mUnit;
	}

	public void setUnit(String mUnit) {
		this.mUnit = mUnit;
	}

	public float getPrice() {
		return mPrice;
	}

	public void setPrice(float mPrice) {
		this.mPrice = mPrice;
	}

	public boolean isVariablePrice() {
		return mVariablePrice;
	}

	public void setVariablePrice(boolean mVariablePrice) {
		this.mVariablePrice = mVariablePrice;
	}

	public float getCost() {
		return mCost;
	}

	public void setCost(float mCost) {
		this.mCost = mCost;
	}

	public float getGrossProfit() {
		return mGrossProfit;
	}

	public void setGrossProfit(float mGrossProfit) {
		this.mGrossProfit = mGrossProfit;
	}

	public String getNameEn() {
		return mNameEn;
	}

	public void setNameEn(String mNameEn) {
		this.mNameEn = mNameEn;
	}

	public String getNameJp() {
		return mNameJp;
	}

	public void setNameJp(String mNameJp) {
		this.mNameJp = mNameJp;
	}

	public ImageInfo getImageInfo() {
		return mImageInfo;
	}

	public void setImageInfo(ImageInfo mImageInfo) {
		this.mImageInfo = mImageInfo;
	}

	public void setCategoryCodes(ArrayList<String> mCategoryCodes) {
		this.mCategoryList = mCategoryCodes;
	}

	public ArrayList<CookInfo> getCookInfos() {
		return mCookInfos;
	}

	public void setCookInfos(ArrayList<CookInfo> mCookInfos) {
		this.mCookInfos = mCookInfos;
	}

	public int getFlag() {
		return mFlag;
	}

	public void setFlag(int mFlag) {
		this.mFlag = mFlag;
	}

	public class CookInfo{
		private String style;
		private float price;
		
		public CookInfo(String style, float price){
			this.style = style;
			this.price = price;
		}
		
		public String getStyle() {
			return style;
		}
		public void setStyle(String style) {
			this.style = style;
		}
		public float getPrice() {
			return price;
		}
		public void setPrice(float price) {
			this.price = price;
		}
		
	}
}
