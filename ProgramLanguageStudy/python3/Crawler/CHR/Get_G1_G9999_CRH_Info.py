#coding=utf-8

import sys
import random
import urllib
import re
import time

from urllib import request
from bs4 import BeautifulSoup

g_AllTrainMsg = []              #存储所有车次的列表，列表中存放为字典

def GetTrainMsg(TrainNumber):
    '''根据车次号，通过携程网页将车次的详细界面信息获取'''
    url = "http://trains.ctrip.com/TrainSchedule/"+TrainNumber+"/"

    headers1 = {'User-Agent':'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) '
                                       'Chrome/51.0.2704.63 Safari/537.36'}
    headers2 = {'User-Agent':'Mozilla/5.0 (Windows NT 6.2; rv:16.0) Gecko/20100101 Firefox/16.0',
         'Accept':'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8'}

    i = (random.randint(0,9))%2
#    print("i=%d"%i)
    if i:
        headers = headers1
    else:
        headers = headers2

    request1 = urllib.request.Request(url = url, headers = headers)
    response1 = urllib.request.urlopen(request1)

    if response1.getcode() == 200:#判断请求是否成功
#        print("http return Correct")
        data = response1.read()
#        print(data.decode('gbk'))
        return data.decode('gbk')
    else:
#        print("http return Error")
        return


def CheckVaildData(WebTrainMsg, TrainNumber):
    '''判断获取的列车信息中是否是有效数据'''
    EffectiveMsg = "ctl00_MainContentPlaceHolder_pnlResult"
    if EffectiveMsg in WebTrainMsg:
#        print("查询到%s车次的信息..."%TrainNumber.title())
        return True
    else:
#        print("未查询到%s车次的信息..."%TrainNumber.title())
        return False

def GetTrainStartEnd(WebTrainMsg):
    '''通过正则表达式来获取到车次的出发地和到达地'''
    Departure_key = '<a\s*id="ctl00_MainContentPlaceHolder_hyDepartureStationName".*\s*">([^<]*)<'
    Arrival_key = '<a\s*id="ctl00_MainContentPlaceHolder_hyArrivalStationName".*\s*">([^<]*)<'

    Departure = re.search(Departure_key, WebTrainMsg)
    Arrival = re.search(Arrival_key, WebTrainMsg)

    if Departure[1] != "" and Arrival[1] != "":
        print("出发地:%-10s\t到达地:%-10s" %(Departure[1], Arrival[1]))

def GetDetailMsgOfTrain(WebTrainMsg, TrainNumber):
    '''通过BeautifulSoup获取车次的详细信息，包括起终点，发车时间，到达时间，花费时长'''
    DetailMsg = {}
    DetailMsg["车次"] = TrainNumber.title()
    soup = BeautifulSoup(WebTrainMsg, 'lxml')

#    print(soup.title)
#    print(soup.head)
    Departure = soup.find(id="ctl00_MainContentPlaceHolder_hyDepartureStationName").get_text()
    Arrival = soup.find(id="ctl00_MainContentPlaceHolder_hyArrivalStationName").get_text()
    print("DEPARTURE:%-15s\t ARRIVAL:%-15s" %(Departure, Arrival))

'''
#测试程序
#Train = input("请输入列车车次:")
Train = "G2"
TrainMessage = GetTrainMsg(Train)
#CheckVaildData(TrainMessage, Train)
#GetTrainStartEnd(TrainMessage)
GetDetailMsgOfTrain(TrainMessage, Train)

'''
for i in range(1,9999):
#    time.sleep(1)
    Train = "G" + str(i)
    TrainMessage = GetTrainMsg(Train)
    if TrainMessage is None:
        continue
    value = CheckVaildData(TrainMessage, Train)
    if value:
        print("车次:%-10s\t" %Train ,end = '')
#        GetTrainStartEnd(TrainMessage)
        GetDetailMsgOfTrain(TrainMessage, Train)
        sys.stdout.flush()

