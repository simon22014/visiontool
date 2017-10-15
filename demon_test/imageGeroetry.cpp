/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include"imageGeroetry.h"
#include"imageFindLine.h"
#include"GeroetryMouse.h"

 void imageGeroetry(Mat& image_m)
 {
     Mat srcImage1;
     srcImage1= image_m.clone();
   //   imshow("image",srcImage1);  
      int theChoice;
      cout<< "0,line find,1,connre find"<<endl;
      cin >> theChoice;
   
      switch(theChoice)
      {
          case FINDLINE:
              findLineFun(srcImage1);
              cout<< "wq"<<endl;
              break;
          case FINDRECTANGLE:
              findCornerFun(srcImage1);
              break;
          default:
              break;
              
              
      
      }
      
 }     
      
    
#if 0
void MouseEvent(int event, int x, int y, int flags, void* data)
{
    Mat image = srcImage1.clone();
	if (event == EVENT_LBUTTONDOWN)
	{
		downFlag = true;
		startPoint.x = x;
		startPoint.y = y;     
                 circle(image,startPoint,3,Scalar(255,255,0),1); 
	} 
	if (event == EVENT_LBUTTONUP)
            
	{
		upFlag = true;
		endPoint.x = x;
		endPoint.y = y;      
                circle(image,endPoint,3,Scalar(255,255,0),1); 
	}
        if (downFlag == true && upFlag == true)
	{
              rectangle(image,startPoint,endPoint,Scalar(0,0,255),3,8,0);
                downFlag = false;
	upFlag = false;        
	}       
        imshow("image",image);
        waitKey(0);
}
#endif 