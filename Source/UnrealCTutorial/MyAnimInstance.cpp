// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


void UMyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	auto Pawn = TryGetPawnOwner();

	//만약에 Pawn이 존재 한다면
	if (IsValid(Pawn))
	{
		//형변환
		auto Character = Cast<ACharacter>(Pawn);

		//만약에 Character가 존재 한다면
		if (IsValid(Character))
		{
			//CharacterMovement에 Character에 있는 CharacterMovement를 넣어줌
			CharacterMovement = Character->GetCharacterMovement();
		}
	}


}

