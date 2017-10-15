# -*- coding: utf - 8 -*-
import sys
import cv2
import numpy as np
import copy
#img = "weq";
img = cv2.imread("/home/aqq/NetBeansProjects/demon_test/png/findLine.png")
rows,cols,channels = img.shape


def open_simon():
    global img,rows,cols,channels
    print rows,cols,channels
    file__Object = open('simon.txt','w+')
    theList = [];
    theAll = cols * rows * channels 
    for i in range(0,cols):
        for j in range(0,rows):
            for k in range(0,channels):
                theList.append(img[j,i,k])
             #   try:
            text = '  '+ str(theList)
            text = text.encode('utf -8')
            file__Object.write(text)
            theList = []
               # finally:
               #     file__Object.close()
    file__Object.close()  
def print_list(t_List):
 #   print  type(t_List[0:50])
  #  print len(t_List[0:50])

 #   for  i in t_List[0:50]:
 #       print i
    b = np.array(t_List[0:200])
   # print b
    cv2.imshow("img",b)
    cv2.waitKey(0)    
def show_image(img):
      print "qwe"
      print     type(img)
      print len(img)
      print img
      print_list(img)
      print "qw"

#list_simon = [12,2,3,4,[1,3,4],"23",[],[2,34,3]]
#show_image(img)
      #file__Object = open('simon.txt','w+')
    #  open_simon(img)
    #  file__Object = open('simon.txt','w+')
   #  print image


#
#image = hello()
#open_simon()



