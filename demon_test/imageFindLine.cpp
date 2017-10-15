/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//#include"imageFindLine.h"
#include"GeroetryMouse.h"
#include"imageFindLineClass.h"
#include"imageGeroetry.h"
void findLineFun(Mat & srcImage1)
{
    Point startPoint;
    Point endPoint;
    Mat image = srcImage1.clone();
    if(!image.data)
    {
        cout << "the image data is wrong" <<endl;
        return;
    }
    
   // namedWindow("image");
    
  //  GeroetryMouse *gerMouse = new  GeroetryMouse(image);
     std::auto_ptr<GeroetryMouse> gerMouse ( new GeroetryMouse(image));
   // imshow("image",image);
   //     waitKey(0);
    gerMouse->LineGetStartEndPoint();
    
    startPoint = gerMouse->getStartPoint();
    endPoint = gerMouse->getEndPoint();
      cout <<"12"<<endl;
      cout<<startPoint <<endPoint<<endl;
     // imageFindLineClass* findLine = new imageFindLineClass(startPoint,endPoint,image);
    std::auto_ptr<imageFindLineClass> findLine ( new imageFindLineClass(startPoint,endPoint,image));
     findLine->imageEnlarge();
     #if 0
      findLine->imageOther();
     findLine->imageSobel();
     findLine->imageMargin();
     findLine->imageGetLine();  
#endif 
      findLine->imageOutLine();

}
