#ifndef KBBS_H
#define KBBS_H

#include "kmatchcore.h"

#include <vector>

class KBBS :public KMatchCore
{
public:
    KBBS(int = 3);
    virtual ~KBBS(){}
    void calc_spatial_distance();
    void show_keypoint();
    void do_prepare(cv::Mat inputImg, cv::Mat inputTem){
        int temp_size = (inputTem.rows / m_iPatchSize)*(inputTem.cols / m_iPatchSize);
        m_vecResBuff.clear();
        m_vecResBuff.resize((inputImg.cols -inputTem.cols) / m_iPatchSize, cv::Mat(temp_size, temp_size, CV_MAKETYPE(CV_32F, 1)));
        m_matSpatialDis.create(temp_size, temp_size, CV_MAKETYPE(CV_32F, 1));
        m_iStep = inputImg.cols / m_iPatchSize;
        calc_spatial_distance();
    }
    float do_single_match(cv::Mat, cv::Mat, int, int);
    int get_cur_patchsize(){ return m_iPatchSize; }
private:
    int m_iPatchSize;
    int m_iStep;
    int m_iNowCol;
    std::vector<cv::Mat> m_vecResBuff;
    cv::Mat m_matSpatialDis;
    cv::Point get_bbp(cv::Mat, cv::Mat, cv::Mat, int, int);
    void calc_colordis(cv::Vec3b, int, int);
};

#endif // KBBS_H
