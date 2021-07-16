# MFC를 이용한 같은그림찾기게임
### 진행기간
2019.11 ~ 2019.12
### SKILLS / IDE
C++

MFC

### Rewards
정보통신프로토콜설계 B+

## 내가 맡은 부분
1. GUI프로그래밍
2. 소켓 통신

## 시스템 구조도
* 플레이어 1과 플레이어 2는 서버를 통해 메시지를 주고받는다.

![image](https://user-images.githubusercontent.com/59634413/126001039-7e886a14-6ad9-4fd6-b6ee-ade4e2a3a2ff.png)

## 시스템 흐름도
* 서버에서 소켓을 뚫어 데이터를 주고받을 수 있는 통로를 만든 이후, Accept와 Receive는 다중 쓰레드 형태로 구성하여 다중 클라이언트 통신을 할 수 있게 한다. 모든 동작을 끝마치면 소켓을 close한다.
![image](https://user-images.githubusercontent.com/59634413/126001111-20a1ccee-a667-4b73-b63c-421e2e7784a6.png)

## 게임 진행 순서
1. 서버 오픈
2. 방 생성 및 입장
3. 대화 및 준비 완료
4. 게임 시작 전 3초간 앞면 보여줌
5. 게임 진행 - 같은 그림 짝 맞추기
6. 게임 승리 & 패배
7. 게임 종료

## 게임 진행
1. 서버 오픈

![image](https://user-images.githubusercontent.com/59634413/126001571-ae98dcc6-73f3-471b-8989-86e3ac8e613d.png)

2. 방 생성 및 입장

![image](https://user-images.githubusercontent.com/59634413/126001663-33936ddb-1329-449f-b2b4-cb829e9fff20.png)

3. 대화 및 준비 완료

![image](https://user-images.githubusercontent.com/59634413/126001731-447f454b-1023-4262-b2cc-e06d40038aab.png)

4. 게임 시작 전 3초간 앞면 보여줌

![image](https://user-images.githubusercontent.com/59634413/126001922-dc0ba6d0-e0dc-4b33-adc0-ca4c9326251d.png)

5. 게임 진행 - 같은 그림 짝 맞추기

![image](https://user-images.githubusercontent.com/59634413/126001973-0560e036-3120-4dfb-bd8a-99b301755e81.png)

6. 게임 승리 & 패배

![image](https://user-images.githubusercontent.com/59634413/126002092-b6dcc96d-a426-4586-9cc8-1430b6dc59b5.png)

7. 게임 종료

![image](https://user-images.githubusercontent.com/59634413/126002150-33c660cf-cf5b-4950-b821-dfec4747e987.png)

## 고찰
### GUI 프로그래밍
* Dialog에서 버튼과 라디오박스 등의 배치를 처음부터 생각하고 프로그래밍을 해야하기 때문에 여러번 수정했다.
* 다음엔 먼저 스토리보드를 짜서 어떤 구현을 할 지 정확히 정하면 더 수월하게 할 수 있을 것 같다.
* 버튼을 눌렀을 때 메서드가 여러개라 했갈렸다. 변수 설정 등 이름을 구분하기 쉽게 프로그래밍 하면 좋겠다.
### 소켓 통신
* 처음에는 막막했는데 클라이언트-서버간 주고받아야 할 데이터를 먼저 정했다.
* 서버가 메인으로 데이터를 갖고 있으면서 클라이언트는 게임을 진행하고 승 패 결과만 주면 되기 때문에 많은 정보가 필요하지 않아 메시지의 개수가 그렇게 많지 않았다.
* Winsock을 이용하여 서버에서 소켓을 뚫고 클라이언트-서버의 동작을 미리 정해놨기 때문에 연결된 이후부터는 쉬웠다.
* 이 시스템에서 서버는 전달의 역할만 하고 승/패 여부는 정확히 알지 못한다.
* 다음 시스템을 설계할 때에는 서버가 모든 정보들을 관리하는 시스템을 만들어보아야겠다.
