// Copyright 2021 Darby Costello. All Rights Reserved.
#include "VRTPMobile.h"
#include "Engine/Engine.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/TextureCube.h"
#include "VRTPMask.h"

UVRTunnellingProMobile::UVRTunnellingProMobile()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
	PrimaryComponentTick.bTickEvenWhenPaused = true;

	bAutoActivate = true;
	bWantsInitializeComponent = true;
}

void UVRTunnellingProMobile::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}


void UVRTunnellingProMobile::CacheSettings()
{
	SkyboxBlueprintSwap = SkyboxBlueprint;
	CubeMapOverrideSwap = CubeMapOverride;
	PostProcessMaterialSwap = PostProcessMaterial;
	EffectColorSwap = EffectColor;
	EffectCoverageSwap = EffectCoverage;
	EffectFeatherSwap = EffectFeather;
	BackgroundModeSwap = BackgroundMode;
	ApplyEffectColorSwap = ApplyEffectColor;
	ForceEffectSwap = ForceEffect;
	MaskModeSwap = MaskMode;
	StencilIndexSwap = StencilIndex;
	bUseAngularVelocitySwap = bUseAngularVelocity;
	AngularStrengthSwap = AngularStrength;
	AngularMinSwap = AngularMin;
	AngularMaxSwap = AngularMax;
	AngularSmoothingSwap = AngularSmoothing;
	bUseVelocitySwap = bUseVelocity;
	VelocityStrengthSwap = VelocityStrength;
	VelocityMinSwap = VelocityMin;
	VelocityMaxSwap = VelocityMax;
	VelocitySmoothingSwap = VelocitySmoothing;
	bUseAccelerationSwap = bUseAcceleration;
	AccelerationStrengthSwap = AccelerationStrength;
	AccelerationMinSwap = AccelerationMin;
	AccelerationMaxSwap = AccelerationMax;
	AccelerationSmoothingSwap = AccelerationSmoothing;
}

void UVRTunnellingProMobile::InitFromPreset()
{

	if (Preset && bEnablePreset)
	{
		CacheSettings();
		SetPresetData(Preset);
	}

	if (!bEnablePreset)
	{
		SkyboxBlueprint = SkyboxBlueprintSwap;
		CubeMapOverride = CubeMapOverrideSwap;
		PostProcessMaterial = PostProcessMaterialSwap;
		EffectColor = EffectColorSwap;
		EffectCoverage = EffectCoverageSwap;
		EffectFeather = EffectFeatherSwap;
		BackgroundMode = BackgroundModeSwap;
		ApplyEffectColor = ApplyEffectColorSwap;
		ForceEffect = ForceEffectSwap;
		MaskMode = MaskModeSwap;
		StencilIndex = StencilIndexSwap;
		bUseAngularVelocity = bUseAngularVelocitySwap;
		AngularStrength = AngularStrengthSwap;
		AngularMin = AngularMinSwap;
		AngularMax = AngularMaxSwap;
		AngularSmoothing = AngularSmoothingSwap;
		bUseVelocity = bUseVelocitySwap;
		VelocityStrength = VelocityStrengthSwap;
		VelocityMin = VelocityMinSwap;
		VelocityMax = VelocityMaxSwap;
		VelocitySmoothing = VelocitySmoothingSwap;
		bUseAcceleration = bUseAccelerationSwap;
		AccelerationStrength = AccelerationStrengthSwap;
		AccelerationMin = AccelerationMinSwap;
		AccelerationMax = AccelerationMaxSwap;
		AccelerationSmoothing = AccelerationSmoothingSwap;
	}
}

