// Blend mode processing macros for OpenCV cv::Mat images.
// Supports only on CV_8UC3 images.

#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

#ifndef uint8
#define uint8 unsigned char
#endif

#ifndef min
#define min(a,b)    ((a < b) ? a : b)
#endif

#ifndef max
#define max(a,b)    ((a > b) ? a : b)
#endif

#define ChannelBlend_Normal(A,B)     ((uint8)(A))
#define ChannelBlend_Lighten(A,B)    ((uint8)((B > A) ? B:A))
#define ChannelBlend_Darken(A,B)     ((uint8)((B > A) ? A:B))
#define ChannelBlend_Multiply(A,B)   ((uint8)((A * B) / 255))
#define ChannelBlend_Average(A,B)    ((uint8)((A + B) / 2))
#define ChannelBlend_Add(A,B)        ((uint8)(min(255, (A + B))))
#define ChannelBlend_Subtract(A,B)   ((uint8)((A + B < 255) ? 0:(A + B - 255)))
#define ChannelBlend_Difference(A,B) ((uint8)(abs(A - B)))
#define ChannelBlend_Negation(A,B)   ((uint8)(255 - abs(255 - A - B)))
#define ChannelBlend_Screen(A,B)     ((uint8)(255 - (((255 - A) * (255 - B)) >> 8)))
#define ChannelBlend_Exclusion(A,B)  ((uint8)(A + B - 2 * A * B / 255))
#define ChannelBlend_Overlay(A,B)    ((uint8)((B < 128) ? (2 * A * B / 255):(255 - 2 * (255 - A) * (255 - B) / 255)))
#define ChannelBlend_SoftLight(A,B)  ((uint8)((B < 128)?(2*((A>>1)+64))*((float)B/255):(255-(2*(255-((A>>1)+64))*(float)(255-B)/255))))
#define ChannelBlend_HardLight(A,B)  (ChannelBlend_Overlay(B,A))
#define ChannelBlend_ColorDodge(A,B) ((uint8)((B == 255) ? B:min(255, ((A << 8 ) / (255 - B)))))
#define ChannelBlend_ColorBurn(A,B)  ((uint8)((B == 0) ? B:max(0, (255 - ((255 - A) << 8 ) / B))))
#define ChannelBlend_LinearDodge(A,B)(ChannelBlend_Add(A,B))
#define ChannelBlend_LinearBurn(A,B) (ChannelBlend_Subtract(A,B))
#define ChannelBlend_LinearLight(A,B)((uint8)(B < 128)?ChannelBlend_LinearBurn(A,(2 * B)):ChannelBlend_LinearDodge(A,(2 * (B - 128))))
#define ChannelBlend_VividLight(A,B) ((uint8)(B < 128)?ChannelBlend_ColorBurn(A,(2 * B)):ChannelBlend_ColorDodge(A,(2 * (B - 128))))
#define ChannelBlend_PinLight(A,B)   ((uint8)(B < 128)?ChannelBlend_Darken(A,(2 * B)):ChannelBlend_Lighten(A,(2 * (B - 128))))
#define ChannelBlend_HardMix(A,B)    ((uint8)((ChannelBlend_VividLight(A,B) < 128) ? 0:255))
#define ChannelBlend_Reflect(A,B)    ((uint8)((B == 255) ? B:min(255, (A * A / (255 - B)))))
#define ChannelBlend_Glow(A,B)       (ChannelBlend_Reflect(B,A))
#define ChannelBlend_Phoenix(A,B)    ((uint8)(min(A,B) - max(A,B) + 255))

#define ColorBlend_Buffer(A,B,T,M)     {\
    CV_Assert(((A).cols == (B).cols) && ((A).rows == (B).rows));\
    CV_Assert(((A).cols == (T).cols) && ((A).rows == (T).rows));\
    std::cout << "Mode=" << #M << std::endl;\
    int size = (A).rows * (A).cols;\
    cv::Vec3b *A_ptr = (A).ptr<cv::Vec3b>(0);\
    cv::Vec3b *B_ptr = (B).ptr<cv::Vec3b>(0);\
    cv::Vec3b *T_ptr = (T).ptr<cv::Vec3b>(0);\
    for(int i = 0;i < size;++i) {\
        ((T_ptr[i]))[0] = ChannelBlend_##M(((A_ptr[i]))[0], ((B_ptr[i]))[0]);\
        ((T_ptr[i]))[1] = ChannelBlend_##M(((A_ptr[i]))[1], ((B_ptr[i]))[1]);\
        ((T_ptr[i]))[2] = ChannelBlend_##M(((A_ptr[i]))[2], ((B_ptr[i]))[2]);\
    }\
}
