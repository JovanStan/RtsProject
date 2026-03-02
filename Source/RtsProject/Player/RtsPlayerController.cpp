
#include "RtsPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "RtsProject/Pawns/RtsControllerPawn.h"


ARtsPlayerController::ARtsPlayerController()
{
	bShowMouseCursor = true;
}

void ARtsPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (!DefaultMappingContext) return;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ThisClass::Zoom);
	}
}

void ARtsPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementInput = Value.Get<FVector2D>();
	
	if (APawn* ControlledPawn = GetPawn())
	{
		const FRotator ControlledRotation = ControlledPawn->GetControlRotation();
		const FRotator YawRotation(0, ControlledRotation.Yaw, 0);
		
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		ControlledPawn->AddMovementInput(Forward, MovementInput.Y);
		ControlledPawn->AddMovementInput(Right, MovementInput.X);
	}
}

void ARtsPlayerController::Zoom(const FInputActionValue& Value)
{
	const float ZoomDirection = Value.Get<float>();
	if (APawn* MyPawn = GetPawn())
	{
		if (const ARtsControllerPawn* ControllerPawn = Cast<ARtsControllerPawn>(MyPawn))
		{
			float DesiredOrthoWidth = ControllerPawn->GetCamera()->OrthoWidth - ZoomDirection * ControllerPawn->GetZoomSpeed();
			DesiredOrthoWidth = FMath::Clamp(DesiredOrthoWidth, ControllerPawn->GetMinZoom(), ControllerPawn->GetMaxZoom());
			ControllerPawn->GetCamera()->OrthoWidth = DesiredOrthoWidth;
		}
	}
}
