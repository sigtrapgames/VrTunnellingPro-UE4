// Copyright 2021 Darby Costello. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VRTPMask.generated.h"

/// Mask Component for both desktop and mobile applications. Used to add parent actor to the stencil buffer
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UVRTPMask : public UActorComponent
{
	GENERATED_BODY()

public:
	UVRTPMask();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

};
