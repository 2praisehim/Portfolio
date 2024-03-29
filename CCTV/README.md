# 얼굴인식 CCTV
### 진행기간
2020.04 ~ 2020.06
### SKILLS / IDE
OpenCV 2.4.13(Image Processing)

Bluez 5.4 for Target Board

C++

Linux(Achro-IMX6 Target Board)

Linux(RaspberryPI)

### Rewards
리눅스시스템설계 A+

## 내가 맡은 부분
1. OpenCV
2. 디바이스 모듈 드라이버
3. 블루투스 모바일 통신

## 목표
1. 타겟 보드에서는 모터를 이용하여 카메라를 회전시킬 수 있다.
2. 타겟 보드와 블루투스 통신을 통하여 모터를 제어하여 카메라의 회전 각을 조종한다.
3. 카메라로 찍은 영상에 영상처리를 이용하여 얼굴을 인식하고 미리 저장한다.
4. 저장된 얼굴이 아닌 다른 얼굴을 인식하면 타겟 보드에 있는 부저가 울린다.

## 구현 시스템 흐름
1. 타겟 보드에 있는 카메라로 얼굴인식을 한다. 미리 저장된 얼굴이 아니면 부저가 울린다.
2. 카메라의 회전 각은 타겟 보드의 딥 스위치로 조정할 수 있다.

## 구현 결과
![image](https://user-images.githubusercontent.com/59634413/126008010-59e09900-3a34-48ab-a5af-04ffc51053d1.png)
![image](https://user-images.githubusercontent.com/59634413/126007986-1aed6b1f-9a4a-4ec8-a92c-f28ea02a5415.png)
![image](https://user-images.githubusercontent.com/59634413/126008023-368b8e79-61e2-4113-b8f3-89f808153e28.png)

## 고찰
* 처음에 기획은 블루투스 통신을 이용하여 카메라의 회전 각을 조정할 수 있는 얼굴인식 CCTV였지만, 타겟 보드에서 블루투스 설치를 실패했다.
* 블루투스 4.0의 제어를 하기 위하여 4.0 표준 이상이 지원되는 bluez 5.4를 크로스컴파일하여 실행시켰으나, 종속 라이브러리인 Glib을 설치하는 과정에서 Glib의 종속 라이브러리인 zlib, libffi가 설치된 것을 인지하지 못하는 현상 발생.
* x86이나 ARM에 올라가는 데비안, 레드햇 계열의 배포판에서는 1 ~ 2 줄의 명령어로 패키지 매니저를 통해 설치가 가능했던 것에 비해 타겟 보드의 환경에 맞추어 소스코드를 빌드해주는 과정에서 개발환경에 대한 이해도가 더 필요함을 느겼다.
* 제조사에서 개발환경을 지원해주는 정도를 느끼게 되었고, 개발환경 설정이 제품 개발 기간에 많은 영향을 준다는 것을 알게되었다.
