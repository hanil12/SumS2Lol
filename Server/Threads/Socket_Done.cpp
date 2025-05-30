
// 1. Socket 1:1 프로그래밍
// - 1:1 동기, 블록킹

// 2. Select 기반 Socket 프로그래밍
// - 1:1 동기, 논블로킹

// 3. Event 기반 Socket 프로그래밍
// - 1:1 동기, 논블로킹, 통지 받기 전까지 대기

// 4. Overlapped(겹쳐진) Event 기반 Socket 프로그램ㅇ
// - 1: 다, 비동기, 논블로킹, 
// - WSAWaitForMultipleEvents, 최대 Event 개수가 64개 였다.

// 5. Overlapped Callback 기반 Socket 프로그래밍
// - 1: 다, 비동기, 논블로킹
// - 쓰레드 마다 APC 큐가 있다. => 많은 작업들을 멀티쓰레드 환경에 처리하기에 부적합하다.
// ==> 한 곳(Completion Port)에 일감을 몰아넣고 멀티쓰레드 환경에서 동작하게 하자

// 6. IOCP 기반 소켓 프로그래밍, (Completion Port : 비동기적으로 완료된 일감들을 처리할 수 있게 모아놓은 곳)
// - 1: 다, 비동기, 논블로킹, 멀티쓰레드 환경에 적합