
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RtsPlayerController.generated.h"

class ARtsBasePawn;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class RTSPROJECT_API ARtsPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARtsPlayerController();
	
protected:
	virtual void SetupInputComponent() override;
	
	void Move(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);
	void Select();
	void CommandSelectedActor();
	
private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
    TObjectPtr<UInputAction> ZoomAction;
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> SelectAction;
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> CommandAction;
	
	UPROPERTY()
	TObjectPtr<AActor> SelectedActor;
};
