// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCTUTORIAL_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "Character Movement", EditAnywhere, BlueprintReadOnly)
	bool ShouldMove;
public:
	UPROPERTY(VisibleAnywhere)
	UAnimMontage* AttackMontage;
	UPROPERTY(VisibleAnywhere)
	class UCharacterMovementComponent* CharacterMovement;
public:
	UEnemyAnimInstance();
public:
	void PlayAttackMontage();
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
