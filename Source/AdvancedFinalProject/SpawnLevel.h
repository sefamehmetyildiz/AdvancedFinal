// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnLevel.generated.h"

class ABaseLevel;

UCLASS()
class ADVANCEDFINALPROJECT_API ASpawnLevel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpawnLevel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpawnLevel(bool IsFirst);

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    FHitResult const& SweepResult);

protected:
	APawn* Player;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level2;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level3;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level4;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level5;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level6;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level7;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level8;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level9;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseLevel> Level10;

	TArray<ABaseLevel*> LevelList;

public:
	int RandomLevel;

	FVector SpawnLocation = FVector();
	FRotator SpawnRotation = FRotator();
	FActorSpawnParameters SpawnInfo = FActorSpawnParameters();
	bool bIsSpawning;
};
