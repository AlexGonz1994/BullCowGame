// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString &PlayerInput) override;
	void SetUpGame();
	void EndGame();
	void ProcessGuess(const FString &Guess);
	bool CheckIsogram(const FString &Word) const;
	TArray<FString> GetValidWord(const TArray<FString> &WordList) const;
	void GetBullCows(const FString &Guess, int32 &BullCount, int32 &CowCount) const;

	// Your declarations go below!
private:
	FString HiddenWord;
	int32 Lives;
	bool GameOver;
	TArray<FString> Isograms;
};
