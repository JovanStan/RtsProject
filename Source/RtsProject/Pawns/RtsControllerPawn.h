
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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom", meta=(AllowPrivateAccess=true))
	float ZoomSpeed = 10.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom", meta=(AllowPrivateAccess=true))
	float MaxZoom = 2500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Zoom", meta=(AllowPrivateAccess=true))
	float MinZoom = 600.f;
	
public:
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE float GetZoomSpeed() const { return ZoomSpeed; }
	FORCEINLINE float GetMaxZoom() const { return MaxZoom; }
	FORCEINLINE float GetMinZoom() const { return MinZoom; }
};
