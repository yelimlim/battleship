// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#ifdef _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__,__LINE__)

#pragma comment(lib, "BGNL_debug.lib")

#else
// Release로 빌드하는 경우
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









// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
