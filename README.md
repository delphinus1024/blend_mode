# blend_mode

A Macro definition of "Blend Mode" processing with OpenCV.

## Description

blend_mode is a OpenCV macros to process "blend mode" operations which are frequently used by such as Photoshop or AfterEffects.
blend_mode.h contains macros to process varisous blending operation, so that simply including this h file in your host program and call either of macros.
This macro is based on following article of StackOverflow.

http://stackoverflow.com/questions/5919663/how-does-photoshop-blend-two-images-together

## Features

- Blend mode processing of two cv::Mat images.
- Currently it supports only CV_8UC3 images.

## Requirement

- OpenCV 3.0.0 or above is preferable.
- Checked with win7 32bit + msys2 + gcc

## Usage

Refer to example.cpp which is simple program to show how to call the macros.
Note that two input images and result image must be same size and CV_8UC3 type. You must allocate the result image in advance.

## Installation

1. Include blend_mode.h in your host program.
2. Modify Makefile according to your host program and OpenCV environment.
3. make

## Author

delphinus1024

## License

[MIT](https://raw.githubusercontent.com/delphinus1024/blend_mode/master/LICENSE.txt)

