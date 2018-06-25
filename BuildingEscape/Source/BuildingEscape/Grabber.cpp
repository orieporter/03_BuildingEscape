// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();	

	FindPhysicsHandleComponent();

	SetupInputComponent();
}

// Find input component and bind actions to keys
void UGrabber::SetupInputComponent()
{
	// Look for attached Input Component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	// If input component exists
	if (InputComponent)
	{
		// Bind the input actions
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		// Log an error that no input component exists
		UE_LOG(LogTemp, Error, TEXT("Input component on %s not found!"), *GetOwner()->GetName());
	}
}

// Check if physics handle component exists and, if so, store it in PhysicsHandle
void UGrabber::FindPhysicsHandleComponent()
{
	// Look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// Physics handle is found
	}
	else
	{
		// Log an error that no component is found
		UE_LOG(LogTemp, Error, TEXT("Physics Handle on %s not found!"), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!PhysicsHandle) { return; }
	// if the physics handle has grabbed something
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holding to end of line trace
		PhysicsHandle->SetTargetLocation(GetLineTracePoints().v2);
	}
	
}

// Grab actor hit by line trace using PhysicsHandle
void UGrabber::Grab()
{
	// Line Trace and see if we reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();

	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (!PhysicsHandle) { return; }
	// If we hit an actor
	if (ActorHit)
	{
		// Grab it using PhysicsHandle
		PhysicsHandle->GrabComponent(
			ComponentToGrab,
			NAME_None, // No bone needed
			ComponentToGrab->GetOwner()->GetActorLocation(), // Where to grab it
			true // Allow rotation
		);
	}
}

// Release actor using PhysicsHandle
void UGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	// Release object using PhysicsHandle
	PhysicsHandle->ReleaseComponent();
}

// Finds first actor hit by line trace
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	// Setup query parameters
	FCollisionQueryParams TraceParameters(
		FName(TEXT("")), // No tag needed
		false, // Use simple collision
		GetOwner() // Ignore collision with self
	);

	FTwoVectors LineTracePoints = GetLineTracePoints();

	// Line trace out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit, LineTracePoints.v1, LineTracePoints.v2, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	return Hit;
}

// Return the beginning and end of the line trace
const FTwoVectors UGrabber::GetLineTracePoints()
{
	FVector StartLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(StartLocation, PlayerViewPointRotation);
	FVector EndLocation = StartLocation + (PlayerViewPointRotation.Vector() * Reach);

	return FTwoVectors(StartLocation, EndLocation);
}