// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBlackHole.generated.h"

UCLASS()
class FPSGAME_API AFPSBlackHole : public AActor
{
    GENERATED_BODY()

public:
    AFPSBlackHole();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnInnerOverlap(UPrimitiveComponent *OverlapComp, AActor *Other, UPrimitiveComponent *OtherComp, int32 otherIndex, bool fromSweep, const FHitResult &SweepResult);
    
#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& e) override;
#endif
    
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BlackHoleVisibility", Meta = (AllowPrivateAccess = "True"))
    class USceneComponent* BlackHoleSceneRootComp;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BlackHoleVisibility", Meta = (AllowPrivateAccess = "True"))
    class UStaticMeshComponent* BlackHoleMeshComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Area", Meta = (AllowPrivateAccess = "True"))
    class USphereComponent* BlackHoleDestroyComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Area", Meta = (AllowPrivateAccess = "True"))
    class USphereComponent* BlackHoleCollisionComp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect radius", Meta = (AllowPrivateAccess = "True"))
    float BlackHoleRadius = 256.f; 
};
