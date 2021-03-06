/*
	Morphological Operations - Dilation.cpp
	Dilates image using a specific kernel.
	Test with odd kernels only, probably will break with even, probably not.
	The code is optimized to break the loop conveniently to avoid comparing all values.

	Test case:
	Image
	0000000000
	0111111100
	0000111100
	0000111100
	0001111100
	0000111100
	0001100000
	0000000000
	0000000000

	Default Kernel
	111
	111
	111

	Expected output:
	59

	@author Cristóbal Silva
*/

#include <vector>
#include <iostream>

using namespace std;

typedef vector< vector <int> > Mat;

Mat input = {
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,1,1,1,1,1,1,0,0 },
	{ 0,0,0,0,1,1,1,1,0,0 },
	{ 0,0,0,0,1,1,1,1,0,0 },
	{ 0,0,0,1,1,1,1,1,0,0 },
	{ 0,0,0,0,1,1,1,1,0,0 },
	{ 0,0,0,1,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0 }
};

Mat kernel = {
	{ 1,1,1 },
	{ 1,1,1 },
	{ 1,1,1 }
};

int pixels;

void dilate(int row, int col, Mat &img, Mat &out) {

	int krows = kernel.size();
	int kcols = kernel[0].size();
	int sum = 0;
	bool marked = false;
	for (int i = -krows/2; i <= krows/2; i++) {
		for (int j = -kcols/2; j <= kcols/2; j++) {
			//sum = sum + kernel[i + krows/2][j + kcols/2] * img[row - i][col - j];
			if (kernel[i + krows / 2][j + kcols / 2] * img[row - i][col - j] > 0) {
				marked = true;
				break;
			}
		}
		if (marked) {
			out[row][col] = 1;
			pixels++;
			break;
		}
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
	pixels = 0;
	
	for (int row = 1; row < rows + 1; row++) {
		for (int col = 1; col < cols + 1; col++) {
			dilate(row, col, img, out);
		}
	}

	/* Display Final Image */
	/*
	for (int i = 1; i < rows + 1; i++) {
		for (int j = 1; j < cols + 1; j++) {
			cout << out[i][j];
		}
		cout << endl;
	}
	*/

	cout << pixels << endl;
	return 0;
}