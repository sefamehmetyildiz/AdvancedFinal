#include "SpawnLevel.h"
#include "BaseLevel.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"

ASpawnLevel::ASpawnLevel()
{
	PrimaryActorTick.bCanEverTick = true;


	bIsSpawning = false;
}

void ASpawnLevel::BeginPlay()
{
	Super::BeginPlay();


	SpawnLevel(true);
	SpawnLevel(false);
	SpawnLevel(false);
	SpawnLevel(false);
}

void ASpawnLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnLevel::SpawnLevel(bool IsFirst)
{
	if (bIsSpawning)
	{
		return;
	}

	bIsSpawning = true;

	SpawnLocation = FVector(0.0f, 1000.0f, 0.0f);
	SpawnRotation = FRotator(0.0f, 90.0f, 0.0f);

	if (!IsFirst && LevelList.Num() > 0)
	{
		ABaseLevel* LastLevel = LevelList.Last();
		SpawnLocation = LastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}

	RandomLevel = FMath::RandRange(1, 10);
	ABaseLevel* NewLevel = nullptr;

	switch (RandomLevel)
	{
	case 1:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level1, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 2:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level2, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 3:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level3, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 4:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level4, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 5:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level5, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 6:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level6, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 7:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level7, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 8:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level8, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 9:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level9, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	case 10:
		NewLevel = GetWorld()->SpawnActor<ABaseLevel>(Level10, SpawnLocation, SpawnRotation, SpawnInfo);
		break;
	default:
		break;
	}

	if (NewLevel)
	{
		if (NewLevel->GetTrigger())
		{
			NewLevel->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ASpawnLevel::OnOverlapBegin);
		}
		LevelList.Add(NewLevel);


		if (LevelList.Num() > 5)
		{
			LevelList.RemoveAt(0);
		}
	}

	bIsSpawning = false;
}

void ASpawnLevel::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                 bool bFromSweep, FHitResult const& SweepResult)
{
	SpawnLevel(false);
}
