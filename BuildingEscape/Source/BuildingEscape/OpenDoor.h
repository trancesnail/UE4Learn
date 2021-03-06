// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnDoorEvent );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void SetDoorRotation(FRotator NewRotation);

	void OpenDoor();
	void CloseDoor();

	UPROPERTY(BlueprintAssignable)
	FOnDoorEvent OnOpenRequest;
	UPROPERTY(BlueprintAssignable)
	FOnDoorEvent OnCloseRequest;
private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;
	UPROPERTY(EditAnywhere)
	ATriggerVolume * PressurePlate;
	UPROPERTY(EditAnywhere)
	AActor * ActorThatOpen;
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 1.f;
	
	float LastDoorOpenTimes;

	AActor * Owner;

	bool Isopen = false;
};
