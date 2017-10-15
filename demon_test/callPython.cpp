/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 #include"callPython.h"
int callPythonTestHello()
{
   Mat image =  imread("/home/aqq/NetBeansProjects/demon_test/png/findLine.png");
  //  int image[0][0][0] = {1,2,4};
 //   int image = 11110;
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/aqq/NetBeansProjects/demon_test/Python/')");
    PyObject* pModule = NULL;
    PyObject* pFunc = NULL;
    PyObject* pArgs = NULL;
    PyObject* pDict;
    PyObject * list;

    pModule = PyImport_ImportModule("helloworld");
    pDict = PyModule_GetDict(pModule);
    pFunc = PyDict_GetItemString(pDict,"show_image");
    //pFunc = PyObject_GetAttrString(pModule,"show_image");
    int theAllLength = image.cols * image.rows ;
  //  cout <<  theAllLength<<endl;
    list = PyList_New(theAllLength) ;
   // vector<int > theAllData;
   // vector<int>::iterator it;
 //   int theAllData = image.cols * image.rows * image.channels()
  //  int theRGBdata[theAllData] = {0};
    int z = 0;
    for(int i = 0 ; i <image.rows; i++)
    {
        for(int j = 0 ; j < image.cols;j++)
        {
            int B  = image.at<Vec3b> (i,j)[0];
            int G =  image.at<Vec3b> (i,j)[1];
            int R = image.at<Vec3b> (i,j)[2];  
          PyList_Append(list,Py_BuildValue("[i,i,i]",B,G,R));  
        //  cout << z++<<endl;
   //      printf("[%d,%d,%d] ",B,G,R);
         // PyList_SetItem(list,(i *  j),Py_BuildValue("[i,i,i]",B,G,R));
        }
    }
   pArgs = PyTuple_New(1);
   PyTuple_SetItem(pArgs,0,list);
   PyEval_CallObject(pFunc,pArgs); 

      if (pModule)
              Py_DECREF(pModule);
       if (pArgs)

              Py_DECREF(pArgs);

       if (pFunc)

              Py_DECREF(pFunc);

       if (pDict)

              Py_DECREF(pDict);

       if (list)

              Py_DECREF(list);
   
    Py_Finalize();
    //cout <<"112"<<endl;
    return 0;
}