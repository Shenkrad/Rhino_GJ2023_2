// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "Rhino_MainWidget.h"

#include "Rhino_HUD.generated.h"

/**
 * 
 */
UCLASS()
class RHINO_GJ2023_API ARhino_HUD : public AHUD
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void SetUIVisibility(ESlateVisibility State);
	UFUNCTION(BlueprintCallable)
		void SetTimer(FString FormatedString);
	UFUNCTION(BlueprintCallable)
		void SetDashCount(FString FormatedString);
	UFUNCTION(BlueprintCallable)
		void SetKillCount(FString FormatedString);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<URhino_MainWidget> WidgetClass;

	URhino_MainWidget* MainWidget;

	virtual void BeginPlay() override;
};
