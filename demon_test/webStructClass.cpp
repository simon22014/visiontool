/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "webStructClass.h"

WebStrucetCLASS::WebStrucetCLASS()
{  
 }
WebStrucetCLASS::WebStrucetCLASS(shStorage*getAndWebShare)
   :getAndWebShare(getAndWebShare)
{  
    strcpy(rgbData_mode,getAndWebShare->rgbData_mode);
   strcpy(rgbData_test,getAndWebShare->rgbData_test);
     int width = 656;
     int height = 492;
     Mat Mat_template(height,width, CV_8UC3);
     Mat Mat_test(height,width, CV_8UC3);
     Mat_Image_template = Mat_template.clone();
     Mat_Image_test = Mat_test.clone();     
}
WebStrucetCLASS:: ~WebStrucetCLASS()
{
    
}
Mat WebStrucetCLASS::carveImageTemplate()
{
    Mat image = Mat_Image_template.clone();
    Mat craveMat((getAndWebShare->x2 - getAndWebShare->x1),(getAndWebShare->y2 - getAndWebShare->y1),
    Mat_Image_template.type());
    Mat_Image_template(Rect(getAndWebShare->x1,getAndWebShare->y1,
            (getAndWebShare->x2 - getAndWebShare->x1),(getAndWebShare->y2 - getAndWebShare->y1)))
            .copyTo(craveMat);
//   imshow("crave",craveMat);
 // waitKey(0);
    return    craveMat; 


}
    Mat  WebStrucetCLASS:: readRgbDataMode()
    {
         Mat image =  GetImage(Mat_Image_template, rgbData_mode);
       Mat_Image_template = image.clone();
      Point  Point1;
      Point  Point2;
       Point1.x = getAndWebShare->x1;
       Point1.y = getAndWebShare->y1;
       Point2.x = getAndWebShare->x2;
       Point2.y = getAndWebShare->y2;
      circle(Mat_Image_template,Point1,3,Scalar(255,255,0),1);
       circle(Mat_Image_template,Point2,3,Scalar(255,255,0),1);
   //    imshow("Mat_Image_template",Mat_Image_template);
   //    waitKey(0);
       
                return Mat_Image_template;

        
    }
    Mat WebStrucetCLASS::readRgbDataTest()
    {
       Mat image =  GetImage(Mat_Image_test, rgbData_test);
       Mat_Image_test = image.clone();
       
       
       ChangeMatChar(Mat_Image_test);
       
               
      //    imshow("Mat_Image_test",Mat_Image_test);
     //   waitKey(0);
     //   return Mat_Image_test;
 
    }
void  WebStrucetCLASS:: getRGBInNum(int *RGBInNum,int row,int cols)
{
    *(RGBInNum+0)   = changeNumber[row][cols][0];
     *(RGBInNum+1) =  changeNumber[row][cols][1];
     *(RGBInNum+2) =  changeNumber[row][cols][2];

}
 void WebStrucetCLASS::change16To10( char* capBuf)
  {
  int num1,num2;
    char *  capBUF = capBuf;
    for(int i = 0 ; i < capHeight;i++)//capHeight
    {
        for(int k = 0 ; k < capWidth ;k++)
        {
        for (int j = 0; j <3 ; j++)
        {
#if 0
            char H=*(capBuf+(k* capWidth+i)*3*2 + 0);
            char  L=*(capBuf+(k* capWidth+i)*3*2 + 1);
            num1=getV10(H);
            num2=getV10(L);
            changeNumber[i][k][j]=num1*16 + num2;
#endif          
             char c1 = *(capBUF++ );  
            if( c1 > '9')
                num1 = c1 - 87;
            else 
                num1 = c1 - '0';
            if( *capBUF> '9')
                num2 = *capBUF - 87;
            else 
                num2 = *capBUF - '0';  
             capBUF++ ;
             changeNumber[i][k][j]  = num1*16 + num2;
        } 
        }
    }
  }
 void WebStrucetCLASS::ChangeMatChar(Mat & image)
 {
     
 Mat BRGMat = image.clone();
     cvtColor(BRGMat,BRGMat,CV_BGR2RGB);
     if(!BRGMat.isContinuous())
     {
         cout << "the image is not continus"<<endl;
         return;
     }
    int theALL = BRGMat.cols  * BRGMat.rows * BRGMat.channels();
    char *capBuf  = new char[theALL * 2];
   unsigned char *data  =  new unsigned char[theALL +1];
   unsigned  char *data_first = data;
     for(int i = 0 ;i < BRGMat.rows;i++)
                    {
                          for(int j = 0; j <BRGMat.cols ; j++)
                          {
                           *(data_first++) = (BRGMat.at<Vec3b>(i,j)[0]);
                              *(data_first++) = (BRGMat.at<Vec3b>(i,j)[1]);
                              *(data_first++) = (BRGMat.at<Vec3b>(i,j)[2]);
                          }
                    }
         for(int i=0;i<BRGMat.rows*BRGMat.cols*3;i++){
                 int kH=i*2;
                 int kL=kH+1;
                 unsigned char uc=*(data+ i);
                 int c=uc;
                 int a=c%16;
                 char cL=getCharByNum(a);
                 c/=16;
                 a=c%16;
                 char cH=getCharByNum(a);
                 *(capBuf+ kH)=cH;
                 *(capBuf+ kL)=cL;
         }
        memcpy(getAndWebShare->rgbData_test,capBuf,strlen(capBuf) +1);
        getAndWebShare->status = 10;
        getAndWebShare->code = 3;
   
  //       char *CAPBuf = theClass->GetBuf();
   //      CAPBuf= capBuf;
 //         Mat testImage = theClass->CchangeShareMat(theWebData->rgbData_test);
          
          
   //      imshow("TESTiMjkAGE",testImage);
   //       waitKey(0);
 }
 char WebStrucetCLASS::getCharByNum(int num){
     char c='0';
     if(num<=9){
         return c+num;
     }
     c='a'+num-10;
     if(c>'z')c='?';
     return c;
 }

 Mat  WebStrucetCLASS::GetImage(Mat & image, char * rgbData_mode)
 {
     
             //     int  changeNumberCap[capWidth*capHeight][3];
  //            int** changeNumber = &changeNumberCap;
                  change16To10(rgbData_mode);
	/////////
	int nr = image.rows; int W = nr;
	int nc = image.cols; int H = nc;
	int channel = image.channels();	if (channel != 3) return (Mat){'0','0','0'};

	for (int j = 0; j < nr; j++) {
		char* da = image.ptr<char>(j);
		for (int i = 0; i<nc; i++) {
			int addb = i; addb *= 3;
                                                       int RGBInNum[3]= {0};
			char* pu = da + addb;                                                  
                                                       getRGBInNum(RGBInNum, j, i);     
				*(pu + 0) = RGBInNum[2];
				*(pu + 1) = RGBInNum[1];
				*(pu + 2) = RGBInNum[0];
   
		}
	}
        return image;
 }