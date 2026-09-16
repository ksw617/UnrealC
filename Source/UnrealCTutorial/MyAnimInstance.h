// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCTUTORIAL_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "Character Movement", EditAnywhere, BlueprintReadOnly)
	bool ShouldMove;
private:
	UPROPERTY(VisibleAnywhere)
	class UCharacterMovementComponent* CharacterMovement;

public:
	virtual void NativeBeginPlay() override;
	
};
