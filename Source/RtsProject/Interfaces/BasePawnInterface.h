
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BasePawnInterface.generated.h"

enum class ECharacterType : uint8;

UINTERFACE(MinimalAPI)
class UBasePawnInterface : public UInterface
{
	GENERATED_BODY()
};


class RTSPROJECT_API IBasePawnInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ECharacterType GetCharacterType(); 
};
