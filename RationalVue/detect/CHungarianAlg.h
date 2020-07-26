#pragma once
#include <vector>
#include <CTracking.h>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "CImageMatching.h"
//#include "HungarianAlg.h"

class AssignmentProblemSolver
{
private:
	// --------------------------------------------------------------------------
	// Computes the optimal assignment (minimum overall costs) using Munkres algorithm.
	// --------------------------------------------------------------------------
	void assignmentoptimal(int *assignment, double *cost, double *distMatrix, int nOfRows, int nOfColumns);
	void buildassignmentvector(int *assignment, bool *starMatrix, int nOfRows, int nOfColumns);
	void computeassignmentcost(int *assignment, double *cost, double *distMatrix, int nOfRows);
	void step2a(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
	void step2b(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
	void step3(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);
	void step4(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim, int row, int col);
	void step5(int *assignment, double *distMatrix, bool *starMatrix, bool *newStarMatrix, bool *primeMatrix, bool *coveredColumns, bool *coveredRows, int nOfRows, int nOfColumns, int minDim);

	void assignmentsuboptimal1(int *assignment, double *cost, double *distMatrixIn, int nOfRows, int nOfColumns);

	void assignmentsuboptimal2(int *assignment, double *cost, double *distMatrixIn, int nOfRows, int nOfColumns);
public:
	enum TMethod { optimal, many_forbidden_assignments, without_forbidden_assignments };
	AssignmentProblemSolver();
	~AssignmentProblemSolver();
	//void FeatureMatching(vector<vector<double>>& DistMatrix, vector<int>& Assignment);
	void FeatureMatching(CObjectRect &var);
	int count = 0;
};