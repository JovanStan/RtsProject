
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RtsProject/Interfaces/SelectableInterface.h"
#include "RtsBasePawn.generated.h"

class UFloatingPawnMovement;
class UCapsuleComponent;

UCLASS()
class RTSPROJECT_API ARtsBasePawn : public APawn, public ISelectableInterface
{
	GENERATED_BODY()

public:
	ARtsBasePawn();
	
	virtual void SelectActor_Implementation(const bool Select) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> SelectedIndicatorMesh;
};
