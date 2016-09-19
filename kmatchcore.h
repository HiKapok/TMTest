#ifndef KMATCHCORE_H
#define KMATCHCORE_H

#include <ctime>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

class KMatchCore
{
public:
    KMatchCore();
    virtual ~KMatchCore(){}
    bool imgload(cv::String, cv::String);
    bool imgload(cv::String, cv::String, cv::String);
    bool run_match();
    int creat_dummy_color(int, bool = false);
    virtual int get_cur_patchsize(){ return 1; }
    virtual void show_keypoint(){}
    void show_similar_map(cv::String="C://similar_map.bmp");
    void save_match_image(cv::String = "C://result.bmp");
    virtual void do_prepare(cv::Mat, cv::Mat){}
    virtual float do_single_match(cv::Mat, cv::Mat, int, int) = 0;
    std::time_t get_begin_time(){ return m_tBegin; }
private:
    cv::Mat m_imgSource;
    cv::Mat m_imgTemplate;
    cv::Mat m_imgSimilarMap;
    std::time_t m_tBegin;
    std::vector<cv::Vec3b> m_veColorMap;
};

#endif // KMATCHCORE_H
