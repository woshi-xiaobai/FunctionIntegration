bool count_duplicate_points(std::vector<cv::Point2f> &_points,
                            std::vector < std::vector<cv::Point2f>> &
                                _point_list
                            ) {
  if (_points.size()<0) {
    return false;
  }

  // 统计每个点出现的次数
  for (auto p : _points) {
    bool flag = false;
    for (size_t j = 0; j < _point_list.size(); j++) {
      if (p == _point_list[j][0]) {
        _point_list[j].push_back(p);
        flag = true;
      }
    }
    if (flag) {
      continue;
    }
    std::vector<cv::Point2f> temp = {p};
    _point_list.push_back(temp);
  }
  // 对 nestedVectors 进行排序，按照每个内部 std::vector 的元素数量
  std::sort(
      _point_list.begin(), _point_list.end(),
      [](const std::vector<cv::Point2f> &v1,
         const std::vector<cv::Point2f> &v2) {
              return v1.size() > v2.size();
            });
  if (_point_list.size() < 1) {
    return false;
  }
  return true;
}
