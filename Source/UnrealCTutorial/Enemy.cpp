

#include "Enemy.h"
#include "EnemyAIController.h"
#include "EnemyAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "HpUserWidget.h"

AEnemy::AEnemy()
{
 	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0, 0.0, -90.0), FRotator(0.0, -90.0, 0.0));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInst(TEXT("/Script/Engine.AnimBlueprint'/Game/Animations/ABP_Enemy.ABP_Enemy_C'"));
	if (AnimInst.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimInst.Class);
	}

	AIControllerClass = AEnemyAIController::StaticClass();

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(GetRootComponent());
	HpBar->SetRelativeLocation(FVector(0.0, 0.0, 130.0));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	HpBar->SetDrawSize(FVector2D(200.0, 20.0));

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	EnemyAnimInstace = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	EnemyAnimInstace->OnMontageEnded.AddDynamic(this, &AEnemy::OnAttackMontageEnded);
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Log, TEXT("Damaged : %f"), Damage);
	return 0.0f;
}

void AEnemy::EnemyAttack()
{
	if (IsValid(EnemyAnimInstace))
	{
		if (!IsAttacking)
		{
			EnemyAnimInstace->PlayAttackMontage();
			IsAttacking = true;
		}
	}
}

void AEnemy::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterupted)
{
	IsAttacking = false;
}

