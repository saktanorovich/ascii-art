#pragma once
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

namespace fs = std::filesystem;

namespace ascii {

#pragma pack(push, 1)

struct bmp_file_header {
    uint16_t bfType;      // must be 'BM' (0x4D42)
    uint32_t bfSize;      // size of the file
    uint16_t bfReserved1; // reserved
    uint16_t bfReserved2; // reserved
    uint32_t bfOffBits;   // offset to pixel data
};

struct bmp_info_header {
    uint32_t biSize;          // size of this header (40 bytes)
    int32_t  biWidth;         // width in pixels
    int32_t  biHeight;        // height in pixels
    uint16_t biPlanes;        // must be 1
    uint16_t biBitCount;      // bits per pixel (e.g. 24)
    uint32_t biCompression;   // compression (0 = none)
    uint32_t biSizeImage;     // size of pixel data
    int32_t  biXPelsPerMeter; // horizontal resolution
    int32_t  biYPelsPerMeter; // vertical resolution
    uint32_t biClrUsed;       // colors in palette
    uint32_t biClrImportant;  // important colors
};

#pragma pack(pop)

const std::string PALETTE = "@%#*+=-:. ";

class renderer {
public:
    void make_art(const std::string& file_name, int h, int w) {
        cv::Mat img = cv::imread(file_name);
        if (img.empty()) {
            std::cerr << "Could not open input image" << std::endl;
            exit(1);
        }
        auto file_name_bmp = file_name + ".bmp";
        if (fs::exists(file_name_bmp)) {
            fs::remove(file_name_bmp);
        }
        cv::Mat img_bmp = cv::imread(file_name, cv::IMREAD_GRAYSCALE);
        cv::Mat resized;
        cv::resize(img, resized, cv::Size(w, h));
        if (!cv::imwrite(file_name_bmp, resized)) {
            std::cerr << "Failed to save BMP file" << std::endl;
            exit(1);
        }
        std::ifstream file_bmp(file_name_bmp, std::ios::binary);

        // define iterators
        std::istreambuf_iterator<char> begin(file_bmp);
        std::istreambuf_iterator<char> end;

        // construct buffer from iterators
        std::vector<uchar> buffer(begin, end);

        // decode image from memory buffer
        img_bmp = cv::imdecode(buffer, cv::IMREAD_COLOR);
        if (img_bmp.empty()) {
            std::cerr << "Failed to decode BMP from stream" << std::endl;
            exit(1);
        }

        // render ascii
        for (int y = 0; y < img_bmp.rows; ++y) {
            for (int x = 0; x < img_bmp.cols; ++x) {
                cv::Vec3b pixel = img_bmp.at<cv::Vec3b>(y, x);
                int b = pixel[0];
                int g = pixel[1];
                int r = pixel[2];
                int brightness = (r + b + g) / 3;
                int index = (brightness * (PALETTE.size() - 1)) / 255;

                // ANSI truecolor escape sequence
                std::cout << "\033[38;2;"
                    << r << ";"  // R
                    << g << ";"  // G
                    << b << "m"  // B
                    << PALETTE[index]
                    << "\033[0m";
            }
            std::cout << std::endl;
        }
        file_bmp.close();
        if (fs::exists(file_name_bmp)) {
            fs::remove(file_name_bmp);
        }
    }
};

} // namespace ascii
