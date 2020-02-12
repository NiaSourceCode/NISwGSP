# Natural Image Stitching with the Global Similarity Prior

## [Origin Manual](./origin.md)

## 新说明

### 编译

1. 在`vlfeat-{版本号}/`下`make`
2. use the CMake to configure the project and make sure set the VLFEAT_LIBRARY with the "./vlfeat-0.9.20/bin/(the name depend on you system)/libvl"
3. mkdir build 
4. cd build && cmake .. && make 
5. BE AWARE THE DEAFULT BUILD-TYPE IS "debug"

### 常见问题

1. `vlfeat`编译失败

```
vl/mathop.h:92:37: error: ‘vl_infinity_d’ not specified in enclosing ‘parallel’
   92 | #define VL_INFINITY_D (vl_infinity_d.value)
```

解决:
