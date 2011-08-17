package org.mfn.dishes.datastore;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.mfn.dishes.vo.UserInfo;

public class UserDataStore implements IUserDataStore {
	private HashMap<String, UserInfo> userInfoList = null;

	public UserDataStore() {
		userInfoList = new HashMap<String, UserInfo>();
	}

	@Override
	public void addUserInfo(String userId, UserInfo userInfo) {
		if(this.userInfoList.containsKey(userId)){
			return;
		}
		this.userInfoList.put(userId, userInfo);
	}

	@Override
	public void delUserInfo(String userId) {
		if(this.userInfoList.containsKey(userId)){
			this.userInfoList.remove(userId);
		}
	}

	@Override
	public void editUserInfo(UserInfo oldUserInfo, UserInfo newUserInfo) {
		if(this.userInfoList.containsKey(oldUserInfo.getId()) && !this.userInfoList.containsKey(newUserInfo.getId())){
			this.userInfoList.remove(oldUserInfo.getId());
			this.userInfoList.put(newUserInfo.getId(), newUserInfo);
		}
	}

	@Override
	public boolean isUserInfoExist(String userId) {
		if(this.userInfoList.containsKey(userId)){
			return true;
		}
		return false;
	}

	@Override
	public List<UserInfo> getAllUserInfo() {
		ArrayList<UserInfo> userInfos = new ArrayList<UserInfo>();
		Iterator<UserInfo> iterator = this.userInfoList.values().iterator();
		while (iterator.hasNext()) {
			userInfos.add(iterator.next());			
		}
		return userInfos;
	}

	@Override
	public UserInfo getUserInfo(String userId) {
		if(this.userInfoList.containsKey(userId)){
			return this.userInfoList.get(userId);
		}
		return null;
	}

	/**
	 * clear all user data
	 */
	public void clearUserData(){
		this.userInfoList.clear();
	}
}
