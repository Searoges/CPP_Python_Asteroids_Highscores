#pragma once
#include <map>
#include <SDL.h>

class StateMachine
{
public:

	class State
	{
	public:
		virtual void Init() { frameCount = 0; }
		virtual bool Update() 
		{ 
			frameCount++;
			return true; 
		}
		virtual void Draw() {};
		virtual void Exit() {};

		virtual const char* Name()
		{
			return "No label defined";
		}

		virtual bool CanPause() { return false; }

		int frameCount;
	};

	class PausibleState : public State
	{
	public:
		virtual bool CanPause() { return true; }
	};

	StateMachine();

	void Init();
	void SetState(const char* NewState);
	bool Update();
	void Draw();
	void Exit();

	std::map<const char*, State*> stateDictionary;

	void AddState(const char* name, State* state);

	void RestartGameFromPauseMode(const char* NewState);
	void ReturnToGameFromPauseMode();
	void SetPauseMode(const char* NewState);

private:

	void Reset();

	const char* TheGameState;
	const char* TheNextGameState;
	const char* PrePauseState;
	const char* pauseState;

};