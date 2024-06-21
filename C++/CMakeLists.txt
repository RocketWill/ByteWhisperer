cmake_minimum_required(VERSION 3.15)
project(YOLOv8Example)

# 設置 C++ 標準
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 加載 Conan 生成的檔案
include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup()

# 添加可執行檔
add_executable(yolov8_example example.cpp)

# 連結 OpenCV 庫和 YOLOv8 導出庫
target_link_libraries(yolov8_example ${CONAN_LIBS})

# 包含目錄
target_include_directories(yolov8_example PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 複製 DLL 檔案到構建目錄
file(GLOB DLL_FILES "${CMAKE_SOURCE_DIR}/../DLL/*.dll")
foreach(DLL ${DLL_FILES})
    add_custom_command(TARGET yolov8_example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${DLL}" $<TARGET_FILE_DIR:yolov8_example>)
endforeach()