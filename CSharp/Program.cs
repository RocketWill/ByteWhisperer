using System;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;

class Program
{
    // Define Config struct
    // 定義 Config 結構體，用於配置 YOLOv8 的參數
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct Config
    {
        public float confThreshold;  // Detection confidence threshold
                                     // 檢測置信度閾值
        public float nmsThreshold;   // Non-maximum suppression threshold
                                     // 非極大值抑制閾值
        public float scoreThreshold; // Score threshold
                                     // 得分閾值
        public int inpWidth;         // Width of the input image
                                     // 輸入圖像的寬度
        public int inpHeight;        // Height of the input image
                                     // 輸入圖像的高度
        [MarshalAs(UnmanagedType.LPStr)]
        public string onnx_path;     // Path to the ONNX model file
                                     // ONNX 模型文件的路徑
    }

    // Define Detection struct
    // 定義 Detection 結構體，用於存儲檢測結果
    [StructLayout(LayoutKind.Sequential)]
    public struct Detection
    {
        public int class_id;         // Class ID
                                     // 類別 ID
        public float confidence;     // Confidence
                                     // 置信度
        public Rectangle box;        // Bounding box
                                     // 檢測框

        // Constructor to set default values
        // 構造函數，設置默認值
        public Detection(int class_id = -1, float confidence = -1.0f, Rectangle box = default)
        {
            this.class_id = class_id; // Set class ID
                                      // 設置類別 ID
            this.confidence = confidence; // Set confidence
                                          // 設置置信度
            this.box = box == default ? new Rectangle(0, 0, 0, 0) : box; // Set bounding box
                                                                         // 設置檢測框
        }
    }

    // Import functions from YOLOv8 DLL
    // 從 YOLOv8 DLL 中導入函數
    [DllImport("YOLOv8_SDK.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr CreateYOLOV8(Config config); // Create YOLOv8 object
                                                             // 創建 YOLOv8 對象

    [DllImport("YOLOv8_SDK.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void DestroyYOLOV8(IntPtr yolov8); // Destroy YOLOv8 object
                                                            // 銷毀 YOLOv8 對象

    [DllImport("YOLOv8_SDK.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void DetectYOLOV8(IntPtr yolov8, IntPtr image_data, int data_length, int width, int height); // Perform YOLOv8 detection
                                                                                                                      // 執行 YOLOv8 檢測

    [DllImport("YOLOv8_SDK.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void GetDetectionsYOLOV8(IntPtr yolov8, IntPtr detections, ref int num_detections); // Get YOLOv8 detections
                                                                                                             // 獲取 YOLOv8 檢測結果

    // Convert Bitmap to byte array
    // 將 Bitmap 轉換為字節數組
    public static byte[] BitmapToByteArray(Bitmap bitmap)
    {
        using (MemoryStream ms = new MemoryStream())
        {
            bitmap.Save(ms, ImageFormat.Png); // Save bitmap to memory stream
                                              // 將 bitmap 保存到內存流
            return ms.ToArray(); // Return byte array
                                 // 返回字節數組
        }
    }

    static void Main(string[] args)
    {
        // Configure YOLOv8 parameters
        // 配置 YOLOv8 參數
        Config config = new Config
        {
            confThreshold = 0.5f,  // Set confidence threshold
                                   // 設置置信度閾值
            nmsThreshold = 0.4f,   // Set NMS threshold
                                   // 設置非極大值抑制閾值
            scoreThreshold = 0.3f, // Set score threshold
                                   // 設置得分閾值
            inpWidth = 640,        // Set input width
                                   // 設置輸入寬度
            inpHeight = 640,       // Set input height
                                   // 設置輸入高度
            onnx_path = @"D:\workspace\ByteWhisperer\Models\yolov8n.onnx" // Set ONNX model path
                                                                         // 設置 ONNX 模型路徑
        };

        // Create YOLOv8 object
        // 創建 YOLOv8 對象
        IntPtr yolov8 = CreateYOLOV8(config);

        // Read image and convert to byte array
        // 讀取圖像並轉換為字節數組
        Bitmap bitmap = new Bitmap(@"D:\workspace\ByteWhisperer\TestImages\bus.jpg");
        byte[] imageData = BitmapToByteArray(bitmap);

        // Allocate unmanaged memory and copy image data
        // 分配非托管內存並複製圖像數據
        IntPtr unmanagedImageData = Marshal.AllocHGlobal(imageData.Length);
        Marshal.Copy(imageData, 0, unmanagedImageData, imageData.Length);

        // Call YOLOv8 detection
        // 調用 YOLOv8 檢測
        DetectYOLOV8(yolov8, unmanagedImageData, imageData.Length, bitmap.Width, bitmap.Height);

        // Get detection results
        // 獲取檢測結果
        int maxNumDetections = 100; // Maximum number of detections
                                    // 最大檢測數量
        int realNumDetection = 0;   // Actual number of detections
                                    // 實際檢測數量

        Detection[] detections = new Detection[maxNumDetections]; // Create array to hold detections
                                                                  // 創建數組以保存檢測結果
        IntPtr unmanagedDetections = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(Detection)) * maxNumDetections); // Allocate unmanaged memory for detections
                                                                                                                 // 分配非托管內存以保存檢測結果
        try
        {
            GetDetectionsYOLOV8(yolov8, unmanagedDetections, ref realNumDetection); // Get detections from YOLOv8
                                                                                    // 從 YOLOv8 獲取檢測結果

            // Copy detection results from unmanaged memory to managed array
            // 將檢測結果從非托管內存複製到托管數組
            for (int i = 0; i < maxNumDetections; i++)
            {
                IntPtr detectionPtr = new IntPtr(unmanagedDetections.ToInt64() + i * Marshal.SizeOf(typeof(Detection))); // Calculate pointer to each detection
                                                                                                                         // 計算每個檢測結果的指針
                detections[i] = Marshal.PtrToStructure<Detection>(detectionPtr); // Copy detection to managed array
                                                                                 // 將檢測結果複製到托管數組
            }

            // Print detection results
            // 打印檢測結果
            for (int i = 0; i < realNumDetection; ++i)
            {
                Console.WriteLine($"Class ID: {detections[i].class_id}, Confidence: {detections[i].confidence}, Box: {detections[i].box}");
                // 打印每個檢測結果的類別 ID、置信度和檢測框
            }
        }
        finally
        {
            // Free unmanaged memory
            // 釋放非托管內存
            Marshal.FreeHGlobal(unmanagedDetections);
        }

        // Free unmanaged memory
        // 釋放非托管內存
        Marshal.FreeHGlobal(unmanagedImageData);

        // Destroy YOLOv8 object
        // 銷毀 YOLOv8 對象
        DestroyYOLOV8(yolov8);
    }
}
