
#include "RtsBasePawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ARtsBasePawn::ARtsBasePawn()
{
	PrimaryActorTick.bCanEverTick = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = CapsuleComponent;
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);
	
	SelectedIndicatorMesh = CreateDefaultSubobject<UStaticMeshComponent>("SelectedIndicatorMesh");
	SelectedIndicatorMesh->SetupAttachment(CapsuleComponent);
	SelectedIndicatorMesh->SetHiddenInGame(true);
	SelectedIndicatorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
}

void ARtsBasePawn::SelectActor_Implementation(const bool Select)
{
	SelectedIndicatorMesh->SetHiddenInGame(!Select);
}

void ARtsBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}




