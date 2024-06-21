# ByteWhisperer

ByteWhisperer is a multi-language example repository demonstrating how to use C++, Python, and C# to invoke YOLOv8 DLL for object detection. This repository does not contain any deep learning-related code, focusing instead on showcasing how to utilize dynamic-link libraries (DLLs) to achieve real-time object detection tasks across different programming languages and platforms.

## Key Features

- **C++ and Visual Studio**: Demonstrates how to compile and invoke YOLOv8 DLL.
- **Python and OpenCV**: Shows how to use Python to invoke YOLOv8 DLL for image processing and detection.
- **C# and .NET Framework**: Illustrates how to call YOLOv8 DLL using C# in a Windows environment.

## Installation Guide

### 1. Environment Setup

- **C++**:
  - Install a C++ compiler and Visual Studio.
  - Use CMake to compile the project.

- **Python**:
  - Install Python 3.x.
  - Install the required dependencies using `requirements.txt`:
    ```
    pip install -r requirements.txt
    ```

- **C#**:
  - Install .NET Framework 4.7.2 or higher.
  - Ensure the project is set to **x64 Release** mode for compilation.

### 2. Configure YOLOv8

- **Model File**:
  - Place the YOLOv8 model weights file (`yolov8n.onnx`) in the `Models` directory.
  - Modify the model path parameter in the code to point to the correct model file path.

- **DLL File**:
  - Ensure that all necessary DLL files, including YOLOv8.dll, are placed in the DLL directory.

## Usage Instructions

Each language's example code folder contains a corresponding `README.md` file with detailed instructions. Here are the basic usage steps:

1. **Compile and Run**:
   - Follow the instructions for the respective language to compile and run the example code.
   - Ensure all dependencies and configuration files are correctly set up.
