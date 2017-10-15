/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include"imageSmoothness.h"
#include"imageNoiseClass.h"
void  imageSmoothness(Mat &image_m)
{
    Mat image = image_m.clone();
    if(!image.data)
    {
        cout <<"the image data is wrong"<<endl;
        return;
    }
    cout << "image smoothness.0,image sampling,1:add noise"<<endl;
    int theChoiceNum;
    cin >> theChoiceNum;
    switch(theChoiceNum)
    {
        case IMAGESAMPLING:
        {
     //       imageSamplingClass *imageSamp = new imageSamplingClass(image);
              std::auto_ptr<imageSamplingClass> imageSamp ( new imageSamplingClass(image));
            imageSamp->latelyNextInsertVaule(100,100);
            imageSamp->bothLinearInsertVaule(100,100);
        }
        break;
        case IMAGENOISE:
        {
      //      imageNoiseClass * imageNoise = new imageNoiseClass(image);
                 std::auto_ptr<imageNoiseClass> imageNoise ( new imageNoiseClass(image));
            imageNoise->addSaltNoise(1000,255);
       //     imageNoise->addGaussianNoise();
            cout << "the noise"<<endl;
        }
        break;
            
        default:
            break;
    
    }
    return;
    

}