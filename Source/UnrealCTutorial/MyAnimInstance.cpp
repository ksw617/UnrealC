// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"		   
#include "MyPlayer.h" 
#include "Kismet/KismetMathLibrary.h"// Ãß°¡


UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage(TEXT("/Game/ParagonSparrow/Characters/Heroes/Sparrow/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage"));

	if (AnimMontage.Succeeded())
	{
		AttackMontage = AnimMontage.Object;
	}
}

void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	
	auto Pawn = TryGetPawnOwner();
	
	if (IsValid(Pawn))
	{
		Character = Cast<AMyPlayer>(Pawn);
	
		if (IsValid(Character))
		{
			CharacterMovement = Character->GetCharacterMovement();
		}
	}


}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (IsValid(CharacterMovement))
	{
		Velocity = CharacterMovement->Velocity;
		GroundSpeed = Velocity.Size2D();
		IsFalling = CharacterMovement->IsFalling();
		

		FRotator ActorRotation = Character->GetActorRotation();
		FVector UnrotateVector = ActorRotation.UnrotateVector(Velocity);
		UnrotateVector.Normalize();

		Vertical = UnrotateVector.X;
		Horizontal = UnrotateVector.Y;

		auto Acceleration = CharacterMovement->GetCurrentAcceleration();

		ShouldMove = GroundSpeed > 0.1 && Acceleration != FVector::Zero();

		AimRotation = Character->GetBaseAimRotation();

		FRotator RotFromX = UKismetMathLibrary::MakeRotFromX(Velocity);

		FRotator DeltaRotation = RotFromX - AimRotation;
		DeltaRotation.Normalize();

		YawOffset = DeltaRotation.Yaw;

		UE_LOG(LogTemp, Log, TEXT("Yaw Offset : %f"), YawOffset);


	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	if (IsValid(AttackMontage))
	{
		if (!Montage_IsPlaying(AttackMontage))
		{
			Montage_Play(AttackMontage);

			Character->PlayerAttack();
		}
	}
}

