#pragma once
#include <opencv2\opencv.hpp>
//==============================================================================
//	@name		:	Feature
//	@biref		:	���������Ľṹ
//	@author		:	
//===============================================================================

class CFeature {
public:
	std::vector<cv::Scalar> feat_Scalar;
	std::vector<float> feat_float_vec;
};
