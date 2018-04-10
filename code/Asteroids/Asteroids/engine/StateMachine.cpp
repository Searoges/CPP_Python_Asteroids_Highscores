#include "StateMachine.h"
#include <stdlib.h>
#include <assert.h>
#include "Input.h"



StateMachine::StateMachine()
{
	Reset();
}

void StateMachine::AddState(const char * name, State * state)
{
	if (stateDictionary.find(name) == stateDictionary.end())
	{
		stateDictionary.insert(std::pair<const char*, State*>(name, state));
	}
}

void StateMachine::Reset()
{
	TheGameState = NULL;
	TheNextGameState = NULL;
}

void StateMachine::Init()
{
	if (TheGameState != NULL)
	{
		stateDictionary[TheGameState]->Init();
	}
	else
	{
		if (TheNextGameState != NULL)
		{
			if (TheGameState != NULL)
			{
				stateDictionary[TheGameState]->Exit();

			}

			TheGameState = TheNextGameState;
			TheNextGameState = NULL;
		}

		if (TheGameState)
		{
			stateDictionary[TheGameState]->Init();
		}
	}
}

void StateMachine::SetState(const char * NewState)
{
	TheNextGameState = NewState;
}

void StateMachine::SetPauseMode(const char* NewState)
{
	pauseState = NewState;
}

void StateMachine::ReturnToGameFromPauseMode()
{
	if (PrePauseState != NULL) // currently in pause, so go back to the game
	{
		stateDictionary[TheGameState]->Exit();
		TheGameState = PrePauseState;
		PrePauseState = NULL;
	}
	
}

void StateMachine::RestartGameFromPauseMode(const char* NewState)
{
	TheGameState = NULL;

	if (PrePauseState != NULL)
	{
		PrePauseState = NULL;
	}

	if (NewState != NULL)
	{
		SetState(NewState);
		Update();
	}
}


bool StateMachine::Update()
{
	if ((Input::Get()->GetKeyState('P') == KeyState_Pressed)
		&& (TheGameState != NULL)
		&& (TheGameState != pauseState)
		)
	{
		if (PrePauseState != NULL) // currently in pause, so go back to the game
		{
			stateDictionary[TheGameState]->Exit();
			TheGameState = PrePauseState;
			PrePauseState = NULL;
		}
		else
		{
			//not in pause state, so see if we can transfer ..
			if (stateDictionary[TheGameState]->CanPause() == true)
			{
				assert(PrePauseState == NULL);

				PrePauseState = TheGameState;
				TheGameState = pauseState;

				stateDictionary[TheGameState]->Init();
			}
		}
	}
	else
	{
		if (TheNextGameState != NULL)
		{
			if (TheGameState != NULL)
			{
				stateDictionary[TheGameState]->Exit();
			}

			TheGameState = TheNextGameState;
			TheNextGameState = NULL;

			stateDictionary[TheGameState]->Init();
		}


		if (TheGameState == NULL)
		{
			return true;
		}
	}
	return stateDictionary[TheGameState]->Update();

}

void StateMachine::Draw()
{

	if (TheGameState != NULL)
	{
		stateDictionary[TheGameState]->Draw();
	}
}

void StateMachine::Exit()
{
	if (TheGameState != NULL)
	{
		stateDictionary[TheGameState]->Exit();

		TheGameState = NULL;
	}

	if (TheNextGameState != NULL)
	{
		TheNextGameState = NULL;
	}
}