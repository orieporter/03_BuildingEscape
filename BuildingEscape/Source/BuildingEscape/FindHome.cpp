// Fill out your copyright notice in the Description page of Project Settings.

#include "FindHome.h"


// Sets default values for this component's properties
UFindHome::UFindHome()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UFindHome::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UFindHome::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Check if owner is overlapping HomeVolume
	if (GetOwner()->IsOverlappingActor(HomeVolume))
	{
		StartLocation = GetOwner()->GetActorLocation();
		StartRotation = GetOwner()->GetActorRotation();
		NearHome.Broadcast(); // TODO create blueprint event to smoothly move actor into volume
		UE_LOG(LogTemp, Warning, TEXT("%s is overlapping."), *GetOwner()->GetName());
	}
}

void UFindHome::SetIsHome(const bool bHome)
{
	IsHome = bHome;
	return;
}

bool UFindHome::GetIsHome()
{
	return IsHome;
}