#ifndef KBBS_H
#define KBBS_H

#include "kmatchcore.h"

#include <vector>

class KBBS :public KMatchCore
{
public:
    KBBS(int = 3, float = 2.f);
    virtual ~KBBS(){}
    void calc_spatial_distance();
    void show_keypoint();
    void do_prepare(cv::Mat inputImg, cv::Mat inputTem){
        int temp_size = (inputTem.rows / m_iPatchSize)*(inputTem.cols / m_iPatchSize);
        m_vecResBuff.clear();
        for(int index = 0;index < (inputImg.cols -inputTem.cols) / m_iPatchSize + 1;++index){
            m_vecResBuff.push_back(cv::Mat(temp_size, temp_size, CV_MAKETYPE(CV_32F, 1)));
        }
        // never use this
        //m_vecResBuff.resize((inputImg.cols -inputTem.cols) / m_iPatchSize + 1, cv::Mat(temp_size, temp_size, CV_MAKETYPE(CV_32F, 1)));
        m_vecPlanes.clear();
        for(int index = 0;index < inputTem.channels();++index){
            m_vecPlanes.push_back(cv::Mat(m_iPatchSize, m_iPatchSize, CV_MAKETYPE(CV_32F, 1)));
        }
        // never use this
        //m_vecPlanes.resize(inputTem.channels(), cv::Mat(m_iPatchSize, m_iPatchSize, CV_MAKETYPE(CV_32F, 1)));
        m_matSpatialDis.create(temp_size, temp_size, CV_MAKETYPE(CV_32F, 1));
        m_iYStep = inputTem.cols / m_iPatchSize;
        m_iXStep = inputTem.rows / m_iPatchSize;
        calc_spatial_distance();
        m_matTemp.create(m_iPatchSize, m_iPatchSize, CV_MAKETYPE(CV_32F, inputImg.channels()));
        m_matDiffResult.create(m_iPatchSize, m_iPatchSize, CV_MAKETYPE(CV_32F, 1));
        m_matGaussianMat.create(m_iPatchSize, m_iPatchSize, CV_MAKETYPE(CV_32F, 1));
        m_matGaussianMat = cv::Scalar::all(1.f);
        [&](float delta = 0.6){
            float sum = 0.f;
            float * temp_gaussian = new (std::nothrow) float[m_iPatchSize * m_iPatchSize];
            if(nullptr == temp_gaussian) return;
            for (int iY = -m_iPatchSize / 2; iY <= m_iPatchSize / 2; ++iY)
            {
                for (int iX = -m_iPatchSize / 2; iX <= m_iPatchSize / 2; ++iX)
                {
                    temp_gaussian[(iY + m_iPatchSize / 2)*m_iPatchSize + iX + m_iPatchSize / 2] = std::exp(-1.f * (std::pow(iX, 2.f) + std::pow(iY, 2.f)) / (2 * std::pow(delta, 2.f)));
                    sum += temp_gaussian[(iY + m_iPatchSize / 2)*m_iPatchSize + iX + m_iPatchSize / 2];
                }
            }
            for (int iY = 0; iY < m_iPatchSize; ++iY)
            {
                float *gaussianMat = m_matGaussianMat.ptr<float>(iY);
                for (int iX = 0; iX < m_iPatchSize; ++iX) gaussianMat[iX] = temp_gaussian[iY*m_iPatchSize + iX] / sum;
            }
            delete [] temp_gaussian;
        }();
    }
    float do_single_match(cv::Mat, cv::Mat, int, int);
    int get_cur_patchsize(){ return m_iPatchSize; }
private:
    int m_iPatchSize;
    float m_fGamma;
    int m_iXStep;
    int m_iYStep;
    std::vector<cv::Mat> m_vecResBuff;
    cv::Mat m_matSpatialDis;
    cv::Mat m_matGaussianMat;
    cv::Mat m_matTemp;
    cv::Mat m_matDiffResult;
    std::vector<cv::Mat> m_vecPlanes;
    void calc_color_distance(cv::Mat, cv::Mat, float*);
};

#endif // KBBS_H
