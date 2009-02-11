
import logging
import json
import curl
import time
import commands
import os
import sys 
import tempfile
from park_algo import getNextToPark

def usage():
    print """
Parking Version 0.1 rewritten in python by http://wushituichao.cn/
Original version is written in php by http://www.onemouse.cn/
Usage: python parking.py -u <user> -p <password> | -h | -t | -l
  -u  your kaixin001.com's user
  -p  your kaixin001.com's password
  -h  print help info
  -t  parking your cars
  -l  show your cars info
"""

def getUserData(cookies):
#    logging.debug('cookies: ' + cookies)
    userUrl = 'http://www.kaixin001.com/app/app.php?aid=1040'
    data = curl.getUrlEx(userUrl, False, cookies)
    begin = 'var v_userdata = '
    middle = 'var v_frienddata = '
    end = 'var today = new Date();'
    beginPos = data.find(begin)
    middlePos = data.find(middle, beginPos + len(begin))
    endPos = data.find(end, middlePos + len(middle))

    me = data[beginPos + len(begin) : middlePos + len(begin) - len(middle)]
    #~ print 'me||', json.read(me)
    friends = data[middlePos + len(middle) : endPos + len(middle) - len(end) + 1]
    #~ print 'friends||', friends
    
    key = 'var g_verify = "'
    end = '";'
    beginPos = data.find(key, endPos)
    endPos = data.find(end, beginPos + len(key))
    verify = data[beginPos + len(key) : endPos]

    beginTag = '<script language=javascript>'
    #endTag = '</script>\r\n\r\n<script language=javascript>'
    endTag = 'function notice()'
    begin = data.find(beginTag, beginPos-100) + len(beginTag)
    end = data.find(endTag, begin)
    javascript = data[begin : end]
    javascript += ' WScript.Echo(acc());'
    javascript = javascript.replace('\n', '').replace('\r', '')

    fd, fn = tempfile.mkstemp('.js')
    #~ print fn
    fh = os.fdopen(fd, 'w')
    fh.write(javascript)
    fh.close()
    #~ logging.info(fn)
  #  status, acc = commands.getstatusoutput('/usr/bin/js ' + fn)
    result = os.popen('cscript.exe /nologo ' + fn)
 #   status = result.status()
    acc = result.read()
    #~ print "ACC: ", acc
	os.remove(fn)

    #~ if status != 0:
        #~ logging.info('Cannot execute "js", plz install spidermonkey first')
   #     sys.exit(2)

    return {'cars':json.read(me), 
            'friends':json.read(friends), 
            'verify':verify,
            'acc':acc,
            }

def getNeighborParkingInfo(cookies, uid, verify):
    data = {'puid':uid, 'verify':verify}
    url = 'http://www.kaixin001.com/parking/neighbor.php'
    data = curl.getUrlEx(url, data, cookies)
    return json.read(data)

def getFriendParkingInfo(cookies, uid, verify):
    data = {'puid':uid, 'verify':verify}
    url = 'http://www.kaixin001.com/parking/user.php'
    data = curl.getUrlEx(url, data, cookies)
    return json.read(data)

def parkCar(cookies, carid, first_fee_parking, neighbor, park_uid, parkid, verify, acc):
    url = 'http://www.kaixin001.com/parking/park.php'
    data = {
            'carid':carid,
            'first_fee_parking':first_fee_parking,
            'neighbor':neighbor,
            'park_uid':park_uid,
            'parkid':parkid,
            'verify':verify,
            'acc':acc,
            }
    result = curl.getUrlEx(url, data, cookies)
    #~ logging.debug('For parking, post:' + str(data))
    #~ logging.debug('kaixin returns:' + str(result))
    return json.read(result)

