#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/PrimitiveComponent.h"
#include "SceneViewExtension.h"
#include "IMotionController.h"
#include "LateUpdateManager.h"
#include "IIdentifiableXRDevice.h" // for FXRDeviceId
#include "Components/ActorComponent.h"
// DEV BRANCH
/*
#include "Engine/TextureRenderTarget2D.h"
#include "Components/SceneCaptureComponent2D.h"
*/
#include "Components/SceneCaptureComponentCube.h"
#include "Engine/TextureRenderTargetCube.h"

#include "Engine/DataAsset.h"
#include "VRTP.generated.h"

UENUM(BlueprintType)
enum class EVRTPBackgroundMode : uint8
{
	MM_COLOR 		UMETA(DisplayName = "Color"),
	MM_SKYBOX		UMETA(DisplayName = "Skybox"),
	// DEV BRANCH
	/*
	MM_CAGECOLOR	UMETA(DisplayName = "Cage + Color"),
	MM_CAGESKYBOX	UMETA(DisplayName = "Cage + Skybox"),
	*/
	MM_BLUR 		UMETA(DisplayName = "Blur"),
};

UENUM(BlueprintType)
enum class EVRTPMaskMode : uint8
{
	MM_OFF 			UMETA(DisplayName = "Off"),
	MM_MASK			UMETA(DisplayName = "Mask"),
	MM_WINDOW 		UMETA(DisplayName = "Window"),
	MM_PORTAL		UMETA(DisplayName = "Portal"),
};

USTRUCT(BlueprintType)
struct FVRTPPreset
{
	GENERATED_USTRUCT_BODY()
	
	// DEV BRANCH
	/*
	//Cage Blueprint to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
		TSubclassOf<class AActor> CageBlueprint;
	*/

	//Skybox Blueprint to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
		TSubclassOf<class AActor> SkyboxBlueprint;

	//Post Process Material to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post Process")
		UMaterial* PostProcessMaterial;

	//Effect Vignette Color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
		FLinearColor EffectColor;

	//Effect Vignette Coverage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float EffectCoverage;

	//Effect Vignette Feather
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings", meta = (ClampMin = "0.0", ClampMax = "10.0"))
		float EffectFeather;

	//Effect Background Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
		EVRTPBackgroundMode BackgroundMode;

	//Enable Effect Colour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
		bool ApplyEffectColor;

	//Force Vignette Effect (Useful for debugging)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
		bool ForceEffect;

	//Effect Mask Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings|Mask Settings")
		EVRTPMaskMode MaskMode;

	//Effect Mask Stencil Index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings|Mask Settings", meta = (ClampMin = "0", ClampMax = "255"))
		int32 StencilIndex;

	//Enable Effect for Angular Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity")
		bool bUseAngularVelocity;

	//Angular Effect Strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
		float AngularStrength;

	//Minimum Angular Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
		float AngularMin;

	//Maximum Angular Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
		float AngularMax;

	//Angular Smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float AngularSmoothing;

	//Enable Effect for Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity")
		bool bUseVelocity;

	//Velocity Effect Strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
		float VelocityStrength;

	//Minimum Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
		float VelocityMin;

	//Maximum Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
		float VelocityMax;

	//Velocity Smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float VelocitySmoothing;

	//Enable Effect for Acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration")
		bool bUseAcceleration;

	//Acceleration Effect Strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "10.0"))
		float AccelerationStrength;

	//Minimum Acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
		float AccelerationMin;

	//Maximum Acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
		float AccelerationMax;

	//Acceleration Smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float AccelerationSmoothing;

	//Constructor
	FVRTPPreset()
	{
		// DEV BRANCH
		/*
		CageBlueprint = NULL;
		*/
		SkyboxBlueprint = NULL;
		PostProcessMaterial = NULL;
		EffectColor = FLinearColor::Black;
		EffectCoverage = 0;
		EffectFeather = 0;
		BackgroundMode = EVRTPBackgroundMode::MM_COLOR;
		ApplyEffectColor = false;
		ForceEffect = false;
		MaskMode = EVRTPMaskMode::MM_OFF;
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

UCLASS()
class UVRTPPresetData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FVRTPPreset Data;
};

class FPrimitiveSceneInfo;
class FRHICommandListImmediate;
class FSceneView;
class FSceneViewFamily;

UCLASS(Blueprintable, meta = (BlueprintSpawnableComponent), ClassGroup = MotionController, HideCategories = ("VRTunnellingPro"))
class UVRTunnellingPro : public UPrimitiveComponent
{
	GENERATED_UCLASS_BODY()

	virtual void BeginPlay() override;
	void BeginDestroy() override;

