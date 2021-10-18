import sys
import struct
from scapy.all import *

'''
伪造一个数据包,并且通过scapy库中的函数发送
struct.pack这没怎么看懂
'''
data = struct.pack('6s', b'Voyage')
pkt = IP(src='192.168.10.66', dst='192.168.10.77')/TCP(sport=12345, dport=6666)/data
send(pkt, inter=0.1, count=100)
