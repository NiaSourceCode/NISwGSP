//
//  main.cpp
//  UglyMan_Stitching
//
//  Created by uglyman.nothinglo on 2015/8/15.
//  Copyright (c) 2015 nothinglo. All rights reserved.
//

#include <iostream>
#include "./Stitching/NISwGSP_Stitching.h"
#include "./Debugger/TimeCalculator.h"

using namespace std;

int main(int argc, const char * argv[]) {
  Eigen::initParallel(); /* remember to turn off "Hardware Multi-Threading */
  cout << "nThreads = " << Eigen::nbThreads() << endl;
  cout << "[#Images : " << argc - 1 << "]" << endl;

  TimeCalculator timer;
  for(int i = 1; i < argc; ++i) {
    cout << "i = " << i << ", [Images : " << argv[i] << "]" << endl;
    MultiImages multi_images(argv[i], LINES_FILTER_WIDTH, LINES_FILTER_LENGTH);

    timer.start();
    /* 2D */
    // NISwGSP_Stitching niswgsp(multi_images);
    // niswgsp.setWeightToAlignmentTerm(1);
    // niswgsp.setWeightToLocalSimilarityTerm(0.75);
    // niswgsp.setWeightToGlobalSimilarityTerm(6, 20, GLOBAL_ROTATION_2D_METHOD);
    // // niswgsp.writeImage(niswgsp.solve(BLEND_AVERAGE), BLENDING_METHODS_NAME[BLEND_AVERAGE]);
    // Mat result_linear = niswgsp.solve(BLEND_LINEAR);
    // niswgsp.writeImage(result_linear,  BLENDING_METHODS_NAME[BLEND_LINEAR]);

    /** 
     * TODO
     */

    const int CIRCLE_RADIUS    = 3;
    const int CIRCLE_THICKNESS = 1;
    const int LINE_THICKNESS   = 1;
    const int RGB_8U_RANGE     = 256;

    RED("%ld", multi_images.apap_matching_points.size());// 和图片数相等
    RED("%ld %ld", multi_images.apap_matching_points[0][1].size()
        , multi_images.apap_matching_points[1][0].size());

    // TODO 匹配点配对
    vector<Point2> f1, f2;
    long my_pair_size = min(multi_images.apap_matching_points[1][0].size(), multi_images.apap_matching_points[0][1].size());
    f1.reserve(my_pair_size);
    f2.reserve(my_pair_size);
    Mat img1 = multi_images.images_data[0].img;
    Mat img2 = multi_images.images_data[1].img;
    for (int i = 0; i < my_pair_size; i ++) {
      f1.emplace_back(multi_images.apap_matching_points[0][1][i]);
      f2.emplace_back(multi_images.apap_matching_points[1][0][i]);
    }
    Mat my_matching_pairs = getImageOfFeaturePairs(img1, img2, f1, f2);

    // TODO 描绘匹配点
    Mat result = Mat::zeros(result_linear.rows, result_linear.cols, CV_8UC3);
    Mat img_8UC3;
    if (result_linear.type() == CV_8UC3) {
      img_8UC3 = result_linear;
    } else {
      result_linear.convertTo(img_8UC3, CV_8UC3);
    }
    img_8UC3.copyTo(result);// 将图片复制到结果Mat
    for (int i = 0; i < f1.size(); i ++) {
      Scalar color(255, 0, 0);
      circle(result, f1[i], CIRCLE_RADIUS, color, -1);
      circle(result, f2[i], CIRCLE_RADIUS, color, -1);
    }

    imwrite(multi_images.parameter.debug_dir + "fuck.png", result);
    RED("%ld", my_pair_size);

    /**
     *  TODO end
     */

    /* 3D */
    // niswgsp.setWeightToAlignmentTerm(1);
    // niswgsp.setWeightToLocalSimilarityTerm(0.75);
    // niswgsp.setWeightToGlobalSimilarityTerm(6, 20, GLOBAL_ROTATION_3D_METHOD);
    // niswgsp.writeImage(niswgsp.solve(BLEND_AVERAGE), BLENDING_METHODS_NAME[BLEND_AVERAGE]);
    // niswgsp.writeImage(niswgsp.solve(BLEND_LINEAR),  BLENDING_METHODS_NAME[BLEND_LINEAR]);
    timer.end("[NISwGSP] " + multi_images.parameter.file_name);
  }
  return 0;
}
