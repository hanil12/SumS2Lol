#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <future>
#include <Windows.h>

using namespace std;

// Context Switching
// - 하던 일을 멈추고 다른 걸 하러간다.
// => 레지스터,캐시에 저장되어있던 정보를 교체
// => cout(모니터에 접근하는 일), 계산하던 일(기본저인 연산)을 번갈아하면 Context Switching Overhead

// Spin Lock : 화장실에 누가 있어서 거기 앞에서 대기
// Sleep Lock : 화장실에 누가 있어서 내 자리로 돌아와서 대기(100ms) 하다가 돌아가서 확인
// Event Lock : 화장실에 누가 있어서 꼬붕을 세워놓고, "야 화장실에서 누구 나오면 말해" 하고 자리로 돌아가서 대기

// 캐시 
// CPU에 있는 가장 작은 임시저장공간
// - 코어 마다 있다.

// 캐시 철학
// - Temporal Locality : 시간적 지역 => '방금' 본 메모리에서 또 다시 접근할 일이 생길 거 같다.
// - Sptial Locality :  공간적 지역 => 봤던 메모리 '주변'에 또 접근할 일이 생길 거 같다.

int buffer[10000][10000];

int main()
{
	{
		memset(buffer, 0, sizeof(buffer));

		__int64 start = GetTickCount64();

		__int64 sum = 0;
		for (int i = 0; i < 10000; i++)
		{
			for (int j = 0; j < 10000; j++)
			{
				sum += buffer[i][j];
			}
		}

		__int64 end = GetTickCount64();
		cout << "Elapsed Tick " << end - start << "ms" << endl;
	}

	{
		memset(buffer, 0, sizeof(buffer));

		__int64 start = GetTickCount64();

		__int64 sum = 0;
		for (int i = 0; i < 10000; i++)
		{
			for (int j = 0; j < 10000; j++)
			{
				sum += buffer[j][i];
			}
		}

		__int64 end = GetTickCount64();
		cout << "Elapsed Tick " << end - start << "ms" << endl;
	}


	return 0;
}