// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "Rhino_MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class RHINO_GJ2023_API URhino_MainWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetTimer(FString FormatedString) { Timer->SetText(FText::FromString(FormatedString)); };
	void SetDashCount(FString FormatedString) { DashCount->SetText(FText::FromString(FormatedString)); };
	void SetKillCount(FString FormatedString) { KillCount->SetText(FText::FromString(FormatedString)); };
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* DashCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* KillCount;
	
};
