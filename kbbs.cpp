#include "kbbs.h"
#include <tuple>

KBBS::KBBS(int _patch_size) :m_iPatchSize(_patch_size), m_iStep(0), m_iNowCol(0)
{

}

void KBBS::calc_spatial_distance()
{
    // the i_th row in m_matSpatialDis represnt the distance
    // between the i_th patch (row first) and all the other patches
    m_matSpatialDis = cv::Scalar::all(0.);

    for(int iHeight = 0; iHeight < m_matSpatialDis.rows; ++iHeight){
        float * distance = m_matSpatialDis.ptr<float>(iHeight);
        for(int iWidth = 0; iWidth < m_matSpatialDis.cols; ++iWidth){
            distance[iWidth] = std::pow(((iHeight % m_iStep) - (iWidth % m_iStep)), 2.)+std::pow(((iHeight / m_iStep)-(iWidth / m_iStep)), 2.);
        }
    }
}

void KBBS::show_keypoint()
{

}

float KBBS::do_single_match(cv::Mat _imgsrc, cv::Mat _imgtmp, int row, int col)
{
//    if(_imgsrc.size() != _imgtmp.size() || _imgsrc.channels() != _imgtmp.channels()) return 0.f;
//    cv::Mat tempMat(_imgsrc.rows, _imgsrc.cols, CV_MAKETYPE(CV_32F, 1));
//    //cv::absdiff(_imgsrc, _imgtmp, tempMat);
//    int num_bbp = 0;

//    for(int iY = 0; iY < tempMat.rows; ++iY){
//        for(int iX = 0;iX < tempMat.cols; ++iX){
//            cv::Point another_pair = get_bbp(_imgsrc, _imgtmp, tempMat, iY, iX);
//            cv::Point this_pair = get_bbp(_imgsrc, _imgtmp, tempMat, another_pair.y, another_pair.x);
//            if(this_pair == another_pair) ++num_bbp;
//        }
//    }
//    return num_bbp*1.f;
    if(_imgsrc.size() != _imgtmp.size() || _imgsrc.channels() != _imgtmp.channels()) return 0.f;
    cv::Mat tempMat(_imgsrc.rows / m_iPatchSize, _imgsrc.cols / m_iPatchSize, CV_MAKETYPE(CV_32F, 1));
    //cv::absdiff(_imgsrc, _imgtmp, tempMat);
    int num_bbp = 0;
    m_iNowCol = col;
    for(int iY = 0; iY < tempMat.rows; ++iY){
        for(int iX = 0;iX < tempMat.cols; ++iX){
            cv::Point another_pair = get_bbp(_imgsrc, _imgtmp, tempMat, iY, iX);
            cv::Point this_pair = get_bbp(_imgsrc, _imgtmp, tempMat, another_pair.y, another_pair.x);
            if(this_pair == another_pair) ++num_bbp;
        }
    }
    return num_bbp*1.f;
}

cv::Point KBBS::get_bbp(cv::Mat _imgsrc, cv::Mat _imgtmp, cv::Mat tempResult, int iY, int iX)
{
//    for(int iH = 0; iH < tempResult.rows; ++iH){
//        float * data = tempResult.ptr<float>(iH);
//        for(int iW = 0;iW < tempResult.cols; ++iW){
//            data[iW] = (_imgsrc.at<cv::Vec3b>(iY,iX)[0] - _imgtmp.at<cv::Vec3b>(iH,iW)[0]) * (_imgsrc.at<cv::Vec3b>(iY,iX)[0] - _imgtmp.at<cv::Vec3b>(iH,iW)[0])
//                    + (_imgsrc.at<cv::Vec3b>(iY,iX)[1] - _imgtmp.at<cv::Vec3b>(iH,iW)[1]) * (_imgsrc.at<cv::Vec3b>(iY,iX)[1] - _imgtmp.at<cv::Vec3b>(iH,iW)[1])
//                    + (_imgsrc.at<cv::Vec3b>(iY,iX)[2] - _imgtmp.at<cv::Vec3b>(iH,iW)[2]) * (_imgsrc.at<cv::Vec3b>(iY,iX)[2] - _imgtmp.at<cv::Vec3b>(iH,iW)[2])
//                    + 2 * ( (iY - iH)*(iY - iH) * 1.f / (tempResult.rows * tempResult.rows) + (iX - iW)*(iX - iW) * 1.f / (tempResult.cols * tempResult.cols) );
//        }
//    }
//    cv::Point max_pos(0, 0);
//    cv::minMaxLoc(tempResult, nullptr, nullptr, &max_pos , nullptr);
    //    return max_pos;
}

void KBBS::calc_colordis(cv::Vec3b point, cv::Mat _template, int row, int col)
{
    float * distance = m_vecResBuff[m_iNowCol].ptr<float>(row * m_iStep + col);

    for(int iHeight = 0; iHeight < _template.rows; ++iHeight){

        for(int iWidth = 0; iWidth < _template.cols; ++iWidth){
            distance[iHeight*m_iStep + iWidth] = ([]{})(point, _template.at<cv::Vec3b>(iHeight,iWidth));
        }
    }
}

