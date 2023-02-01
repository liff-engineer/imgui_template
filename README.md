# `imgui`样板工程

用来在`Windows`环境下快速创建基于[`Hello ImGui`](https://github.com/pthom/hello_imgui)的`C++`应用程序，已集成了：
- [`Dear ImGui`](https://github.com/ocornut/imgui)
- [`Hello ImGui`](https://github.com/pthom/hello_imgui)
- [`Node Editor in ImGui`](https://github.com/thedmd/imgui-node-editor)

## 为什么要做这个样板

- 所在地区间歇性无法正常访问`github`，不能使用现有的其它方案，譬如`Hello ImGui`虽然可以直接配置完成，但是会卡在从`github`拉取依赖的过程中；
- `Node Editor in ImGui`无法正常支持中文输入；
- `Hello ImGui`的特性相对`Dear ImGui`丰富，更适合用来学习和开发应用程序。

## 使用方式

### 1. 调整`external`目录下第三方库下载配置

例如`external/imgui/CMakeLists.txt`：

```C++
include(FetchContent)
include(CMakePrintHelpers)

if(NOT TARGET imgui)
    FetchContent_Declare(
        imgui
        URL "ftp://yourhost/imgui-docking.zip"
        URL_HASH SHA512=4dae3e090f3c68148de1b37084047e0b985d8d0c92d07a0b0d05c18c714eaef273f0be7e87135aadf5da64bc7918343b5578097c480d8eef0a87e64be04a5c1f
        DOWNLOAD_NAME "imgui-docking.zip"
        DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/external/downloads/imgui  
    )
```

修改`FetchContent_Declare`为适合场景的配置，例如：

1. 为避免每次都联网下载，可将对应的`imgui-docking.zip`从`github`下载好，计算出`SHA512`，然后存放于内部的`ftp`服务器上；
2. 在某些地区无法正常访问`github`，可以通过特殊方式下载到`imgui-docking.zip`，计算出`SHA512`，然后存放为`external/downloads/imgui/imgui-docking.zip`，从而无需联网直接可用；
3. 对`imgui`源码进行了修改，可存放于特定位置，使用自己的版本。

采用类似的方式将所有第三方库调整完成。

### 2. 进行`CMake`配置并构建

确保本地安装了`CMake`、`Visual Studio 2019`或以上版本，然后在源码目录命令行执行：

```bash
cmake -B build 
```

从而在`build`目录生成`imgui_template.sln`，打开后构建运行`hello_world`等示例。

## 开箱即用的分支

在`just_make_it`分支上附带了第三方库源码包，可以不修改第三方库下载配置，直接构建运行

## 注意事项

- 由于[`Node Editor in ImGui`](https://github.com/thedmd/imgui-node-editor)使用的[`Dear ImGui`](https://github.com/ocornut/imgui)为修改版本，会构建不过，可参考`external/imgui-node-editor/README.md`进行修改；
- [`Hello ImGui`](https://github.com/pthom/hello_imgui)使用了[`Dear ImGui`](https://github.com/ocornut/imgui)的`docking`支持分支，注意下载匹配的分支。
- 示例代码使用了[LXGW Bright](https://github.com/lxgw/LxgwBright)字体以支持中文显示，在`assets`目录下存放了该字体；
- 可以采用类似的方法添加第三方库，或者修改为`Linux`等平台也支持的工程；
- 目前资源文件在`assets`目录下，只有`hello_world`工程会拷贝，单独编译其它示例会因为资源文件未拷贝而报错，可以全部构建来解决，或者为对应工程添加资源拷贝指令。
