// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino_HUD.h"


void ARhino_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass)
	{
		MainWidget= CreateWidget<URhino_MainWidget>(GetWorld(), WidgetClass);
		if (MainWidget)
		{
			MainWidget->AddToViewport();
			SetUIVisibility(ESlateVisibility::Visible);
		}
	}
}

void ARhino_HUD::SetUIVisibility(ESlateVisibility State)
{
	if (MainWidget)
		MainWidget->SetVisibility(State);
}

void ARhino_HUD::SetTimer(FString FromatedString)
{
	if (MainWidget)
		MainWidget->SetTimer(FromatedString);
}


void ARhino_HUD::SetDashCount(FString FormatedString)
{
	if (MainWidget)
		MainWidget->SetDashCount(FormatedString);
}

void ARhino_HUD::SetKillCount(FString FormatedString)
{
	if (MainWidget)
		MainWidget->SetKillCount(FormatedString);
}