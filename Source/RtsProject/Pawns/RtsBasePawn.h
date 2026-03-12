
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RtsProject/Enums/CommonEnums.h"
#include "RtsProject/Interfaces/BasePawnInterface.h"
#include "RtsProject/Interfaces/NavigableInterface.h"
#include "RtsProject/Interfaces/SelectableInterface.h"
#include "RtsBasePawn.generated.h"

enum class ECharacterType : uint8;
class UFloatingPawnMovement;
class UCapsuleComponent;

UCLASS()
class RTSPROJECT_API ARtsBasePawn : public APawn, public ISelectableInterface, public INavigableInterface, public IBasePawnInterface
{
	GENERATED_BODY()

public:
	ARtsBasePawn();
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void SelectActor_Implementation(const bool Select) override;
	virtual void MoveToLocation_Implementation(const FVector& TargetLocation) override;
	virtual ECharacterType GetCharacterType_Implementation() override;

protected:
	void OrientCharacterRotationToMovement();
	
	FVector MoveTargetLocation;
	bool bMoving = false;
	
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceDistance = 50.f;
	UPROPERTY(EditDefaultsOnly)
	float CharacterTurnSpeed = 5.f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> SelectedIndicatorMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	ECharacterType CharacterType = ECharacterType::Villager;
};
