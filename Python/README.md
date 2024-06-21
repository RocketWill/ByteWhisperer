# YOLOv8 Object Detection SDK

This repository provides an example of integrating YOLOv8 DLL for object detection using Python ctypes. It demonstrates how to configure and use the YOLOv8 SDK for real-time object detection tasks.

## Requirements

- Python 3.x
- Windows operating system (for DLL usage)

## Installation

2. Install dependencies:

   ```
   pip install -r requirements.txt
   ```

## Usage

1. Set up the configuration in `example.py`:

   ```python
   # Configure YOLOv8
   config = Config(
       confThreshold=0.5,
       nmsThreshold=0.4,
       scoreThreshold=0.3,
       inpWidth=640,
       inpHeight=640,
       onnx_path=os.path.join(parent_dir, "Models/yolov8n.onnx").encode()
   )
   ```

2. Run the main script to perform object detection:

   ```
   python example.py
   ```

## Structure

- `example.py`: Main script demonstrating YOLOv8 DLL integration and object detection.
- `DLL/`: Directory containing YOLOv8 SDK DLL files.
- `Models/`: Directory for storing ONNX model files.
- `TestImages/`: Directory containing sample images for testing.
