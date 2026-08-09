# Python `ctypes` integration

This example maps the native YOLOv8 SDK interface into Python with `ctypes`. It defines compatible configuration and detection structures, assigns explicit function signatures, transfers encoded image bytes, and converts the native result buffer into Python-readable values.

## Requirements

- Windows x64
- Python 3
- `YOLOv8_SDK.dll` and its runtime dependencies in `../DLL`
- A compatible YOLOv8 ONNX model

Install the only third-party Python dependency:

```powershell
pip install -r requirements.txt
```

`ctypes` is part of the Python standard library. Pillow is used only to read the original image dimensions passed to the SDK.

## Run

From the repository root:

```powershell
python Python\example.py
```

The default model and image are `Models/yolov8n.onnx` and `TestImages/bus.jpg`. Both paths can be overridden:

```powershell
python Python\example.py path\to\model.onnx path\to\image.jpg
```

The script prints the class ID, confidence value, and bounding box returned for each detection.

## Integration notes

- Keep each `_fields_` declaration aligned with the native structure order and field width.
- Set both `argtypes` and `restype`; relying on `ctypes` defaults can truncate pointers on a 64-bit process.
- Build and run Python with the same x64 architecture as the native DLL.
- Always call `DestroyYOLOV8` for a successfully created handle.
- The current SDK interface uses a fixed result buffer in the example. Review the capacity contract before adapting it to unbounded inputs.
