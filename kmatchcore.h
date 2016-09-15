#ifndef KMATCHCORE_H
#define KMATCHCORE_H

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
    bool run_match();
    virtual int get_cur_patchsize(){ return 1; }
    virtual void show_keypoint(){}
    void show_similar_map();
    virtual void do_prepare(cv::Mat, cv::Mat){}
    virtual float do_single_match(cv::Mat, cv::Mat, int, int) = 0;
private:
    cv::Mat m_imgSource;
    cv::Mat m_imgTemplate;
    cv::Mat m_imgSimilarMap;
};

#endif // KMATCHCORE_H
