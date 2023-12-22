#pragma once
#include "Controller/BasePlayerController.h"
#include "LobbyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class SURVIVORSROGUELIKE_API ALobbyPlayerController : public ABasePlayerController
{
	GENERATED_BODY()
public:
	ALobbyPlayerController();

private:
	TObjectPtr<UInputMappingContext> m_IMC;
	TObjectPtr<UInputAction> m_Move;
	TObjectPtr<UInputAction> m_Jump;
	TObjectPtr<UInputAction> m_Sprint;
	TObjectPtr<UInputAction> m_Crouch;
	TObjectPtr<UInputAction> m_Walk;
	TObjectPtr<UInputAction> m_Interaction;
	TObjectPtr<UInputAction> m_Prone;

public:
	UInputAction* GetKeyMove()
	{
		return m_Move;
	}
	UInputAction* GetKeyJump()
	{
		return m_Jump;
	}
	UInputAction* GetKeySprint()
	{
		return m_Sprint;
	}
	UInputAction* GetKeyCrouch()
	{
		return m_Crouch;
	}
	UInputAction* GetKeyWalk()
	{
		return m_Walk;
	}
	UInputAction* GetKeyInteraction()
	{
		return m_Interaction;
	}
	UInputAction* GetKeyProne()
	{
		return m_Prone;
	}

	void SetNewController();
	void AddController();

	UFUNCTION(BlueprintCallable)
	void RefreshKeyMapping();
};
