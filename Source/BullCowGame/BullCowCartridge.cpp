// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Isograms = GetValidWord(Words);
    SetUpGame();

    // PrintLine(TEXT("Number of valid words %i"), GetValidWord(Words).Num());
}

void UBullCowCartridge::OnInput(const FString &PlayerInput) // When the player hits enter
{
    if (GameOver)
    {
        ClearScreen();
        SetUpGame();
    }
    else
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetUpGame()
{

    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
    Lives = 4;
    GameOver = false;

    PrintLine(TEXT("Welcome to the Bull and Cow game\n"));
    PrintLine(TEXT("You have %i lives "), Lives);
    PrintLine(TEXT("The Word is %s"), *HiddenWord);
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("Enter your Guess. \nand press enter to continue"));

    CheckIsogram(HiddenWord);
}

void UBullCowCartridge::EndGame()
{
    GameOver = true;
    PrintLine(TEXT("\nPress Enter to play again"));
}

void UBullCowCartridge::ProcessGuess(const FString &Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You Win"));
        EndGame();
        return;
    }

    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Sorry, The hidden word has %i letters"), HiddenWord.Len());
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

    int32 Bulls, Cows;
    GetBullCows(Guess, Bulls, Cows);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Bulls, Cows);

    PrintLine(TEXT("Guess again, you have %i remaining lives"), Lives);
}

bool UBullCowCartridge::CheckIsogram(const FString &Word) const
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

TArray<FString> UBullCowCartridge::GetValidWord(const TArray<FString> &WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && CheckIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    };
    return ValidWords;
}

void UBullCowCartridge::GetBullCows(const FString &Guess, int32 &BullCount, int32 &CowCount) const
{
    BullCount = 0;
    CowCount = 0;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            BullCount++;
            continue;
        }
        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                CowCount++;
            }
        }
    }
}