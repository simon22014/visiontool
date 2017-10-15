/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include"histImage.h"
#include"histImageClass.h"
#include"histImageOperate.h"
void imageHist(Mat &image)
{
      cout << "welcome to hist image" <<endl;
      Mat beforeImage = image.clone();
      if(!beforeImage.data)
      {
          cout << "the image data is wrong"<<endl;
          return;
      }
   //  histImageClass * hist = new histImageClass(beforeImage);
       std::auto_ptr<histImageClass> hist ( new histImageClass(beforeImage));
     hist->histImageType();
      
   //  histImageOperate * histOperate = new histImageOperate(beforeImage);
 //     std::auto_ptr<histImageOperate> histOperate ( new histImageOperate(beforeImage));
//      histOperate->histImageOperateType();
      
       
}
  