	/** Which player index this motion controller should automatically follow */
	UPROPERTY(BlueprintReadWrite, BlueprintSetter = SetAssociatedPlayerIndex, Category = "VR Tunnelling | MotionController")
		int32 PlayerIndex;
	
	/** DEPRECATED (use MotionSource instead) Which hand this component should automatically follow */
	UPROPERTY(BlueprintSetter = SetTrackingSource, BlueprintGetter = GetTrackingSource, Category = "VR Tunnelling | MotionController")
		EControllerHand Hand_DEPRECATED;

	UPROPERTY(BlueprintReadWrite, BlueprintSetter = SetTrackingMotionSource, Category = "VR Tunnelling | MotionController")
		FName MotionSource;

	/** If false, render transforms within the motion controller hierarchy will be updated a second time immediately before rendering. */
	UPROPERTY(BlueprintReadWrite, Category = "VR Tunnelling | MotionController")
		uint32 bDisableLowLatencyUpdate : 1;

	/** The tracking status for the device (e.g. full tracking, inertial tracking only, no tracking) */
	UPROPERTY(BlueprintReadOnly, Category = "VR Tunnelling | MotionController")
		ETrackingStatus CurrentTrackingStatus;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	/** Whether or not this component had a valid tracked device this frame */
	UFUNCTION(BlueprintPure, Category = "MotionController") bool IsTracked() const
	{
		return bTracked;
	}

	UFUNCTION(BlueprintSetter, meta = (DeprecatedFunction, DeprecationMessage = "Please use the Motion Source property instead of Hand"))
		void SetTrackingSource(const EControllerHand NewSource);

	UFUNCTION(BlueprintGetter, meta = (DeprecatedFunction, DeprecationMessage = "Please use the Motion Source property instead of Hand"))
		EControllerHand GetTrackingSource() const;

	UFUNCTION(BlueprintSetter)
		void SetTrackingMotionSource(const FName NewSource);

	UFUNCTION(BlueprintSetter)
		void SetAssociatedPlayerIndex(const int32 NewPlayer);

	//*****************************************************************
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Tunnelling|Effect Preset")
		UVRTPPresetData* Preset;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Tunnelling|Effect Preset")
		bool bEnablePreset;
	
	// DEV BRANCH
	/*
	//Cage Blueprint to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "VR Tunnelling")
		TSubclassOf<class AActor> CageBlueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> CageBlueprintSwap;
	*/

	//Skybox Blueprint to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "VR Tunnelling")
		TSubclassOf<class AActor> SkyboxBlueprint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> SkyboxBlueprintSwap;

	//Post Process Material to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, AdvancedDisplay, Category = "VR Tunnelling")
		UMaterial* PostProcessMaterial;
	UPROPERTY(EditAnywhere)
		UMaterial* PostProcessMaterialSwap;

	//Effect Vignette Color
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
		FLinearColor EffectColor;
	UPROPERTY(EditAnywhere)
		FLinearColor EffectColorSwap;

	//Effect Vignette Coverage
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float EffectCoverage;
	UPROPERTY(EditAnywhere)
		float EffectCoverageSwap;

	//Effect Vignette Feather
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings", meta = (ClampMin = "0.0", ClampMax = "10.0"))
		float EffectFeather;
	UPROPERTY(EditAnywhere)
		float EffectFeatherSwap;

	//Effect Background Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
		EVRTPBackgroundMode BackgroundMode;
	UPROPERTY(EditAnywhere)
		EVRTPBackgroundMode BackgroundModeSwap;

	//Enable Effect Colour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
		bool ApplyEffectColor;
	UPROPERTY(EditAnywhere)
		bool ApplyEffectColorSwap;

	//Force Vignette Effect (Useful for debugging)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings")
		bool ForceEffect;
	UPROPERTY(EditAnywhere)
		bool ForceEffectSwap;

	//Effect Mask Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings|Mask Settings")
		EVRTPMaskMode MaskMode;
	UPROPERTY(EditAnywhere)
		EVRTPMaskMode MaskModeSwap;

	//Effect Mask Stencil Index
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Effect Settings|Mask Settings", meta = (ClampMin = "0", ClampMax = "255"))
		int32 StencilIndex;
	UPROPERTY(EditAnywhere)
		int32 StencilIndexSwap;

	//Enable Effect for Angular Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity")
		bool bUseAngularVelocity;
	UPROPERTY(EditAnywhere)
		bool bUseAngularVelocitySwap;

	//Angular Effect Strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
		float AngularStrength;
	UPROPERTY(EditAnywhere)
		float AngularStrengthSwap;

	//Minimum Angular Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
		float AngularMin;
	UPROPERTY(EditAnywhere)
		float AngularMinSwap;

