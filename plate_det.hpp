#ifndef PLATE_DET_HPP
#define PLATE_DET_HPP

#include <vector>
#include <memory>
#include <string>
#include <opencv2/opencv.hpp>

namespace CLPR
{
    struct box
    {
        float x, y, w, h;
    };

    struct detection
    {
        box bbox;
        int cls;
        float score;
        int batch_idx;
        float landmarks[8];
    };
    enum class ImageType : int
    {
        CVMat = 0,
        HostBGR = 1,
        HostRGB = 2
        // DeviceYUV = 3;
    };
    struct Image
    {
        ImageType type = ImageType::CVMat;
        cv::Mat cvmat;

        uint8_t *host_data = nullptr;
        int width = 0, height = 0;

        Image() = default;
        Image(const cv::Mat &cvmat) : cvmat(cvmat), type(ImageType::CVMat) {}
        Image(uint8_t *data, int width, int height, ImageType type)
            : host_data(data), width(width), height(height), type(type) {}

        int get_width() const
        {
            return type == ImageType::CVMat ? cvmat.cols : width;
        }
        int get_height() const
        {
            return type == ImageType::CVMat ? cvmat.rows : height;
        }
        cv::Size get_size() const
        {
            return cv::Size(get_width(), get_height());
        }
        bool empty() const
        {
            return type == ImageType::CVMat ? cvmat.empty() : (host_data == nullptr || width < 1 || height < 1);
        }
        size_t get_data_size() const
        {
            switch (type)
            {
            case ImageType::CVMat:
                return cvmat.rows * cvmat.cols * 3;
            case ImageType::HostBGR:
                return width * height * 3;
            // case ImageType::DeviceYUV:
            //     return width * height * 1.5;
            case ImageType::HostRGB:
                return width * height * 3;
            default:
                return 0;
            }
        }
    };
    using PlateRegion = detection;
    using PlateRegionArray = std::vector<PlateRegion>;

    class DetInfer
    {
    public:
        virtual PlateRegionArray commit(const Image &image) = 0;
        // virtual std::vector<PlateRegionArray> commits(const std::vector<Image> &images) = 0;
    };

    std::shared_ptr<DetInfer> create_det(const std::string &engine_file, float confidence_threshold = 0.5,
                                         float nms_threshold = 0.4, int max_objects = 1024);
}

#endif