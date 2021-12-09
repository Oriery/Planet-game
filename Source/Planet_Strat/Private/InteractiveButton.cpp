#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::White, text);

#include "InteractiveButton.h"

AInteractiveButton::AInteractiveButton() : AInteractiveStaticActor::AInteractiveStaticActor()
{

	PlaceOfButtonDefault = CreateDefaultSubobject<USceneComponent>(TEXT("PlaceOfButtonDefault"));
	PlaceOfButtonDefault->SetupAttachment(VisibleMeshStaticPart);

	PlaceOfButtonWhenPressed = CreateDefaultSubobject<USceneComponent>(TEXT("PlaceOfButtonWhenPressed"));
	PlaceOfButtonWhenPressed->SetupAttachment(PlaceOfButtonDefault);

}

void AInteractiveButton::ResetPositionOfButtonToDefault()
{
	VisibleMeshMovingPart->SetWorldLocation(PlaceOfButtonDefault->GetComponentLocation());
}

void AInteractiveButton::reactGraphicallyToPress(bool switchingOn)
{
	MulticastRPC_reactGraphicallyToPress(switchingOn);
}

void AInteractiveButton::MulticastRPC_reactGraphicallyToPress_Implementation(bool switchingOn = true)
{
	if (!HasAuthority())
	{
		if (isToogle)
		{
			if (switchingOn)
			{
				VisibleMeshMovingPart->SetWorldLocation(PlaceOfButtonWhenPressed->GetComponentLocation());
			}
			else
			{
				VisibleMeshMovingPart->SetWorldLocation(PlaceOfButtonDefault->GetComponentLocation());
			}
		}
		else
		{
			VisibleMeshMovingPart->SetWorldLocation(PlaceOfButtonWhenPressed->GetComponentLocation());
			FTimerHandle timerHandle;
			GetWorldTimerManager().SetTimer(timerHandle, this, &AInteractiveButton::ResetPositionOfButtonToDefault, 1.0, false, 0.5);
		}
	}
}
