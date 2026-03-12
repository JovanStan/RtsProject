
#pragma once
#include "Engine/DataTable.h"
#include "RtsProject/Pawns/RtsBasePawn.h"
#include "CharacterData.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ECharacterType CharacterType;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString DisplayName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<UTexture2D> Texture;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BaseHealth = 0;
	
	FCharacterData() : CharacterType(ECharacterType::Villager), DisplayName(""), Texture(nullptr), BaseHealth(0) {}
	
	FCharacterData(const ECharacterType Type, const FString& Name, UTexture2D* Texture, int32 Value) : 
	CharacterType(Type), DisplayName(Name), Texture(Texture), BaseHealth(Value) {}
};