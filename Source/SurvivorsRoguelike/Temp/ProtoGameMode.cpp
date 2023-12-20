// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtoGameMode.h"
#include "ProtoCharacter.h"
#include "ProtoPlayerController.h"

AProtoGameMode::AProtoGameMode()
{
	DefaultPawnClass = AProtoCharacter::StaticClass();
	PlayerControllerClass = AProtoPlayerController::StaticClass();
}
