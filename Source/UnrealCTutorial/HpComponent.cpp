// Fill out your copyright notice in the Description page of Project Settings.


#include "HpComponent.h"

// Sets default values for this component's properties
UHpComponent::UHpComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHp = 100.f;
}


void UHpComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHp(MaxHp);
	
}

