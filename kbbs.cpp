#include "kbbs.h"
#include <tuple>
#include <iostream>

KBBS::KBBS(int _patch_size) :m_iPatchSize(_patch_size + (_patch_size % 2 == 0 ? 1 : 0) ), m_iXStep(0), m_iYStep(0)
{

}

void KBBS::calc_spatial_distance()
{
    // the i_th row in m_matSpatialDis represnt the distance
    // between the i_th patch (row first) and all the other patches
    m_matSpatialDis = cv::Scalar::all(0.);

    for (int iHeight = 0; iHeight < m_matSpatialDis.rows; ++iHeight){
        float * distance = m_matSpatialDis.ptr<float>(iHeight);
        for (int iWidth = 0; iWidth < m_matSpatialDis.cols; ++iWidth){
            distance[iWidth] = std::pow(((iHeight % m_iYStep) - (iWidth % m_iYStep)) * m_iPatchSize, 2.)
                + std::pow(((iHeight / m_iYStep) - (iWidth / m_iYStep)) * m_iPatchSize, 2.);
        }
    }
}

void KBBS::show_keypoint()
{

}

float KBBS::do_single_match(cv::Mat _imgsrc, cv::Mat _imgtmp, int row, int col)
{
    if(_imgsrc.size() != _imgtmp.size() || _imgsrc.channels() != _imgtmp.channels()) return 0.f;
    int num_bbp = 0;
//std::cout<<row<<" "<<col<<std::endl;
    if(0 == row && 0== col){
        for(int iY = 0; iY < m_iXStep; ++iY){
            for(int iX = 0;iX < m_iYStep; ++iX){
                float * distance = m_vecResBuff[col].ptr<float>(iY * m_iYStep + iX);
                cv::Mat thisPatch = _imgsrc(cv::Rect(iX * m_iPatchSize, iY * m_iPatchSize, m_iPatchSize, m_iPatchSize));
                calc_color_distance(thisPatch, _imgtmp, distance);
            }
        }
    }else if(0 == row && col > 0){
        for(int iY = 0; iY < m_iXStep; ++iY){
            (m_vecResBuff[col - 1].rowRange(1, (_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize))).copyTo(m_vecResBuff[col].rowRange(0, (_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize) - 1));
            float * distance = m_vecResBuff[col].ptr<float>(iY * m_iYStep + m_iYStep - 1);
            cv::Mat thisPatch = _imgsrc(cv::Rect((m_iYStep - 1) * m_iPatchSize, iY * m_iPatchSize, m_iPatchSize, m_iPatchSize));
            calc_color_distance(thisPatch, _imgtmp, distance);
        }
    }else if(row > 0 && 0 == col){
        for(int iX = 0;iX < m_iYStep; ++iX){
            (m_vecResBuff[0].rowRange(m_iYStep, (_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize))).copyTo(m_vecResBuff[0].rowRange(0, (_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize) - m_iYStep));
            float * distance = m_vecResBuff[0].ptr<float>((m_iXStep-1) * m_iYStep + iX);
            cv::Mat thisPatch = _imgsrc(cv::Rect(iX * m_iPatchSize, (m_iXStep-1) * m_iPatchSize, m_iPatchSize, m_iPatchSize));
            calc_color_distance(thisPatch, _imgtmp, distance);
        }
    }else{
        (m_vecResBuff[col].rowRange(m_iYStep, (_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize))).copyTo(m_vecResBuff[col].rowRange(0, (_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize) - m_iYStep));
        (m_vecResBuff[col - 1].rowRange((_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize) - m_iYStep + 1, (_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize))).copyTo(m_vecResBuff[col].rowRange((_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize) - m_iYStep, (_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize) - 1));
        float * distance = m_vecResBuff[col].ptr<float>((m_iXStep-1) * m_iYStep + m_iYStep - 1);
        cv::Mat thisPatch = _imgsrc(cv::Rect((m_iYStep - 1) * m_iPatchSize, (m_iXStep-1) * m_iPatchSize, m_iPatchSize, m_iPatchSize));
        calc_color_distance(thisPatch, _imgtmp, distance);
    }

    int *col_min_index = new (std::nothrow) int[(_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize)];
    if(nullptr == col_min_index) return 0.f;

    memset(col_min_index, -1, (_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize)*sizeof(int));
    cv::Mat join_distance = m_matSpatialDis * 2 + m_vecResBuff[col];
    cv::Point min_loc(0, 0);
    for(int index = 0;index < (_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize);++index){
        cv::minMaxLoc(join_distance.rowRange(index, index + 1), nullptr, nullptr, &min_loc, nullptr);
        int row_min = min_loc.x;
        if(col_min_index[row_min] == -1){
            cv::minMaxLoc(join_distance.colRange(row_min, row_min + 1), nullptr, nullptr, &min_loc, nullptr);
            col_min_index[row_min] = min_loc.y;
        }
        if(col_min_index[row_min] == index) ++num_bbp;
    }

    delete [] col_min_index;

    return num_bbp*1.f/(_imgtmp.rows / m_iPatchSize)*(_imgtmp.cols / m_iPatchSize);
}

void KBBS::calc_color_distance(cv::Mat _patch, cv::Mat _template, float * distance)
{
    for(int iY = 0;iY < m_iXStep;++iY){
        for(int iX = 0;iX < m_iYStep;++iX){
            cv::addWeighted(_patch, 1., _template(cv::Rect(iX * m_iPatchSize, iY * m_iPatchSize, m_iPatchSize, m_iPatchSize)), -1., 0., m_matTemp, CV_32F);
            cv::split(m_matTemp, m_vecPlanes);
            double color_distance = 0.;
            for(auto &chan : m_vecPlanes){
                cv::multiply(chan, m_matGaussianMat, m_matDiffResult, 1, CV_32F);
                cv::multiply(m_matDiffResult, m_matDiffResult, m_matDiffResult);
                //cv::pow(m_matDiffResult, 2., m_matDiffResult);
                color_distance += cv::sum(m_matDiffResult)(0);
            }
            distance[iY * m_iYStep + iX] = color_distance;
        }
    }
}

