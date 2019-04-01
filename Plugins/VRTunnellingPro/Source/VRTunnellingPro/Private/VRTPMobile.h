#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SceneCaptureComponentCube.h"
#include "Engine/TextureRenderTargetCube.h"
#include "Engine/DataAsset.h"
#include "VRTPMobile.generated.h"

UENUM(BlueprintType)
enum class EVRTPMBackgroundMode : uint8
{
	MM_COLOR 		UMETA(DisplayName = "Color"),
	MM_SKYBOX		UMETA(DisplayName = "Skybox")
};

UENUM(BlueprintType)
enum class EVRTPMMaskMode : uint8
{
	MM_OFF 			UMETA(DisplayName = "Off"),
	MM_MASK			UMETA(DisplayName = "Mask"),
	MM_WINDOW 		UMETA(DisplayName = "Window"),
	MM_PORTAL		UMETA(DisplayName = "Portal"),
};

USTRUCT(BlueprintType)
struct FVRTPMPreset
{
	GENERATED_USTRUCT_BODY()

	//Skybox Blueprint to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Capture")
	TSubclassOf<class AActor> SkyboxBlueprint;

	//Effect Material to use
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
	EVRTPMBackgroundMode BackgroundMode;

	//Enable Effect Colour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
	bool ApplyEffectColor;

	//Force Vignette Effect (Useful for debugging)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings")
	bool ForceEffect;

	//Effect Mask Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect Settings|Mask Settings")
	EVRTPMMaskMode MaskMode;

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
	FVRTPMPreset()
	{
		SkyboxBlueprint = NULL;
		PostProcessMaterial = NULL;
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

UCLASS()
class UVRTPMPresetData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FVRTPMPreset Data;
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Tunnelling|Effect Preset")
	UVRTPMPresetData* Preset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Tunnelling|Effect Preset")
	bool bEnablePreset;

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
	EVRTPMBackgroundMode BackgroundMode;
	UPROPERTY(EditAnywhere)
	EVRTPMBackgroundMode BackgroundModeSwap;

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
	EVRTPMMaskMode MaskMode;
	UPROPERTY(EditAnywhere)
	EVRTPMMaskMode MaskModeSwap;

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
	UTextureRenderTargetCube* TC;
	float HFov;
	float VFov;
	UMaterialInstanceDynamic* PostProcessMID;
	AActor* Skybox;
	bool CaptureInit;

	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void ApplyPreset(UVRTPMPresetData* NewPreset);

	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void SetBackgroundMode(EVRTPMBackgroundMode NewBackgroundMode);

	UFUNCTION(BlueprintCallable, Category = "VR Tunnelling")
	void SetMaskMode(EVRTPMMaskMode NewMaskMode);

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
	void InitFromPreset();
	void SetPresetData(UVRTPMPresetData* NewPreset);
	void UpdateEffectSettings();

	void CalculateMotion(float DeltaTime);
	void ApplyBackgroundMode();
	void ApplyMaskMode();
	void ApplyStencilMasks();
		
	
};
