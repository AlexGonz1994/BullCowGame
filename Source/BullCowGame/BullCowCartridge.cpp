// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetUpGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ProcessGuess(Input);
}

void UBullCowCartridge::SetUpGame()
{
    HiddenWord = TEXT("word");
    HiddenWordLength = HiddenWord.Len();
    Lives = 4;
    GameOver = false;

    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord); //Debug Line
    PrintLine(TEXT("Welcome to the Bull and Cow game\n"));
    PrintLine(TEXT("You have %i lives: "), Lives);
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWordLength);
    PrintLine(TEXT("Enter your Guess. \nand press enter to continue"));

    CheckIsogram(HiddenWord);
}

void UBullCowCartridge::EndGame()
{
    GameOver = true;
    PrintLine(TEXT("\nPress Enter to play again"));
    Lives = 4;
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You Win"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWordLength)
    {
        PrintLine(TEXT("Sorry, The hidden word has %i letters"), HiddenWordLength);
        PrintLine(TEXT("You have %i remaining lives"), Lives);
        return;
    }

    if (!CheckIsogram(Guess))
    {
        PrintLine(TEXT("You have repeating letters"));
        return;
    }

    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You've run out of lives"));
        PrintLine(TEXT("The hidden word was %s"), *HiddenWord);

        EndGame();
        return;
    }

    PrintLine(TEXT("Guess again, you have %i remaining lives"), Lives);
}

bool UBullCowCartridge::CheckIsogram(FString Word) const
{
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 j = i + 1; j < Word.Len(); j++)
            if (Word[i] == Word[j])
            {
                return false;
            }
    };
    return true;
}