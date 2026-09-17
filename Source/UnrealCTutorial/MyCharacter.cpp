#include "MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MyAnimInstance.h" // Ãß°¡

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

	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::KeyAttack);

}

void AMyCharacter::KeyUpDown(float value)
{
	AddMovementInput(GetActorForwardVector(), value, false);
}

void AMyCharacter::KeyLeftRight(float value)
{
	AddMovementInput(GetActorRightVector(), value, false);
}

void AMyCharacter::KeyAttack()
{
	if (IsValid(AnimInstace))
	{
		AnimInstace->PlayAttackMontage();
	}
}

