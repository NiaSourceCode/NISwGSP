//
//  Parameter.cpp
//  UglyMan_Stitching
//
//  Created by uglyman.nothinglo on 2015/8/15.
//  Copyright (c) 2015 nothinglo. All rights reserved.
//

#include "Parameter.h"

bool isFileExist (const string & name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

Parameter::Parameter(const string & _file_name) {

  // file_name = _file_name;
  // file_dir = "./dataset/" + _file_name + "/";
  // result_dir = "./dataset/0_results/" + _file_name + "-result/";
  // 
  // mkdir("./dataset/0_results/", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
  // mkdir(result_dir.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
  file_name = _file_name;
  file_dir = "./dataset/" + _file_name + "/";
  result_dir = "./dataset/" + _file_name + "/result/";
  debug_dir =  "./dataset/" + _file_name + "/debug/";

  mkdir(result_dir.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
#ifndef NDEBUG
  // debug_dir = "./dataset/1_debugs/" + _file_name + "-result/";
  // mkdir("./dataset/1_debugs/", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
  mkdir(debug_dir.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
#endif

  stitching_parse_file_name = file_dir + _file_name + "-STITCH-GRAPH.txt";// TODO 没用

  /*** 需要手写 ***/
  images_count = 2;// 图片总数
  center_image_index = 0;// 以0开始
  center_image_rotation_angle = 0;
  assert(center_image_index >= 0 && center_image_index < images_count);
  char image_name[128];
  for (int i = 1; i <= images_count; i ++) {
    sprintf(image_name, "%d.jpg", i);
    image_file_full_names.emplace_back(image_name);
  }
  LOG("img num %d", images_count);

  /*** configure ***/
  grid_size = GRID_SIZE;
  down_sample_image_size = DOWN_SAMPLE_IMAGE_SIZE;

  /*** 来自于宏定义, 不需要手写 ***/
  global_homography_max_inliers_dist  = GLOBAL_HOMOGRAPHY_MAX_INLIERS_DIST;
  local_homogrpahy_max_inliers_dist   = LOCAL_HOMOGRAPHY_MAX_INLIERS_DIST;
  local_homography_min_features_count = LOCAL_HOMOGRAPHY_MIN_FEATURES_COUNT;

  images_match_graph_manually.resize(images_count);
  for (int i = 0; i < images_count; i ++) {
    images_match_graph_manually[i].resize(images_count, false);
  }
  for (int i = 1; i < images_count; i ++) {
    images_match_graph_pair_list.emplace_back(i - 1, i);
    images_match_graph_manually[i - 1][i] = true;
  }
}

const vector<vector<bool> > & Parameter::getImagesMatchGraph() const {
  if(images_match_graph_manually.empty()) {
    printError("F(getImagesMatchGraph) image match graph verification [2] didn't be implemented yet");
    return images_match_graph_automatically; /* TODO */
  }
  return images_match_graph_manually;
}

const vector<pair<int, int> > & Parameter::getImagesMatchGraphPairList() const {
  if(images_match_graph_pair_list.empty()) {
    const vector<vector<bool> > & images_match_graph = getImagesMatchGraph();
    for(int i = 0; i < images_match_graph.size(); ++i) {
      for(int j = 0; j < images_match_graph[i].size(); ++j) {
        if(images_match_graph[i][j]) {
          images_match_graph_pair_list.emplace_back(i, j);
        }
      }
    }
  }
  return images_match_graph_pair_list;
}
