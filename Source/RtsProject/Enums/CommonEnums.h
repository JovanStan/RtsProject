#pragma once

UENUM(BlueprintType)
enum class EResourceTypes : uint8
{
	Wood UMETA(DisplayName = "Wood"),
	Gold UMETA(DisplayName = "Gold"),
	Stone UMETA(DisplayName = "Stone"),
	Food UMETA(DisplayName = "Food"),
	Population UMETA(DisplayName = "Population")
};

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Villager UMETA(DisplayName = "Villager"),
	Swordman UMETA(DisplayName = "Swordman"),
	Knight UMETA(DisplayName = "Knight"),
	Archer UMETA(DisplayName = "Archer")
};