#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include "yolov8.h"

// 定義函數指標類型
typedef void* (__cdecl *CreateYOLOV8_t)(Config);
typedef void (__cdecl *DestroyYOLOV8_t)(void*);
typedef void (__cdecl *DetectYOLOV8_t)(void*, unsigned char*, int, int, int);
typedef void (__cdecl *GetDetectionsYOLOV8_t)(void*, Detection*, int*);

int main() {
    // 加載 YOLOv8 DLL (Load YOLOv8 DLL)
    HMODULE hYOLOv8 = LoadLibrary(TEXT("../../../DLL/YOLOv8_SDK.dll"));
    if (!hYOLOv8) {
        std::cerr << "Unable to load YOLOv8_SDK.dll" << std::endl;
        return -1;
    }

    // 獲取函數地址 (Get function addresses)
    CreateYOLOV8_t CreateYOLOV8 = (CreateYOLOV8_t)GetProcAddress(hYOLOv8, "CreateYOLOV8");
    DestroyYOLOV8_t DestroyYOLOV8 = (DestroyYOLOV8_t)GetProcAddress(hYOLOv8, "DestroyYOLOV8");
    DetectYOLOV8_t DetectYOLOV8 = (DetectYOLOV8_t)GetProcAddress(hYOLOv8, "DetectYOLOV8");
    GetDetectionsYOLOV8_t GetDetectionsYOLOV8 = (GetDetectionsYOLOV8_t)GetProcAddress(hYOLOv8, "GetDetectionsYOLOV8");

    if (!CreateYOLOV8 || !DestroyYOLOV8 || !DetectYOLOV8 || !GetDetectionsYOLOV8) {
        std::cerr << "Unable to load YOLOv8_SDK.dl" << std::endl;
        FreeLibrary(hYOLOv8);
        return -1;
    }

    // 配置 YOLOv8 參數 (Configure YOLOv8 parameters)
    Config config;
    config.confThreshold = 0.5;
    config.nmsThreshold = 0.4;
    config.scoreThreshold = 0.3;
    config.inpWidth = 640;
    config.inpHeight = 640;
    config.onnx_path = "../../../Models/yolov8n.onnx";  // ONNX 模型路徑 (Path to ONNX model)

    // 創建 YOLOv8 對象 (Create YOLOv8 object)
    void* yolov8 = CreateYOLOV8(config);

    // 讀取圖像數據 (Read image data)
    std::ifstream file("../../../TestImages/bus.jpg", std::ios::binary);
    std::vector<unsigned char> image_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // 執行 YOLOv8 檢測 (Perform YOLOv8 detection)
    cv::Mat image = cv::imread("../../../TestImages/bus.jpg");  // 使用 OpenCV 讀取圖像 (Read image using OpenCV)
    int original_width = image.cols;  // 獲取原始圖像寬度 (Get original image width)
    int original_height = image.rows;  // 獲取原始圖像高度 (Get original image height)
    DetectYOLOV8(yolov8, image_data.data(), image_data.size(), original_width, original_height);

    // 獲取檢測結果 (Get detection results)
    const int maxDetections = 100;
    Detection detections[maxDetections];
    int numDetections = 0;
    GetDetectionsYOLOV8(yolov8, detections, &numDetections);

    // 打印檢測結果並繪製檢測框 (Print detection results and draw bounding boxes)
    for (int i = 0; i < numDetections; ++i) {
        Detection& detection = detections[i];
        std::cout << "Class ID: " << detection.class_id << ", Confidence: " << detection.confidence 
                  << ", Box: [" << detection.box.x << ", " << detection.box.y << ", " 
                  << detection.box.width << ", " << detection.box.height << "]" << std::endl;

        cv::rectangle(image, detection.box, cv::Scalar(0, 255, 0), 2);
        std::string label = "ID: " + std::to_string(detection.class_id) + ", Conf: " + std::to_string(detection.confidence);
        cv::putText(image, label, cv::Point(detection.box.x, detection.box.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
    }

    // 顯示檢測結果 (Display detection results)
    cv::imshow("Detections", image);
    cv::waitKey(0);
    cv::destroyAllWindows();

    // 銷毀 YOLOv8 對象 (Destroy YOLOv8 object)
    DestroyYOLOV8(yolov8);

    // 釋放 DLL 資源 (Free DLL resources)
    FreeLibrary(hYOLOv8);

    return 0;
}
