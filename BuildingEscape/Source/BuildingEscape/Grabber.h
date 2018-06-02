// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Determines length at which objects can be grabbed
	float Reach = 100.0f;

	// Component that handles grabbing, moving, releasing
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	// Component that handles button/axis input
	UInputComponent* InputComponent = nullptr;

	// Line trace and grab what's in reach
	void Grab();

	// Release grabbed object
	void Release();

	// Verify input component is attached and bind actions to keys
	void SetupInputComponent();

	// Verify that component is present and store in PhysicsHandle
	void FindPhysicsHandleComponent();

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	// Return start and end vectors of line trace
	const FTwoVectors GetLineTracePoints();
};
