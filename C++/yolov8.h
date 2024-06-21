#pragma once
#include <string>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <openvino/openvino.hpp>
#include <fstream>
#include <vector>
#include <random>

#ifdef YOLOV8DLL_EXPORTS
#define YOLOV8_API __declspec(dllexport)
#else
#define YOLOV8_API __declspec(dllimport)
#endif

// Define Config struct
// 定義 Config 結構體
extern "C" {
    struct Config {
        float confThreshold;   // Detection confidence threshold
                               // 檢測置信度閾值
        float nmsThreshold;    // Non-maximum suppression threshold
                               // 非極大值抑制閾值
        float scoreThreshold;  // Score threshold
                               // 得分閾值
        int inpWidth;          // Input image width
                               // 輸入圖像寬度
        int inpHeight;         // Input image height
                               // 輸入圖像高度
        const char* onnx_path; // Path to ONNX model
                               // ONNX 模型的路徑
    };

    // Define Detection struct
    // 定義 Detection 結構體
    struct Detection {
        int class_id;         // Class ID
                              // 類別 ID
        float confidence;     // Confidence
                              // 置信度
        cv::Rect box;         // Bounding box
                              // 檢測框
    };

    // Declare external C functions for YOLOv8
    // 聲明 YOLOv8 的外部 C 函數
    YOLOV8_API void* CreateYOLOV8(Config config); // Create YOLOv8 object
                                                  // 創建 YOLOv8 對象
    YOLOV8_API void DestroyYOLOV8(void* yolov8);  // Destroy YOLOv8 object
                                                  // 銷毀 YOLOv8 對象
    YOLOV8_API void DetectYOLOV8(void* yolov8, unsigned char* image_data, int data_length, int width, int height); // Perform detection
                                                                                                                  // 執行檢測
    YOLOV8_API void GetDetectionsYOLOV8(void* yolov8, Detection* detections, int* num_detections); // Get detection results
                                                                                                  // 獲取檢測結果
}

// Define Resize struct
// 定義 Resize 結構體
struct Resize {
    cv::Mat resized_image; // Resized image
                           // 調整大小的圖像
    int dw;                // Padding width
                           // 填充寬度
    int dh;                // Padding height
                           // 填充高度
};

// Define YOLOV8 class
// 定義 YOLOV8 類
class YOLOV8 {
public:
    YOLOV8(Config config);  // Constructor
                            // 構造函數
    ~YOLOV8();              // Destructor
                            // 析構函數
    void detect(const unsigned char* image_data, int data_length, int width, int height); // Perform detection
                                                                                         // 執行檢測
    std::vector<Detection> getDetections() const; // Get detections
                                                  // 獲取檢測結果

private:
    float confThreshold;   // Detection confidence threshold
                           // 檢測置信度閾值
    float nmsThreshold;    // Non-maximum suppression threshold
                           // 非極大值抑制閾值
    float scoreThreshold;  // Score threshold
                           // 得分閾值
    int inpWidth;          // Input image width
                           // 輸入圖像寬度
    int inpHeight;         // Input image height
                           // 輸入圖像高度
    float rx;              // Width ratio of original image and resized image
                           // 原始圖像和調整大小圖像的寬度比例
    float ry;              // Height ratio of original image and resized image
                           // 原始圖像和調整大小圖像的高度比例
    std::string onnx_path; // Path to ONNX model
                           // ONNX 模型的路徑
    Resize resize;         // Resize struct instance
                           // Resize 結構體實例
    ov::Tensor input_tensor;        // Input tensor for model inference
                                    // 模型推理的輸入張量
    ov::InferRequest infer_request; // Inference request
                                    // 推理請求
    ov::CompiledModel compiled_model; // Compiled model
                                      // 編譯後的模型
    std::vector<Detection> detections; // Vector to store detection results
                                       // 存儲檢測結果的向量
    void initialmodel(); // Initialize model
                         // 初始化模型
    void preprocess_img(const unsigned char* image_data, int data_length, int width, int height); // Preprocess image
                                                                                                  // 圖像預處理
    void postprocess_img(cv::Mat& frame, float* detections, ov::Shape& output_shape); // Postprocess image
                                                                                      // 圖像後處理
};
