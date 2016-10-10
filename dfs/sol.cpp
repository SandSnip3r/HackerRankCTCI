#include <iostream>
#include <vector>

using namespace std;

class Cell {
public:
	bool set{false}, visited{false};
	Cell() = default;
	Cell(bool s) : set(s) {}
};

class Matrix {
public:
	vector<vector<Cell>> cells;

	Matrix(int rows, int cols) {
		cells = vector<vector<Cell>>(rows, vector<Cell>(cols, Cell()));
	}

	void set(int row, int col, int val) {
		bool b = (val == 0 ? false : true);
		cells.at(row).at(col) = Cell(b);
	}

	int getLargestClusterSize() {
		int largestSize = 0;
		for (size_t row=0; row<cells.size(); ++row) {
			for (size_t col=0; col<cells.at(row).size(); ++col) {
				int thisSize = explorePotentialCluster(row,col);
				if (thisSize > largestSize) {
					largestSize = thisSize;
				}
			}
		}
		return largestSize;
	}

	int explorePotentialCluster(int row, int col) {
		int clusterCount = 0;
		Cell &thisCell = cells.at(row).at(col);
		if (thisCell.set && !thisCell.visited) {
			thisCell.visited = true;
			++clusterCount;
			//left
			if (col-1 >= 0) {
				clusterCount += explorePotentialCluster(row, col-1);
			}
			//right
			if (col+1 < static_cast<int>(cells.at(row).size())) {
				clusterCount += explorePotentialCluster(row, col+1);
			}
			//up
			if (row-1 >= 0) {
				clusterCount += explorePotentialCluster(row-1, col);
			}
			//down
			if (row+1 < static_cast<int>(cells.size())) {
				clusterCount += explorePotentialCluster(row+1, col);
			}
			//up-right
			if (col+1 < static_cast<int>(cells.at(row).size()) && row-1 >= 0) {
				clusterCount += explorePotentialCluster(row-1, col+1);
			}
			//up-left
			if (col-1 >= 0 && row-1 >= 0) {
				clusterCount += explorePotentialCluster(row-1, col-1);
			}
			//down-right
			if (col+1 < static_cast<int>(cells.at(row).size()) && row+1 < static_cast<int>(cells.size())) {
				clusterCount += explorePotentialCluster(row+1, col+1);
			}
			//down-left
			if (col-1 >= 0 && row+1 < static_cast<int>(cells.size())) {
				clusterCount += explorePotentialCluster(row+1, col-1);
			}
		}
		return clusterCount;
	}
};

int main() {
	int rowCount, columnCount;
	cin >> rowCount >> columnCount;
	Matrix matrix(rowCount, columnCount);
	for (int row=0; row<rowCount; ++row) {
		for (int col=0; col<columnCount; ++col) {
			int temp;
			cin >> temp;
			matrix.set(row, col, temp);
		}
	}
	cout << matrix.getLargestClusterSize() << '\n';
}