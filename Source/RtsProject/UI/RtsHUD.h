
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RtsHUD.generated.h"


UCLASS()
class RTSPROJECT_API ARtsHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void ShowSelectionRect(const FVector2D& InSelectionRectStart, const FVector2D& InSelectionRectSize);
	void HideSelectionRect();
	
	TArray<AActor*> GetSelectedActors();
	
protected:
	virtual void DrawHUD() override;
	
private:
	bool bDrawSelectionRect = false;
	FVector2D SelectionRectStart;
	FVector2D SelectionRectSize;
	FLinearColor SelectionRectColor = FLinearColor(0.f, 0.6f, 1.f, .2f);
	
	void SelectActorsInRect();
	bool bSelectActors = false;
	
	UPROPERTY()
	TArray<AActor*> SelectedActors;
};
