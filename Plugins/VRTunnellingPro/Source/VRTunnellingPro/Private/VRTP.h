// Copyright 2021 Darby Costello. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/TextureCube.h"
#include "Components/PrimitiveComponent.h"
#include "SceneViewExtension.h"
#include "IMotionController.h"
#include "LateUpdateManager.h"
#include "IIdentifiableXRDevice.h" // for FXRDeviceId
#include "Components/ActorComponent.h"
#include "Components/SceneCaptureComponentCube.h"
#include "Engine/TextureRenderTargetCube.h"
#include "Engine/DataAsset.h"
#include "VRTP.generated.h"

/// Background Mode Enumerator (Color || Skybox || Blur)
UENUM(BlueprintType)
enum class EVRTPBackgroundMode : uint8
{
	MM_COLOR 		UMETA(DisplayName = "Color"),
	MM_SKYBOX		UMETA(DisplayName = "Skybox"),
	MM_BLUR 		UMETA(DisplayName = "Blur")
};

/// Mask Mode Enumerator (Off || Mask || Window || Portal)
UENUM(BlueprintType)
enum class EVRTPMaskMode : uint8
{
	MM_OFF 			UMETA(DisplayName = "Off"),
	MM_MASK			UMETA(DisplayName = "Mask"),
	MM_WINDOW 		UMETA(DisplayName = "Window"),
	MM_PORTAL		UMETA(DisplayName = "Portal")
};

/// VRTP Preset Definition (Applied to desktop version only)
/// This struct defines a *comfort preset* for VR Tunnelling Pro.
/// Values are copied onto the component at runtime; this struct itself
/// does NOT execute logic.
USTRUCT(BlueprintType)
struct FVRTPPreset
{
	GENERATED_USTRUCT_BODY()

	/* ================================
	 * Capture / Background Setup
	 * ================================ */

	 /// Actor class used as the skybox when rendering peripheral background.
	 /// Should be simple, unlit, and visually stable for comfort.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
	TSubclassOf<class AActor> SkyboxBlueprint;

	/// Optional static cubemap used instead of live scene capture.
	/// Cheaper and more stable than capturing the scene each time.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
	UTextureCube* CubeMapOverride;

	/* ================================
	 * Post Process
	 * ================================ */

	 /// Post-process material that applies the tunnelling / vignette effect.
	 /// Usually provided by the plugin; override only for custom visuals.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process")
	UMaterial* PostProcessMaterial;

	/* ================================
	 * Effect Appearance
	 * ================================ */

	 /// Color of the vignette / tunnel edge.
	 /// Black is strongest comfort; dark neutral colors feel softer.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
	FLinearColor EffectColor;

	/// Maximum vignette coverage (0–1).
	/// Controls how far inward the tunnel can close at full strength.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float EffectCoverage;

	/// Softness of the tunnel edge.
	/// Higher values = smoother, less distracting transitions.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float EffectFeather;

	/// Determines what fills the vignetted area:
	/// solid color, skybox, cubemap, or captured scene.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
	EVRTPBackgroundMode BackgroundMode;

	/// Enables tinting the vignette using EffectColor.
	/// If false, masking may still occur without color.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
	bool ApplyEffectColor;

	/// Forces the vignette to be visible at all times.
	/// Useful for debugging or visual tuning.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
	bool ForceEffect;

	/* ================================
	 * Mask / Stencil Settings
	 * ================================ */

	 /// Determines how the vignette mask is applied.
	 /// May use stencil buffer or full-screen mask.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings|Mask Settings")
	EVRTPMaskMode MaskMode;

	/// Stencil index used when MaskMode relies on custom depth/stencil.
	/// Must match the stencil value of the masked geometry.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings|Mask Settings", meta = (ClampMin = "0", ClampMax = "255"))
	int32 StencilIndex;

	/* ================================
	 * Direction-Specific Motion
	 * ================================ */

	 /// Enables different tunnelling strength per movement direction.
	 /// Useful to reduce tunnelling when moving forward vs sideways.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Direction specific")
	bool bDirectionSpecific;

	/// Strength multiplier for vertical (forward/backward) motion.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Direction specific")
	float DirectionalVerticalStrength;

	/// Strength multiplier for horizontal (sideways) motion.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Direction specific")
	float DirectionalHorizontalStrength;

	/* ================================
	 * Angular Velocity (Turning)
	 * ================================ */

	 /// Enables tunnelling in response to rotation (turning).
	 /// Important for smooth turning comfort.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity")
	bool bUseAngularVelocity;

