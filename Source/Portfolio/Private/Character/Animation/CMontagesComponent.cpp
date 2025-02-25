// Fill out your copyright notice in the Description page of Project Settings.


#include "CMontagesComponent.h"
#include "GameFramework/Character.h"

// Sets default values
UCMontagesComponent::UCMontagesComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	

}

// Called when the game starts or when spawned
void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!DataTable)
	{
		return;
	}

	TArray<FMontageData*> ReadDatas;
	DataTable->GetAllRows<FMontageData>("", ReadDatas);

	for (int32 i = 0; i < (int32)EStateType::Max; i++)
	{
		for (const auto& It : ReadDatas)
		{
			if ((EStateType)i == It->Type)
			{
				Datas[i] = It;
				break;
			}
		}
	}
}

void UCMontagesComponent::PlayEvade()
{
	PlayAnimMontage(EStateType::Evade);
}

void UCMontagesComponent::PlayHitted()
{
	PlayAnimMontage(EStateType::Hitted);
}

void UCMontagesComponent::PlayAnimMontage(EStateType InType)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	
	if (!OwnerCharacter) return;

	const FMontageData* Data = Datas[(int32)InType];

	if (Data && Data->AnimMontage)
	{
		OwnerCharacter->PlayAnimMontage(Data->AnimMontage, Data->PlayRate, Data->StartSection);
	}
}