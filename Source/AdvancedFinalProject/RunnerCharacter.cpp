// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerCharacter.h"

#include "Coin.h"
#include "Engine.h"
#include "PowerJump.h"
#include "PowerSpeed.h"
#include "Spikes.h"
#include "TripleCoin.h"
#include "WallSpike.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ARunnerCharacter::ARunnerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	GetCharacterMovement()->GravityScale = 3.0f;
	GetCharacterMovement()->AirControl = 0.60f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.0f;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	GetCharacterMovement()->MaxFlySpeed = 400.0f;

	tempPos = GetActorLocation();
	zPosition = tempPos.Z + 300.0f;
}

// Called when the game starts or when spawned
void ARunnerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARunnerCharacter::OnOverlapBegin);

	isDead = false;
	CanMove = true;
	timer = 0;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&ARunnerCharacter::UpdateCounter,
		1.0f,
		true
	);
}

// Called every frame
void ARunnerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	tempPos = GetActorLocation();
	tempPos.X -= 850.0f;
	tempPos.Z = zPosition;
	SideViewCamera->SetWorldLocation(tempPos);
}

// Called to bind functionality to input
void ARunnerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ARunnerCharacter::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void ARunnerCharacter::MoveRight(float Value)
{
	if (CanMove)
	{
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
	}
}

void ARunnerCharacter::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName("GameOverScene"));

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;

		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputMode);
	}

	totalCoin = 0;
	PlayerController->bShowMouseCursor = false;
	PlayerController->SetInputMode(FInputModeGameOnly());


	timer = 0;
}

void ARunnerCharacter::ResetSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ARunnerCharacter::ResetJump()
{
	GetCharacterMovement()->JumpZVelocity = 1000.0f;
}

void ARunnerCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
                                      class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      FHitResult const& SweepResult)
{
	if (OtherActor != nullptr)
	{
		ASpikes* WallSpike = Cast<AWallSpike>(OtherActor);
		ASpikes* Spike = Cast<ASpikes>(OtherActor);

		//PowerUPS
		ASpikes* Coin = Cast<ACoin>(OtherActor);
		ASpikes* PowerSpeed = Cast<APowerSpeed>(OtherActor);
		ASpikes* PowerJump = Cast<APowerJump>(OtherActor);
		ASpikes* TripleCoin = Cast<ATripleCoin>(OtherActor);


		if (Coin)
		{
			totalCoin++;
			Coin->Destroy();
		}
		else if (PowerJump)
		{
			GetCharacterMovement()->JumpZVelocity = 2000.0f;
			FTimerHandle PowerJumpTimer;
			GetWorldTimerManager().SetTimer(PowerJumpTimer, this, &ARunnerCharacter::ResetJump, 3.0f, false);
			PowerJump->Destroy();
		}

		else if (PowerSpeed)
		{
			GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
			FTimerHandle PowerSpeedTimer;
			GetWorldTimerManager().SetTimer(PowerSpeedTimer, this, &ARunnerCharacter::ResetSpeed, 3.0f, false);
			PowerSpeed->Destroy();
		}

		else if (TripleCoin)
		{
			totalCoin += 3;
			TripleCoin->Destroy();
		}

		else if (WallSpike || Spike)
		{
			CanMove = false;
			isDead = true;
			GetMesh()->Deactivate();
			GetMesh()->SetVisibility(false);

			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &ARunnerCharacter::RestartLevel, 1.0f, false);
		}
	}
}


void ARunnerCharacter::UpdateCounter()
{
	timer++;
}
