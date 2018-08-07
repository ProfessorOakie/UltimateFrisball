// Fill out your copyright notice in the Description page of Project Settings.

#include "FrisballPlayerState.h"
#include "UnrealNetwork.h"

void AFrisballPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFrisballPlayerState, m_TeamNumber1);
	DOREPLIFETIME(AFrisballPlayerState, m_TeamAssigned);
}

