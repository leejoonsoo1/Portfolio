<img width="3428" height="1440" alt="1" src="https://github.com/user-attachments/assets/533d8d25-e4cf-4b0a-bafe-0fc5e9d8d6cd" />
<img width="3435" height="1440" alt="2" src="https://github.com/user-attachments/assets/a3c0b712-3dae-47b3-b37e-63de178a8549" />
<img width="954" height="822" alt="몬스터" src="https://github.com/user-attachments/assets/49c51d48-ffbd-426b-8f87-2ada0c4b13c0" />
<img width="891" height="928" alt="캐릭터" src="https://github.com/user-attachments/assets/594b72b4-65fd-4c82-8d53-0df0f54c1781" />

## 목차

# 프로젝트명: 몬스터 헌터 모작 Unreal Engine 5
1. 프로젝트 개요
2. AI 시스템
3. 

\*\*언리얼 엔진 5(Unreal Engine 5)\*\*를 기반으로 제작한 개인 프로젝트 입니다. 몬스터 AI, 스태미나 전투 구조, 상태 기반 전환 시스템 등을 중심으로 게임 구조에 맞춘 설계를 경험하며 개바ㄹ 역량을 키운 프로젝트입니다.
***

##  프로젝트 개요
<hr></hr>

|항목|내용|
|---|---|
|플랫폼|PC (Windows)|
|개발 기간| 2025.01 ~ 2025.04 (에셋 추출 및 개발)|
|개발 인원| 1인 개발|

주요 목표

* 몬스터 헌터 몬스터 중 리오레우스와 전투를 언리얼에서 구현.
* 구조화된 상태 머신과 BT/BB 기반 AI 설계
* 전반적인 시스템의 확장성과 유지보수성 고려



주요 특징

* 몬스터 AI : Behavior Tree + Blackboard 기반, 상태 전이 및 특정 패턴(Roar 등) 제어
* 무기 시스템 : ACWpeaon 기반 무기 클래스 구조, 대검/해머/활 등 교체 가능성 고려.
* 스테미나 시스템 : 소모/지연 회복 구조, 대시, 공격, 회피와 연동
* UI 연동 : 애님 노티파이와 연동된 UI 반응



사용 기술

* 엔진 : Unreal Engine 5
* 언어 : C++
* AI : Behavior Tree, Blackboard



시스템 구성

🔸몬스터 AI

* 상태 기반 전이 (Idle/Ptrol/Chase/Attack 등)
* 일정 시간 간격으로 Roar 모드 진입
* 체력/거리/시간에 따라 공격 패턴 분기



🔸 무기 시스템

* 상위 ACWeapon에서 공통 인터페이스 제공.



🔸 스태미나 \& 체력 시스템

* Timer로 회복 딜레이 제어
* 모든 소비 행동(행동, 달리기 등)과 연동.
