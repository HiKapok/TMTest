#include "kmatchcore.h"
#include <fstream>
#include <tuple>

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

bool KMatchCore::imgload(cv::String _src_filename, cv::String _tem_filename, cv::String _rect_filename)
{
    std::fstream fs(_rect_filename.c_str(), std::ios_base::in);
    if (false == fs.is_open()) return false;

    int _xstart = 0;
    int _ystart = 0;
    int _width = 0;
    int _height = 0;

    std::string tempStr("");
    std::getline(fs, tempStr);
    std::istringstream parambuff(tempStr);
    std::tie(_xstart, _ystart, _width, _height) = [&parambuff]() -> std::tuple<int, int, int, int>
    {
        int index(4);
        float _temp_value(0.f);
        int _rect_buff[4];
        while (index-->0){
            (parambuff >> _temp_value).ignore(1);
            _rect_buff[index] = static_cast<int>(std::round(_temp_value));
        }
        return std::make_tuple(_rect_buff[3], _rect_buff[2], _rect_buff[1], _rect_buff[0]);
    }();

    fs.close();

    m_imgSource = cv::imread(_src_filename);
    if(!m_imgSource.data) return false;
    cv::Mat _tempMat = cv::imread(_tem_filename);
    if(!_tempMat.data) return false;
    if (_xstart < 0 || _ystart < 0 || _xstart >= _tempMat.cols || _ystart >= _tempMat.rows) return false;
    if (_width - 1 >= _tempMat.cols || _height - 1 >= _tempMat.rows) return false;
    m_imgTemplate = _tempMat(cv::Rect(_xstart, _ystart, _width + 1, _height + 1)).clone();

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

    m_imgSimilarMap.create((m_imgSource.rows - m_imgTemplate.rows)/ _patch_size + 1, (m_imgSource.cols - m_imgTemplate.cols) / _patch_size + 1, CV_32FC1);
    m_imgSimilarMap = cv::Scalar::all(0.);

    for(int iHeight = 0; iHeight <= m_imgSource.rows - m_imgTemplate.rows; iHeight+=_patch_size){
        float * similarMap = m_imgSimilarMap.ptr<float>(iHeight/_patch_size);
        for(int iWidth = 0; iWidth <= m_imgSource.cols - m_imgTemplate.cols; iWidth+=_patch_size){
            cv::Mat tempROI = m_imgSource(cv::Rect(iWidth, iHeight, m_imgTemplate.cols, m_imgTemplate.rows));
            similarMap[iWidth/_patch_size] = do_single_match(tempROI, m_imgTemplate, iHeight/_patch_size, iWidth/_patch_size);
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

int KMatchCore::creat_dummy_color(int _step, bool _b_start_blue)
{
    int iB = 255;
    int iG = 0;
    int iR = 160;
    m_veColorMap.clear();
    if(_b_start_blue) iR = _step;
    else m_veColorMap.push_back(cv::Vec3b(static_cast<uchar>(iB), static_cast<uchar>(iG), static_cast<uchar>(iR)));
    for (iR -= _step; iR > 0; iR -= _step) m_veColorMap.push_back(cv::Vec3b(static_cast<uchar>(iB), static_cast<uchar>(iG), static_cast<uchar>(iR)));
    if (std::abs(iR) > 2 * _step / 3) { iR = 0; iG += _step; }
    for (iR = 0; iG < 128; iG += _step) m_veColorMap.push_back(cv::Vec3b(static_cast<uchar>(iB), static_cast<uchar>(iG), static_cast<uchar>(iR)));
    for (; iG < 255 && iB > 0; iG += _step, iB -= 2*_step) m_veColorMap.push_back(cv::Vec3b(static_cast<uchar>(iB), static_cast<uchar>(iG), static_cast<uchar>(iR)));
    if (std::abs(iG - 255) > 2 * _step / 3 && std::abs(iB) > 2 * _step / 3) { iG = 255; iB = 0; iR += 2 * _step; }
    for (iG = 255, iB = 0; iR < 255; iR += 2 * _step) m_veColorMap.push_back(cv::Vec3b(static_cast<uchar>(iB), static_cast<uchar>(iG), static_cast<uchar>(iR)));
    if (std::abs(iR - 255) > 2 * _step / 3) { iR = 255; iG -= _step; }
    for (iR = 255; iG > 0; iG -= _step) m_veColorMap.push_back(cv::Vec3b(static_cast<uchar>(iB), static_cast<uchar>(iG), static_cast<uchar>(iR)));
    for (iG = 255 / 5, iR -= 2 * _step; iR > 2 * iG; iR -=  _step) m_veColorMap.push_back(cv::Vec3b(static_cast<uchar>(iB), static_cast<uchar>(iG), static_cast<uchar>(iR)));
    return m_veColorMap.size();
}

void KMatchCore::show_similar_map()
{ 
    if (!m_imgSource.data || !m_imgTemplate.data) return;
    cv::Mat image_toshow(m_imgSimilarMap.rows, m_imgSimilarMap.cols, CV_8UC3);
    double min_value = 0.;
    double max_value = 0.;     
    cv::minMaxLoc(m_imgSimilarMap, &min_value, &max_value, nullptr, nullptr);
    double delta = max_value - min_value;
    if(delta < 1.) delta = 1.;
    int num_colors = creat_dummy_color(25, true);
    float _delta = 256. / num_colors;
    for(int iY = 0;iY < m_imgSimilarMap.rows;++iY){
        float *_data = m_imgSimilarMap.ptr<float>(iY);
        for(int iX = 0;iX < m_imgSimilarMap.cols;++iX){
            //float _temp_value = (_data[iX] - 0) * 255. / 105;
            float _temp_value = (_data[iX] - min_value) * 255. / delta;
            image_toshow.at<cv::Vec3b>(iY,iX) = m_veColorMap[_temp_value / _delta];
        }
    }

    //cv::addWeighted(m_imgSimilarMap, 255. / delta, cv::Scalar(min_value * 255. / delta), -1., 0., image_toshow, CV_8U);
    //cv::normalize(m_imgSimilarMap, image_toshow, 0., 255., cv::NORM_L2, CV_8U);
    cv::namedWindow("similarmap");
    cv::imshow("similarmap", image_toshow);
    cv::waitKey(0);
}

void KMatchCore::save_match_image(cv::String filename)
{
    if (!m_imgSource.data || !m_imgTemplate.data) return;
    int _patch_size = 1;
    int _pen_width = std::min(m_imgTemplate.cols, m_imgTemplate.rows) / 20;
    if(_pen_width < 2) _pen_width = 2;
    if(_pen_width > 10) _pen_width = 10;
    cv::Point max_loc(0, 0);
    if((_patch_size = get_cur_patchsize()) < 1) return;
    cv::minMaxLoc(m_imgSimilarMap, nullptr, nullptr, nullptr, &max_loc);
    cv::rectangle(m_imgSource, cv::Rect(max_loc.x * _patch_size, max_loc.y * _patch_size, m_imgTemplate.cols, m_imgTemplate.rows), cv::Scalar(0), _pen_width);
    cv::imwrite(filename, m_imgSource);
}

