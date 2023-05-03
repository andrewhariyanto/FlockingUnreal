// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "FlockingManager.generated.h"

UCLASS()
class FLOCKING_API UFlockingManager : public UObject
{

public:
	GENERATED_BODY()

		void Init(UWorld* world, UStaticMeshComponent* mesh);
	void Flock();

private:
	UWorld* World;
	bool initialized;
	TArray<class AAgent*> Agents;
	FVector Rule1(AAgent* agent);
	FVector Rule2(AAgent* agent);
	FVector Rule3(AAgent* agent);
	FVector LimitBoundaries(AAgent* agent);
	FVector Wind();
};