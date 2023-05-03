// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"

AAgent::AAgent() {
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AgentMesh"));
	RootComponent = Mesh;
	Velocity = FVector(FMath::RandRange(-2.0f, 2.0f), FMath::RandRange(-2.0f, 2.0f), FMath::RandRange(-2.0f, 2.0f));
	Acceleration = FVector(0.0f);
	MaxForce = 1.0f;
	MaxSpeed = 4.0f;
}

void AAgent::BeginPlay() {
	Super::BeginPlay();
}

void AAgent::Init(UStaticMeshComponent* mesh, int id) {
	UE_LOG(LogTemp, Warning, TEXT("Agent initialized."));
	Mesh->SetStaticMesh(mesh->GetStaticMesh());
}

void AAgent::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("Values are %f, %f, %f"), Velocity.X, Velocity.Y, Velocity.Z);

	FVector loc = GetActorLocation();
	SetActorLocation(loc + Velocity);
	Velocity = Velocity + Acceleration;
	//Limit Velocity rule
	if (Velocity.Size() > MaxSpeed) {
		Velocity = Velocity * MaxSpeed / Velocity.Size();
	}
	Acceleration = FVector::Zero();
}