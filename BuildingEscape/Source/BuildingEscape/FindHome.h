// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Engine/TriggerVolume.h"
#include "FindHome.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHomeEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UFindHome : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFindHome();

	UFUNCTION(BlueprintCallable)
		bool GetIsHome();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Home)
		ATriggerVolume* HomeVolume;

	UPROPERTY(BlueprintReadOnly)
		FVector StartLocation;

	UPROPERTY(BlueprintReadOnly)
		FRotator StartRotation;

	UFUNCTION(BlueprintCallable)
		void SetIsHome(const bool bHome);

public:	
	// Called every fram
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(BlueprintAssignable)
		FHomeEvent NearHome;

	bool IsHome = false;
	
};
