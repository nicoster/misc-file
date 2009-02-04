
import sys
import getopt
import logging

from curl import login
from common import usage, getUserData, showUserInfo, parking2
from park_algo import getNextToPark

logging.basicConfig(level=logging.DEBUG)
#logging.basicConfig(level=logging.INFO)

def main(argv):
    try:
        opts, args = getopt.getopt(argv, "u:p:htl");
    except getopt.GetoptError:
        usage()
        sys.exit(2)

    opt = dict(opts)

    if opt.has_key('-u') and opt.has_key('-p'):
        user = opt['-u']
        passwd = opt['-p']
    else:
        #print "Error: set your username & password plz"
        #usage()
        #sys.exit(2)
        user='titan5010@163.com'
        passwd='123456'
        
    cookies = login(user, passwd)

    if opt.has_key('-h'):
        usage()
        sys.exit()

    if 1: #opt.has_key('-t') or opt.has_key('-l'):
        data = getUserData(cookies)

        if data == False:
            print "Error: set your username & password plz"
            usage()
            sys.exit(2)
        cars = data['cars']
        user = cars['user']
        #~ print user
        car = cars['car']
        #~ print car
        friends = data['friends']
        verify = data['verify']
        acc = data['acc']
        showUserInfo(user, car)
        
        
        
    if opt.has_key('-t'):
        total_money = parking2(cookies, user, car, friends, verify, acc)
        if total_money:
            print 'Congrats! You got', total_money, 'RMB.'

if __name__ == "__main__":
    main(sys.argv[1:])