void UVRTunnellingProMobile::SetPresetData(UVRTPMPresetData* NewPreset)
{
	if (NewPreset)
	{
		Preset = NewPreset;
		SkyboxBlueprint			= Preset->Data.SkyboxBlueprint;
		CubeMapOverride			= Preset->Data.CubeMapOverride;
		PostProcessMaterial		= Preset->Data.PostProcessMaterial;
		EffectColor				= Preset->Data.EffectColor;
		EffectCoverage			= Preset->Data.EffectCoverage;
		EffectFeather			= Preset->Data.EffectFeather;
		BackgroundMode			= Preset->Data.BackgroundMode;
		ApplyEffectColor		= Preset->Data.ApplyEffectColor;
		ForceEffect				= Preset->Data.ForceEffect;
		MaskMode				= Preset->Data.MaskMode;
		StencilIndex			= Preset->Data.StencilIndex;
		bUseAngularVelocity		= Preset->Data.bUseAngularVelocity;
		AngularStrength			= Preset->Data.AngularStrength;
		AngularMin				= Preset->Data.AngularMin;
		AngularMax				= Preset->Data.AngularMax;
		AngularSmoothing		= Preset->Data.AngularSmoothing;
		bUseVelocity			= Preset->Data.bUseVelocity;
		VelocityStrength		= Preset->Data.VelocityStrength;
		VelocityMin				= Preset->Data.VelocityMin;
		VelocityMax				= Preset->Data.VelocityMax;
		VelocitySmoothing		= Preset->Data.VelocitySmoothing;
		bUseAcceleration		= Preset->Data.bUseAcceleration;
		AccelerationStrength	= Preset->Data.AccelerationStrength;
		AccelerationMin			= Preset->Data.AccelerationMin;
		AccelerationMax			= Preset->Data.AccelerationMax;
		AccelerationSmoothing	= Preset->Data.AccelerationSmoothing;
	}
}


void UVRTunnellingProMobile::UpdateEffectSettings()
{
	if (PostProcessMID)
	{
		ApplyBackgroundMode();
		ApplyMaskMode();
		ApplyColor(ApplyEffectColor);
		SetFeather(EffectFeather);
		SetStencilMask(StencilIndex, true);
	}
}

void UVRTunnellingProMobile::ApplyPreset(UVRTPMPresetData* NewPreset)
{
	if (NewPreset)
	{
		SetPresetData(NewPreset);
		if (CaptureInit) 
		{
			UpdateEffectSettings();
		}
	}
}

// Called when the game starts
void UVRTunnellingProMobile::BeginPlay()
{
	Super::BeginPlay();
	CaptureInit = false;
}

// Called every frame
void UVRTunnellingProMobile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CaptureInit)
	{
		CaptureInit = true;
		if (!CubeMapOverride)
		{
			InitCapture();
			InitSkybox();
		}
		InitIris();
		UpdateEffectSettings();
	}

	if (PostProcessMID)
	{
		CalculateMotion(DeltaTime);
		PostProcessMID->SetVectorParameterValue(FName("Up"), GetOwner()->GetActorUpVector());
		PostProcessMID->SetVectorParameterValue(FName("Right"), GetOwner()->GetActorRightVector());
		PostProcessMID->SetVectorParameterValue(FName("Forward"), GetOwner()->GetActorForwardVector());
	}

	if (IrisOuterMID && IrisInnerMID)
	{
		IrisOuterMID->SetVectorParameterValue(FName("Up"), GetOwner()->GetActorUpVector());
		IrisOuterMID->SetVectorParameterValue(FName("Right"), GetOwner()->GetActorRightVector());
		IrisOuterMID->SetVectorParameterValue(FName("Forward"), GetOwner()->GetActorForwardVector());

		IrisInnerMID->SetVectorParameterValue(FName("Up"), GetOwner()->GetActorUpVector());
		IrisInnerMID->SetVectorParameterValue(FName("Right"), GetOwner()->GetActorRightVector());
		IrisInnerMID->SetVectorParameterValue(FName("Forward"), GetOwner()->GetActorForwardVector());
	}

}

#if WITH_EDITOR
//=============================================================================
void UVRTunnellingProMobile::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
}

