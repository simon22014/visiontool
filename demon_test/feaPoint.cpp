/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "feaPoint.h"
#include "theClass.h" 
#include "man.h"
Mat  feaPointChangeRay(Mat & image)
{
      Mat image_clone;
 //    changeRay *imageGry = new changeRay(true,image);
    std::auto_ptr<changeRay> imageGry ( new changeRay(true,image));
     imageGry->printNum();
    imshow("imageRag",imageGry->getImageRag());
   waitKey(0);
     image_clone = (imageGry->getImageRag()).clone();
 
     return image_clone;
}
void   feaPointdimDealWitch(Mat &image)
{
  //      dimDealWitch *dimDeal = new dimDealWitch(image);
       std::auto_ptr<dimDealWitch> dimDeal ( new dimDealWitch(image));
        dimDeal->dimDealWithType();
  //    imshow("dimdealwitch",image);

}
Mat feaPointArithmetic(Mat &image)
{
//feaPointAri*feaPointA = new feaPointAri(image);
      std::auto_ptr<feaPointAri> feaPointA ( new feaPointAri(image));
feaPointA ->showFeaPoint();


return (feaPointA->getTheMat());

}
void peinFeaPointMat(Mat & image)
{
    Mat image_m = image.clone();
    int channel = image_m.channels();
    if(channel == 3)
    {
    for(int i = 0 ;i < image_m.rows;i++)        
    {
        Vec3b* pixrow = image_m.ptr<Vec3b>(i);
          for(int j = 0;j < image.cols;j++)
          {
            cout<<"R:"<<pixrow[j][0];
            cout<<"G:"<<pixrow[j][1];
            cout<<"B:"<<pixrow[j][2];   
          }
    }
    }
    else if (channel == 1)
    {
       for(int i = 0 ;i < image_m.rows;i++)        
    {
        float* pixrow = image_m.ptr<float>(i);
          for(int j = 0;j < image.cols;j++)
          {
             cout<<"pixel"<<pixrow[j];
          }
    }
    }
    else 
    {
              cout << "the channel is wrrory";
    }
 
}

void feaPointMatching()
{
  //    feaPointAri* feaPoint = new feaPointAri();
      std::auto_ptr<feaPointAri> feaPoint ( new feaPointAri());
      feaPoint->templateMatchingChoiceWay();
    if (SaveMatIntToVector.size()  < 2)
    {
        cout << "the image size is less than 2,so you can't matching "<< endl;
        return ;
    }
      feaPoint->showTheMatchingWay();
      feaPoint ->printNum(); 
      return ;
}