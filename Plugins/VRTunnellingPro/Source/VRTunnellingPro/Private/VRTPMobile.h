#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SceneCaptureComponentCube.h"
#include "Engine/TextureRenderTargetCube.h"
#include "Engine/DataAsset.h"
#include "Engine/TextureCube.h"
#include "VRTPMobile.generated.h"

/// Mobile Background Mode Enumerator (Color || Skybox || Blur)
UENUM(BlueprintType)
enum class EVRTPMBackgroundMode : uint8
{
	MM_COLOR 		UMETA(DisplayName = "Color"),
	MM_SKYBOX		UMETA(DisplayName = "Skybox")
};

/// Mobile Mask Mode Enumerator (Off || Mask || Window || Portal)
UENUM(BlueprintType)
enum class EVRTPMMaskMode : uint8
{
	MM_OFF 			UMETA(DisplayName = "Off"),
	MM_MASK			UMETA(DisplayName = "Mask"),
	MM_WINDOW 		UMETA(DisplayName = "Window"),
	MM_PORTAL		UMETA(DisplayName = "Portal"),
};

/// VRTP Mobile Preset Definition (Applied to mobile version only)
USTRUCT(BlueprintType)
struct FVRTPMPreset
{
	GENERATED_USTRUCT_BODY()

	/// Skybox blueprint to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
	TSubclassOf<class AActor> SkyboxBlueprint;

	/// Cubemap texture cube to use as an override for skybox-only modes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
	UTextureCube* CubeMapOverride;

	/// Effect material to use for post process effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process")
	UMaterial* PostProcessMaterial;

	/// Iris mesh to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iris")
	UStaticMesh* IrisMesh;

	/// Effect vignette color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
	FLinearColor EffectColor;

	/// Effect vignette coverage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float EffectCoverage;

	/// Effect vignette feather
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float EffectFeather;

	/// Effect background mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
	EVRTPMBackgroundMode BackgroundMode;

	/// Enable effect colour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
	bool ApplyEffectColor;

	/// Force vignette effect (useful for debugging)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
	bool ForceEffect;

	/// Effect mask mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings|Mask Settings")
	EVRTPMMaskMode MaskMode;

	/// Effect mask stencil index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings|Mask Settings", meta = (ClampMin = "0", ClampMax = "255"))
	int32 StencilIndex;

	/// Enable effect for angular velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity")
	bool bUseAngularVelocity;

	/// Angular effect strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float AngularStrength;

	/// Minimum angular velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float AngularMin;

	/// Maximum angular velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float AngularMax;

	/// Angular smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AngularSmoothing;

	/// Enable effect for velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity")
	bool bUseVelocity;

	/// Velocity effect strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float VelocityStrength;

	/// Minimum velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float VelocityMin;

	/// Maximum velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float VelocityMax;

	/// Velocity smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VelocitySmoothing;

	/// Enable effect for acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration")
	bool bUseAcceleration;

	/// Acceleration effect strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float AccelerationStrength;

	/// Minimum acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float AccelerationMin;

	/// Maximum acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float AccelerationMax;

	/// Acceleration smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AccelerationSmoothing;

	FVRTPMPreset()
	{
		SkyboxBlueprint = NULL;
		CubeMapOverride = NULL;
		PostProcessMaterial = NULL;
		IrisMesh = NULL;
		EffectColor = FLinearColor::Black;
		EffectCoverage = 0;
		EffectFeather = 0;
		BackgroundMode = EVRTPMBackgroundMode::MM_COLOR;
		ApplyEffectColor = false;
		ForceEffect = false;
		MaskMode = EVRTPMMaskMode::MM_OFF;
		StencilIndex = 200;
		bUseAngularVelocity = false;
		AngularStrength = 0;
		AngularMin = 0;
		AngularMax = 0;
		AngularSmoothing = 0;
		bUseVelocity = false;
		VelocityStrength = 0;
		VelocityMin = 0;
		VelocityMax = 0;
		VelocitySmoothing = 0;
		bUseAcceleration = false;
		AccelerationStrength = 0;
		AccelerationMin = 0;
		AccelerationMax = 0;
		AccelerationSmoothing = 0;
	}
};

/// Mobile preset data asset definition
UCLASS()
class UVRTPMPresetData : public UDataAsset
{
	GENERATED_BODY()

public:
	/// Data Asset to use as preset
	UPROPERTY(EditAnywhere)
	FVRTPMPreset Data;
};

/// Tunnelling actor component, for mobile applications
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = MotionController, HideCategories = ("VRTunnellingProMobile"))
class UVRTunnellingProMobile : public UActorComponent
{
	GENERATED_BODY()

public:	

