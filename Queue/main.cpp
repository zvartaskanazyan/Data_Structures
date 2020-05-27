#include "pch.h"
#include <iostream>
#include <fstream>
#include "AQueue.h"
#include <queue>
#include "DoubleStackQueue.h"

int main(int argc, char* argv[])
{
	const std::string file_name = "input.txt";


	std::ifstream fin{ file_name };

	if (!fin.is_open()) {
		std::cerr << "File not found" << std::endl;
	}

	int n = 0;
	fin >> n;
	DoubleStackQueue<int> q;
	std::ofstream fout{ "output.txt" };
	for (int i = 0; i < n; ++i) {
		int type = 0;
		fin >> type;
		switch (type) {
		case 1:
		{
			int val = 0;
			fin >> val;
			q.enqueue(val);
			break;
		}
		case 2:
		{
			if (q.empty()) {
				throw std::invalid_argument{ "error" };
			}

			q.dequeue();
			break;
		}
		case 3:
		{
			if (q.empty()) {
				throw std::invalid_argument{ "error" };
			}

			fout << q.front() << std::endl;
			break;
		}
		default:
			assert(false);
		}
	}
	fin.close();
	fout.close();

	system("pause");
	return 0;
}