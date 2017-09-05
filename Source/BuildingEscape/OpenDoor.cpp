// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner1 = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	FString Owner = GetOwner()->GetName();
	FString OwnerRotation = GetOwner()->GetActorRotation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s  %s"), *Owner, *OwnerRotation);

	
	
	Owner1->SetActorRotation(FRotator (0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	FString Owner = GetOwner()->GetName();
	FString OwnerRotation = GetOwner()->GetActorRotation().ToString();
//	UE_LOG(LogTemp, Warning, TEXT("%s  %s"), *Owner, *OwnerRotation);

	
	
	Owner1->SetActorRotation(FRotator (0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	if ((GetWorld()->GetTimeSeconds()-LastDoorOpenTime) >= DoorCloseDelay)
	{
		CloseDoor();
	}
}

