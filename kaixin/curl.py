#!/usr/bin/python
#coding=utf-8

import logging
import httplib
import urllib
import re
import Cookie

#httplib.HTTPConnection.debuglevel = 1

def login(user, passwd):
    url = 'http://www.kaixin001.com/login/login.php'
    data = {'email':user,
            'password':passwd,
            'remeber':0, #remember?
            'url':'/'}
    return getLoginUrlEx(url, data)

def getLoginUrlEx(url, data = False):
    return getLoginUrl(url, data)

def getUrlEx(url, data = False, cookies = ''):
    return getUrl(url, data, cookies)

def getLoginUrl(url, data):
    headers = {
        'Host':' www.kaixin001.com',
        'User-Agent':'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.1 Gecko/2008072820 Firefox/3.0.1)',
        'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        'Accept-Language':'en-us,en;q=0.5',
        'Accept-Charset':'UTF-8,*',
        'Keep-Alive':'300',
        'Connection':'keep-alive',
        'Content-Type':'application/x-www-form-urlencoded; charset=UTF-8',
        'Referer':'http://www.kaixin001.com/app/app.php?aid=1040',
    }
    (scheme, netloc, path, query, fragment) = httplib.urlsplit(url)
    conn = httplib.HTTPConnection(netloc)
    if data:
        params = urllib.urlencode(data)
        conn.request("POST", path, params, headers)
    else:
        conn.request("GET", path+'?'+query, '', headers)
    response = conn.getresponse()
    
    cookies = response.getheader('set-cookie')
    conn.close()

    simplecookie = Cookie.SimpleCookie()
    simplecookie.load(cookies)
    cookiestr = ''
    for c in simplecookie.keys():
        cookiestr += c + '=' + simplecookie[c].value + '; '

    return cookiestr

def getUrl(url, data, cookies = ''):
    headers = {
        'Host':' www.kaixin001.com',
        'User-Agent':'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.1 Gecko/2008072820 Firefox/3.0.1)',
        'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
        'Accept-Language':'en-us,en;q=0.5',
        'Accept-Charset':'UTF-8,*',
        'Keep-Alive':'300',
        'Connection':'keep-alive',
        'Content-Type':'application/x-www-form-urlencoded; charset=UTF-8',
        'Referer':'http://www.kaixin001.com/app/app.php?aid=1040',
        'Cookie':cookies
    }
    (scheme, netloc, path, query, fragment) = httplib.urlsplit(url)
    conn = httplib.HTTPConnection(netloc)
    if data:
        params = urllib.urlencode(data)
        conn.request("POST", path, params, headers)
    else:
        conn.request("GET", path+'?'+query, '', headers)
    response = conn.getresponse()
    c = response.status
    if c != 200 and c != 302:
        logging.info('curl.getUrl error: ' + c + ' ' + response.reason)
        return False

    result = response.read()
    conn.close()
    return result
