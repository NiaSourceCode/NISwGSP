# Natural Image Stitching with the Global Similarity Prior

Ubuntu:
[![Build Status](https://www.travis-ci.org/Yannnnnnnnnnnn/NISwGSP.svg?branch=master)](https://www.travis-ci.org/Yannnnnnnnnnnn/NISwGSP)

- [Project page](http://www.cmlab.csie.ntu.edu.tw/project/stitching-wGSP/)
- [Paper](http://www.cmlab.csie.ntu.edu.tw/project/stitching-wGSP/ECCV-2016-NISwGSP.pdf)
- [Supplementary](http://www.cmlab.csie.ntu.edu.tw/project/stitching-wGSP/ECCV-2016-NISwGSP-supplementary-material.pdf)

### Download

1. [Poster](http://www.cmlab.csie.ntu.edu.tw/project/stitching-wGSP/Poster.pdf), [Short Presentation](http://www.cmlab.csie.ntu.edu.tw/project/stitching-wGSP/Short-Presentation.pdf) and [Thesis Presentation](http://www.cmlab.csie.ntu.edu.tw/project/stitching-wGSP/Thesis-Presentation.pdf)
2. [Paper](http://www.cmlab.csie.ntu.edu.tw/project/stitching-wGSP/ECCV-2016-NISwGSP.pdf)
3. [Supplementary](http://www.cmlab.csie.ntu.edu.tw/project/stitching-wGSP/ECCV-2016-NISwGSP-supplementary-material.pdf)
	* We tested four state-of-the-art methods and ours on 42 sets of images in same setting (grid size, feature points and parameters).
4. [Input-42-data](http://www.cmlab.csie.ntu.edu.tw/project/stitching-wGSP/input-42-data.zip)
5. [All our results](http://www.cmlab.csie.ntu.edu.tw/project/stitching-wGSP/0_results.zip)

### Usage

1. Download code and compile.
	* You need **Eigen**, **VLFeat**, **OpenCV 3.0.0** and [**OpenMP**](https://github.com/nothinglo/NISwGSP/issues/8) (if you don't need to use omp.h, you can ignore it.)
	* My GCC_VRSION is Apple LLVM 6.0
	```
	GCC_C_LANGUAGE_STANDARD = GNU99 [-std=gnu99]
	CLANG_CXX_LANGUAGE_STANDARD = GNU++14 [-std=gnu++14]
	CLANG_CXX_LIBRARY = libc++ (LLVM C++ standard library with C++11 support)
	```
	* My Eigen version is 3.2.7 (development branch). You need to make sure you can use "LeastSquaresConjugateGradient" class.
	
2. Download [input-42-data](http://www.cmlab.csie.ntu.edu.tw/project/stitching-wGSP/input-42-data.zip). 
	* 42 sets of images: 6 from [1], 3 from [2], 3 from [3], 7 from [4], 4 from [5] and 19 collected by ourselves.
	
3. Move **[input-42-data]** folder to your working directory(the working directory is where the executable file is).
![workding](https://github.com/Yannnnnnnnnnnn/NISwGSP/blob/master/UglyMan_NISwGSP_Stitching/UglyMan_NISwGSP_Stitching/Screenshot%20from%202017-12-27%2022-27-39.bmp)
4. Run the command:

	```
	./exe folder_name_in_[input-42-data]_folder
	```
  example:
  
  	```
	./NISwGSP AANAP-building
	```
	
The results can be found in **[0_results]** folder under **[input-42-data]** folder.




![exe](https://github.com/Yannnnnnnnnnnn/NISwGSP/blob/master/UglyMan_NISwGSP_Stitching/UglyMan_NISwGSP_Stitching/Screenshot%20from%202017-12-27%2022-28-08.bmp)


5. Optional:
	* You can control the parameters in **Configure.h** or **xxx-STITCH-GRAPH.txt**

### Results

For More Results please look to https://github.com/nothinglo/NISwGSP