def getFriendEmptyParking(cookies, friends, verify):
    # sort according to the uid. lambda, cool!
    friends.sort(key = lambda item: item['uid'])
    all = []
    for v in friends:
        #~ print v
        #~ print '--------------------------------------------------------------------------------'
        if int(v['full']) == 0:  # or v['full'] == 0:
            all.append(v)
            #~ print 'appended', v['uid']

    #~ print '#### len', len(all)

    
    data = {}
    for v in all:
        if v['uid'] <= 2:
            data[v['uid']] = getNeighborParkingInfo(cookies, v['uid'], verify)
        else:
            data[v['uid']] = getFriendParkingInfo(cookies, v['uid'], verify)
        #~ print v['uid']
        #~ print '==================================================='
        #~ print data[v['uid']]

    parking_spaces = []
    for (uid, user_parking) in data.items():
        parking_space = {}
        for park_info in user_parking['parking']:
            if park_info['car_uid'] == 0 and not (int(park_info['parkid']) >> 16 & 255):
                if not parking_space.has_key('parking'):
                    parking_space['parking'] = []
                parking_space['parking'].append(park_info)
        if parking_space:
            parking_space['user'] = user_parking['user']
        parking_spaces.append(parking_space)

    #~ print parking_spaces
    return parking_spaces

def showUserInfo(user, cars):
    if not user:
        usage()
        sys.exit(2)

    count = len(cars)
    cash = 0
    print user['real_name'], 'has', count, 'car(s).'
    print 'They are:'
    for v in cars:
        print  v['car_name'], v['price'], 'RMB, parked at', v['park_real_name'], 'for', int((time.time() - v['ctime']) / 60), 'minutes.'
        cash += int(v['price'])

    print 'Now you have cash:', user['cash'], 'RMB'
    print 'Your cars value:', cash, 'RMB'
    print 'Total:', (cash + int(user['cash'])), 'RMB'
    
def parking2(cookies, user, cars, friends, verify, acc):
    print 'start parking..'
    total_money = 0
    parking_spaces = getFriendEmptyParking(cookies, friends, verify)

    #~ return
    if not parking_spaces:
        print 'oops..no parking space left.'
        return total_money
    retried = 0
    #~ for (uid, parking_space_group) in parking_spaces.items():
    for parking_space_group in parking_spaces:
        uid = parking_space_group['user']['uid']
        # for dbg 
        #~ print parking_space_group['user']['real_name']
        #~ continue
        
        try:
            friend = parking_space_group['user'];
            for parking_space in parking_space_group['parking']:
                park_uid = uid
                parkid = parking_space['parkid']
                park_uname = friend['real_name']
                neighbor = friend['neighbor']
                first_fee_parking = 0 #friend['first_fee_parking'] # absent in car struct
                while 1:
                    print '___________________________________________________________________________'
                    print 'Got a parking space owned by', park_uname
                    car = getNextToPark(cars, park_uid)
                    #~ return total_money
                    if not car:
                        print 'No more cars to park.'
                        if not retried:
                            retried = 1
                            print 'no cars to park to', park_uname, '. Try another friend\'s parking space to see if any car parked at', park_uname, 'can be repacked.'
                            raise Exception('')
                        return total_money
                    print 'Try to park', car['car_name'], '...'
                    time.sleep(7)
                    ret = parkCar(cookies, car['carid'], first_fee_parking, neighbor, park_uid, parkid, verify, acc)
                    if ret['errno'] == 0:
                        print '  car', car['car_name'], 'from', car['park_real_name'], 'to', park_uname, 'got', car['park_profit'], 'RMB'
                        total_money += car['park_profit']
                        parkid = car['parkid']
                        park_uid = car['park_uid']
                        neighbor = car['neighbor']
                        park_uname = car['park_real_name']
                        cars.remove(car)
                        
                        # the car parked just now is not parked before, need to get a new park space
                        if not parkid:
                            break
                    else:
                        if ret['errno'] == 6:
                            print 'cannot park a car to the same person\'s parking space. try another one..'
                            raise Exception('')
                        else:
                            print '  car', car['car_name'], 'from', car['park_real_name'], car['park_uid'], car['parkid'], 'to', park_uname, park_uid, parkid, 'error:', ret['error']
                            #cars.remove(car);
                            return total_money
        except Exception, e:
            pass
    print 'No more parking spaces..done.'
    return total_money

