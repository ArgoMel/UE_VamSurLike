#include "Controller/LobbyPlayerController.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>	IMC_Lobby(TEXT(
		"/Game/0_KBJ/Input/IMC_Lobby.IMC_Lobby"));
	if (IMC_Lobby.Succeeded())
	{
		m_IMC = IMC_Lobby.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>	IA_Move(TEXT(
		"/Game/0_KBJ/Input/IA_Move.IA_Move"));
	if (IA_Move.Succeeded())
	{
		m_Move = IA_Move.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>	IA_Sprint(TEXT(
		"/Game/0_KBJ/Input/IA_Sprint.IA_Sprint"));
	if (IA_Sprint.Succeeded())
	{
		m_Sprint = IA_Sprint.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>	IA_Jump(TEXT(
		"/Game/0_KBJ/Input/IA_Jump.IA_Jump"));
	if (IA_Jump.Succeeded())
	{
		m_Jump = IA_Jump.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>	IA_Interaction(TEXT(
		"/Game/0_KBJ/Input/IA_Interaction.IA_Interaction"));
	if (IA_Interaction.Succeeded())
	{
		m_Interaction = IA_Interaction.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>	IA_Crouch(TEXT(
		"/Game/0_KBJ/Input/IA_Crouch.IA_Crouch"));
	if (IA_Crouch.Succeeded())
	{
		m_Crouch = IA_Crouch.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>	IA_Walk(TEXT(
		"/Game/0_KBJ/Input/IA_Walk.IA_Walk"));
	if (IA_Walk.Succeeded())
	{
		m_Walk = IA_Walk.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>	IA_Prone(TEXT(
		"/Game/0_KBJ/Input/IA_Prone.IA_Prone"));
	if (IA_Prone.Succeeded())
	{
		m_Prone = IA_Prone.Object;
	}
}

void ALobbyPlayerController::SetNewController()
{
	ULocalPlayer* localPlayer = GetLocalPlayer();
	if (IsValid(localPlayer))
	{
		UEnhancedInputLocalPlayerSubsystem* subSystem =
			localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (IsValid(subSystem))
		{
			subSystem->ClearAllMappings();
			subSystem->AddMappingContext(m_IMC, 0);
		}
	}
}

void ALobbyPlayerController::AddController()
{
	ULocalPlayer* localPlayer = GetLocalPlayer();
	if (IsValid(localPlayer))
	{
		UEnhancedInputLocalPlayerSubsystem* subSystem =
			localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (IsValid(subSystem))
		{
			subSystem->AddMappingContext(m_IMC, 0);
		}
	}
}
