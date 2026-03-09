
#include "RtsPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "RtsProject/Pawns/RtsBasePawn.h"
#include "RtsProject/Pawns/RtsControllerPawn.h"
#include "RtsProject/UI/RtsHUD.h"


ARtsPlayerController::ARtsPlayerController()
{
	bShowMouseCursor = true;
}

void ARtsPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	Hud = Cast<ARtsHUD>(GetHUD());
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
		
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ThisClass::Select);
		
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Started, this, &ThisClass::SelectStart);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ThisClass::SelectOnGoing);
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Completed, this, &ThisClass::SelectEnd);
		
		EnhancedInputComponent->BindAction(CommandAction, ETriggerEvent::Completed, this, &ThisClass::CommandSelectedActors);
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

void ARtsPlayerController::Select()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, false, HitResult);
	
	//Deselect Previous Actor
	if (SelectedActor)
	{
		if (SelectedActor->Implements<USelectableInterface>())
		{
			ISelectableInterface::Execute_SelectActor(SelectedActor, false);
		}
	}
	
	SelectedActor = HitResult.GetActor();
	if (SelectedActor)
	{
		//Select new Actor
		if (SelectedActor->Implements<USelectableInterface>())
		{
			ISelectableInterface::Execute_SelectActor(SelectedActor, true);
		}
	}
}

void ARtsPlayerController::CommandSelectedActors()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Camera, false, HitResult);
	if (!HitResult.bBlockingHit) return;

	if (SelectedActors.Num() > 0)
	{
		int i = SelectedActors.Num() / -2;
		for (AActor* Actor : SelectedActors)
		{
			if (Actor)
			{
				if (Actor->Implements<UNavigableInterface>())
				{
					INavigableInterface::Execute_MoveToLocation(Actor, HitResult.Location + FVector(0, 100 * i, 0));
					i++;
				}
			}
		}
	}
	else 
	{
		if (SelectedActor->Implements<UNavigableInterface>())
		{
			INavigableInterface::Execute_MoveToLocation(SelectedActor, HitResult.Location);
		}
	}
}

void ARtsPlayerController::SelectStart()
{
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);
	SelectionStartPosition = FVector2D(MouseX, MouseY);
}

void ARtsPlayerController::SelectOnGoing()
{
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);
	SelectionSize = FVector2D(MouseX - SelectionStartPosition.X, MouseY - SelectionStartPosition.Y);

	if (Hud)
	{
		Hud->ShowSelectionRect(SelectionStartPosition, SelectionSize);
	}
}

void ARtsPlayerController::SelectEnd()
{
	if (Hud)
	{
		//Select new actors
		Hud->HideSelectionRect();
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::SelectMultipleActors, .2f, false);
	}
}

void ARtsPlayerController::SelectMultipleActors()
{
	if (Hud)
	{
		//Deselect previous selected actors
		for (AActor* Actor : SelectedActors)
		{
			if (Actor)
			{
				if (Actor->Implements<USelectableInterface>())
				{
					ISelectableInterface::Execute_SelectActor(Actor, false);
				}
			}
		}
		SelectedActors.Empty();
		//Select new actors
		TArray<AActor*> AllSelectedActors = Hud->GetSelectedActors();
		for (AActor* Actor : AllSelectedActors)
		{
			if (Actor)
			{
				if (Actor->Implements<USelectableInterface>())
				{
					ISelectableInterface::Execute_SelectActor(Actor, true);
					SelectedActors.AddUnique(Actor);
				}
			}
		}
	}
}
