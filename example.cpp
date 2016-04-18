// Example of blend_mode

#include <iostream>
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "blend_mode.h"

std::string title = "blend mode";

const cv::String keys =
	"{help h usage ? |         | show help            }"
	"{@image1        |         | input image file #1  }"
	"{@image2        |         | input image file #2  }"
	"{M mode         |         | blend mode           }"
	;


int main(int argc, char** argv) {
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about(title);

    std::string imagefile1 = parser.get<std::string>("@image1");
    std::string imagefile2 = parser.get<std::string>("@image2");
    int mode = parser.get<int>("M");

    if (parser.has("h") || !parser.check() || imagefile1.empty() || imagefile2.empty()) {
        parser.printMessage();
        return -1;
    }

    cv::Mat image_a = cv::imread(imagefile1);
    if(image_a.empty()) {
        std::cout << "error: could not find image file " << imagefile1 << std::endl;
        return -1;
    }
    
    cv::Mat image_b = cv::imread(imagefile2);
    if(image_b.empty()) {
        std::cout << "error: could not find image file " << imagefile2 << std::endl;
        return -1;
    }
    
    if(image_a.size() != image_b.size()) {
        std::cout << "error: different size of images."  << std::endl;
    }
    
    cv::Mat image_blended = cv::Mat::zeros(image_a.size(),image_a.type());
    
    switch(mode) {
        case 0     :
            ColorBlend_Buffer(image_a,image_b,image_blended,Normal);
            break;
        case 1    :
            ColorBlend_Buffer(image_a,image_b,image_blended,Lighten);
            break;
        case 2     :
            ColorBlend_Buffer(image_a,image_b,image_blended,Darken);
            break;
        case 3   :
            ColorBlend_Buffer(image_a,image_b,image_blended,Multiply);
            break;
        case 4    :
            ColorBlend_Buffer(image_a,image_b,image_blended,Average);
            break;
        case 5        :
            ColorBlend_Buffer(image_a,image_b,image_blended,Add);
            break;
        case 6   :
            ColorBlend_Buffer(image_a,image_b,image_blended,Subtract);
            break;
        case 7 :
            ColorBlend_Buffer(image_a,image_b,image_blended,Difference);
            break;
        case 8   :
            ColorBlend_Buffer(image_a,image_b,image_blended,Negation);
            break;
        case 9     :
            ColorBlend_Buffer(image_a,image_b,image_blended,Screen);
            break;
        case 10  :
            ColorBlend_Buffer(image_a,image_b,image_blended,Exclusion);
            break;
        case 11    :
            ColorBlend_Buffer(image_a,image_b,image_blended,Overlay);
            break;
        case 12  :
            ColorBlend_Buffer(image_a,image_b,image_blended,SoftLight);
            break;
        case 13  :
            ColorBlend_Buffer(image_a,image_b,image_blended,HardLight);
            break;
        case 14 :
            ColorBlend_Buffer(image_a,image_b,image_blended,ColorDodge);
            break;
        case 15  :
            ColorBlend_Buffer(image_a,image_b,image_blended,ColorBurn);
            break;
        case 16:
            ColorBlend_Buffer(image_a,image_b,image_blended,LinearDodge);
            break;
        case 17 :
            ColorBlend_Buffer(image_a,image_b,image_blended,LinearBurn);
            break;
        case 18:
            ColorBlend_Buffer(image_a,image_b,image_blended,LinearLight);
            break;
        case 19 :
            ColorBlend_Buffer(image_a,image_b,image_blended,VividLight);
            break;
        case 20   :
            ColorBlend_Buffer(image_a,image_b,image_blended,PinLight);
            break;
        case 21    :
            ColorBlend_Buffer(image_a,image_b,image_blended,HardMix);
            break;
        case 22    :
            ColorBlend_Buffer(image_a,image_b,image_blended,Reflect);
            break;
        case 23       :
            ColorBlend_Buffer(image_a,image_b,image_blended,Glow);
            break;
        case 24    :
            ColorBlend_Buffer(image_a,image_b,image_blended,Phoenix);
            break;
        default:
            std::cout << "error: illegal mode."  << std::endl;
            return -1;
    }
    cv::namedWindow(title,cv::WINDOW_NORMAL);
    cv::imshow(title,image_blended);
    cv::imwrite("result.tif",image_blended);
    cv::waitKey(0);
    
    return 0;
}
