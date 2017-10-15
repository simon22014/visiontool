/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include"marginFunctor.h"
#include"marginFunctorClass.h"
#include "marginGeometryClass.h"
#include"marginShapeClass.h"
void imageMarginFunctor(Mat image_m)
{
    Mat image = image_m.clone();
    if(!image.data)
    {
        cout<< "the image have not data"<<endl;
        return ;
    }
     int choiceNum;
    cout << "0:the image margin functor,1:margin geomrtry,2:margin shape "<<endl;
    cin >> choiceNum;
    switch(choiceNum)
    {
        case  MARGINFUNCTOR:
        {
              //    marginFunctorClass * margin  = new marginFunctorClass(image_m);
               std::auto_ptr<marginFunctorClass> margin ( new marginFunctorClass(image_m));
                     margin ->marginChoice();
        }
        break;
        case MARGINGEOMETRY:
        {
  //          marginGeometryClass * marginGeometry = new marginGeometryClass(image_m);
        std::auto_ptr<marginGeometryClass> marginGeometry ( new marginGeometryClass(image_m));
        marginGeometry->marginGeomrtryType();
 //           cout << "qw"<<endl;
        }
        case MARGINSHAPE:
        {
         std::auto_ptr<marginShapeClass> marginShape ( new marginShapeClass(image_m));
         marginShape->marginShapeType();
        }
        break;
        default:
            break;
    
    }
  
 //  margin-> marginPrewittFun();

  
}
