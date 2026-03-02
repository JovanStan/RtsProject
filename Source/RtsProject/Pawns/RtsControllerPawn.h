
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RtsControllerPawn.generated.h"

class UFloatingPawnMovement;
class UCameraComponent;
class USpringArmComponent;
class UCapsuleComponent;

UCLASS()
class RTSPROJECT_API ARtsControllerPawn : public APawn
{
	GENERATED_BODY()

public:
	ARtsControllerPawn();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
};
