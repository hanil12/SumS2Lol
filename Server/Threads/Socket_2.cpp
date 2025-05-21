#include "framework.h"

#pragma comment(lib,"ws2_32.lib")

using namespace std;

// 라이브러리 : 프로그램에서 필요한 함수나, 자료형 등을 모아놓은 곳
// 동적라이브러리 vs 정적라이브러리

// 정적라이브러리
// => 컴파일 시간에 링커에서 obj로 파일결합.
// 장점 : 다른 파일이 필요없다(dll)
// 단점 : 유지보수가 어렵다. (lib가 수정되면 컴파일해서 다시 재배포해야한다.)

// 동적라이브러리(dll : dynamic link library)
// => 런타임 도중에 (프로그램사용자)메모리에 올려서 그 때 필요한 함수,자료형 등을 갖고온다.
// 장점 : 유지보수가 쉽다. (lib가 수정되면 dll만 새로 배포)
// 단점 : dll 종속성

int main()
{


	return 0;
}
