# 딥러닝을 활용한 중증장애인을 위한 충치 디텍팅 머신
### 진행기간
2020.03 ~ 2020.09
### SKILLS / IDE
YOLOv3(CNN)

OpenCV(Image Processing)

Python

PyQT5

Apache(Database)

Linux

### Rewards
**한국통신학회 우수상**:trophy:

**한국산업기술대학교 산학협력단 장려상**:trophy:

종합설계기획 A+

종합설계1 A+

종합설계2 A

### :trophy:논문 링크
https://www.dbpia.co.kr/journal/articleDetail?nodeId=NODE10501304

## 내가 맡은 부분
1. 딥러닝
2. 영상처리 알고리즘(watershed)
3. GUI Framework(PyQT5)
4. Key unction(치아 갤러리, 치과 지도(GPS), 보호자 SMS전송)
## Motivation
* 정확한 의사 표현이 어려운 중증장애인의 경우 치아관리가 어렵고, 초기에 치과 진료를 받지 못해 치아질환이 심해지는 경우가 많음
* 중증장애인은 의사소통 및 행동조절의 어려움이 있어 대부분 전신마취 후 치과 치료를 진행
* 충치가 생기기 전에 예방이 중요
## System configuration & Hardware
<img src="https://user-images.githubusercontent.com/59634413/125993050-51e61fe3-d5c7-4671-994c-7568e7d1ccbb.png" width="760" height="320">

## Watershed Algorithm
* Watershed Algorithm을 활용하여 치아의 형태와 개수 확보
* 일정한 치아 수가 확보되면 서보 모터를 회전하여 윗니, 아랫니 촬영
<img src="https://user-images.githubusercontent.com/59634413/125993339-aa9c9b60-c273-4dd5-a6ba-d97e418d845d.png" width="480" height="320">

## Darknet Yolo-v3 Model
* 전체 사진의 크기의 비해 충치는 작기 때문에 세 개의 스케일을 이용하여 작은 객체 탐지에 최적화된 YOLO-v3 알고리즘 이용

![image](https://user-images.githubusercontent.com/59634413/125993569-7bd839d8-2f23-40d3-a452-26a691d1c9c7.png)

![image](https://user-images.githubusercontent.com/59634413/125993644-00fdc31e-c7e1-49c0-ad11-e44aaf18d175.png)

## Deep learning
* 이미지 전처리에서는 Image augmentation을 통해 다양한 환경의 학습 데이터를 증가시켜 클래스당 1,000개의 Dataset을 가지고 Labeling을 진행
* Google Colaboratory 환경에서는 Darknet53을 이용하여 모델 학습을 진행하였고, 총 6,000번의 학습을 진행하여 평균 loss rate는 0.026, 90% 이상의 높은 인식률 달성
<img src="https://user-images.githubusercontent.com/59634413/125994320-c1c911b1-31e5-4b70-98a5-47adf49112b2.png" width="720" height="240">

## Key function
* 사용자마다 저장된 치아 이미지를 날짜별 확인 가능
* 사용자 위치 주변의 치과와 전화번호 정보 제공
* 미리 설정한 보호자의 휴대폰 번호로 사용자의 충치 개수와 사진을 전송
<img src="https://user-images.githubusercontent.com/59634413/125994624-1f285715-b7bb-4ab4-ab06-389aaa34d20a.png" width="720" height="240">

## Key function - [Database]
* 충치 디텍팅이 끝나면 사용자 정보와 검진 결과를 각 데이터베이스에 저장
* 데이터베이스에서 관리하는 회원 정보에 치과 전문의가 웹 서버를 통해 접근 가능
* 담당 전문의가 디텍팅된 회원의 치아 상태를 보고 소견서 작성하여 추가 검진 가능
<img src="https://user-images.githubusercontent.com/59634413/125994875-1f2af689-1be6-4452-890b-6c9cc58697a6.png" width="720" height="240">

## Conclusion
* 딥러닝을 통해 충치, 아말감, 골드 크라운을 자동으로 분류하여 치아 상태 파악
* 검사 결과 보호자 SMS 전송, 근처 치과 지도(GPS) 기능을 이용하여 가정에서 중증 장애인의 신속한 초기 대처 가능
* 웹 서버 모니터링 기능을 제공하여 치과 전문의에게 추가 검진을 받을 수 있음

## 고찰
### 딥러닝
* 실제 시스템의 카메라로 촬영했을 때 나온 데이터셋이 많지 않기 때문에 Image augmentation을 사용했으나 데이터셋이 많은 것보다는 정확도가 떨어졌다.
* 치아가 안쪽부터 썩어서 색이 많이 변하지 않기 때문에 영상으로는 완전히 충치라고 판별할 수 없는 경우가 있었다. 이는 충분한 데이터 셋을 보유한다면 어느정도 보완이 가능하나 한계가 있다고 생각한다.
* 이미지 학습 시 Google Colaboratory 환경에서 진행했기 때문에 인터넷 세션 연결이 끊어지면 처음부터 다시 해야해서 시간이 오래걸렸다. 세션이 끊기지 않게 인터넷 설정 옵션을 조정했다.
* 이미지 학습 시 .jpg만 읽어오고 .JPG는 읽지 않는 문제 수정하였다.

### 영상처리
* 처음엔 영상의 명도와 채도를 조정하여 검정색으로 보이는 부분(충치라고 판단)의 개수를 알아낼 생각이었으나, 정확하지 않을 뿐 아니라 크라운과 아말감도 구별하기 어려움.
* Contour를 이용하여 치아의 경계면이 생기면 치아 정보를 하나하나 저장하여 충치 여부를 판단하려고 했음. 그러나 치아와 치아가 아닌 것은 구별하기 쉽지만, 치아끼리는 경계면 색상이 매우 비슷하기 때문에 따로 구별이 안되는 문제 발생.
* 딥러닝 CNN으로 충치를 구분하자!! -> 성공
* 사진 가지고 충치 디텍팅은 성공했으나 실제 카메라에서는 충치 디텍팅이 잘 되지 않는다.
* 데이터셋의 문제도 있었지만 문제는 화질!
* 카메라와 치아의 거리가 가깝기 때문에 화질 문제를 해결하려면 비용 문제가 생긴다.
* 초점이 잘 맞는 최적의 환경을 찾아 자동으로 사진을 찍고, 그 영상을 사용할 수 있을까??
* 모든 치아가 화면에 다 담겼을 때 가장 좋은 사진이 된다.
* 치아의 개수 추적 -> Watershed 알고리즘 이용
* 최상의 컨디션에 자동으로 촬영하기 때문에 중증 장애인분들이 편하게 이용할 수 있다.

### GUI & Key Function
* MFC에서 제공하는 GUI는 사용해봤지만 파이썬에서는 처음이라 고민 끝에 PyQT5 이용.
* 레이아웃의 중첩 문제, 메인 레이아웃과 서브 레이아웃을 어떻게 배치할 지?
* 동료들의 코드를 하나로 모으는 작업을 했기 때문에 소통의 부재가 많은 영향을 줬고, 개인적으로 시간을 따로 내어 코드를 분석한 것이 도움이 많이 되었다.
* 충치 디텍팅 과정이 길어 디텍팅 도중 프로그램의 응답이 없는 현상이 발생했는데 멀티 쓰레드를 이용하여 화면은 계속 띄워주어 응답 없음 현상 해결
* 치아 정보를 사람, 날짜별로 저장해야해서 폴더 생성에 신경을 많이 썼음.
