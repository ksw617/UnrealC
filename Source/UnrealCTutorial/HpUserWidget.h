// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpUserWidget.generated.h"

/**
 * 
 */

class UHpComponent;
class UProgressBar;

UCLASS()
class UNREALCTUTORIAL_API UHpUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UHpComponent> HpComp;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HP_ProgressBar;
public:
	void BindHp(TObjectPtr<UHpComponent> HpActorComp);
	void UpdateHP();

	
};
