/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor
 */

// demarcate.cpp : 定义控制台应用程序的入口点。
//

#include "demarcate.h"
#include <stdio.h>

void printf_mat(Mat & image)
{
	Mat cramera = image.clone();
	for (int i = 0; i < cramera.rows; i++)
	{
		float* pixrow = cramera.ptr<float>(i);
		for (int j = 0; j < cramera.cols; j++)
		{
		//	cout << " " << pixrow[j];
			printf(" %.2f  ", pixrow[j] ) ;

		}
	}
	cout << endl;
}
void main_temarcate()
{ 
//	ifstream fin("calibdata.txt"); /* 标定所用图像文件的路径 */
	//ofstream fout("caliberation_result.txt");  /* 保存标定结果的文件 */
											   //读取每一幅图像，从中提取出角点，然后对角点进行亚像素精确化   
	cout << "开始提取角点………………";
	int image_count = 0;  /* 图像数量 */
	Size image_size;  /* 图像的尺寸 */
	Size board_size = Size(4, 6);    /* 标定板上每行、列的角点数 */
	vector<Point2f> image_points_buf;  /* 缓存每幅图像上检测到的角点 */
	vector<vector<Point2f> > image_points_seq ; /* 保存检测到的所有角点 */
	string filename;
	int count = 0;//用于存储角点个数。  
//	while (getline(fin, filename))
	{
		image_count++;
		// 用于观察检验输出  
		cout << "image_count = " << image_count << endl;
		/* 输出检验*/
		cout << "-->count = " << count * 24 << endl;
		Mat imageInput = imread(filename);
		if (image_count == 1)  //读入第一张图片时获取图像宽高信息  
		{
			image_size.width = imageInput.cols;
			image_size.height = imageInput.rows;
			cout << "image_size.width = " << image_size.width << endl;
			cout << "image_size.height = " << image_size.height << endl;
		}

		/* 提取角点 */
		if (0 == findChessboardCorners(imageInput, board_size, image_points_buf))
		{
			cout << "can not find chessboard corners!\n"; //找不到角点  
		//	exit(1);

		}
		else
		{
			Mat view_gray;
			cvtColor(imageInput, view_gray, CV_RGB2GRAY);
			/* 亚像素精确化 */
			find4QuadCornerSubpix(view_gray, image_points_buf, Size(5, 5)); //对粗提取的角点进行精确化  
																			//cornerSubPix(view_gray,image_points_buf,Size(5,5),Size(-1,-1),TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1));  
			image_points_seq.push_back(image_points_buf);  //保存亚像素角点  
														   /* 在图像上显示角点位置 */
			drawChessboardCorners(view_gray, board_size, image_points_buf, false); //用于在图片中标记角点  
			imshow("Camera Calibration", view_gray);//显示图片  
			waitKey(500);//暂停0.5S    
			count++;
		}
	}
	int total = image_points_seq.size();
	cout << "total = " << total << endl;
	int CornerNum = board_size.width*board_size.height;  //每张图片上总的角点数  
	for (int ii = 0; ii < total;ii++)
	{
		if (0 == ii%CornerNum)// 24 是每幅图片的角点个数。此判断语句是为了输出 图片号，便于控制台观看   
		{
			int i = -1;
			i = ii / CornerNum;
			int j = i + 1;
			cout << "--> 第 " << j << "图片的数据 --> : " << endl;
		}
		if (0 == ii % 3)  // 此判断语句，格式化输出，便于控制台查看  
		{
			cout << endl;
		}
		else
		{
			cout.width(10);
		}
		//输出所有的角点  
		for (int j = 0; j < 24;j++)
		{
			cout << " x-->" << image_points_seq[ii][j].x;
			cout << " y-->" << image_points_seq[ii][j].y;
		}
		cout << endl;
	}
	cout << "角点提取完成！\n";

	//以下是摄像机标定  
	cout << "开始标定………………";
	/*棋盘三维信息*/
	Size square_size = Size(28, 28);  /* 实际测量得到的标定板上每个棋盘格的大小 */
	vector<vector<Point3f> > object_points; /* 保存标定板上角点的三维坐标 */
										   /*内外参数*/
	Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 摄像机内参数矩阵 */
	vector<int> point_counts;  // 每幅图像中角点的数量  
	Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0)); /* 摄像机的5个畸变系数：k1,k2,p1,p2,k3 */
	vector<Mat> tvecsMat;  /* 每幅图像的旋转向量 */
	vector<Mat> rvecsMat; /* 每幅图像的平移向量 */
						  /* 初始化标定板上角点的三维坐标 */
	//int i, j, t;
	for (int t = 0;t < count;t++)
	{
		//image_count
		vector<Point3f> tempPointSet;
		for (int i = 0;i < board_size.height;i++)
		{
			for (int j = 0;j < board_size.width;j++)
			{
				Point3f realPoint;
				/* 假设标定板放在世界坐标系中z=0的平面上 */
				realPoint.x = i*square_size.width;
				realPoint.y = j*square_size.height;
				realPoint.z = 0;
				tempPointSet.push_back(realPoint);
			}
		}
		vector<Point3f>::iterator iter;
		for (iter = tempPointSet.begin();iter != tempPointSet.end(); iter++)
		{
			cout  << "x: " << (*iter).x << "  y:" << (*iter).y << "  z:" << (*iter).z;

		}
		cout << endl;


		object_points.push_back(tempPointSet);

	}
	/* 初始化每幅图像中的角点数量，假定每幅图像中都可以看到完整的标定板 */
	for (int i = 0;i < count;i++)
	{
		//count
		point_counts.push_back(board_size.width*board_size.height);
	}

	/* 开始标定 */
	calibrateCamera(object_points, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, 0);
	std::cout << "nima de bu " << endl;
