# YOLOv8 Object Detection SDK

This readme provides instructions on setting up and running a C# demo application using the YOLOv8 DLL for object detection.

## Requirements

1. **Environment Setup**
   - Ensure your environment meets the following requirements:
     ```xml
     <?xml version="1.0" encoding="utf-8"?>
     <packages>
       <package id="System.Drawing.Common" version="8.0.6" targetFramework="net472" />
       <package id="System.Drawing.Primitives" version="4.3.0" targetFramework="net472" />
     </packages>
     ```
   - Your project must target .NET Framework 4.7.2 and must be compiled for **x64 Release** mode.

2. **YOLOv8 SDK and Dependencies**
   - Obtain the YOLOv8 SDK DLL (`YOLOv8_SDK.dll`) and any other necessary DLLs required for object detection. Place these DLL files in the same directory as your application's executable (`exe`).

## Configuration

### Model Setup
- **ONNX Model**: 
  - Ensure you have an ONNX model file prepared for YOLOv8. Update the `onnx_path` parameter in the `Config` struct (`Config.onnx_path`) to reflect the path to your specific ONNX model file.

### Config Struct

The `Config` struct is used to configure YOLOv8 parameters:
- `confThreshold`: Detection confidence threshold
- `nmsThreshold`: Non-maximum suppression threshold
- `scoreThreshold`: Score threshold
- `inpWidth`: Input image width
- `inpHeight`: Input image height
- `onnx_path`: Path to the ONNX model file

Modify these parameters according to your model's requirements.

## Notes

- Ensure that all relevant DLL files (`YOLOv8_SDK.dll` and others) are placed in the same directory as your application's executable (`exe`).
- Verify that the paths (`onnx_path`, image paths) specified in the configuration match your actual file locations.
- Customize parameters and handle exceptions according to your application's requirements.
- Ensure proper management of unmanaged resources (`IntPtr`, memory allocations) to prevent memory leaks. 