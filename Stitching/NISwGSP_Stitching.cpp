//
//  NISwGSP_Stitching.cpp
//  UglyMan_Stitching
//
//  Created by uglyman.nothinglo on 2015/8/15.
//  Copyright (c) 2015 nothinglo. All rights reserved.
//

#include "NISwGSP_Stitching.h"

NISwGSP_Stitching::NISwGSP_Stitching(const MultiImages & _multi_images) : MeshOptimization(_multi_images) {

}

void NISwGSP_Stitching::setWeightToAlignmentTerm(const double _weight) {
  MeshOptimization::setWeightToAlignmentTerm(_weight);
}

void NISwGSP_Stitching::setWeightToLocalSimilarityTerm(const double _weight) {
  MeshOptimization::setWeightToLocalSimilarityTerm(_weight);
}

void NISwGSP_Stitching::setWeightToGlobalSimilarityTerm(const double _weight_beta,
    const double _weight_gamma,
    const enum GLOBAL_ROTATION_METHODS _global_rotation_method) {
  MeshOptimization::setWeightToGlobalSimilarityTerm(_weight_beta, _weight_gamma, _global_rotation_method);
}

Mat NISwGSP_Stitching::solve(const BLENDING_METHODS & _blend_method) {
  const MultiImages & multi_images = getMultiImages();

  vector<Triplet<double> > triplets;
  vector<pair<int, double> > b_vector;

  reserveData(triplets, b_vector, DIMENSION_2D);// 初始化参数

  triplets.emplace_back(0, 0, STRONG_CONSTRAINT);
  triplets.emplace_back(1, 1, STRONG_CONSTRAINT);
  b_vector.emplace_back(0,    STRONG_CONSTRAINT);
  b_vector.emplace_back(1,    STRONG_CONSTRAINT);

  prepareAlignmentTerm(triplets);
  prepareSimilarityTerm(triplets, b_vector);

  vector<vector<Point2> > original_vertices;

  original_vertices = getImageVerticesBySolving(triplets, b_vector);

  Size2 target_size = normalizeVertices(original_vertices);

  Mat result = multi_images.textureMapping(original_vertices, target_size, _blend_method);

  /**
    * TODO
    */

  RED("%ld", original_vertices.size());

  int pm_index = 1;// TODO
  int m1 = 0, m2 = 1;
  Mat result_1;
  Mat img1 = multi_images.images_data[m1].img;
  Mat img2 = multi_images.images_data[m2].img;

  result.copyTo(result_1);
  for (int i = 0; i < multi_images.pairwise_matches[pm_index].matches.size(); i ++) {
    int src  = multi_images.pairwise_matches[pm_index].matches[i].queryIdx;
    int dest = multi_images.pairwise_matches[pm_index].matches[i].trainIdx;

    Point2 src_p = original_vertices[m1][src];
    // Point2 dest_p = multi_images.apap_matching_points[m2][m1][src];

    Scalar color(rand() % 256, rand() % 256, rand() % 256);
    Scalar color_1(255, 255, 0);
    Scalar color_2(0, 255, 255);
    circle(result_1, src_p, 3, color_1, -1);
    // line(result_1, src_p, dest_p + Point2(img1.cols, 0), color, 1, LINE_AA);
    // circle(result_1, dest_p + Point2(img1.cols, 0), 3, color_2, -1);
  }
  imwrite(multi_images.parameter.debug_dir + "mesh.jpg", result_1);

  /**
    * TODO
    */

#ifndef NDEBUG
  multi_images.writeResultWithMesh(result, original_vertices, "-[NISwGSP]" +
      GLOBAL_ROTATION_METHODS_NAME[getGlobalRotationMethod()] +
      BLENDING_METHODS_NAME[_blend_method] +
      "[Mesh]", false);
  multi_images.writeResultWithMesh(result, original_vertices, "-[NISwGSP]" +
      GLOBAL_ROTATION_METHODS_NAME[getGlobalRotationMethod()] +
      BLENDING_METHODS_NAME[_blend_method] +
      "[Border]", true);
#endif
  return result;
}

void NISwGSP_Stitching::writeImage(const Mat & _image, const string _post_name) const {
  const MultiImages & multi_images = getMultiImages();
  const Parameter & parameter = multi_images.parameter;
  string file_name = parameter.file_name;

  imwrite(parameter.result_dir + file_name + "-" +
      "[NISwGSP]" +
      GLOBAL_ROTATION_METHODS_NAME[getGlobalRotationMethod()] +
      _post_name +
      ".png", _image);
}
