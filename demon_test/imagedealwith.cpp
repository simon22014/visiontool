/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "imagedealwith.h"
 #include"feaPoint.h"
#include "imagedealwithclass.h"
Mat imageThresholdValue(Mat & image_clone)
{
    Mat image = image_clone.clone();
 //   theImageThreasholdValue * theThreasholdImage = new theImageThreasholdValue(image);
std::auto_ptr<theImageThreasholdValue> theThreasholdImage ( new theImageThreasholdValue(image));
    return (theThreasholdImage->getTheChangeMat());
}
Mat ImageColorCoversion(Mat & image_clone)
{
    Mat image = image_clone.clone();
//    theImageColorCoversion * theColorImage = new theImageColorCoversion(image);
 std::auto_ptr<theImageColorCoversion> theColorImage ( new theImageColorCoversion(image));
    return (theColorImage->getTheChangeMat());
}
Mat locationChange_Image(Mat & image_clone)
{
    Mat image = image_clone.clone();
  //  locationChangeClass *location = new locationChangeClass(image);
      std::auto_ptr<locationChangeClass> location ( new locationChangeClass(image));
    location->locationChangeChoice();
    
    return (location->getTheChangeMat());

}
Mat remap_Image(Mat & image_clone)
{
    Mat image = image_clone.clone();
    if(!image.data)
    {
        cout << "the image have not data" << endl;
        return image;
    }
    Mat resultImage(image.size(),image.type());
    Mat xMapImage(image.size(),CV_32FC1);
    Mat yMapImage(image.size(),CV_32FC1);
    
    for(int j = 0 ; j < image.rows ;j++)
    {
        for(int i = 0 ; i < image.cols ; i++)
        {
            xMapImage.at<float>(j,i)  = image.cols  -i;
            yMapImage.at<float>(j,i) = image.rows -j;     
        }
    }
        remap(image,resultImage,xMapImage,yMapImage,
                CV_INTER_LINEAR,BORDER_CONSTANT,
                Scalar(0,0,0));
        imshow("image",image);
        imshow("resultImgae",resultImage);
        waitKey(0);
        return resultImage;

}
Mat  imageDealWith(Mat & image_clone)
{
    Mat operate_image;
    Mat image = image_clone.clone();
    cout <<"the image deal with "<< endl;
    cout <<"0:RayImage,1:remap,2:location,3:Change channels,4:image threashold" <<endl;
    int Dim; cin.clear();
    cin  >>Dim;
    switch (Dim)
    {
        case IMAGE_GRY: //change the image become gry
                operate_image =  feaPointChangeRay( image);
                 break;
         case IMAGE_REMAP: //change the image remap
            operate_image  = remap_Image(image);
                 break;
        case IMAGE_LOCATION_CHANGE://the image location is change
                  operate_image =  locationChange_Image(image);            
                  break;
        case IMAGE_COLOR_COVERSION:
            operate_image = ImageColorCoversion(image);
        case IMAGE_THRESHOLDVALUE:
            operate_image = imageThresholdValue(image);
            break;
        default :
            cout <<"the num is wrong" << endl;
            break;          
    }
    return operate_image;
}
