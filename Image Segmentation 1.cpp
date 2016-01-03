/*
	Image Segmentation 1.cpp
	Calculates 4-connected-component number of Labels
	It additionally gets the final image Labeled 

	Test case:
	000110001010
	111011110001
	111010010010
	100000000100

	Expected output:
	7

	@author Cristóbal Silva
*/

#include <vector>
#include <iostream>

using namespace std;

typedef vector< vector <int> > Mat;

Mat input = {
	{ 0,0,0,1,1,0,0,0,1,0,1,0 },
	{ 1,1,1,0,1,1,1,1,0,0,0,1 },
	{ 1,1,1,0,1,0,0,1,0,0,1,0 },
	{ 1,0,0,0,0,0,0,0,0,1,0,0 }
};

int label;

void check(int row, int col, Mat &img, Mat &out) {
	img[row][col] = 0;
	out[row][col] = label;
	if (img[row + 1][col] == 1) {
		check(row + 1, col, img, out);
	}
	if (img[row - 1][col] == 1) {
		check(row - 1, col, img, out);
	}
	if (img[row][col + 1] == 1) {
		check(row, col + 1, img, out);
	}
	if (img[row][col - 1] == 1) {
		check(row, col - 1, img, out);
	}
}

Mat padding(Mat &image) {
	int rows = image.size();
	int cols = image[0].size();
	int newrows = rows + 2;
	int newcols = cols + 2;
	Mat padded(newrows, vector<int>(newcols));

	for (int i = 1; i < newrows - 1; i++) {
		for (int j = 1; j < newcols - 1; j++) {
			padded[i][j] = input[i - 1][j - 1];
		}
	}
	return padded;
}

int main() {
	int rows = input.size();
	int cols = input[0].size();
	Mat img(rows + 2, vector<int>(cols + 2));
	Mat out(rows + 2, vector<int>(cols + 2));

	img = padding(input);

	label = 0;
	for (int row = 1; row < rows + 1; row++) {
		for (int col = 1; col < cols + 1; col++) {
			if (img[row][col] == 1) {
				label++;
				check(row, col, img, out);
			}
		}
	}

	cout << label << endl;
	return 0;
}