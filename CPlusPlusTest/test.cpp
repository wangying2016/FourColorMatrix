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

class Solution {
public:
	/*
	 * 函数作用	：返回指定字符的相邻字符数组
	 * 参数		：指定字符
	 * 返回值	：装载有相邻字符数组的vector字符容器
	 */
	vector<char> getBorderChar(char ch) {
		// 声明一个 “无序set” 容器来存放指定 “字符” 的 “相邻字符集”
		unordered_set<char> border;
		// 遍历每个字符，找到指定字符，并返回上下左右不同的字符
		for (size_t row = 0; row < m_matrix.size(); ++row) {
			for (size_t col = 0; col < m_matrix[row].size(); ++col) {
				if (m_matrix[row][col] == ch) {
					// 上
					if (row != 0 && m_matrix[row - 1][col] != ch) {
						border.insert(m_matrix[row - 1][col]);
					} 
					// 右
					if (col != m_matrix[row].size() - 1 && m_matrix[row][col + 1] != ch) {
						border.insert(m_matrix[row][col + 1]);
					}
					// 下
					if (row != m_matrix.size() - 1 && m_matrix[row + 1][col] != ch) {
						border.insert(m_matrix[row + 1][col]);
					}
					// 左
					if (col != 0 && m_matrix[row][col - 1] != ch) {
						border.insert(m_matrix[row][col - 1]);
					}
				}
			}
		}
		// 返回指定 vector 字符数组
		vector<char> unique_boder(border.begin(), border.end());
		return unique_boder;
	}

	/*
	* 函数作用	：迭代计算各种字符的颜色
	* 参数		：当前处理字符 ； 由 “字符” 到 “相邻字符数组” 的映射
	* 返回值		：处理 private 变量 item_color，其记录每种字符的颜色值
	*/
	void tryToSetColor(char cur, unordered_map<char, vector<char>> items_border)
	{
		// 记录已经用掉的颜色：即当前点的相邻点用掉的颜色
		// 将用掉的颜色结果存储到 “无序set” 中去
		unordered_set<char> used_color;
		for (auto border_use_color : items_border[cur]) {
			if (item_color[border_use_color] != '\0') {
				used_color.insert(item_color[border_use_color]);
			}
		}
		// 每种字符在四种颜色遍历的情况下取色处理
		for (auto color : colors) {
			// --找到可以使用的颜色
			if (used_color.find(color) == used_color.end()) {
				// ----着色成功
				item_color[cur] = color;
				// ----查看当前点的相邻点是否有未着色的点，若有则进行着色处理
				for (auto border_item : items_border[cur]) {
					if (item_color[border_item] == '\0') {
						// ------迭代进行着色处理
						tryToSetColor(border_item, items_border);
					}
				}
				// 全部着色完毕，返回
				return;
			} 
		}
	}
	

	// 函数作用：返回新的打印数组
	vector<vector<char>> fourColorsMatrix(vector<vector<char>> &matrix) {
		m_matrix = matrix;
		// 获得当前阵列中出现的 “字符” set 
		unordered_set<char> items_set;
		for (auto vec : matrix) {
			for (auto item : vec) {
				items_set.insert(item);
			}
		}
		// 获得存储 “字符” 到 “相邻字符数组” 的映射
		unordered_map<char, vector<char>> items_border;
		for (auto item : items_set) {
			items_border[item] = getBorderChar(item);
		}
		// 处理由 “字符” 到 “相邻字符” 的映射，运算后得到着色阵列
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
	// 接收传入的初始阵列
	vector<vector<char>> m_matrix;
	// 记录当前的着色路径
	stack<char> color_path;
	// 由 “字符” 到 “颜色” 的映射
	unordered_map<char, char> item_color;
	// 四种颜色标识数组
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
	// 调用 fourColorsMatrix 函数进行四色着色运算
	Solution solution;
	vector<vector<char>> result = solution.fourColorsMatrix(matrix);	

	// 输出着色阵列
	for (auto vec : result) {
		for (auto c : vec) {
			cout << c << " ";
		}
		cout << endl;
	}
	
	// 仅仅用于命令行暂停
	system("pause");
	return 0;
}