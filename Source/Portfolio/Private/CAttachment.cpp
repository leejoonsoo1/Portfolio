#include "CAttachment.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Components/ShapeComponent.h"
#include "UObject\Object.h"

// Sets default values
ACAttachment::ACAttachment()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");

	if (RootComp)
	{
		SetRootComponent(RootComp);
	}
}

// Called when the game starts or when spawned
void ACAttachment::BeginPlay()
{

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	GetComponents<UShapeComponent>(ShapeComponents);

	Super::BeginPlay();
}

void ACAttachment::OnCollision()
{
}

void ACAttachment::OffCollision()
{
}

void ACAttachment::ActorAttachTo(FName InSocketName)
{
	AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::ComponentAttachTo(USceneComponent* InComp, FName InSocketName)
{
	InComp->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACAttachment::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ACAttachment::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
