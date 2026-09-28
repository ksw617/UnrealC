// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UEnemyAnimInstance::UEnemyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Attack_PrimaryA_Montage.Attack_PrimaryA_Montage"));

	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
}

void UEnemyAnimInstance::PlayAttackMontage()
{
	if (IsValid(AttackMontage))
	{
		if (!Montage_IsPlaying(AttackMontage)) 
		{
			Montage_Play(AttackMontage);
		}
	}
}

void UEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		ACharacter* MyCharacter = Cast<ACharacter>(Pawn);
		if (IsValid(MyCharacter))
		{
			CharacterMovement = MyCharacter->GetCharacterMovement();
		}
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(CharacterMovement))
	{
		FVector Velocity = CharacterMovement->Velocity;
		float GroundSpeed = Velocity.Size2D();

		ShouldMove = GroundSpeed >= 1.0f;
	}
}

