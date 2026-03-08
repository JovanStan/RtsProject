
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RtsProject/Interfaces/SelectableInterface.h"
#include "RtsBaseBuilding.generated.h"

class UBoxComponent;

UCLASS()
class RTSPROJECT_API ARtsBaseBuilding : public AActor, public ISelectableInterface
{
	GENERATED_BODY()
	
public:	
	ARtsBaseBuilding();
	
	virtual void SelectActor_Implementation(const bool Select) override;

protected:
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> SelectedIndicatorMesh;
};
