// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HpComponent.generated.h"

//DECLARE_MULTICAST_DELEGATE(함수포인터이름)
DECLARE_MULTICAST_DELEGATE(FOnHpChanged)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCTUTORIAL_API UHpComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	float MaxHp;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	float Hp;
public:
	//함수 포인터
	FOnHpChanged OnHpChanged; // - void UpdateHP();
public:	
	UHpComponent();
protected:
	virtual void BeginPlay() override;

public:	
	void OnDamaged(float DamagedAmount) { SetHp(Hp - DamagedAmount); }
	float GetHp() const { return Hp; }
	//HP가 변하면 progress bar도 변하게
	void SetHp(float NewHp) { Hp = NewHp > 0 ? NewHp : 0; OnHpChanged.Broadcast(); };
	float GetHpRatio() const { return MaxHp <= 0.f || Hp < 0.f ? 0.0f : Hp / MaxHp; }
		
};
