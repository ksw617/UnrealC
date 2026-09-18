#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyAnimInstance.h" 

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, -90.0), FRotator(0.0, -90.0, 0.0));
	}

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));


	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
	
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeLocationAndRotation(FVector(0.0, 0.0, 100.0), FRotator(-25.0, 0.0, 0.0));
	SpringArm->bUsePawnControlRotation = true;

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInst(TEXT("/Script/Engine.AnimBlueprint'/Game/Animations/ABP_Character.ABP_Character_C'"));

	if (AnimInst.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimInst.Class);
	}

}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimInstace = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForwardBackward"), this, &AMyCharacter::KeyUpDown);
	PlayerInputComponent->BindAxis(TEXT("MoveLeftRight"), this, &AMyCharacter::KeyLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &AMyCharacter::LookLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpDown"), this, &AMyCharacter::LookUpDown);

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::KeyAttack);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &ACharacter::StopJumping);
	
}

void AMyCharacter::KeyUpDown(float value)
{
	AddMovementInput(GetActorForwardVector(), value, false);
}

void AMyCharacter::KeyLeftRight(float value)
{
	AddMovementInput(GetActorRightVector(), value, false);
}

void AMyCharacter::LookLeftRight(float value)
{
	AddControllerYawInput(value);
}

void AMyCharacter::LookUpDown(float value)
{
	AddControllerPitchInput(value);
}

void AMyCharacter::KeyAttack()
{
	if (IsValid(AnimInstace))
	{
		AnimInstace->PlayAttackMontage();
	}
}

void AMyCharacter::PlayerAttack()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 200.f;		//공격범위
	float AttackRadius = 40.f;		//캡슐의 반지름
	float AttackHalfHeight = 90.f;	//캡슐의 높이의 반 길이
	FVector StartPos = GetActorLocation(); //시작 위치 : 현재 Actor의 위치
	FVector EndPos = StartPos + GetActorForwardVector() * AttackRange;

	bool Result = GetWorld()->SweepSingleByChannel
	(
		OUT HitResult,			//충돌 결과를 저장하는 변수
		StartPos,				//시작지점
		EndPos,					//끝 지점
		FQuat::Identity,		//회전 (기본값)
		ECC_Visibility,			//충돌 채널(Visibility)
		FCollisionShape::MakeCapsule(AttackRadius, AttackHalfHeight), // 충돌 형태
		Params
	);
											
	//충돌이 되었다면
	if (Result)
	{
		UE_LOG(LogTemp, Log, TEXT("Collision"));
	}



}