std::cout << "标定完成！\n";


	//对标定结果进行评价  
	cout << "开始评价标定结果………………\n";
	double total_err = 0.0; /* 所有图像的平均误差的总和 */
	double err = 0.0; /* 每幅图像的平均误差 */
	vector<Point2f> image_points2; /* 保存重新计算得到的投影点 */
	cout << "\t每幅图像的标定误差：\n";
	cout << "每幅图像的标定误差：\n";
	for (int i = 0;i<count;i++)
	{
		//count
		vector<Point3f> tempPointSet = object_points[i];
		/* 通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点 */
		projectPoints(tempPointSet, rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, image_points2);
		/* 计算新的投影点和旧的投影点之间的误差*/
		vector<Point2f> tempImagePoint = image_points_seq[i];
		Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2);
		Mat image_points2Mat = Mat(1, image_points2.size(), CV_32FC2);
		for (int j = 0; j < tempImagePoint.size(); j++)
		{
			image_points2Mat.at<Vec2f>(0, j) = Vec2f(image_points2[j].x, image_points2[j].y);
			tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
		}
		err = norm(image_points2Mat, tempImagePointMat, NORM_L2);
		total_err += err /= point_counts[i];
		std::cout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
		cout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
	}
	cout << "总体平均误差：" << total_err / count << "像素" << endl;
	cout << "总体平均误差：" << total_err / count << "像素" << endl << endl;
	cout << "评价完成！" << endl;
	//保存定标结果      
	cout << "开始保存定标结果………………" << endl;
	Mat rotation_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 保存每幅图像的旋转矩阵 */
	cout << "相机内参数矩阵：" << endl;
//	Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 摄像机内参数矩阵 */
	printf_mat(cameraMatrix);
#if 0
	for (int i = 0; i < cameraMatrix.rows; i++)
	{
		float* pixrow = cameraMatrix.ptr<float>(i);
		for (int j = 0; j < cameraMatrix.cols; j++)
		{
			cout << " " << pixrow[j];
	
		}
	}
#endif 
	cout << endl;
	cout << "畸变系数：\n";
	printf_mat(distCoeffs);
#if 0
	for (int i = 0; i < distCoeffs.rows; i++)
	{
		float* pixrow = distCoeffs.ptr<float>(i);
		for (int j = 0; j < distCoeffs.cols; j++)
		{
			cout << " " << pixrow[j];

		}
	}
#endif 
	cout << endl;
	//cout << distCoeffs << endl << endl << endl;
	for (int i = 0; i<count; i++)
	{
		//count
		cout << "第" << i + 1 << "幅图像的旋转向量：" << endl;
		printf_mat(tvecsMat[i]);
	//	cout << tvecsMat[i] << endl;
		/* 将旋转向量转换为相对应的旋转矩阵 */
		Rodrigues(tvecsMat[i], rotation_matrix);
		cout << "第" << i + 1 << "幅图像的旋转矩阵：" << endl;
		printf_mat(rotation_matrix);
	//	cout << rotation_matrix << endl;
		cout << "第" << i + 1 << "幅图像的平移向量：" << endl;
		printf_mat(rvecsMat[i]);
	//	cout << rvecsMat[i] << endl << endl;
	}
	cout << "完成保存" << endl;
	cout << endl;



//	显示定标结果

	Mat mapx = Mat(image_size, CV_32FC1);
	Mat mapy = Mat(image_size, CV_32FC1);
	Mat R = Mat::eye(3, 3, CV_32F);
	cout << "保存矫正图像" << endl;
	string imageFileName;
	std::stringstream StrStm;
	for (int i = 0; i != count; i++)
	{
		std::cout << "Frame #" << i + 1 << "..." << endl;
		initUndistortRectifyMap(cameraMatrix, distCoeffs, R, cameraMatrix, image_size, CV_32FC1, mapx, mapy);
		StrStm.clear();
		imageFileName.clear();
		string filePath = "chess";
		StrStm << i + 1;
		StrStm >> imageFileName;
		filePath += imageFileName;
		filePath += ".bmp";
		Mat imageSource = imread(filePath);
		Mat newimage = imageSource.clone();
		//另一种不需要转换矩阵的方式  
		//undistort(imageSource,newimage,cameraMatrix,distCoeffs);  
		remap(imageSource, newimage, mapx, mapy, INTER_LINEAR);
		StrStm.clear();
		filePath.clear();
		StrStm << i + 1;
		StrStm >> imageFileName;
		imageFileName += "_d.jpg";
		imwrite(imageFileName, newimage);
	}

	std::cout << "保存结束" << endl;
	return;
}

