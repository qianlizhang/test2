cmake_minimum_required(VERSION 3.10)
project(RationalVue) 

# cmake模块的目录
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}") 

# C++14
set(CMAKE_CXX_STANDARD 14)
# 禁止MSVC的wd4996警告
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")  

option (WNT "Use WNT" ON)
add_definitions("-DWNT")


# QT
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed 
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON) 

find_package(Qt5 5.9 COMPONENTS Core Gui Widgets Sql Multimedia MultimediaWidgets UiTools Designer CONFIG  REQUIRED)

# OpenCV
find_package(OpenCV 3.4.3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) 

# glog
find_package(Glog REQUIRED)
include_directories(${GLOG_INCLUDE_DIRS})

# HCNetSDK
#find_package(HCNet REQUIRED)
#include_directories(${HCNET_INCLUDE_DIRS})
include_directories(HCNetSDK/include) 
file(GLOB_RECURSE HKV_LIBS ${PROJECT_SOURCE_DIR}/HCNetSDK/lib/*.lib)

# UWC
include_directories(UWC/include)
file(GLOB_RECURSE UWC_LIBS ${PROJECT_SOURCE_DIR}/UWC/lib/*.lib)


# MySQL
include_directories(MySQL/include)
file(GLOB_RECURSE MYSQL_LIBS ${PROJECT_SOURCE_DIR}/MySQL/lib/*.lib)

#TTS
include_directories(TTS/include)
file(GLOB_RECURSE TTS_LIBS ${PROJECT_SOURCE_DIR}/TTS/libs/*.lib)

#Opencl
include_directories(OpenCL/include)
file(GLOB_RECURSE OPENCL_LIBS ${PROJECT_SOURCE_DIR}/OpenCL/lib/x64/*.lib)

# 3rdparty
# file(GLOB 3RDPARTY_FILES 3rdparty/json.hpp 3rdparty/tts.h)
file(GLOB 3RDPARTY_FILES 3rdparty/*.hpp 3rdparty/*.h)
include_directories(3rdparty)
source_group("3rdparty" FILES ${3RDPARTY_FILES})

#camera
file(GLOB CAMERA_FILES camera/*.h camera/*.hpp camera/*.cpp)
include_directories(camera)
source_group("Camera" FILES ${CAMERA_FILES})

# gui
#WindowNotation文件
file(GLOB WindowNotation_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/WindowNotation/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/WindowNotation/)

#LightControl文件
file(GLOB LightControl_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/LightControl/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/LightControl/)

#MenuBarZone文件
file(GLOB MenuBarZone_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/MenuBarZone/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/MenuBarZone/)

#DataZoneLeft文件
file(GLOB DataZoneLeft_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/DataZoneLeft/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/DataZoneLeft/)

#DataZoneRight文件
file(GLOB DataZoneRight_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/DataZoneRight/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/DataZoneRight/)

#DimensionReportZone文件
file(GLOB DimensionReportZone_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/DimensionReportZone/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/DimensionReportZone/)

#GraphiceZone文件
file(GLOB GraphiceZone_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/GraphiceZone/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/GraphiceZone/)

#OperationZoneLeft文件
file(GLOB OperationZoneLeft_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/OperationZoneLeft/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/OperationZoneLeft/)
#OperationZoneRight文件
file(GLOB OperationZoneRight_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/OperationZoneRight/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/OperationZoneRight/)


#PaintZone文件
file(GLOB PaintZone_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/PaintZone/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/PaintZone/)
#MachineStatusZone文件
file(GLOB MachineStatusZone_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/MachineStatusZone/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/MachineStatusZone/)
#StatusBarZone文件
file(GLOB StatusBarZone_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/StatusBarZone/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/StatusBarZone/)

#MainWindow文件
file(GLOB MainWindow_FILES ${CMAKE_CURRENT_SOURCE_DIR}/GUI/MainWindow/*.*)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/GUI/MainWindow/)

file(GLOB ALL_GUI_FILES ${MenuBarZone_FILES} ${DataZoneLeft_FILES} ${DataZoneRight_FILES} ${DimensionReportZone_FILES}
		${GraphiceZone_FILES} ${OperationZoneLeft_FILES} ${OperationZoneRight_FILES} ${PaintZone_FILES} ${MachineStatusZone_FILES} 
		${StatusBarZone_FILES} ${MainWindow_FILES}
		${LightControl_FILES} ${WindowNotation_FILES}
	)
source_group("GUI/MenuBarZone" FILES ${MenuBarZone_FILES})
source_group("GUI/DataZoneLeft" FILES ${DataZoneLeft_FILES})
source_group("GUI/DataZoneRight" FILES ${DataZoneRight_FILES})
source_group("GUI/DimensionReportZone" FILES ${DimensionReportZone_FILES})
source_group("GUI/GraphiceZone" FILES ${GraphiceZone_FILES})
source_group("GUI/OperationZoneLeft" FILES ${OperationZoneLeft_FILES})
source_group("GUI/OperationZoneRight" FILES ${OperationZoneRight_FILES})
source_group("GUI/MachineStatusZone" FILES ${MachineStatusZone_FILES})
source_group("GUI/StatusBarZone" FILES ${StatusBarZone_FILES})
source_group("GUI/MainWindow" FILES ${MainWindow_FILES})
source_group("GUI/LightControl" FILES ${LightControl_FILES})
source_group("GUI/PaintZone" FILES ${PaintZone_FILES})
source_group("GUI/WindowNotation" FILES ${WindowNotation_FILES})
source_group("GUI/PaintZone" FILES ${PaintZone_FILES})


#common
file(GLOB COMMON_FILES common/*.h common/*.cpp)
include_directories(common)
source_group("Common" FILES ${COMMON_FILES})

# network
#file(GLOB NETWORK_FILES network/*.h network/*.hpp network/*.cpp)
#include_directories(network)
#source_group("Network" FILES ${NETWORK_FILES})

#db
file(GLOB DB_FILES db/*.h network/*.hpp db/*.cpp)
include_directories(db)
source_group("DB" FILES ${DB_FILES})

#Detect
file(GLOB DETECT_FILES detect/*.h detect/*.hpp detect/*.cpp)
include_directories(detect)
source_group("DETECT" FILES ${DETECT_FILES})

# source
file(GLOB HEADERS *.h *.hpp)
# source_group("Header Files" FILES ${HEADERS}) 

#aux_source_directory(. SRC_FILES) 

# exec
add_executable(${PROJECT_NAME} main.cpp common.cpp syscontroller.cpp uwc.cpp  ${HEADERS} ${3RDPARTY_FILES} ${CAMERA_FILES} ${ALL_GUI_FILES} ${DB_FILES} ${DETECT_FILES} ${COMMON_FILES} mainResource.qrc)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${GLOG_LIBRARIES} ${HCNET_LIBRARIES} ${HKV_LIBS} ${MYSQL_LIBS} ${TTS_LIBS} ${OPENCL_LIBS} ${UWC_LIBS} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Sql Qt5::Multimedia Qt5::MultimediaWidgets Qt5::UiTools Qt5::Designer)
# 设置执行的管理员权限
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")


# dlls
function(copy_to_target_dir name)
    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${name} $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endfunction()

file(GLOB_RECURSE DLL_FILES ${PROJECT_SOURCE_DIR}/MySQL/lib/*.dll ${PROJECT_SOURCE_DIR}/UWC/lib/*.dll)
foreach(dll ${DLL_FILES})
    copy_to_target_dir(${dll})
endforeach()
