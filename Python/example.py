import os
import ctypes
from ctypes import *

# 定義 Config 結構體
# Define the Config struct
class Config(Structure):
    _fields_ = [
        ("confThreshold", c_float),  # 檢測置信度閾值
                                     # Detection confidence threshold
        ("nmsThreshold", c_float),   # 非極大值抑制閾值
                                     # Non-maximum suppression threshold
        ("scoreThreshold", c_float), # 得分閾值
                                     # Score threshold
        ("inpWidth", c_int),         # 輸入圖像寬度
                                     # Input image width
        ("inpHeight", c_int),        # 輸入圖像高度
                                     # Input image height
        ("onnx_path", c_char_p)      # ONNX 模型路徑
                                     # Path to ONNX model
    ]

# 定義 Detection 結構體
# Define the Detection struct
class Detection(Structure):
    _fields_ = [
        ("class_id", c_int),         # 類別 ID
                                     # Class ID
        ("confidence", c_float),     # 置信度
                                     # Confidence
        ("box", c_int * 4)           # 檢測框，包含 x, y, 寬度和高度
                                     # Bounding box, representing x, y, width, height
    ]

def main():
    # 獲取當前腳本的絕對目錄
    current_dir = os.path.dirname(os.path.abspath(__file__))
    parent_dir = os.path.dirname(current_dir)
    
    # 設置 YOLOv8 配置
    # Set the configuration for YOLOv8
    config = Config(
        confThreshold=0.5,              # 檢測置信度閾值
        nmsThreshold=0.4,               # 非極大值抑制閾值
        scoreThreshold=0.3,             # 得分閾值
        inpWidth=640,                   # 輸入圖像寬度
        inpHeight=640,                  # 輸入圖像高度
        onnx_path=os.path.join(parent_dir, "Models/yolov8n.onnx").encode()  # ONNX 模型路徑，使用相對路徑
    )

    # 加載 DLL
    # Load the DLL
    dll_path = os.path.join(parent_dir, "DLL/YOLOv8_SDK.dll")
    yolov8_dll = ctypes.CDLL(dll_path)

    # 定義函數原型
    # Define function prototypes
    yolov8_dll.CreateYOLOV8.restype = c_void_p
    yolov8_dll.CreateYOLOV8.argtypes = [Config]

    yolov8_dll.DestroyYOLOV8.restype = None
    yolov8_dll.DestroyYOLOV8.argtypes = [c_void_p]

    yolov8_dll.DetectYOLOV8.restype = None
    yolov8_dll.DetectYOLOV8.argtypes = [c_void_p, POINTER(c_ubyte), c_int, c_int, c_int]

    yolov8_dll.GetDetectionsYOLOV8.restype = None
    yolov8_dll.GetDetectionsYOLOV8.argtypes = [c_void_p, POINTER(Detection), POINTER(c_int)]

    # 創建 YOLOv8 對象
    # Create YOLOv8 object
    yolov8 = yolov8_dll.CreateYOLOV8(config)

    # 讀取圖像並轉換為字節數組
    # Read image and convert to bytes
    image_path = os.path.join(parent_dir, "TestImages/bus.jpg")
    with open(image_path, "rb") as f:
        image_data = f.read()
    image_data = (c_ubyte * len(image_data)).from_buffer_copy(image_data)

    # 執行檢測
    # Perform detection
    yolov8_dll.DetectYOLOV8(yolov8, image_data, len(image_data), 810, 1080)  # (width, height) 為圖片原始尺寸

    # 獲取檢測結果
    # Get detection results
    max_detections = 100  # 最大檢測數量
    detections = (Detection * max_detections)()  # 創建一個存儲檢測結果的數組
    num_detections = c_int(0)  # 實際檢測數量
    yolov8_dll.GetDetectionsYOLOV8(yolov8, detections, byref(num_detections))  # 調用函數獲取檢測結果

    # 打印檢測結果
    # Print detection results
    for i in range(num_detections.value):
        detection = detections[i]
        print(f"Class ID: {detection.class_id}, Confidence: {detection.confidence}, Box: ({detection.box[0]}, {detection.box[1]}, {detection.box[2]}, {detection.box[3]})")

    # 銷毀 YOLOv8 對象
    # Destroy YOLOv8 object
    yolov8_dll.DestroyYOLOV8(yolov8)

if __name__ == "__main__":
    main()
