// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__,__LINE__)

#pragma comment(lib, "BGNL_debug.lib")

#else
// Release�� �����ϴ� ���
#pragma comment(lib, "BGNL.lib")


#endif

#include <stdio.h>
#include "targetver.h"
#include <tchar.h>
#include <crtdbg.h>
#include <iostream>
#include <string>
#include <istream>
#include <time.h>
#include "Network.h"
#include <vector>

using namespace std;









// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
