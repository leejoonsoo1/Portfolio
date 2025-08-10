<img width="3428" height="1440" alt="1" src="https://github.com/user-attachments/assets/533d8d25-e4cf-4b0a-bafe-0fc5e9d8d6cd" />
<img width="3435" height="1440" alt="2" src="https://github.com/user-attachments/assets/a3c0b712-3dae-47b3-b37e-63de178a8549" />
<img width="954" height="822" alt="몬스터" src="https://github.com/user-attachments/assets/49c51d48-ffbd-426b-8f87-2ada0c4b13c0" />
<img width="891" height="928" alt="캐릭터" src="https://github.com/user-attachments/assets/594b72b4-65fd-4c82-8d53-0df0f54c1781" />

***

## 목차
1. [프로젝트 개요](#1-프로젝트-개요)
2. [데이터 관리](#2-데이터-관리)
3. [구조](#3-구조)
4. [캐릭터 콤보](#4-캐릭터-콤보)
5. [AI 시스템](#5-AI-시스템)

   
# 프로젝트명: 몬스터 헌터 모작 Unreal Engine 5

## 1. 프로젝트 개요

\*\*언리얼 엔진 5(Unreal Engine 5.5 ver)\*\*를 기반으로 제작한 개인 프로젝트입니다. 몬스터 AI, 스태미나 전투 구조, 상태 기반 전환 시스템 등을 중심으로 게임 구조에 맞춘 설계를 경험하며 개발 역량을 키운 프로젝트입니다.

|항목|내용|
|---|---|
|플랫폼|PC (Windows)|
|개발 기간|2025.01 ~ 2025.04|
|개발 인원|1인 개발|

***

## 주요 목표

* 몬스터 헌터 몬스터 중 리오레우스와 전투를 언리얼에서 구현.
* 구조화된 상태 머신과 BT/BB 기반 AI 설계
* 전반적인 시스템의 확장성과 유지 보수 고려

## 주요 특징

* 몬스터 AI : Behavior Tree + Blackboard 기반, 상태 전이 및 특정 패턴(Roar 등) 제어
* 캐릭터 : State, AnimnNtifyState와 제어
* 무기 시스템 : ACWpeaon 기반 무기 클래스 구조, 대검/해머/활 등 교체 가능성 고려
* 스태미나 시스템 : 소모/지연 회복 구조, 대시, 공격, 회피와 연동
* UI 연동 : 캐릭터와 연동된 UI 반응


<hr></hr>


## 2. 데이터 관리
🔹캐릭터의 필수 애니메이션 데이터를 테이블로 저장
<img width="1718" height="909" alt="image" src="https://github.com/user-attachments/assets/4a34b374-aa81-442d-b18c-ee7bfbe74043" />

🔹무기의 필수 데이터를 테이블로 저장
<img width="1706" height="804" alt="image" src="https://github.com/user-attachments/assets/40a05a98-5076-4f17-929d-38308f1eb4a8" />

🔹 몬스터의 필수 데이터를 테이블로 저장
<img width="1710" height="877" alt="image" src="https://github.com/user-attachments/assets/fdeb5412-56be-4d48-9d00-c3e56a9c68b8" />


<hr></hr>


## 3. 구조
### 🔸 캐릭터
<br></br>
#### 설계 의도: 컴포넌트 간 결합도를 최소화하기 위해 직접 참조를 지양하고, Owner를 단일 통제 지점으로 두는 구조를 채택
<br></br>
<pre>
ACPlayerCharacter
|
├── UCAttachment
├── UCStateComponent
└── UCMontagesComponent
</pre>

* Owner–Component 구조
* UCAttachment
  * CWeapon을 상속받는 무기들은 AttachmentComp를 통해 모든 상호작용을 한다.
  * 충돌, 대미지, 차징마다 달라지는 대미지 비율 등.
  
* UCStateComponent
  * 캐릭터의 상태, 무기 타입을 관리.
  * 델리게이터로 Getter, Setter 함수를 조작

* UCMontagesComponent
  * 플레이어 전용 Montage Component
  * 플레이어에 관련된 애니메이션 데이터(공격모션 제외)를 불러와 캐릭터의 State에 맞게 함수를 호출한다.


<hr></hr>


### 🔸 몬스터
<pre>
ACMonster - ACMonster_Rathlos
                     │ 
                     ├── UCMonsterEmotionComponent
                     └── UCMonsterStateComponent
</pre>

* ACMonster-ACMonster_Rathalos (상속관계)
    * CMonster - TakeDamge, PlayAttackMontage 등 기본적으로 몬스터 부모가 갖는 함수를 정의
    * CMonster_Rathalos 부모로부터 상속된 함수를 실행한다.

* UCMonsterEmotionComponent, UCMonsterStateComponent
  *  몬스터별 고유 패턴을 반영하기 위해 Emotion과 State를 분리 설계
  *  UCMotionComponent는 Behavior트리에서 사용될 수 있는 상태를 구현 (안정, 경계, 순찰, 분노)
  *  UCMonsterStateComponent는 애니메이션 출력을 위한 상태를 구현 (기본, 액션,  스턴, 넉다운, 데드)


<hr></hr>


### 🔸 무기
ACWeapon-ACGreatSword (상속관계)
     * ACWeapon을 상속받아 무기 별 확장성을 고려하여 설계
     * ACWeapon에서 데이터와 Owner를 설정
     * ACWeapon에서 공통 인터페이스 제공
     * ACGreatSword 무기별 공격 모션이 다르기 떄문에 캐릭터의 공격 애니메이션을 ACGreatSword에 구현


<hr></hr>


## 4. 캐릭터 공격
🔹첫 번째 모션은 데이터 테이블로 관리하고, 연계 동작은 조건 충족 시 AnimNotifyState로 다음 동작을 실행
<img width="1531" height="904" alt="image" src="https://github.com/user-attachments/assets/656b8756-dcc0-493b-bb27-d3b4c79db391" />
* 후속 애니메이션 동작을 직관적으로 파악하기 용이

<img width="452" height="231" alt="image" src="https://github.com/user-attachments/assets/784933a9-1b43-41c9-bfe8-4a8e441acb91" />
 * AnimNotifyState에서 차징 여부를 판단하고, 노티파이 종료 시점까지 차징이 유지되면 콤보 가능한 공격 애니메이션을 출력
 * 차징을 유지하지 않고, 공격을 한다면, 콤보가 불가능한 공격 애니메이션을 출력


<hr></hr>

## 5. AI 시스템

<img width="1334" height="680" alt="image" src="https://github.com/user-attachments/assets/3c218868-a5d4-4acb-bc17-bddd302da23a" />

🔹ACAIController_Monster에 PerceptionUpdated 함수를 통해 캐릭터의 정보를 Black Board에 전달

<img width="904" height="717" alt="image" src="https://github.com/user-attachments/assets/df4fc9fb-3712-462f-9fd9-4a6957436b68" />
<img width="781" height="411" alt="image" src="https://github.com/user-attachments/assets/fa3409ac-65db-4286-9d8f-18eb2059b32a" />

🔹전달된 정보를 바탕으로 UCBTService_UpdateMonsterState에서 캐릭터와의 거리, 방향 등을 판단해 몬스터의 상태를 판단하여 Black Board에 상태 값을 저장한다.


<hr></hr>