	UVRTunnellingProMobile();

#if WITH_EDITOR
	virtual void PreEditChange(UProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif 
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	/// Data Asset to use as preset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Tunnelling|Effect Preset")
	UVRTPMPresetData* Preset;

	/// Toggle between preset values and previous user values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Tunnelling|Effect Preset")
	bool bEnablePreset;

	/// Skybox blueprint to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "VR Tunnelling")
	TSubclassOf<class AActor> SkyboxBlueprint;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> SkyboxBlueprintSwap;

	/// Cubemap texture cube to use as an override for skybox-only modes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "VR Tunnelling")
	UTextureCube* CubeMapOverride;
	UPROPERTY(EditAnywhere)
	UTextureCube* CubeMapOverrideSwap;

	/// Effect material to use for post process effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "VR Tunnelling")
	UMaterial* PostProcessMaterial;
	UPROPERTY(EditAnywhere)
	UMaterial* PostProcessMaterialSwap;

	/// Iris mesh to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "VR Tunnelling")
	UStaticMesh* IrisMesh;
	UPROPERTY(EditAnywhere)
	UStaticMesh* IrisMeshSwap;

	/// Effect vignette color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
	FLinearColor EffectColor;
	UPROPERTY(EditAnywhere)
	FLinearColor EffectColorSwap;

	/// Effect vignette coverage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float EffectCoverage;
	UPROPERTY(EditAnywhere)
	float EffectCoverageSwap;

	/// Effect vignette feather
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float EffectFeather;
	UPROPERTY(EditAnywhere)
	float EffectFeatherSwap;

	/// Effect background mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
	EVRTPMBackgroundMode BackgroundMode;
	UPROPERTY(EditAnywhere)
	EVRTPMBackgroundMode BackgroundModeSwap;

	/// Enable effect colour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
	bool ApplyEffectColor;
	UPROPERTY(EditAnywhere)
	bool ApplyEffectColorSwap;

	/// Force vignette effect (useful for debugging)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
	bool ForceEffect;
	UPROPERTY(EditAnywhere)
	bool ForceEffectSwap;

	/// Effect mask mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings|Mask Settings")
	EVRTPMMaskMode MaskMode;
	UPROPERTY(EditAnywhere)
	EVRTPMMaskMode MaskModeSwap;

	/// Effect mask stencil index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings|Mask Settings", meta = (ClampMin = "0", ClampMax = "255"))
	int32 StencilIndex;
	UPROPERTY(EditAnywhere)
	int32 StencilIndexSwap;

	/// Enable effect for angular velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity")
	bool bUseAngularVelocity;
	UPROPERTY(EditAnywhere)
	bool bUseAngularVelocitySwap;

	/// Angular effect strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float AngularStrength;
	UPROPERTY(EditAnywhere)
	float AngularStrengthSwap;

	/// Minimum angular velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float AngularMin;
	UPROPERTY(EditAnywhere)
	float AngularMinSwap;

	/// Maximum angular velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float AngularMax;
	UPROPERTY(EditAnywhere)
	float AngularMaxSwap;

	/// Angular smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AngularSmoothing;
	UPROPERTY(EditAnywhere)
	float AngularSmoothingSwap;

	/// Enable effect for velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity")
	bool bUseVelocity;
	UPROPERTY(EditAnywhere)
	bool bUseVelocitySwap;

	/// Velocity effect strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float VelocityStrength;
	UPROPERTY(EditAnywhere)
	float VelocityStrengthSwap;

	/// Minimum velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float VelocityMin;
	UPROPERTY(EditAnywhere)
	float VelocityMinSwap;

	/// Maximum velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float VelocityMax;
	UPROPERTY(EditAnywhere)
	float VelocityMaxSwap;

	/// Velocity smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VelocitySmoothing;
	UPROPERTY(EditAnywhere)
	float VelocitySmoothingSwap;

	/// Enable effect for acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration")
	bool bUseAcceleration;
	UPROPERTY(EditAnywhere)
	bool bUseAccelerationSwap;

	/// Acceleration effect strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float AccelerationStrength;
	UPROPERTY(EditAnywhere)
	float AccelerationStrengthSwap;

	/// Minimum acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float AccelerationMin;
	UPROPERTY(EditAnywhere)
	float AccelerationMinSwap;

	/// Maximum acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float AccelerationMax;
	UPROPERTY(EditAnywhere)
	float AccelerationMaxSwap;

	/// Acceleration smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AccelerationSmoothing;
	UPROPERTY(EditAnywhere)
	float AccelerationSmoothingSwap;

	USceneCaptureComponentCube* SceneCaptureCube;
	UTextureRenderTargetCube* TC;
	float HFov;
	float VFov;
	UMaterialInstanceDynamic* PostProcessMID;
	AActor* Skybox;
	UStaticMeshComponent* Iris;
	UMaterialInstanceDynamic* IrisOuterMID;
	UMaterialInstanceDynamic* IrisInnerMID;
	bool CaptureInit;

	/// Load and apply a new VRTP mobile preset, from a VRTP preset data asset
	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void ApplyPreset(UVRTPMPresetData* NewPreset);

	/// Change the background mode
	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void SetBackgroundMode(EVRTPMBackgroundMode NewBackgroundMode);

	/// Change the mask mode
	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void SetMaskMode(EVRTPMMaskMode NewMaskMode);

	/// Change the effect color
	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void SetEffectColor(FLinearColor NewColor);

	/// Toggle whether the effect color is applied
	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void ApplyColor(bool Enabled);

	/// Set the stencil mask and optionally update all existing masked objects with the new index
	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void SetStencilMask(int32 NewStencilIndex, bool UpdateMaskedObjects = true);

	/// Update all existing masked objects, including stencil indices and whether masking is applied
	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void UpdateMaskedObjects();

	/// Set the feathering amount of the effect vignette
	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void SetFeather(float NewFeather);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector LastForward;
	FVector LastPosition;
	float LastSpeed;

	float AngleSmoothed;
	float VelocitySmoothed;
	float AccelerationSmoothed;

	void CacheSettings();
	void InitCapture();
	void InitSkybox();
	void InitIris();
	void InitFromPreset();
	void SetPresetData(UVRTPMPresetData* NewPreset);
	void UpdateEffectSettings();

	void CalculateMotion(float DeltaTime);
	void ApplyBackgroundMode();
	void ApplyMaskMode();
	void ApplyStencilMasks();
};