	//Maximum Angular Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "180.0"))
		float AngularMax;
	UPROPERTY(EditAnywhere)
		float AngularMaxSwap;

	//Angular Smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Angular Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float AngularSmoothing;
	UPROPERTY(EditAnywhere)
		float AngularSmoothingSwap;

	//Enable Effect for Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity")
		bool bUseVelocity;
	UPROPERTY(EditAnywhere)
		bool bUseVelocitySwap;

	//Velocity Effect Strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "10.0"))
		float VelocityStrength;
	UPROPERTY(EditAnywhere)
		float VelocityStrengthSwap;

	//Minimum Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
		float VelocityMin;
	UPROPERTY(EditAnywhere)
		float VelocityMinSwap;

	//Maximum Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
		float VelocityMax;
	UPROPERTY(EditAnywhere)
		float VelocityMaxSwap;

	//Velocity Smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Velocity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float VelocitySmoothing;
	UPROPERTY(EditAnywhere)
		float VelocitySmoothingSwap;

	//Enable Effect for Acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration")
		bool bUseAcceleration;
	UPROPERTY(EditAnywhere)
		bool bUseAccelerationSwap;

	//Acceleration Effect Strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "10.0"))
		float AccelerationStrength;
	UPROPERTY(EditAnywhere)
		float AccelerationStrengthSwap;

	//Minimum Acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
		float AccelerationMin;
	UPROPERTY(EditAnywhere)
		float AccelerationMinSwap;

	//Maximum Acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
		float AccelerationMax;
	UPROPERTY(EditAnywhere)
		float AccelerationMaxSwap;

	//Acceleration Smoothing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SimpleDisplay, Category = "VR Tunnelling|Motion Settings|Acceleration", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float AccelerationSmoothing;
	UPROPERTY(EditAnywhere)
		float AccelerationSmoothingSwap;
	
	USceneCaptureComponentCube* SceneCaptureCube;

	// DEV BRANCH
	/*
	USceneCaptureComponent2D* SceneCaptureLeft;
	USceneCaptureComponent2D* SceneCaptureRight;
	UTextureRenderTarget2D* TL;
	UTextureRenderTarget2D* TR;
	AActor* Cage;
	*/

	UTextureRenderTargetCube* TC;
	float HFov;
	float VFov;
	UMaterialInstanceDynamic* PostProcessMID;
	AActor* Skybox;
	bool CaptureInit;

	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
		void ApplyPreset(UVRTPPresetData* NewPreset);

	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
		void SetBackgroundMode(EVRTPBackgroundMode NewBackgroundMode);

	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
		void SetMaskMode(EVRTPMaskMode NewMaskMode);

	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
		void SetEffectColor(FLinearColor NewColor);

	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
		void ApplyColor(bool Enabled);

	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
		void SetStencilMask(int32 NewStencilIndex, bool UpdateMaskedObjects = true);

	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
		void UpdateMaskedObjects();

	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
		void SetFeather(float NewFeather);


	//*****************************************************************

public:
	//~ UObject interface
	virtual void Serialize(FArchive& Ar) override;

#if WITH_EDITOR
	virtual void PreEditChange(UProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif 

public:
	//~ UActorComponent interface
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

protected:
	//~ Begin UActorComponent Interface.
	virtual void CreateRenderState_Concurrent() override;
	virtual void SendRenderTransform_Concurrent() override;
	//~ End UActorComponent Interface.

	// Cached Motion Controller that can be read by GetParameterValue. Only valid for the duration of OnMotionControllerUpdated
	IMotionController* InUseMotionController;

	/** Blueprint Implementable function for reponding to updated data from a motion controller (so we can use custom paramater values from it) */
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

	/** Whether or not this component had a valid tracked controller associated with it this frame*/
	bool bTracked;

	/** Whether or not this component has authority within the frame*/
	bool bHasAuthority;

	/** If true, the Position and Orientation args will contain the most recent controller state */
	bool PollControllerState(FVector& Position, FRotator& Orientation, float WorldToMetersScale);

	FTransform RenderThreadRelativeTransform;
	FVector RenderThreadComponentScale;

	void CacheSettings();
	void InitCapture();
	void InitSkybox();
	void InitFromPreset();
	void SetPresetData(UVRTPPresetData* NewPreset);
	void UpdatePostProcessSettings();

	// DEV BRANCH
	/*
	void InitCage();
	void GetProjectionMatrices();
	*/

	void CalculateMotion(float DeltaTime);
	void ApplyBackgroundMode();
	void ApplyMaskMode();
	void ApplyStencilMasks();

	/** View extension object that can persist on the render thread without the motion controller component */
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
		virtual bool IsActiveThisFrame(class FViewport* InViewport) const;

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
