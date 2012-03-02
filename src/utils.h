#include <vector>
#include <map>
#include <cv.h>
#include <highgui.h>

/*class Point {
	public:
		int grayLevel;
		int x, y;
		int tag;
		Point(int, int);
};

Point::Point(int xi, int yi) {
	x = xi;
	y = yi;
	tag = -1;
}

class ConnectedComponent {
	public:
		vector<Point> points;
		int size;
		ConnectedComponent();
		ConnectedComponent(int x, int y);
		~ConnectedComponent();
		void setSize();
};

ConnectedComponent::ConnectedComponent() {}
ConnectedComponent::~ConnectedComponent() {}

void ConnectedComponent::setSize() {
	size = points.size();
}*/

using namespace std;
using namespace cv;

bool peekTopLeft(Mat image, int x, int y) {
	Scalar curr;
	if(y - 1 >= 0 && x - 1 >= 0) {
		curr = image.at<uchar>(x, y);
		if(curr.val[0] == 255) {
			return true;
		}
	}
	return false;
}

bool peekTopRight(Mat image, int x, int y) {
	Scalar curr;
	if(y - 1 >= 0 && (x + 1 >= 0 && x + 1 < image.cols)) {
		curr = image.at<uchar>(x, y);
		if(curr.val[0] == 255) {
			return true;
		}
	}
	return false;
}

bool peekTop(Mat image, int x, int y) {
	Scalar curr;
	if(y - 1 >= 0) {
		curr = image.at<uchar>(x, y);
		if(curr.val[0] == 255) {
			return true;
		}
	}
	return false;
}

bool peekLeft(Mat image, int x, int y) {
	Scalar curr;
	if(x - 1 >= 0) {
		curr = image.at<uchar>(x, y);
		if(curr.val[0] == 255) {
			return true;
		}
	}
	return false;
}

map<pair<int, int>, int > findConnectedComponents(Mat image) {
	Scalar curr;
	int tag = 0;
	map<pair<int, int>, int > taggedPoints;

	for(int y = 0; y < image.rows; y++) {
		for(int x = 0 ; x < image.cols; x++) {
			curr = image.at<uchar>(x, y);
			if(curr.val[0] == 255) {
				taggedPoints[make_pair(x, y)] = tag;
			}
			if(tag > 0) {
				taggedPoints[make_pair(x, y)] = ++tag;
				if(peekTopLeft(image, x, y)) {
					taggedPoints[make_pair(x, y)] = taggedPoints[make_pair(x - 1, y - 1)];
				}
				if(peekTop(image, x, y)) {
					taggedPoints[make_pair(x, y)] = taggedPoints[make_pair(x, y - 1)];
				}
				if(peekTopRight(image, x, y)) {
					taggedPoints[make_pair(x, y)] = taggedPoints[make_pair(x+1, y-1)];
				}
				if(peekLeft(image, x, y)) {
					taggedPoints[make_pair(x, y)] = taggedPoints[make_pair(x-1, y)];
				}
			}
		}
	}

	return taggedPoints;
}