//=============================================================================
void UVRTunnellingProMobile::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FProperty* PropertyThatChanged = PropertyChangedEvent.Property;
	const FName PropertyName = (PropertyThatChanged != nullptr) ? PropertyThatChanged->GetFName() : NAME_None;

	if (PropertyThatChanged->GetFName().ToString() == "Preset" || PropertyThatChanged->GetFName().ToString() == "bEnablePreset")
	{
		InitFromPreset();
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

//*************************************************************

void UVRTunnellingProMobile::InitCapture()
{
	// Initialise Cube Capture
	SceneCaptureCube = NewObject<USceneCaptureComponentCube>(GetOwner());

	TC = NewObject<UTextureRenderTargetCube>();
	TC->ClearColor = FLinearColor::Black;
	TC->bHDR = false;
	TC->InitAutoFormat(1024);

	SceneCaptureCube->TextureTarget = TC;
	SceneCaptureCube->bCaptureOnMovement = false;
	SceneCaptureCube->bCaptureEveryFrame = false;
	SceneCaptureCube->bAutoActivate = true;
	SceneCaptureCube->CaptureStereoPass = EStereoscopicPass::eSSP_FULL;

	SceneCaptureCube->ShowFlags.SetAntiAliasing(false);
	SceneCaptureCube->ShowFlags.SetAtmosphere(false);
	SceneCaptureCube->ShowFlags.SetBloom(false);
	SceneCaptureCube->ShowFlags.SetBSP(false);
	SceneCaptureCube->ShowFlags.SetDeferredLighting(false);
	SceneCaptureCube->ShowFlags.SetEyeAdaptation(true);
	SceneCaptureCube->ShowFlags.SetFog(false);
	SceneCaptureCube->ShowFlags.SetVolumetricFog(false);

	UCameraComponent* PlayerCamera = GetOwner()->FindComponentByClass<UCameraComponent>();
	if (PlayerCamera != NULL)
	{
		PostProcessMID = UMaterialInstanceDynamic::Create(PostProcessMaterial, this);
		PlayerCamera->PostProcessSettings.AddBlendable(PostProcessMID, 1.0f);
		UpdateEffectSettings();
		SceneCaptureCube->AttachToComponent(PlayerCamera, FAttachmentTransformRules::KeepRelativeTransform);
		PostProcessMID->SetTextureParameterValue(FName("TC"), TC);
	}
}

void UVRTunnellingProMobile::InitSkybox()
{
	if (SkyboxBlueprint != NULL)
	{
		FVector Location = GetOwner()->GetActorLocation();
		FRotator Rotation = GetOwner()->GetActorRotation();
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = GetOwner();
		Skybox = GetWorld()->SpawnActor(SkyboxBlueprint, &Location, &Rotation, SpawnInfo);

		if (Skybox != NULL)
		{
			Skybox->GetRootComponent()->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			TInlineComponentArray<UActorComponent*> MeshComponents(Skybox);
			for (int32 i = 0; i < MeshComponents.Num(); ++i)
			{
				UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(MeshComponents[i]);
				Mesh->SetOwnerNoSee(true);
			}
		}

		SceneCaptureCube->ShowOnlyActorComponents(Skybox);
		SceneCaptureCube->CaptureScene();
	}
}

void UVRTunnellingProMobile::InitIris()
{
	UCameraComponent* PlayerCamera = GetOwner()->FindComponentByClass<UCameraComponent>();
	if (PlayerCamera != NULL && IrisMesh != NULL)
	{
		Iris = NewObject<UStaticMeshComponent>(GetOwner());
		Iris->RegisterComponent();
		Iris->SetStaticMesh(IrisMesh);
		IrisOuterMID = Iris->CreateDynamicMaterialInstance(0, Iris->GetMaterial(0));
		IrisInnerMID = Iris->CreateDynamicMaterialInstance(1, Iris->GetMaterial(1));
		Iris->SetWorldTransform(FTransform(FRotator(90, 0, 0), FVector(30, 0, 0), FVector(1.5, 1.5, 1.5)));
		Iris->AttachToComponent(PlayerCamera, FAttachmentTransformRules::KeepRelativeTransform);
		IrisInnerMID->SetScalarParameterValue(FName("CubeMapOverride"), (CubeMapOverride ? 1.0f : 0.0f));
		IrisOuterMID->SetScalarParameterValue(FName("CubeMapOverride"), (CubeMapOverride ? 1.0f : 0.0f));
		if (CubeMapOverride != NULL)
		{
			IrisOuterMID->SetTextureParameterValue(FName("CustomCubeMap"), CubeMapOverride);
			IrisInnerMID->SetTextureParameterValue(FName("CustomCubeMap"), CubeMapOverride);
		}
		else
		{
			IrisInnerMID->SetTextureParameterValue(FName("TC"), TC);
			IrisOuterMID->SetTextureParameterValue(FName("TC"), TC);
		}
		Iris->SetHiddenInGame(true);
	}
	
}

void UVRTunnellingProMobile::SetBackgroundMode(EVRTPMBackgroundMode NewBackgroundMode)
{
	BackgroundMode = NewBackgroundMode;
	ApplyBackgroundMode();
}

void UVRTunnellingProMobile::SetMaskMode(EVRTPMMaskMode NewMaskMode)
{
	MaskMode = NewMaskMode;
	ApplyMaskMode();
}

void UVRTunnellingProMobile::ApplyBackgroundMode()
{
	switch (BackgroundMode)
	{
		case EVRTPMBackgroundMode::MM_COLOR:
			if (PostProcessMID) PostProcessMID->SetScalarParameterValue(FName("BackgroundColor"), 1.0f);
			if (PostProcessMID) PostProcessMID->SetScalarParameterValue(FName("BackgroundSkybox"), 0.0f);
			if (IrisOuterMID) IrisOuterMID->SetScalarParameterValue(FName("BackgroundColor"), 1.0f);
			if (IrisOuterMID) IrisOuterMID->SetScalarParameterValue(FName("BackgroundSkybox"), 0.0f);
			if (IrisInnerMID) IrisInnerMID->SetScalarParameterValue(FName("BackgroundColor"), 1.0f);
			if (IrisInnerMID) IrisInnerMID->SetScalarParameterValue(FName("BackgroundSkybox"), 0.0f);
			if (Skybox != NULL) Skybox->SetActorHiddenInGame(true);
			break;

		case EVRTPMBackgroundMode::MM_SKYBOX:
			if (PostProcessMID) PostProcessMID->SetScalarParameterValue(FName("BackgroundColor"), 0.0f);
			if (PostProcessMID) PostProcessMID->SetScalarParameterValue(FName("BackgroundSkybox"), 1.0f);
			if (IrisOuterMID) IrisOuterMID->SetScalarParameterValue(FName("BackgroundColor"), 0.0f);
			if (IrisOuterMID) IrisOuterMID->SetScalarParameterValue(FName("BackgroundSkybox"), 1.0f);
			if (IrisInnerMID) IrisInnerMID->SetScalarParameterValue(FName("BackgroundColor"), 0.0f);
			if (IrisInnerMID) IrisInnerMID->SetScalarParameterValue(FName("BackgroundSkybox"), 1.0f);
			
			if (PostProcessMID) PostProcessMID->SetScalarParameterValue(FName("CubeMapOverride"), (CubeMapOverride ? 1.0f : 0.0f));
			if (IrisOuterMID) IrisOuterMID->SetScalarParameterValue(FName("CubeMapOverride"), (CubeMapOverride ? 1.0f : 0.0f));
			if (IrisInnerMID) IrisInnerMID->SetScalarParameterValue(FName("CubeMapOverride"), (CubeMapOverride ? 1.0f : 0.0f));
			if (CubeMapOverride != NULL)
			{
				PostProcessMID->SetTextureParameterValue(FName("CustomCubeMap"), CubeMapOverride);
				IrisOuterMID->SetTextureParameterValue(FName("CustomCubeMap"), CubeMapOverride);
				IrisInnerMID->SetTextureParameterValue(FName("CustomCubeMap"), CubeMapOverride);
			}
			else
			{
				IrisInnerMID->SetTextureParameterValue(FName("TC"), TC);
				IrisOuterMID->SetTextureParameterValue(FName("TC"), TC);
			}

			if (Skybox != NULL) Skybox->SetActorHiddenInGame(false);
			break;
	}
}

void UVRTunnellingProMobile::ApplyMaskMode()
{
	if (PostProcessMID) 
	{
		switch (MaskMode)
		{
			case EVRTPMMaskMode::MM_OFF:
				PostProcessMID->SetScalarParameterValue(FName("MaskOn"), 0.0f);
				PostProcessMID->SetScalarParameterValue(FName("MaskPortal"), 0.0f);
				PostProcessMID->SetScalarParameterValue(FName("MaskWindow"), 0.0f);
				PostProcessMID->SetScalarParameterValue(FName("Enabled"), 0.0f);
				if (Iris) Iris->SetHiddenInGame(false);
				break;

			case EVRTPMMaskMode::MM_MASK:
				PostProcessMID->SetScalarParameterValue(FName("MaskOn"), 1.0f);
				PostProcessMID->SetScalarParameterValue(FName("MaskPortal"), 0.0f);
				PostProcessMID->SetScalarParameterValue(FName("MaskWindow"), 0.0f);
				PostProcessMID->SetScalarParameterValue(FName("Enabled"), 1.0f);
				if (Iris) Iris->SetHiddenInGame(true);
				break;

			case EVRTPMMaskMode::MM_PORTAL:
				PostProcessMID->SetScalarParameterValue(FName("MaskOn"), 0.0f);
				PostProcessMID->SetScalarParameterValue(FName("MaskPortal"), 1.0f);
				PostProcessMID->SetScalarParameterValue(FName("MaskWindow"), 0.0f);
				PostProcessMID->SetScalarParameterValue(FName("Enabled"), 1.0f);
				if (Iris) Iris->SetHiddenInGame(true);
				break;

			case EVRTPMMaskMode::MM_WINDOW:
				PostProcessMID->SetScalarParameterValue(FName("MaskOn"), 0.0f);
				PostProcessMID->SetScalarParameterValue(FName("MaskPortal"), 0.0f);
				PostProcessMID->SetScalarParameterValue(FName("MaskWindow"), 1.0f);
				PostProcessMID->SetScalarParameterValue(FName("Enabled"), 1.0f);
				if (Iris) Iris->SetHiddenInGame(true);
				break;
		}
	}
}

void UVRTunnellingProMobile::SetEffectColor(FLinearColor NewColor)
{
	EffectColor = NewColor;
	if (PostProcessMID) PostProcessMID->SetVectorParameterValue(FName("EffectColor"), FVector(EffectColor.R, EffectColor.G, EffectColor.B));
	if (IrisOuterMID) IrisOuterMID->SetVectorParameterValue(FName("EffectColor"), FVector(EffectColor.R, EffectColor.G, EffectColor.B));
	if (IrisInnerMID) IrisInnerMID->SetVectorParameterValue(FName("EffectColor"), FVector(EffectColor.R, EffectColor.G, EffectColor.B));
}

void UVRTunnellingProMobile::SetFeather(float NewFeather)
{
	EffectFeather = NewFeather;
	if (PostProcessMID) PostProcessMID->SetScalarParameterValue(FName("Feather"), EffectFeather);
	if (IrisInnerMID) IrisInnerMID->SetScalarParameterValue(FName("Feather"), EffectFeather);
}

void UVRTunnellingProMobile::SetStencilMask(int32 NewStencilIndex, bool UpdateMaskedObjects)
{
	StencilIndex = NewStencilIndex;
	if (PostProcessMID) PostProcessMID->SetScalarParameterValue(FName("MaskStencil"), (float)StencilIndex);
	if (UpdateMaskedObjects) ApplyStencilMasks();
}

void UVRTunnellingProMobile::UpdateMaskedObjects()
{
	ApplyStencilMasks();
}

void UVRTunnellingProMobile::ApplyStencilMasks()
{
	// Apply Custom Depth Stencil Index to all primitives within actors containing VRTPMask Component
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);
	for (AActor* Actor : AllActors)
	{
		if (Actor->FindComponentByClass(UVRTPMask::StaticClass()))
		{
			TInlineComponentArray<UActorComponent*> Components(Actor);
			for (UActorComponent* Component : Components)
			{
				UPrimitiveComponent* Primitive = Cast<UPrimitiveComponent>(Component);
				if (Primitive)
				{
					if (Primitive->IsValidLowLevel()) {
						Primitive->SetCustomDepthStencilValue(StencilIndex);
						if (MaskMode != EVRTPMMaskMode::MM_OFF) Primitive->SetRenderCustomDepth(true);
						else Primitive->SetRenderCustomDepth(false);
					}
				}
			}
		}
	}
}

