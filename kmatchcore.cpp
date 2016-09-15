#include "kmatchcore.h"

KMatchCore::KMatchCore():m_imgSource(), m_imgTemplate(), m_imgSimilarMap()
{
}

bool KMatchCore::imgload(cv::String _src_filename, cv::String _tmp_filename)
{
    m_imgSource = cv::imread(_src_filename);
    if(!m_imgSource.data) return false;
    m_imgTemplate = cv::imread(_tmp_filename);
    if(!m_imgTemplate.data) return false;
    return true;
}

bool KMatchCore::run_match()
{
    int _patch_size = 1;
    if(!m_imgSource.data || !m_imgTemplate.data) return false;

    // use patches rather than points
    if(1 != (_patch_size = get_cur_patchsize())){
        if(_patch_size < 1) return false;
        if(_patch_size > 1){
            if(m_imgSource.rows % _patch_size != 0) m_imgSource = m_imgSource.rowRange((m_imgSource.rows % _patch_size)/2, (m_imgSource.rows % _patch_size)/2 + (m_imgSource.rows / _patch_size) * _patch_size);//.clone();
            if(m_imgSource.cols % _patch_size != 0) m_imgSource = m_imgSource.colRange((m_imgSource.cols % _patch_size)/2, (m_imgSource.cols % _patch_size)/2 + (m_imgSource.cols / _patch_size) * _patch_size);//.clone();
            if(m_imgTemplate.rows % _patch_size != 0) m_imgTemplate = m_imgTemplate.rowRange((m_imgTemplate.rows % _patch_size)/2, (m_imgTemplate.rows % _patch_size)/2 + (m_imgTemplate.rows / _patch_size) * _patch_size);//.clone();
            if(m_imgTemplate.cols % _patch_size != 0) m_imgTemplate = m_imgTemplate.colRange((m_imgTemplate.cols % _patch_size)/2, (m_imgTemplate.cols % _patch_size)/2 + (m_imgTemplate.cols / _patch_size) * _patch_size);//.clone();
        }
    }

    if(m_imgSource.size().width < m_imgTemplate.size().width
            || m_imgSource.size().height < m_imgTemplate.size().height) return false;

    do_prepare(m_imgSource, m_imgTemplate);

    m_imgSimilarMap.create(m_imgSource.rows / _patch_size, m_imgSource.cols / _patch_size, CV_32FC1);
    m_imgSimilarMap = cv::Scalar::all(0.);

    for(int iHeight = 0; iHeight <= m_imgSource.rows - m_imgTemplate.rows; iHeight+=_patch_size){
        float * similarMap = m_imgSimilarMap.ptr<float>(iHeight);
        for(int iWidth = 0; iWidth <= m_imgSource.cols - m_imgTemplate.cols; iWidth+=_patch_size){
            cv::Mat tempROI = m_imgSource(cv::Rect(iWidth, iHeight, m_imgTemplate.cols, m_imgTemplate.rows));
            similarMap[iWidth] = do_single_match(tempROI, m_imgTemplate, iHeight/_patch_size, iWidth/_patch_size);
        }
    }

//    int _half_tmp_height = m_imgTemplate.rows / 2;
//    int _half_tmp_width = m_imgTemplate.cols / 2;

//    int _half_left_height = m_imgTemplate.rows - _half_tmp_height;
//    int _half_left_width = m_imgTemplate.cols - _half_tmp_width;


//    for(int iHeight = _half_tmp_height; iHeight <= m_imgSource.rows - _half_left_height; iHeight+=_patch_size){
//        float * similarMap = m_imgSimilarMap.ptr<float>(iHeight);
//        for(int iWidth = _half_tmp_width; iWidth <= m_imgSource.cols - _half_left_width; iWidth+=_patch_size){
//            cv::Mat tempROI = m_imgSource(cv::Rect(iWidth-_half_tmp_width, iHeight-_half_tmp_height, m_imgTemplate.cols, m_imgTemplate.rows));
//            similarMap[iWidth] = do_single_match(tempROI, m_imgTemplate);
//        }
//    }
    return true;
}

void KMatchCore::show_similar_map()
{
    cv::Mat image_toshow(m_imgSimilarMap.rows, m_imgSimilarMap.cols, CV_8UC1);
    cv::normalize(m_imgSimilarMap, image_toshow, 255.0);
    cv::namedWindow("similarmap");
    cv::imshow("similarmap", image_toshow);
    cv::waitKey(0);
}

