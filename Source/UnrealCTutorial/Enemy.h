// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class UNREALCTUTORIAL_API AEnemy : public ACharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere)
	class UEnemyAnimInstance* EnemyAnimInstace;
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;
private:
	bool IsAttacking = false;
public:
	bool IsAttack() const { return IsAttacking; }
public:
	AEnemy();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	void EnemyAttack();
public:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterupted);
};
