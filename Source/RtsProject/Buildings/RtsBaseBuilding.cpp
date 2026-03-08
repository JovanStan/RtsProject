

#include "RtsBaseBuilding.h"

ARtsBaseBuilding::ARtsBaseBuilding()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;
	
	SelectedIndicatorMesh = CreateDefaultSubobject<UStaticMeshComponent>("SelectedIndicatorMesh");
	SelectedIndicatorMesh->SetupAttachment(RootComponent);
	SelectedIndicatorMesh->SetHiddenInGame(true);
	SelectedIndicatorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ARtsBaseBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARtsBaseBuilding::SelectActor_Implementation(const bool Select)
{
	SelectedIndicatorMesh->SetHiddenInGame(!Select);
}