	/// Strength of the angular velocity effect.
	/// Higher values = tunnel closes faster when turning.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float AngularStrength;

	/// Minimum angular speed (degrees/sec) before tunnelling starts.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float AngularMin;

	/// Angular speed at which the effect reaches full strength.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float AngularMax;

	/// Smoothing factor for angular velocity.
	/// Higher = slower response but less jitter.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AngularSmoothing;

	/* ================================
	 * Linear Velocity (Movement)
	 * ================================ */

	 /// Enables tunnelling in response to linear movement.
	 /// Primary comfort control for smooth locomotion.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity")
	bool bUseVelocity;

	/// Strength of the velocity-based effect.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float VelocityStrength;

	/// Minimum speed required before tunnelling starts.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float VelocityMin;

	/// Speed at which the effect reaches full strength.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float VelocityMax;

	/// Smoothing factor for velocity changes.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VelocitySmoothing;

	/* ================================
	 * Acceleration (Sudden Changes)
	 * ================================ */

	 /// Enables tunnelling based on acceleration.
	 /// Helps reduce discomfort during sudden starts/stops.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration")
	bool bUseAcceleration;

	/// Strength of the acceleration-based effect.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float AccelerationStrength;

	/// Minimum acceleration required before effect activates.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float AccelerationMin;

	/// Acceleration at which effect reaches full strength.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float AccelerationMax;

	/// Smoothing factor for acceleration changes.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AccelerationSmoothing;

	/* ================================
	 * Defaults
	 * ================================ */

	FVRTPPreset()
	{
		SkyboxBlueprint = NULL;
		CubeMapOverride = NULL;
		PostProcessMaterial = NULL;
		EffectColor = FLinearColor::Black;
		EffectCoverage = 0;
		EffectFeather = 0;
		BackgroundMode = EVRTPBackgroundMode::MM_COLOR;
		ApplyEffectColor = false;
		ForceEffect = false;
		MaskMode = EVRTPMaskMode::MM_OFF;
		StencilIndex = 200;
		bDirectionSpecific = false;
		DirectionalVerticalStrength = 1.5f;
		DirectionalHorizontalStrength = 1.5f;
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


/// Preset data asset definition
UCLASS()
class UVRTPPresetData : public UDataAsset
{
	GENERATED_BODY()

public:
	/// Data Asset to use as preset
	UPROPERTY(EditAnywhere, Category = "Presets")
	FVRTPPreset Data;
};

class FPrimitiveSceneInfo;
class FRHICommandListImmediate;
class FSceneView;
class FSceneViewFamily;

/// Tunnelling primitive component, for dektop applications
UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = MotionController, HideCategories = ("VRTunnellingPro"))
class UVRTunnellingPro : public UPrimitiveComponent
{
	GENERATED_UCLASS_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	void BeginDestroy() override;
	void OnUnregister() override;

	/// Which player index this motion controller should automatically follow
	UPROPERTY(BlueprintReadWrite, BlueprintSetter = SetAssociatedPlayerIndex, Category = "VR Tunnelling | MotionController")
	int32 PlayerIndex;
	
	UPROPERTY(BlueprintSetter = SetTrackingSource, BlueprintGetter = GetTrackingSource, Category = "VR Tunnelling | MotionController")
	EControllerHand Hand_DEPRECATED;

	/// Motion source to use for tracking, should be HMD
	UPROPERTY(BlueprintReadWrite, BlueprintSetter = SetTrackingMotionSource, Category = "VR Tunnelling | MotionController")
	FName MotionSource;

	/// If false, render transforms within the motion controller hierarchy will be updated a second time immediately before rendering.
	UPROPERTY(BlueprintReadWrite, Category = "VR Tunnelling | MotionController")
	uint32 bDisableLowLatencyUpdate : 1;

	/// The tracking status for the device (e.g. full tracking, inertial tracking only, no tracking)
	UPROPERTY(BlueprintReadOnly, Category = "VR Tunnelling | MotionController")
	ETrackingStatus CurrentTrackingStatus;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Motion Controller Update") bool IsTracked() const
	{
		return bTracked;
	}

	UFUNCTION(BlueprintSetter, Category = "Motion Controller Update", meta = (DeprecatedFunction, DeprecationMessage = "Please use the Motion Source property instead of Hand"))
	void SetTrackingSource(const EControllerHand NewSource);

