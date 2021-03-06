// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT(" Grabber"));

	/// Look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No PhysicsHandle %s  "), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->InputComponent;

	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s  has Input Component"), *GetOwner()->GetName());

		/// Bind the input action
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);


	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s  missing Input Component"), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// UE_LOG(LogTemp, Warning, TEXT("%s  %s"), *owner , *OwnerRotation);

	// Get player view point this tick
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewLocation,PlayerViewRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s  Rotation: %s"), *PlayerViewLocation.ToString(),*PlayerViewRotation.ToString());

	

	FVector LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * Reach;

	DrawDebugLine(GetWorld(), PlayerViewLocation, LineTraceEnd, FColor (255.f,0.f,0.f), false, 0.f, 0.f,10.f);

	/// setup query parameters
	FCollisionQueryParams TraceParameters (FName(TEXT("")), false, GetOwner());
	/// Line-trace (Ray-cast)
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
		);
	
	if (Hit.GetActor() ) {
		UE_LOG(LogTemp, Warning, TEXT("Hit object: %s  "), *Hit.GetActor()->GetName());
	}

}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"));
}

