#include "ValuableObject.h"

// Sets default values
AValuableObject::AValuableObject()
{
    // Set this actor to call Tick() every frame.
    PrimaryActorTick.bCanEverTick = true;

    // Default Dogecoin value
    DogecoinValue = 0.0f;
}

// Called when the game starts or when spawned
void AValuableObject::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AValuableObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Function to set Dogecoin value dynamically
void AValuableObject::SetDogecoinValue(float NewValue)
{
    DogecoinValue = NewValue;
}

// Function to get the current Dogecoin value
float AValuableObject::GetDogecoinValue() const
{
    return DogecoinValue;
}
