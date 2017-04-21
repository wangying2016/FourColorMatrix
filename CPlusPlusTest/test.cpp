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
	 * ��������	������ָ���ַ��������ַ�����
	 * ����		��ָ���ַ�
	 * ����ֵ	��װ���������ַ������vector�ַ�����
	 */
	vector<char> getBorderChar(char ch) {
		// ����һ�� ������set�� ���������ָ�� ���ַ��� �� �������ַ�����
		unordered_set<char> border;
		// ����ÿ���ַ����ҵ�ָ���ַ����������������Ҳ�ͬ���ַ�
		for (size_t row = 0; row < m_matrix.size(); ++row) {
			for (size_t col = 0; col < m_matrix[row].size(); ++col) {
				if (m_matrix[row][col] == ch) {
					// ��
					if (row != 0 && m_matrix[row - 1][col] != ch) {
						border.insert(m_matrix[row - 1][col]);
					} 
					// ��
					if (col != m_matrix[row].size() - 1 && m_matrix[row][col + 1] != ch) {
						border.insert(m_matrix[row][col + 1]);
					}
					// ��
					if (row != m_matrix.size() - 1 && m_matrix[row + 1][col] != ch) {
						border.insert(m_matrix[row + 1][col]);
					}
					// ��
					if (col != 0 && m_matrix[row][col - 1] != ch) {
						border.insert(m_matrix[row][col - 1]);
					}
				}
			}
		}
		// ����ָ�� vector �ַ�����
		vector<char> unique_boder(border.begin(), border.end());
		return unique_boder;
	}

	/*
	* ��������	��������������ַ�����ɫ
	* ����		����ǰ�����ַ� �� �� ���ַ��� �� �������ַ����顱 ��ӳ��
	* ����ֵ		������ private ���� item_color�����¼ÿ���ַ�����ɫֵ
	*/
	void tryToSetColor(char cur, unordered_map<char, vector<char>> items_border)
	{
		// ��¼�Ѿ��õ�����ɫ������ǰ������ڵ��õ�����ɫ
		// ���õ�����ɫ����洢�� ������set�� ��ȥ
		unordered_set<char> used_color;
		for (auto border_use_color : items_border[cur]) {
			if (item_color[border_use_color] != '\0') {
				used_color.insert(item_color[border_use_color]);
			}
		}
		// ÿ���ַ���������ɫ�����������ȡɫ����
		for (auto color : colors) {
			// --�ҵ�����ʹ�õ���ɫ
			if (used_color.find(color) == used_color.end()) {
				// ----��ɫ�ɹ�
				item_color[cur] = color;
				// ----�鿴��ǰ������ڵ��Ƿ���δ��ɫ�ĵ㣬�����������ɫ����
				for (auto border_item : items_border[cur]) {
					if (item_color[border_item] == '\0') {
						// ------����������ɫ����
						tryToSetColor(border_item, items_border);
					}
				}
				// ȫ����ɫ��ϣ�����
				return;
			} 
		}
	}
	

	// �������ã������µĴ�ӡ����
	vector<vector<char>> fourColorsMatrix(vector<vector<char>> &matrix) {
		m_matrix = matrix;
		// ��õ�ǰ�����г��ֵ� ���ַ��� set 
		unordered_set<char> items_set;
		for (auto vec : matrix) {
			for (auto item : vec) {
				items_set.insert(item);
			}
		}
		// ��ô洢 ���ַ��� �� �������ַ����顱 ��ӳ��
		unordered_map<char, vector<char>> items_border;
		for (auto item : items_set) {
			items_border[item] = getBorderChar(item);
		}
		// ������ ���ַ��� �� �������ַ��� ��ӳ�䣬�����õ���ɫ����
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
	// ���մ���ĳ�ʼ����
	vector<vector<char>> m_matrix;
	// ��¼��ǰ����ɫ·��
	stack<char> color_path;
	// �� ���ַ��� �� ����ɫ�� ��ӳ��
	unordered_map<char, char> item_color;
	// ������ɫ��ʶ����
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
	// ���� fourColorsMatrix ����������ɫ��ɫ����
	Solution solution;
	vector<vector<char>> result = solution.fourColorsMatrix(matrix);	

	// �����ɫ����
	for (auto vec : result) {
		for (auto c : vec) {
			cout << c << " ";
		}
		cout << endl;
	}
	
	// ����������������ͣ
	system("pause");
	return 0;
}