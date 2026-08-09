# C# P/Invoke integration

This example calls the native YOLOv8 SDK from .NET Framework through P/Invoke. It covers sequential structure layout, native function declarations, encoded image transfer, unmanaged result buffers, and cleanup.

## Requirements

- Windows x64
- Visual Studio with .NET Framework 4.7.2 support
- Release/x64 build configuration
- `YOLOv8_SDK.dll` and its runtime dependencies beside the executable or on the Windows DLL search path
- A compatible YOLOv8 ONNX model

## Build and run

1. Open `CSharp.sln` in Visual Studio.
2. Restore NuGet packages.
3. Select **Release** and **x64**.
4. Build and run the application.

The executable resolves the repository's sample model and image by default. Optional paths can be passed on the command line:

```powershell
CSharp.exe path\to\model.onnx path\to\image.jpg
```

## Integration notes

- `[StructLayout(LayoutKind.Sequential)]` must match the field order and widths used by the native SDK.
- `CallingConvention.Cdecl` must remain consistent with the exported functions.
- Use an x64 process. Loading an x64 DLL from an AnyCPU or x86 process will fail.
- Release buffers allocated with `Marshal.AllocHGlobal`, even when native calls fail.
- Destroy every successfully created SDK handle.
- The current result interface does not accept a destination-buffer capacity. Treat the fixed 100-element allocation as part of this example's SDK contract, not a general safety guarantee.
