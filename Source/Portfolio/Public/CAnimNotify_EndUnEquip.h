#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CAnimNotify_EndUnEquip.generated.h"

/*
 *	2025. 03. 02 AM 03 : 47
 *	UnEquip 관련 노티파이 스테이트가 사용되지 않아 새롭게 구현함.
 *	Receive가 실행되면 OwnerCharacter의 EndUnEquipping을 호출하는 단순한 동작 수행.
 */
UCLASS()
class PORTFOLIO_API UCAnimNotify_EndUnEquip : public UAnimNotify
{
	GENERATED_BODY()

public:
	FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};