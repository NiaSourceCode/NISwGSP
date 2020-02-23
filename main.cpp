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

    /*
    const int CIRCLE_RADIUS    = 3;
    const int CIRCLE_THICKNESS = 1;
    const int LINE_THICKNESS   = 1;
    const int RGB_8U_RANGE     = 256;

    // TODO 匹配点配对
    vector<Point2> f1, f2;
    RED("%ld", multi_images.images_data.size());
    Mat result = Mat::zeros(multi_images.images_data[0].img.rows,
                            multi_images.images_data[0].img.cols,
                            CV_8UC3);
    multi_images.doFeatureMatching();
    // RED("%ld", multi_images.apap_matching_points.size());// 和图片数相等
    RED("%ld %ld", multi_images.apap_overlap_mask[0][1].size(),
                   multi_images.apap_overlap_mask[1][0].size());
    RED("%ld %ld", multi_images.apap_homographies[0][1].size(),
                   multi_images.apap_homographies[1][0].size());
    RED("%ld %ld", multi_images.apap_matching_points[0][1].size(),
                   multi_images.apap_matching_points[1][0].size());
    for (int i = 0; i < multi_images.apap_matching_points[0][1].size(); i ++) {
      f1.emplace_back(multi_images.apap_matching_points[0][1][i]);
    }

    // TODO 描绘匹配点
    multi_images.images_data[0].img.copyTo(result);
    for (int i = 0; i < f1.size(); i ++) {
      Scalar color(255, 0, 0);
      circle(result, f1[i], CIRCLE_RADIUS, color, -1);
    }
    imwrite(multi_images.parameter.debug_dir + "fuck.png", result);
    */

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
