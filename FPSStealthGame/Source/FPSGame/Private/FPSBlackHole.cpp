// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AFPSBlackHole::AFPSBlackHole()
{
    PrimaryActorTick.bCanEverTick = true;

    BlackHoleSceneRootComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComp"));
    RootComponent = BlackHoleSceneRootComp;

    BlackHoleMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackHoleMeshComp"));
    BlackHoleMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    BlackHoleMeshComp->SetupAttachment(RootComponent);

    BlackHoleDestroyComp = CreateDefaultSubobject<USphereComponent>(TEXT("BlackHoleDestroyComp"));
    BlackHoleDestroyComp->SetSphereRadius(100);
    BlackHoleDestroyComp->SetupAttachment(RootComponent);

    BlackHoleCollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("BlackHoleCollisionComponent"));
    BlackHoleCollisionComp->SetSphereRadius(BlackHoleRadius);
    BlackHoleCollisionComp->SetupAttachment(RootComponent);
}

void AFPSBlackHole::BeginPlay()
{
    Super::BeginPlay();

    if (BlackHoleDestroyComp)
    {
        BlackHoleDestroyComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OnInnerOverlap);
    }
}

void AFPSBlackHole::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TArray<UPrimitiveComponent*> Overlapping;
    BlackHoleCollisionComp->GetOverlappingComponents(Overlapping);
    for (UPrimitiveComponent* Comp : Overlapping)
    {
        if (Comp && Comp->IsSimulatingPhysics())
        {
            const FVector Origin = GetActorLocation();
            const float Radius = BlackHoleCollisionComp->GetScaledSphereRadius();
            const float Strength = -5000;
            const ERadialImpulseFalloff Falloff = RIF_Linear;
            Comp->AddRadialForce(Origin, Radius, Strength, Falloff, true);
        }
    }
}

void AFPSBlackHole::OnInnerOverlap(UPrimitiveComponent* OverlapComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 otherIndex, bool fromSweep, const FHitResult& SweepResult)
{
    if (Other)
    {
        Other->Destroy();
    }
}


#if WITH_EDITOR
void AFPSBlackHole::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
    const FName BlackHoleRadiusName = (e.Property != nullptr) ? e.Property->GetFName() : NAME_None;
    if (BlackHoleCollisionComp && BlackHoleRadiusName == GET_MEMBER_NAME_CHECKED(AFPSBlackHole, BlackHoleRadius))
    {
        BlackHoleCollisionComp->SetSphereRadius(BlackHoleRadius);
    }
    Super::PostEditChangeProperty(e);
}
#endif
