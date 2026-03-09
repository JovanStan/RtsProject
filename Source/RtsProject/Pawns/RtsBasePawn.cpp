
#include "RtsBasePawn.h"

#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"

ARtsBasePawn::ARtsBasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	RootComponent = CapsuleComponent;
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);
	
	SelectedIndicatorMesh = CreateDefaultSubobject<UStaticMeshComponent>("SelectedIndicatorMesh");
	SelectedIndicatorMesh->SetupAttachment(CapsuleComponent);
	SelectedIndicatorMesh->SetHiddenInGame(true);
	SelectedIndicatorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
}

void ARtsBasePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	OrientCharacterRotationToMovement();
}

void ARtsBasePawn::SelectActor_Implementation(const bool Select)
{
	SelectedIndicatorMesh->SetHiddenInGame(!Select);
}

void ARtsBasePawn::MoveToLocation_Implementation(const FVector& TargetLocation)
{
	bMoving = true;
	
	MoveTargetLocation = TargetLocation;
	AAIController* PawnAiController = Cast<AAIController>(GetController());
	PawnAiController->MoveToLocation(TargetLocation, AcceptanceDistance);
}


void ARtsBasePawn::OrientCharacterRotationToMovement()
{
	if (!bMoving) return;

	FVector MoveDirection = MoveTargetLocation - GetActorLocation();
	if (MoveDirection.Length() < AcceptanceDistance)
	{
		bMoving = false;
		return;
	}

	MoveDirection.Normalize(1);

	FRotator DesiredRotation = UKismetMathLibrary::MakeRotFromX(MoveDirection);
	DesiredRotation.Pitch = 0;
	DesiredRotation.Roll = 0;

	const FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), DesiredRotation, GetWorld()->GetDeltaSeconds(), CharacterTurnSpeed);
	SetActorRotation(NewRotation);
}





