
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RtsPlayerController.generated.h"

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
	
private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
    TObjectPtr<UInputAction> ZoomAction;
};
