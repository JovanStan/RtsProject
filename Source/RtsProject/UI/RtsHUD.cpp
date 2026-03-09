
#include "RtsHUD.h"

void ARtsHUD::DrawHUD()
{
	Super::DrawHUD();
	
	if (bDrawSelectionRect)
	{
		DrawRect(SelectionRectColor, SelectionRectStart.X, SelectionRectStart.Y, SelectionRectSize.X, SelectionRectSize.Y);
	}
	if (bSelectActors)
	{
		SelectActorsInRect();
	}
}

void ARtsHUD::ShowSelectionRect(const FVector2D& InSelectionRectStart, const FVector2D& InSelectionRectSize)
{
	SelectionRectStart = InSelectionRectStart;
	SelectionRectSize = InSelectionRectSize;
	bDrawSelectionRect = true;
}

void ARtsHUD::HideSelectionRect()
{
	bDrawSelectionRect = false;
	bSelectActors = true;
}

TArray<AActor*> ARtsHUD::GetSelectedActors()
{
	return SelectedActors;
}

void ARtsHUD::SelectActorsInRect()
{
	SelectedActors.Empty();
	const FVector2D FirstPoint = SelectionRectStart;
	const FVector2D SecondPoint = SelectionRectStart + SelectionRectSize;
	GetActorsInSelectionRectangle<AActor>(FirstPoint, SecondPoint, SelectedActors, false);
	bSelectActors = false;	
}
