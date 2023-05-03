// Fill out your copyright notice in the Description page of Project Settings.


#include "FlockingManager.h"
#include "Agent.h"
#include <Runtime/Engine/Classes/Kismet/KismetMathLibrary.h>

#define AGENT_COUNT 30
void UFlockingManager::Init(UWorld* world, UStaticMeshComponent* mesh) {
    UE_LOG(LogTemp, Warning, TEXT("Manager initialized"));

    World = world;
    float incr = (PI * 2.f) / AGENT_COUNT;
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (World != nullptr) {
            FRotator rotation = FRotator();

            FVector location = FVector(FMath::RandRange(-1000.0f, 1000.0f), FMath::RandRange(-1000.0f, 1000.0f), FMath::RandRange(-1000.0f, 1000.0f));
            /*
            location.X = FMath::Sin(incr * i) * 150.f;
            location.Z = FMath::Cos(incr * i) * 150.f;*/

            AAgent* agent = World->SpawnActor<AAgent>(location, rotation);
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}

void UFlockingManager::Flock() {
    FVector vector1 = FVector(0.0f, 0.0f, 0.0f);
    FVector vector2 = FVector(0.0f, 0.0f, 0.0f);
    FVector vector3 = FVector(0.0f, 0.0f, 0.0f);
    FVector vector4 = FVector(0.0f, 0.0f, 0.0f);
    FVector vector5 = FVector(0.0f, 0.0f, 0.0f);

    for (int i = 0; i < Agents.Num(); i++) {
        vector1 = Rule1(Agents[i]);
        vector2 = Rule2(Agents[i]);
        vector3 = Rule3(Agents[i]);
        vector4 = LimitBoundaries(Agents[i]);
        vector5 = Wind();
        Agents[i]->Acceleration = vector1 + vector2 + vector3 + vector4 + vector5;
    }
}

FVector UFlockingManager::Rule1(AAgent* agent) {
    FVector steering = FVector(0.0f, 0.0f, 0.0f);
    float perceptionRadius = 150.0f;
    int total = 0;
    for (int i = 0; i < Agents.Num(); i++) {
        FVector distance = Agents[i]->GetActorLocation() - agent->GetActorLocation();
        if (agent != Agents[i] && distance.Size() < perceptionRadius) {
            steering = steering + Agents[i]->GetActorLocation();
            total++;
        }
    }

    if (total > 0) {
        steering = steering / total;
        steering = steering - agent->GetActorLocation();
        steering = steering * agent->MaxSpeed / steering.Size();
        steering = steering - agent->Velocity;
        if (steering.Size() > agent->MaxForce) {
            steering = steering * agent->MaxForce / steering.Size();
        }
    }
    return steering;
}

FVector UFlockingManager::Rule2(AAgent* agent) {
    FVector steering = FVector(0.0f, 0.0f, 0.0f);
    float perceptionRadius = 30.0f;
    int total = 0;
    for (int i = 0; i < Agents.Num(); i++) {
        FVector distance = Agents[i]->GetActorLocation() - agent->GetActorLocation();
        if (agent != Agents[i] && distance.Size() < perceptionRadius) {
            FVector diff = agent->GetActorLocation() - Agents[i]->GetActorLocation();
            diff = diff / distance.Size();
            steering = steering + diff;
            total++;
        }
    }

    if (total > 0) {
        steering = steering / total;
        steering = steering * agent->MaxSpeed / steering.Size();
        steering = steering - agent->Velocity;
        if (steering.Size() > agent->MaxForce) {
            steering = steering * agent->MaxForce / steering.Size();
        }
    }
    return steering*1.2;
}

FVector UFlockingManager::Rule3(AAgent* agent) {
    FVector steering = FVector(0.0f, 0.0f, 0.0f);
    float perceptionRadius = 150.0f;
    int total = 0;
    for (int i = 0; i < Agents.Num(); i++) {
        FVector distance = Agents[i]->GetActorLocation() - agent->GetActorLocation();
        if (agent != Agents[i] && distance.Size() < perceptionRadius) {
            steering = steering + Agents[i]->Velocity;
            total++;
        }
    }

    if (total > 0) {
        steering = steering / total;
        steering = steering * agent->MaxSpeed / steering.Size();
        steering = steering - agent->Velocity;
        if (steering.Size() > agent->MaxForce) {
            steering = steering * agent->MaxForce / steering.Size();
        }
    }
    return steering;
}

FVector UFlockingManager::LimitBoundaries(AAgent* agent) {
    int Xmin = -1000, Xmax = 1000, Ymin = -1000, Ymax = 1000, Zmin = 0, Zmax = 2000;
    FVector result = FVector(0.0f, 0.0f, 0.0f);
    if (agent->GetActorLocation().X < Xmin) {
        result.X = Xmin - agent->GetActorLocation().X;
    }
    else if (agent->GetActorLocation().X > Xmax) {
        result.X = Xmax - agent->GetActorLocation().X;
    }
    if (agent->GetActorLocation().Y < Ymin) {
        result.Y = Ymin - agent->GetActorLocation().Y;
    }
    else if (agent->GetActorLocation().Y > Ymax) {
        result.Y = Ymax - agent->GetActorLocation().Y;
    }
    if (agent->GetActorLocation().Z < Zmin) {
        result.Z = Zmin - agent->GetActorLocation().Z;
    }
    else if (agent->GetActorLocation().Z > Zmax) {
        result.Z = Zmax - agent->GetActorLocation().Z;
    }

    if (!result.IsZero()) {
        result = result / result.Size();
        result = result * agent->MaxSpeed / result.Size();
        result = result - agent->Velocity;
        if (result.Size() > agent->MaxForce) {
            result = result * agent->MaxForce / result.Size();
        }
    }
    return result;
}

FVector UFlockingManager::Wind() {
    return FVector(0.05f, 0.0f, 0.0f);
}
