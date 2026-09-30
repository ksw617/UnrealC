// Fill out your copyright notice in the Description page of Project Settings.


#include "HpUserWidget.h"
#include "Components/ProgressBar.h"
#include "HpComponent.h"

void UHpUserWidget::BindHp(TObjectPtr<UHpComponent> HpActorComp)
{
	//HpComponent 등록해서
	HpComp = HpActorComp;

	//HpComponent 에 있는 OnHpChanged 함수 포인터에 UpdateHP 함수 등록
	HpComp->OnHpChanged.AddUObject(this, &UHpUserWidget::UpdateHP);

	UpdateHP();
}

void UHpUserWidget::UpdateHP()
{
	HP_ProgressBar->SetPercent(HpComp->GetHpRatio());
}
