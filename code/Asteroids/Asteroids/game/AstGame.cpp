#include "AstGame.h"
#include "GameStates.h"
#include <assert.h>

void AstGame::ExplodeRock(Rock& rock)
{
	explosionManager.Add(rock.GetPosition(),rock.GetLineList());

	switch(rock.size)
	{
	case Rock::Size_big:
	{
		for(int i=0;i<4;i++)
		{
			Rock *pNewRock = new Rock();
			rockList.push_back(pNewRock);
			
			pNewRock->Init(rock);						
		}

		Score += 10;
	}
	break;

	case Rock::Size_medium:
	{				
		for(int i=0;i<3;i++)
		{
			Rock *pNewRock = new Rock();
			rockList.push_back(pNewRock);

			pNewRock->Init(rock);
		}

		Score += 50;
	}
	break;

	case Rock::Size_small:
		Score += 100;
		break;

	default:
		assert(0);
		break;
	}
	rock.SetInUse(false);
}

void AstGame::Init()
{
	TheShip.Init();
	bShipActive = false;

	CreateRocks();
	ResetScore();	

	explosionManager.Clear();
}
bool AstGame::OnOneTimeInit()
{	
	Init();

	stateMachine.AddState(GameState_Attract::Label, new GameState_Attract());

	stateMachine.AddState(GameState_StartGame::Label, new GameState_StartGame());
	stateMachine.AddState(GameState_CreateWave::Label, new GameState_CreateWave());
	stateMachine.AddState(GameState_PlaceShip::Label, new GameState_PlaceShip());
	stateMachine.AddState(GameState_Play::Label, new GameState_Play());
	stateMachine.AddState(GameState_EndOfWave::Label, new GameState_EndOfWave());
	stateMachine.AddState(GameState_GameOver::Label, new GameState_GameOver());
	stateMachine.AddState(PauseGameState::Label, new PauseGameState());

	stateMachine.SetState(GameState_Attract::Label);
	stateMachine.SetPauseMode(PauseGameState::Label);

	return true;
}

void AstGame::Update()
{
	if(IsShipActive() == true)
	{
		TheShip.Update();
	}
		
	TheShip.SetCollided(false);
	
	for (std::list<Rock*>::iterator rock = rockList.begin(); rock != rockList.end(); rock++)
	{
		if((*rock)->IsInUse() == true)
		{			
			for (std::list<Bullet*>::iterator bullet = bulletList.begin(); bullet != bulletList.end(); bullet++)
			{
				if( ((*bullet)->IsInUse() == true) && ((*rock)->IsInUse() == true))
				{
					if((*bullet)->CollidesWith((*rock)) == true)
					{
						ExplodeRock(*(*rock));
						
						(*bullet)->SetInUse(false);
					}
				}
			}

			if(IsShipActive() == true)
			{
				if(((*rock)->IsInUse() == true) && (TheShip.CollidesWith((*rock) ) == true))
				{
					if (TheShip.canCollide() == true)
					{
						TheShip.SetCollided(true);						
					}
					ExplodeRock(*(*rock));					
				}
			}
		}
	}

	if(TheShip.GetCollided() == true)
	{
		TheShip.OnCollided();		
		explosionManager.Add(TheShip.GetPosition(),TheShip.GetLineList());

		bShipActive = false;
		Ships--;
	}

	std::list<Rock*>::iterator rock = rockList.begin();
	while (rock != rockList.end())
	{
		if ((*rock)->IsInUse() == true)
		{
			(*rock)->Update();
			rock++;
		}
		else
		{
			delete (*rock);
			rock = rockList.erase(rock);
		}
	}


	std::list<Bullet*>::iterator bullet = bulletList.begin();
	while (bullet != bulletList.end())
	{
		if ((*bullet)->IsInUse() == true)
		{
			(*bullet)->Update();
			bullet++;
		}
		else
		{
			delete(*bullet);
			bullet = bulletList.erase(bullet);
		}
	}

	


	explosionManager.Update();
}

void AstGame::Draw()
{
	SDL_SetRenderDrawColor(Renderer::Get()->renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer::Get()->renderer);

	Renderer::Viewport vp;
	Renderer::Get()->GetViewport(vp);

	Renderer::Get()->DrawRect(0,0,(float)vp.Width, (float)vp.Height,RGBTOCOLOR(0,0,0));
	
	if(IsShipActive() == true)
	{
		TheShip.Draw();
	}

	for (std::list<Rock*>::iterator rock = rockList.begin(); rock != rockList.end(); rock++)
	{
		if ((*rock)->IsInUse() == true)
		{
			(*rock)->Draw();
		}
	}

	for (std::list<Bullet*>::iterator bullet = bulletList.begin(); bullet != bulletList.end(); bullet++)
	{
		if ((*bullet)->IsInUse() == true)
		{
			(*bullet)->Draw();
		}
	}
	
	explosionManager.Draw();

	Renderer::Get()->debugPrinter->Print(700,20,RGBTOCOLOR(255,255,255),"Score: %d",Score);

	char text[32] = "";

	for(int i=0;i<Ships;i++)
	{
		strcat(text,"A");
	}


	Renderer::Get()->debugPrinter->Print(700,50,RGBTOCOLOR(255,255,255), text);
}


void AstGame::CreateRocks()
{	
#if false
	rockList.Clear();
	rockList.GetFree()->Init(Vector2(100,0),Rock::Size_big,Vector2(0,-1));
	rockList.GetFree()->Init(Vector2(150,0),Rock::Size_big,Vector2(0,1));

	rockList.GetFree()->Init(Vector2(550,0),Rock::Size_big,Vector2(0,-1));
	rockList.GetFree()->Init(Vector2(500,0),Rock::Size_big,Vector2(0,1));
#endif

	std::list<Rock*>::iterator it = rockList.begin();
	while (it != rockList.end())
	{
		Rock *pRock = (*it);
		delete pRock;

		it = rockList.erase(it);		
	}


	Rock *pRock = new Rock();
	rockList.push_back(pRock);
	pRock->Init(Vector2(100, 0), Rock::Size_big, Vector2(0, -1));

	pRock = new Rock();
	rockList.push_back(pRock);
	pRock->Init(Vector2(150, 0), Rock::Size_big, Vector2(0, 1));

	pRock = new Rock();
	rockList.push_back(pRock);
	pRock->Init(Vector2(550, 0), Rock::Size_big, Vector2(0, -1));

	pRock = new Rock();
	rockList.push_back(pRock);
	pRock->Init(Vector2(500, 0), Rock::Size_big, Vector2(0, 1));
}

bool AstGame::IsShipActive()
{
	return bShipActive;
}

void AstGame::PlaceShip()
{
	TheShip.Init();
	bShipActive = true;
}

void AstGame::ResetScore()
{
	Score = 0;
	Ships = 3;
}

void AstGame::GUIPrint(int x, int y,char* fmt)
{
	Renderer::Get()->debugPrinter->Print(x, y, RGBTOCOLOR(255, 255, 255), fmt);
}

void AstGame::SetInvincible()
{
	TheShip.SetInvincible();
}