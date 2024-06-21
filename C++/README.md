# YOLOv8 Object Detection SDK

This repository provides an example of integrating YOLOv8 DLL for object detection using C++. It demonstrates how to configure and use the YOLOv8 SDK for real-time object detection tasks.

## Requirements
- Windows 64-bit operating system
- C++ Compiler
- Conan Package Manager
- CMake 3.15 or higher
- OpenCV 4.8.1
- OpenVINO 2023.1.0

## Installation

1. **Install Dependencies with Conan:**

   Ensure Conan is installed and configured.

   ```bash
   mkdir build && cd build
   conan install .. --install-folder=.
   ```

   This command installs the required dependencies (`opencv`, `openvino`) and generates the necessary `CMake` configuration files in the `build` directory.

## Building the Project

1. **Configure with CMake:**

   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Release
   ```

   This command configures the project with CMake for Release mode.

2. **Build the Project:**

   ```bash
   cmake --build . --config Release
   ```

   This command builds the project in `Release` mode, linking with the dependencies installed by Conan (`opencv`, `openvino`).

## Running the Application

1. **Execute the Application:**

   After building successfully, you can run the executable:

   ```bash
   cd bin
   ./yolov8_example.exe
   ```

   This runs the YOLOv8 object detection on the provided image (`bus.jpg`) located in the `TestImages` directory.

2. **Viewing Results:**

   The application will display the detected objects overlaid on the input image using OpenCV's graphical interface.

## Troubleshooting

- **DLL Loading Issues:**
  If encountering "Unable to load YOLOv8_SDK.dll" errors, ensure the DLL is located correctly in relation to the executable or specify the full path.
