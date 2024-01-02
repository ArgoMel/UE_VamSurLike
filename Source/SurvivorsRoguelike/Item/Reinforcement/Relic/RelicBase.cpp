// Fill out your copyright notice in the Description page of Project Settings.


#include "RelicBase.h"
#include "../Public/Character/BaseCharacter.h"

ARelicBase::ARelicBase()
{
	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
}

void ARelicBase::Act()
{
}
