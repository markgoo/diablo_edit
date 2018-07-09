// Generate Data.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <streambuf>

#include "compress_quicklz.h"

using namespace std;

int main()
{
	const char * input = "itemdata.txt";
	const char * output = "itemdata.dat";
	// Read input file
	ifstream inf(input);
	if (!inf.is_open()) {
		cerr << "Error: cannot open input file '" << input << "'\n";
		return 1;
	}
	string in_buf;
	in_buf.assign(istreambuf_iterator<char>(inf), istreambuf_iterator<char>());
	inf.close();
	// Compress data
	string out_buf;
	if (!CCompressorQuickLZ().compress(in_buf, out_buf)) {
		cerr << "Error: cannot compress input data (len=" << in_buf.size() << ")\n";
		return 1;
	}
	// Write output file
	ofstream outf(output, ios_base::binary);
	if (!outf.is_open()) {
		cerr << "Error: cannot open output file '" << output << "'\n";
		return 1;
	}
	outf.write(out_buf.c_str(), out_buf.size());
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
