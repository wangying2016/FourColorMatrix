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

	// �������ã�����ÿ���ַ��������Ҳ�ͬ���ַ�����
	vector<char> getBorderChar(char ch, vector<vector<char>> matrix) {
		// ֮����ѡ�� map����Ϊ�˷���ȥ��
		unordered_map<char, int> boder;
		// ����ÿ���ַ����ҵ�ָ���ַ����������������Ҳ�ͬ���ַ�
		for (size_t row = 0; row < matrix.size(); ++row) {
			for (size_t col = 0; col < matrix[row].size(); ++col) {
				if (matrix[row][col] == ch) {
					// ��
					if (row != 0 && matrix[row - 1][col] != ch) {
						++boder[matrix[row - 1][col]];
					} 
					// ��
					if (col != matrix[row].size() - 1 && matrix[row][col + 1] != ch) {
						++boder[matrix[row][col + 1]];
					}
					// ��
					if (row != matrix.size() - 1 && matrix[row + 1][col] != ch) {
						++boder[matrix[row + 1][col]];
					}
					// ��
					if (col != 0 && matrix[row][col - 1] != ch) {
						++boder[matrix[row][col - 1]];
					}
				}
			}
		}
		// ȥ��
		vector<char> unique_boder;
		for (auto boder : boder) {
			unique_boder.push_back(boder.first);
		}
		return unique_boder;
	}

	void tryToSetColor(char cur, unordered_map<char, vector<char>> items_border)
	{
		// ��¼�Ѿ��õ�����ɫ���������ڵ��õ���ɫ�͵�ǰ�㳢����ɫ
		unordered_set<char> used_color;
		for (auto border_use_color : items_border[cur]) {
			if (item_color[border_use_color] != '\0') {
				used_color.insert(item_color[border_use_color]);
			}
		}
		// �жϵ�һ������ʹ�õ���ɫ���ҵ���ߵĵ�һ��û����ɫ���������ѭ��
		for (auto color : colors) {
			if (used_color.find(color) == used_color.end()) {
				// --��ɫ�ɹ�
				item_color[cur] = color;
				// --����ǰ��ѹջ
				color_path.push(cur);
				for (auto border_item : items_border[cur]) {
					if (item_color[border_item] == '\0') {
						// ----�ٴγ�����ɫ
						tryToSetColor(border_item, items_border);
					}
				}
				// ȫ����ɫ���
				return;
			} 
		}
	}
	

	// �������ã������µĴ�ӡ����
	vector<vector<char>> fourColorsMatrix(vector<vector<char>> &matrix) {
		// ��ô洢 ���ַ��� �� ���ַ����֡� ������ӳ��
		unordered_map<char, int> items_count;
		for (auto vec : matrix) {
			for (auto item : vec) {
				items_count[item]++;
			}
		}
		// ��ô洢 ���ַ��� �� �������ַ��� ��ӳ��
		// ��ȡÿ���ַ����������ĸ���ͬ�ַ����أ������� items_border �ļ�ֵ��
		unordered_map<char, vector<char>> items_border;
		for (auto item : items_count) {
			items_border[item.first] = getBorderChar(item.first, matrix);
		}
		// ��ȱ��� ���ַ��� �� �������ַ��� ��ӳ��
		tryToSetColor(items_border.begin()->first, items_border);
		// �����Ӧ�ַ�
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