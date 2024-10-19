#include "ValuableMesh.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AValuableMesh::AValuableMesh()
{
    // Create and attach the StaticMeshComponent
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void AValuableMesh::BeginPlay()
{
    Super::BeginPlay();
}

// Function to dynamically set the mesh of this object
void AValuableMesh::SetMesh(UStaticMesh* NewMesh)
{
    if (MeshComponent && NewMesh)
    {
        MeshComponent->SetStaticMesh(NewMesh);
    }
}
