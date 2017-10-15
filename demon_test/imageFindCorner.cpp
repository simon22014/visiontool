/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include"GeroetryMouse.h"
#include"imageFindCornerClass.h"
#include"imageGeroetry.h"
void findCornerFun(Mat & srcImage1)
{
    cout << "23"<<endl;
    vector<Vec4f> linescorner;
    Mat image = srcImage1.clone();
    if(!image.data)
    {
        cout << "the image data is wrong" <<endl;
        return;
    }
  //  GeroetryMouse *gerMouse = new  GeroetryMouse(image);
     std::auto_ptr<GeroetryMouse> gerMouse ( new GeroetryMouse(image));
     gerMouse->CornerGetPoint();
      linescorner =  gerMouse->getLinesCorner();

      cout <<"12"<<endl;
  //    imageFindCornerClass* findCorner = new imageFindCornerClass(linescorner,image);
         std::auto_ptr<imageFindCornerClass> findCorner ( new imageFindCornerClass(linescorner,image));
      findCorner->FindLine();
      findCorner->printTwoLine();
      findCorner->showCornerAngle();
  

}
