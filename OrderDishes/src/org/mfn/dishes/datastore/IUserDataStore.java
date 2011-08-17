package org.mfn.dishes.datastore;

import java.util.List;

import org.mfn.dishes.vo.UserInfo;

public interface IUserDataStore {
	/**
	 * add a user info to data store
	 * @param userId
	 * @param userInfo
	 */
	public void addUserInfo(String userId, UserInfo userInfo);
	
	/**
	 * remove a user from data store
	 * @param userId
	 */
	public void delUserInfo(String userId);
	
	/**
	 * edit a user info
	 * @param oldUserInfo
	 * @param newUserInfo
	 */
	public void editUserInfo(UserInfo oldUserInfo, UserInfo newUserInfo);
	
	/**
	 * check whether user exist
	 * @param userId
	 * @return
	 */
	public boolean isUserInfoExist(String userId);
	
	/**
	 * age all the user infos
	 * @return
	 */
	public List<UserInfo> getAllUserInfo();
	
	/**
	 * get a uer info
	 * @param userId
	 * @return
	 */
	public UserInfo getUserInfo(String userId);
	
	/**
	 * clear all user data
	 */
	public void clearUserData();
}
