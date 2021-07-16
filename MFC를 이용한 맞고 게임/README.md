# MFC를 이용한 맞고 게임
### 진행기간
2018.11 ~ 2018.12
### SKILLS / IDE
C++

MFC

### Rewards
Visual C++ B+

## 내가 맡은 부분
1. GUI프로그래밍
2. 점수 계산

## 시스템 구조도
* 플레이어 1과 플레이어 2는 서버를 통해 메시지를 주고받는다.

![image](https://user-images.githubusercontent.com/59634413/126001039-7e886a14-6ad9-4fd6-b6ee-ade4e2a3a2ff.png)

## 시스템 흐름도
* 서버에서 소켓을 뚫어 데이터를 주고받을 수 있는 통로를 만든 이후, Accept와 Receive는 다중 쓰레드 형태로 구성하여 다중 클라이언트 통신을 할 수 있게 한다. 모든 동작을 끝마치면 소켓을 close한다.
![image](https://user-images.githubusercontent.com/59634413/126001111-20a1ccee-a667-4b73-b63c-421e2e7784a6.png)

## 게임 진행 순서
1. 준비 완료
2. 게임 진행
3. 점수 계산
4. 승패 결정
5. 게임 종료

## 게임 진행
1. 게임 준비

![image](https://user-images.githubusercontent.com/59634413/126005186-1ac3c03b-7c01-490b-83c6-8ba898ee4b8d.png)

2. 게임 진행

![image](https://user-images.githubusercontent.com/59634413/126005232-46f2cf1b-0007-42b2-8199-990112a8f521.png)

3. 점수 계산

![image](https://user-images.githubusercontent.com/59634413/126005292-cea99212-aa63-43df-9ff3-b63cfab91cdf.png)

4. 승패 결정 및 게임 종료

![image](https://user-images.githubusercontent.com/59634413/126005330-e9143378-7ad3-4264-89de-d6bce333f0be.png)

## 고찰
### GUI 프로그래밍
* 항상 콘솔창으로 프로그래밍 하다가 GUI를 하니까 보기엔 편했지만, 내가 건드려야 할 것들이 많다는 것을 느꼈다.
* 버튼, 라디오 박스, 메시지 박스 등이 아직 잘 숙지가 되지 않아서 내가 원하는 기능에 필요한게 무엇인지 잘 몰라 시간이 오래 걸렸다.
* 다음에는 클라이언트-서버 같은 전체적인 시스템의 설계도 해보고 싶다.
### 점수 계산
* 7점 이상이면 점수 계산을 해야하는데 항상 점수가 몇점인지를 알고있어야 한다.
* 전체적인 코드 동작의 흐름을 알고 있어야 점수 계산을 해야하는 시점이 꼬이지 않는데 서버-클라이언트 쪽은 잘 몰라서 점수 계산이 꼬였던 것 같다.
* 좀 더 적극적으로 동료에게 관심을 갖고 물으며 프로젝트가 어떻게 진행되는지 조율을 할 필요가 있는 것 같다..
