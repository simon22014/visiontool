/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dataStruct.h
 * Author: aqq
 *
 * Created on 2017年4月18日, 上午10:24
 */

#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
enum enum_order{
    GETTHEIMAGE,// get the image 0 template 
    GETTHEIMAGERAG ,//change rag the image1
    DIMDEALWITCH,//dim the image 2 
    FEAPOINTALG,   //find the point 3
    SAVELATERUSE,//save it     4
    FEAPOINTMATCHING,  //matching 5
    TEMPLATEMATCHING,  //template Matching6
    IMAGEDEAL_WITH,  //deal with image 7
    TESTIMAGE, //get test image 8
    IMAGE_GEROETRY,//geroerry9
    IMAGEMARGINFUNCTOR, //10
    IMAGEHIST, //11hist
    IMAGESMOOTHNESS, 
    IMAGECHANGEGRAY, //change image gray
    IMAGECORNERDETECTION, // image corner test
    QUIT,//quit the routine 15
};
   enum enum_template_Matching{
        SQDIFF,
        SQDIFFNORMED,
        TMCCORR,
        TMCCORRNORMED,
        TMCOEFF,
        TMCOEFFNORMED,    
};
enum enum_who_tem_test{
    ZERO_ONE,
    ONE_TEST,
};



 
enum enum_status {
	status_1_nothing, //闲
	status_2_work,//待处理
	status_3_busy, //忙
	status_4_done, //完成
	status_5_error, //出错
};
typedef struct showStorage
{
	int code; //web发出的指令
	int x1;  //x1,y1, x2,y2, 模板的左上与右下两点坐标
	int y1;
	int x2;
	int y2;
	char rgbData_mode[capSize]; //模板rgb数据   
	char rgbData_test[capSize]; //待测试rgb数据
	int status;  //运行状态
	char error[300]; //出错原因描述
	int score;  //得分,反映识别结果令人满意的程度
	int x;  //识别到的x坐标
	int y;  //识别到的y坐标
       //         int order[6];
}shStorage;
/*
web与后台进程的握手过程：
后台进程 启动后，把共享内存struct_shareMem的ID写入文件： /home/aqq/workspace/web/WebContent/jni/cameraMemId/memId.conf
web启动后读取ID，依次写入：struct_shareMem.code 值，同时将struct_shareMem.status赋值为status_2_work
后台检测到status_2_work后，读取struct_shareMem.code进行处理，同时将struct_shareMem.status赋值为status_3_busy
处理完后，设置struct_shareMem.status赋值为status_4_done
如果出错，设置struct_shareMem.status赋值为status_5_error,并将出错原因写入struct_shareMem.error.
web每发送一条指令后，检测struct_shareMem.status，只有当其为status_4_done时才发下一条指令。
///
struct_shareMem.status 初始化为 status_1_nothing
struct_shareMem.code 初始化为 status_1_null

*/


enum enum_code {
	code_1_null,//空
	code_2_getModeRgbData,  //抓图到模板数据里 rgbData_mode 0  
                 code_3_save,   //save
	code_4_getTestRgbData,  //抓图到测试数据里 rgbData_mode
                  code_5_template,//template 
                  code_6_templateArith, //arith       
//	code_5_dsp, //运行识别过程
//	code_6_restart,//重启功能，跳出故障
  //                 code_7_demarcate,  //demarcate the camrea                 
                    //code_3_setRect, //设置模板的位置 x1,y1,x2,y2

};
#endif /* DATASTRUCT_H */

