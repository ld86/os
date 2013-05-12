#!/usr/bin/python

import sys
import dbus
from subprocess import Popen, PIPE

def usage(argv):
    print("Usage: %s <file> <from jabber> <to jabber>" % argv[0])
    return 1

def get_status(filename):
    p = Popen(["inotifywait", filename], stdout=PIPE, stderr=PIPE)
    result = (p.communicate()[0]).strip()
    if p.returncode != 0:
        return None
    return result

def get_interface():
    try:
        obj = dbus.SessionBus().get_object("im.pidgin.purple.PurpleService" , "/im/pidgin/purple/PurpleObject")
        return dbus.Interface(obj , "im.pidgin.purple.PurpleInterface")
    except Exception, e:
        print(e)
        return None

def send_message(interface, from_jabber_id, to_jabber, message):
    conv_id = interface.PurpleConversationNew(1 , from_jabber_id, to_jabber)
    im = interface.PurpleConvIm(conv_id)
    interface.PurpleConvImSend(im , message)
    interface.PurpleConversationDestroy(conv_id)

def main(argv):
    if len(argv) != 4:
        return usage(argv)

    filename, from_jabber, to_jabber = argv[1:4]

    interface = get_interface()
    if interface is None:
        return 2

    from_jabber_id = interface.PurpleAccountsFind(from_jabber, "prpl-jabber")
    if from_jabber_id is None:
        print("From account not found")
        return 3
    
    while True:
        status = get_status(filename)
        if status is None:
            print("Something wrong")
            return 4
        send_message(interface, from_jabber_id, to_jabber, status)

if __name__ == "__main__":
    main(sys.argv)
