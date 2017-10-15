/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "template.h"
#include "templateMatching.h"
void templateMating()
{
 //   templateMatching* temMat = new templateMatching();
    std::auto_ptr<templateMatching> temMat ( new templateMatching());
    if (SaveMatIntToVector.size()  < 2)
    {
        cout << "the image size is less than 2,so you can't matching "<< endl;
        return ;
    }
    temMat->templateMatchingChoiceWay();

    temMat->choiceMatching(); 

   temMat->printMatchingPoint(); 
  //  waitKey(0);
    return;
}