void UVRTunnellingProMobile::ApplyColor(bool Enabled)
{
	ApplyEffectColor = Enabled;
	SetEffectColor(EffectColor);
	if (PostProcessMID) PostProcessMID->SetScalarParameterValue(FName("ApplyEffectColor"), (float)ApplyEffectColor);
	if (IrisOuterMID) IrisOuterMID->SetScalarParameterValue(FName("ApplyEffectColor"), (float)ApplyEffectColor);
	if (IrisInnerMID) IrisInnerMID->SetScalarParameterValue(FName("ApplyEffectColor"), (float)ApplyEffectColor);
}

void UVRTunnellingProMobile::CalculateMotion(float DeltaTime)
{
	float Radius = 0;
	float RadiusTarget = 0;
	float VelocityFinal = 0;
	if (!ForceEffect)
	{
		if (bUseAngularVelocity)
		{
			float AngleDelta = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GetOwner()->GetActorForwardVector(), LastForward))) / DeltaTime;
			// Check for divide by zero
			if (FMath::IsNearlyEqual(AngularMin, AngularMax, 0.001f)) AngleDelta = 0;
			else AngleDelta = (AngleDelta - AngularMin) / (AngularMax - AngularMin);
			float InterpSpeed = FMath::GetMappedRangeValueClamped(FVector2D(0, 1), FVector2D(1, 20), AngularSmoothing);
			AngleSmoothed = FMath::FInterpTo(AngleSmoothed, AngleDelta, DeltaTime, InterpSpeed);
			RadiusTarget += AngleSmoothed * (AngularStrength * 0.5);
			LastForward = GetOwner()->GetActorForwardVector();
		}

		if (bUseVelocity || bUseAcceleration)
		{
			float VelocityDelta = FVector::Distance(GetOwner()->GetActorLocation(), LastPosition) / DeltaTime;
			LastPosition = GetOwner()->GetActorLocation();

			if (bUseVelocity)
			{
				float InterpSpeed = FMath::GetMappedRangeValueClamped(FVector2D(0, 1), FVector2D(1, 20), VelocitySmoothing);
				VelocitySmoothed = FMath::FInterpTo(VelocitySmoothed, VelocityDelta, DeltaTime, InterpSpeed);

				// Check for divide by zero
				if (!FMath::IsNearlyEqual(VelocityMin, VelocityMax, 0.001f))
				{
					VelocityFinal = FMath::Clamp((VelocitySmoothed - VelocityMin) / (VelocityMax - VelocityMin), 0.0f, 1.0f);
				}
				RadiusTarget += VelocityFinal * VelocityStrength;
			}

			if (bUseAcceleration)
			{
				float AccelerationDelta = FMath::Abs(GetOwner()->GetVelocity().Size() - LastSpeed) / DeltaTime;
				LastSpeed = GetOwner()->GetVelocity().Size();

				// Check for divide by zero
				if (!FMath::IsNearlyEqual(AccelerationMin, AccelerationMax, 0.001f))
				{
					AccelerationDelta = FMath::Clamp((AccelerationDelta - AccelerationMin) / (AccelerationMax - AccelerationMin), 0.0f, 1.0f);
				}

				float InterpSpeed = FMath::GetMappedRangeValueClamped(FVector2D(0, 1), FVector2D(1, 20), AccelerationSmoothing);
				AccelerationSmoothed = FMath::FInterpTo(AccelerationSmoothed, AccelerationDelta, DeltaTime, InterpSpeed);
				RadiusTarget += AccelerationSmoothed * AccelerationStrength;
			}
		}

		if (bUseAngularVelocity || bUseAcceleration || bUseVelocity)
		{
			Radius = FMath::GetMappedRangeValueClamped(FVector2D(0, 1), FVector2D(1.5, 1 - EffectCoverage), RadiusTarget);
		}
		else
		{
			Radius = 1.5f;
		}
	}
	else
	{
		Radius = 0.3f;
	}

	if (PostProcessMID) PostProcessMID->SetScalarParameterValue(FName("Radius"), Radius);
	if (IrisOuterMID) IrisOuterMID->SetScalarParameterValue(FName("Radius"), Radius);
	if (IrisInnerMID) IrisInnerMID->SetScalarParameterValue(FName("Radius"), Radius);

	
}
