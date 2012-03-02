#include "utils.h"

int main() {
	Mat img = imread("img.tiff");
	findConnectedComponents(img);
}
