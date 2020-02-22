# Natural Image Stitching with the Global Similarity Prior

## [Origin Manual](./origin.md)

## 新说明

### 第三方库

- Vlfeat

在`vlfeat-{版本号}/`下`make`

- Eigen

```bash
sudo apt install libeigen3-dev
```

- OpenCV

将`OpenCVConfig.cmake`,`opencv-config.cmake`的路径添加到`OpenCV_DIR`

```bash
export OpenCV_DIR=$OpenCV_DIR:/home/lynx/fuck_mount/opencv/install_dir/3_4_5/share/OpenCV
```

### 编译

1. 准备第三方库
2. 原项目中在根目录(`NISwGSP/`下)包含`vlfeat-0.9.20/`文件夹,如要修改请记得修改相关配置文件(同时保证将`VLFEAT_LIBRARY`在`./vlfeat-0.9.20/bin/(the name depend on you system)/libvl`目录下)
3. `mkdir build `
4. `cd build && cmake .. && make`
5. BE AWARE THE DEAFULT BUILD-TYPE IS "debug"

### 常见问题

1. `vlfeat`编译失败

```
vl/mathop.h:92:37: error: ‘vl_infinity_d’ not specified in enclosing ‘parallel’
   92 | #define VL_INFINITY_D (vl_infinity_d.value)
```

解决: `/vl/kmeans.c`([参考](https://github.com/colmap/colmap/commit/6af3d8b0048cecc3b9fc6f4e78c3214dd038180b))

```cpp
// #pragma omp parallel default(none)
#pragma omp parallel \
```

### 使用

- 测试图片的相对路径设置在`Stitching/Parameter.cpp`设置
