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
    NISwGSP_Stitching niswgsp(multi_images);
    niswgsp.setWeightToAlignmentTerm(1);
    niswgsp.setWeightToLocalSimilarityTerm(0.75);
    niswgsp.setWeightToGlobalSimilarityTerm(6, 20, GLOBAL_ROTATION_2D_METHOD);
    // niswgsp.writeImage(niswgsp.solve(BLEND_AVERAGE), BLENDING_METHODS_NAME[BLEND_AVERAGE]);
    Mat result_linear = niswgsp.solve(BLEND_LINEAR);
    niswgsp.writeImage(result_linear,  BLENDING_METHODS_NAME[BLEND_LINEAR]);

    /** 
     * TODO
     */

    const vector<pair<int, int> > & images_match_graph_pair_list = multi_images.parameter.getImagesMatchGraphPairList();
    for (int i = 0; i < images_match_graph_pair_list.size(); i ++) {
      const pair<int, int> & match_pair = images_match_graph_pair_list[i];
      const int m1 = match_pair.first;
      const int m2 = match_pair.second;
      const vector<detail::MatchesInfo> & pairwise_matches = multi_images.getPairwiseMatchesByMatchingPoints();
      // 绘制矩阵
      Mat img1 = multi_images.images_data[m1].img;
      Mat img2 = multi_images.images_data[m2].img;
      Mat result = Mat::zeros(max(img1.rows, img2.rows), img1.cols + img2.cols, CV_8UC3);
      Mat left (result, Rect(0, 0, img1.cols, img1.rows));
      Mat right(result, Rect(img1.cols, 0, img2.cols, img2.rows));
      img1.copyTo(left);
      img2.copyTo(right);
      // 获取匹配信息
      const int pm_index = m1 * (int)multi_images.images_data.size() + m2;
      for (int j = 0; j < pairwise_matches[pm_index].matches.size(); j ++) {
        DMatch my_match = pairwise_matches[pm_index].matches[j];
        int src = my_match.queryIdx;
        int dest = my_match.trainIdx;
        int num = my_match.imgIdx;
        // CYAN("[%d %d %d %d]", j, src, dest, num);
      }
    }

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
