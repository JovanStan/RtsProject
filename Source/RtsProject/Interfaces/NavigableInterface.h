
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NavigableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UNavigableInterface : public UInterface
{
	GENERATED_BODY()
};


class RTSPROJECT_API INavigableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void MoveToLocation(const FVector& TargetLocation);
};
