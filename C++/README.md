# C++ native integration

This example loads the YOLOv8 SDK dynamically with the Windows API. It resolves the exported symbols, configures an ONNX model, passes encoded image bytes to the SDK, reads detection structures, and renders the returned boxes with OpenCV.

## Requirements

- Windows x64
- C++14 compiler
- CMake 3.15 or newer
- Conan
- OpenCV 4.8.1
- OpenVINO 2023.1.0

## Configure and build

```powershell
mkdir build
cd build
conan install .. --install-folder=.
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

The CMake configuration copies the DLL files from the repository's `DLL` directory beside the example executable after a successful build.

## Run

Run `yolov8_example.exe` from the generated output directory. The example uses `Models/yolov8n.onnx` and `TestImages/bus.jpg`, prints each detection, and opens an OpenCV window with the predicted boxes.

## Integration notes

- Check every symbol returned by `GetProcAddress` before calling the SDK.
- Keep the application, SDK, runtime dependencies, and model architecture compatible with Windows x64.
- Match the exported calling convention and structure layout exactly.
- Release the inference handle before calling `FreeLibrary`.
- The current SDK interface returns detections through a caller-provided array without a capacity argument. Confirm the maximum-result contract before using the pattern with another model or workload.
