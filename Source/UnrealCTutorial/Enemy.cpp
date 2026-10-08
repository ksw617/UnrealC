

#include "Enemy.h"
#include "EnemyAIController.h"
#include "EnemyAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "HpUserWidget.h"
#include "HpComponent.h"
#include "Kismet/GameplayStatics.h"	 //추가


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

	static ConstructorHelpers::FClassFinder<UHpUserWidget> UserWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));
	if (UserWidget.Succeeded())
	{
		HpBar->SetWidgetClass(UserWidget.Class);
	}

	HpComponent = CreateDefaultSubobject<UHpComponent>(TEXT("HP Component"));

}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	EnemyAnimInstace = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	EnemyAnimInstace->OnMontageEnded.AddDynamic(this, &AEnemy::OnAttackMontageEnded);
	

	auto HpWidget = Cast<UHpUserWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(HpComponent);
	}
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
	HpComponent->OnDamaged(Damage);

	UE_LOG(LogTemp, Log, TEXT("Causer %s"), *EventInstigator->GetPawn().GetName());
	
	return Damage;
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

void AEnemy::EnemyHit()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 200.f;
	float AttackRadius = 40.f;
	float AttackHalfHeight = 90.f;

	FVector startPos = GetActorLocation();
	FVector Forward = GetActorForwardVector();
	FVector FwdVector = Forward * AttackRange;

	FVector EndPos = startPos + FwdVector;
	FQuat AttackRotation = FRotationMatrix::MakeFromZ(Forward).ToQuat();

	bool Result = GetWorld()->SweepSingleByChannel
	(
		OUT HitResult,
		startPos,
		EndPos,
		AttackRotation,
		ECC_GameTraceChannel1,
		FCollisionShape::MakeCapsule(AttackRadius, AttackHalfHeight),
		Params
	);

	FColor DebugColor = Result ? FColor::Green : FColor::Red;
	FVector Center = startPos + FwdVector * 0.5f;

	DrawDebugCapsule
	(
		GetWorld(),
		Center,
		AttackHalfHeight,
		AttackRadius,
		AttackRotation,
		DebugColor,
		false,
		2.0f
	);


	//Damage 주기
	if (Result && HitResult.GetActor())
	{
		auto Target = HitResult.GetActor();

		UGameplayStatics::ApplyDamage(Target, 10.f, GetController(), this, NULL);
	}

}

void AEnemy::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterupted)
{
	IsAttacking = false;
}

