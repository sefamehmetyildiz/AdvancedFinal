// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RunnerCharacter.generated.h"

UCLASS()
class ADVANCEDFINALPROJECT_API ARunnerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* SideViewCamera;

public:
	ARunnerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveRight(float Value);

public:
	class UCameraComponent* GetSideViewCamera() const { return SideViewCamera; }

	void RestartLevel();

	void ResetSpeed();

	void ResetJump();
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    FHitResult const& SweepResult);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Coin")
	int totalCoin;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int timer;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	bool isDead;

private:
	float zPosition;
	FVector tempPos = FVector();

	FTimerHandle TimerHandle; // Timer için bir handle
	void UpdateCounter();

	bool CanMove;
};
