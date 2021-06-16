#include <iostream>
#include "opencv2/opencv.hpp"
#include <cmath>
#include <string>

using namespace std;
using namespace cv;

int main()
{
    string input = "c";
    while(input != "q")
    {
        string imageNum;
        cout << "����ͼƬ���: ";
        cin >> imageNum;
        stringstream  ss;
        ss << "D:\\��־����\\��������־���Ͼ�-RH\\visualized\\" << imageNum << ".visualized.jpg";
        cout << ss.str() << endl;

        Mat srcImage, srcImageRez;
        srcImage = imread(ss.str());
        if (srcImage.empty())
        {
            cout << "��ȡ����" << endl;
            return -1;
        }

        double srcHeight = srcImage.rows;
        double srcWeight = srcImage.cols;
        resize(srcImage, srcImageRez, Size(cvRound(srcWeight) / 4, cvRound(srcHeight) / 4));
        imshow("srcImageRez", srcImageRez);
        waitKey(0);
        cout << "srcHeight:" << srcHeight << endl;
        cout << "srcWeight:" << srcWeight << endl;

        Mat srcImageGray;
        cvtColor(srcImage, srcImageGray, COLOR_BGR2GRAY);

        Mat srcImageGrayExt;
        copyMakeBorder(srcImageGray, srcImageGrayExt, 1, 1, 1, 1, BORDER_REPLICATE);
        double extHeight = srcImageGrayExt.rows;
        double extWeight = srcImageGrayExt.cols;

        /*----��ȡ����Ԫ������----------*/
        //int extType = srcImageGrayExt.type();
        //cout << "type:" << extType << endl;

        cout << "extHeight:" << extHeight << endl;
        cout << "extWeight:" << extWeight << endl;


        double pingFangHe = 0.0;
        double duiBiDu;

/*----------------ֱ�ӷ���ÿ�����ص�ֵ����Աȶ�--------------*/
//       for (int i = 1; i < extHeight - 1; i++)
//        {
//            for (int j = 1; j < extWeight - 1; j++)
//            {
//                double left = pow(saturate_cast<int>(srcImageGrayExt.at<uchar>(i, j)) - saturate_cast<int>(srcImageGrayExt.at<uchar>(i, j - 1)), 2);
//                double right = pow(saturate_cast<int>(srcImageGrayExt.at<uchar>(i, j)) - saturate_cast<int>(srcImageGrayExt.at<uchar>(i, j + 1)), 2);
//                double down = pow(saturate_cast<int>(srcImageGrayExt.at<uchar>(i, j)) - saturate_cast<int>(srcImageGrayExt.at<uchar>(i - 1, j)), 2);
//                double top = pow(saturate_cast<int>(srcImageGrayExt.at<uchar>(i, j)) - saturate_cast<int>(srcImageGrayExt.at<uchar>(i + 1, j)), 2);
//                pingFangHe += left + right + down + top;
//            }
//        }

/*-------------------ʹ��ָ�뷨����Աȶ�------------------*/
       for (int i = 1; i < extHeight - 1; i++)
        {
            auto* dataTop = srcImageGrayExt.ptr<uchar>(i - 1);
            auto* dataDown = srcImageGrayExt.ptr<uchar>(i + 1);
            auto* data = srcImageGrayExt.ptr<uchar>(i);

            for (int j = 1; j < extWeight - 1; j++)
            {
                double left = pow(saturate_cast<int>(data[j]) - saturate_cast<int>(data[j - 1]), 2);
                double right = pow(saturate_cast<int>(data[j]) - saturate_cast<int>(data[j + 1]), 2);
                double down = pow(saturate_cast<int>(data[j]) - saturate_cast<int>(dataDown[j]), 2);
                double top = pow(saturate_cast<int>(data[j]) - saturate_cast<int>(dataTop[j]), 2);
                pingFangHe += left + right + down + top;
            }
        }

        duiBiDu = pingFangHe / (4 * (srcHeight - 2) * (srcWeight - 2) + 2 * (srcHeight - 2) * 3 +
                                2 * (srcWeight - 2) * 3 + 4 * 2);
        cout << "�Աȶȣ�" << duiBiDu << endl;

        cout <<"����q������������������: ";
        cin >> input;

    }
    return 0;
}
