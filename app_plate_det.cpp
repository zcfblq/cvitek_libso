#include "plate_det.hpp"

void app_plate_det()
{
    cv::Mat image = cv::imread("test.jpg");
    auto net = CLPR::create_det("plate_model.cvimodel");
    auto result = net->commit(image);
    printf("result.size()=%d", result.size());
}

int main()
{
    app_plate_det();
}
