
#pragma once
#include "RtsProject/Enums/CommonEnums.h"
#include "ResourceData.generated.h"


USTRUCT(BlueprintType)
struct FResourceData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EResourceTypes ResourceType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefaultValue = 0;
	
	FResourceData() : ResourceType(EResourceTypes::Wood), DisplayName(""), Texture(nullptr), DefaultValue(0) {}
	
	FResourceData(const EResourceTypes Type, const FString& Name, UTexture2D* Texture, int32 Value) : 
	ResourceType(Type), DisplayName(Name), Texture(Texture), DefaultValue(Value) {}
};