	UFUNCTION(BlueprintGetter, Category = "Motion Controller Update", meta = (DeprecatedFunction, DeprecationMessage = "Please use the Motion Source property instead of Hand"))
	EControllerHand GetTrackingSource() const;

	UFUNCTION(BlueprintSetter, Category = "Motion Controller Update")
	void SetTrackingMotionSource(const FName NewSource);

	UFUNCTION(BlueprintSetter, Category = "Motion Controller Update")
	void SetAssociatedPlayerIndex(const int32 NewPlayer);

	/// Data Asset to use as preset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Tunnelling|Effect Preset")
	UVRTPPresetData* Preset;

	/// Toggle between preset values and previous user values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Tunnelling|Effect Preset")
	bool bEnablePreset;

	/// Skybox blueprint to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "VR Tunnelling")
	TSubclassOf<class AActor> SkyboxBlueprint;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling")
	TSubclassOf<class AActor> SkyboxBlueprintSwap;

	/// Cubemap texture cube to use as an override for skybox-only modes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "VR Tunnelling")
	UTextureCube* CubeMapOverride;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling")
	UTextureCube* CubeMapOverrideSwap;

	/// Effect material to use for post process effect
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "VR Tunnelling")
	UMaterial* PostProcessMaterial;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling")
	UMaterial* PostProcessMaterialSwap;

	/// Effect vignette color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
	FLinearColor EffectColor;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Effect Settings")
	FLinearColor EffectColorSwap;

	/// Effect vignette coverage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float EffectCoverage;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Effect Settings")
	float EffectCoverageSwap;

	/// Effect vignette feather
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float EffectFeather;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Effect Settings")
	float EffectFeatherSwap;

	/// Effect background mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
	EVRTPBackgroundMode BackgroundMode;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Effect Settings")
	EVRTPBackgroundMode BackgroundModeSwap;

	/// Enable effect colour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
	bool ApplyEffectColor;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Effect Settings")
	bool ApplyEffectColorSwap;

	/// Force vignette effect (useful for debugging)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
	bool ForceEffect;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Effect Settings")
	bool ForceEffectSwap;

	/// Effect mask mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings|Mask Settings")
	EVRTPMaskMode MaskMode;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Effect Settings|Mask Settings")
	EVRTPMaskMode MaskModeSwap;

	/// Effect mask stencil index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings|Mask Settings", meta = (ClampMin = "0", ClampMax = "255"))
	int32 StencilIndex;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Effect Settings|Mask Settings")
	int32 StencilIndexSwap;

	/// Enable directional-specific tunnelling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Direction Specific")
	bool bDirectionSpecific;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Direction Specific")
	bool bDirectionSpecificSwap;

	/// Directional-specific tunnelling vertical strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Direction Specific")
	float DirectionalVerticalStrength;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Direction Specific")
	float DirectionalVerticalStrengthSwap;

	/// Directional-specific tunnelling horizontal strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Direction Specific")
	float DirectionalHorizontalStrength;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Direction Specific")
	float DirectionalHorizontalStrengthSwap;

	/// Enable effect for angular velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity")
	bool bUseAngularVelocity;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Angular Velocity")
	bool bUseAngularVelocitySwap;

	/// Angular effect strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float AngularStrength;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Angular Velocity")
	float AngularStrengthSwap;

	/// Minimum angular velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float AngularMin;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Angular Velocity")
	float AngularMinSwap;

	/// Maximum angular velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
	float AngularMax;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Angular Velocity")
	float AngularMaxSwap;

	/// Angular smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AngularSmoothing;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Angular Velocity")
	float AngularSmoothingSwap;

	/// Enable effect for velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity")
	bool bUseVelocity;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Velocity")
	bool bUseVelocitySwap;

	/// Velocity effect strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float VelocityStrength;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Velocity")
	float VelocityStrengthSwap;

	/// Minimum velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float VelocityMin;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Velocity")
	float VelocityMinSwap;

	/// Maximum velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float VelocityMax;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Velocity")
	float VelocityMaxSwap;

	/// Velocity smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VelocitySmoothing;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Velocity")
	float VelocitySmoothingSwap;

	/// Enable effect for acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration")
	bool bUseAcceleration;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Acceleration")
	bool bUseAccelerationSwap;

	/// Acceleration effect strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "10.0"))
	float AccelerationStrength;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Acceleration")
	float AccelerationStrengthSwap;

	/// Minimum acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float AccelerationMin;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Acceleration")
	float AccelerationMinSwap;

