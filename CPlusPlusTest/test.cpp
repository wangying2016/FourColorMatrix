#include <iostream>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;
using std::unordered_map;
using std::unordered_set;
using std::stack;
using std::unique;

class Solution {
public:

	// 函数作用：返回每个字符上下左右不同的字符数组
	vector<char> getBorderChar(char ch, vector<vector<char>> matrix) {
		// 之所以选择 map，是为了方便去重
		unordered_map<char, int> boder;
		// 遍历每个字符，找到指定字符，并返回上下左右不同的字符
		for (size_t row = 0; row < matrix.size(); ++row) {
			for (size_t col = 0; col < matrix[row].size(); ++col) {
				if (matrix[row][col] == ch) {
					// 上
					if (row != 0 && matrix[row - 1][col] != ch) {
						++boder[matrix[row - 1][col]];
					} 
					// 右
					if (col != matrix[row].size() - 1 && matrix[row][col + 1] != ch) {
						++boder[matrix[row][col + 1]];
					}
					// 下
					if (row != matrix.size() - 1 && matrix[row + 1][col] != ch) {
						++boder[matrix[row + 1][col]];
					}
					// 左
					if (col != 0 && matrix[row][col - 1] != ch) {
						++boder[matrix[row][col - 1]];
					}
				}
			}
		}
		// 去重
		vector<char> unique_boder;
		for (auto boder : boder) {
			unique_boder.push_back(boder.first);
		}
		return unique_boder;
	}

	void tryToSetColor(char cur, unordered_map<char, vector<char>> items_border)
	{
		// 记录已经用掉的颜色：包括相邻点用掉颜色和当前点尝试颜色
		unordered_set<char> used_color;
		for (auto border_use_color : items_border[cur]) {
			if (item_color[border_use_color] != '\0') {
				used_color.insert(item_color[border_use_color]);
			}
		}
		// 判断第一个可以使用的颜色，找到身边的第一个没有颜色点继续迭代循环
		for (auto color : colors) {
			if (used_color.find(color) == used_color.end()) {
				// --着色成功
				item_color[cur] = color;
				// --将当前点压栈
				color_path.push(cur);
				for (auto border_item : items_border[cur]) {
					if (item_color[border_item] == '\0') {
						// ----再次尝试着色
						tryToSetColor(border_item, items_border);
					}
				}
				// 全部着色完毕
				return;
			} 
		}
	}
	

	// 函数作用：返回新的打印数组
	vector<vector<char>> fourColorsMatrix(vector<vector<char>> &matrix) {
		// 获得存储 “字符” 到 “字符出现” 次数的映射
		unordered_map<char, int> items_count;
		for (auto vec : matrix) {
			for (auto item : vec) {
				items_count[item]++;
			}
		}
		// 获得存储 “字符” 到 “相邻字符” 的映射
		// 获取每个字符上下左右四个不同字符返回，并加入 items_border 的键值中
		unordered_map<char, vector<char>> items_border;
		for (auto item : items_count) {
			items_border[item.first] = getBorderChar(item.first, matrix);
		}
		// 深度遍历 “字符” 到 “相邻字符” 的映射
		tryToSetColor(items_border.begin()->first, items_border);
		// 更替对应字符
		for (auto item : item_color) {
			for (auto &vec : matrix) {
				for (auto &c : vec) {
					if (c == item.first) {
						c = item.second;
					}
				}
			}
		}
		return matrix;
	}

private:
	stack<char> color_path;
	unordered_map<char, char> item_color;
	const vector<char> colors = { '+', '-', '*', '/' };
};

int main()
{
	vector<vector<char>> matrix = { 
		{ '0', '2', '3', '3', '3', '7', '7', '7', '7', 'a' },
		{ '0', '2', '2', '2', '3', '7', '8', '8', 'a', 'a' },
		{ '0', '0', '2', '4', '3', '6', '6', '8', '8', 'a' },
		{ '1', '0', '4', '4', '4', '6', '9', '9', '8', 'a' },
		{ '1', '1', '1', '4', '6', '6', '9', 'b', 'b', 'b' },
		{ '1', '5', '5', '5', '5', '5', '9', '9', 'b', 'b' }
	};
	Solution solution;
	vector<vector<char>> result = solution.fourColorsMatrix(matrix);	

	for (auto vec : result) {
		for (auto c : vec) {
			cout << c << " ";
		}
		cout << endl;
	}

	system("pause");
	return 0;
}