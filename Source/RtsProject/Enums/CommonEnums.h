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