	/// Maximum acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float AccelerationMax;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Acceleration")
	float AccelerationMaxSwap;

	/// Acceleration smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float AccelerationSmoothing;
	UPROPERTY(EditAnywhere, Category = "VR Tunnelling|Motion Settings|Acceleration")
	float AccelerationSmoothingSwap;

private:
	USceneCaptureComponentCube* SceneCaptureCube;
	UTextureRenderTargetCube* TC;
	float HFov;
	float VFov;
	UMaterialInstanceDynamic* PostProcessMID;
	AActor* Skybox;
	bool CaptureInit;

public:
	/// Load and apply a new VRTP preset, from a VRTP preset data asset
	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void ApplyPreset(UVRTPPresetData* NewPreset);

	/// Change the background mode
	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void SetBackgroundMode(EVRTPBackgroundMode NewBackgroundMode);

	/// Change the mask mode
	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void SetMaskMode(EVRTPMaskMode NewMaskMode);

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

	//~ UObject interface
	virtual void Serialize(FArchive& Ar) override;

#if WITH_EDITOR
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif 

public:
	//~ UActorComponent interface
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

protected:
	//~ Begin UActorComponent Interface.
	//virtual void CreateRenderState_Concurrent();
	virtual void SendRenderTransform_Concurrent();
	//~ End UActorComponent Interface.

	// Cached Motion Controller that can be read by GetParameterValue. Only valid for the duration of OnMotionControllerUpdated
	IMotionController* InUseMotionController;

	// Blueprint Implementable function for responding to updated data from a motion controller (so we can use custom paramater values from it)
	UFUNCTION(BlueprintImplementableEvent, Category = "Motion Controller Update")
	void OnMotionControllerUpdated();

	// Returns the value of a custom parameter on the current in use Motion Controller (see member InUseMotionController). Only valid for the duration of OnMotionControllerUpdated 
	UFUNCTION(BlueprintCallable, Category = "Motion Controller Update")
	float GetParameterValue(FName InName, bool& bValueFound);

private:

	FVector LastForward;
	FVector LastPosition;
	float LastSpeed;

	float AngleSmoothed;
	float VelocitySmoothed;
	float AccelerationSmoothed;

	// Whether or not this component had a valid tracked controller associated with it this frame
	bool bTracked;

	// Whether or not this component has authority within the frame
	bool bHasAuthority;

	// If true, the Position and Orientation args will contain the most recent controller state
	bool PollControllerState(FVector& Position, FRotator& Orientation, float WorldToMetersScale);

	FTransform RenderThreadRelativeTransform;
	FVector RenderThreadComponentScale;

	void CacheSettings();
	void InitCapture();
	void InitSkybox();
	void InitFromPreset();
	void SetPresetData(UVRTPPresetData* NewPreset);
	void UpdatePostProcessSettings();
	void CalculateMotion(float DeltaTime);
	void ApplyBackgroundMode();
	void ApplyMaskMode();
	void ApplyStencilMasks();
	void ReleaseCaptureResources();
	void ShutdownCaptureAndSkybox();

	// View extension object that can persist on the render thread without the motion controller component
	class FViewExtension : public FSceneViewExtensionBase
	{
	public:
		FViewExtension(const FAutoRegister& AutoRegister, UVRTunnellingPro* InMotionControllerComponent);
		virtual ~FViewExtension() {}

		/** ISceneViewExtension interface */
		virtual void SetupViewFamily(FSceneViewFamily& InViewFamily) override {}
		virtual void SetupView(FSceneViewFamily& InViewFamily, FSceneView& InView) override {}
		virtual void BeginRenderViewFamily(FSceneViewFamily& InViewFamily) override;
		virtual void PreRenderView_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneView& InView) override {}
		virtual void PreRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily) override;
		virtual void PostRenderViewFamily_RenderThread(FRHICommandListImmediate& RHICmdList, FSceneViewFamily& InViewFamily) override;
		virtual int32 GetPriority() const override { return -10; }

	private:
		friend class UVRTunnellingPro;


		

		/** Motion controller component associated with this view extension */
		UVRTunnellingPro* MotionControllerComponent;
		FLateUpdateManager LateUpdate;
		FTransform PrevTransform;
	};
	TSharedPtr< FViewExtension, ESPMode::ThreadSafe > ViewExtension;

#if WITH_EDITOR
	int32 PreEditMaterialCount = 0;
#endif
};
