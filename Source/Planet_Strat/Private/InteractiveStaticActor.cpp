#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::White, text);

#include "InteractiveStaticActor.h"

// Sets default values
AInteractiveStaticActor::AInteractiveStaticActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	isOn = false;
	isToogle = false;

	VisibleMeshStaticPart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMeshStaticPart"));

	VisibleMeshMovingPart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleMeshMovingPart"));
	VisibleMeshMovingPart->SetupAttachment(VisibleMeshStaticPart);

	bReplicates = true;
}

// Called when the game starts or when spawned
void AInteractiveStaticActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractiveStaticActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractiveStaticActor::mouseLeftClick(APawn* PawnWhoClicked, UPrimitiveComponent* hitComponent)
{
	if (hitComponent == VisibleMeshMovingPart)
	{
		if (isToogle)
		{
			isOn = !isOn;
			if (isOn)
			{
				SendMainActionSignal();
				reactGraphicallyToPress(true);
			}
			else
			{
				reactGraphicallyToPress(false);
			}
		}
		else
		{
			SendMainActionSignal();
			reactGraphicallyToPress();
		}

	}
}

void AInteractiveStaticActor::SendMainActionSignal()
{
	if (IMainActionInterface* actorWithInterfaceToCall = Cast<IMainActionInterface>(ActorToCallMainAction))
	{
		actorWithInterfaceToCall->mainAction();
	}
}

