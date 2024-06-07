#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include "utils.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_Background = new Texture("Background.png");
	m_EvilWizard = new Texture("EvilWizard.png");
	m_PlebsAliveT = new Texture("Plebs_Alive.png");
	m_PlebsDeadT = new Texture("Plebs_Dead.png");
	m_PollenAmmo = new Texture("PollenCount.png");
	m_GameOver = new Texture("GameOver.png");
	m_StartScreen = new Texture("StartScreen.png");
	m_ScoreCounter = std::to_string(m_Points);
	Font = TTF_OpenFont("AGENCYB.TTF", 30);
	m_Score = new Texture(m_ScoreCounter, Font, Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	m_ScorePrint = new Texture(m_ScoreString, Font, Color4f(1.0f, 0.0f, 0.0f, 1.0f));
	m_Loc.x = 1080.0f / 2.0f - m_EvilWizard->GetWidth() / 2.0f;
	m_Loc.y = 720.0f / 2.0f - m_EvilWizard->GetHeight() / 2.0f;
	m_SourceRect.left = 0.0f;
	m_SourceRect.bottom = 0.0f;
	m_SourceRect.width = m_EvilWizard->GetWidth();
	m_SourceRect.height = m_EvilWizard->GetHeight();
	m_DestRect.left = m_Loc.x;
	m_DestRect.bottom = m_Loc.y;
	m_DestRect.width = m_EvilWizard->GetWidth() / 3 * 2;
	m_DestRect.height = m_EvilWizard->GetHeight() / 3 * 2;

	m_RandomPlebsLoc.x = float(rand() % (930 / 9 * 8) + 30);
	m_RandomPlebsLoc.y = float(rand() % (700 / 9 * 8) + 30);
	m_RandomPlebsLoc2.x = float(rand() % (930 / 9 * 8) + 30);
	m_RandomPlebsLoc2.y = float(rand() % (700 / 9 * 8) + 30);
	m_RandomPlebsLoc3.x = float(rand() % (930 / 9 * 8) + 30);
	m_RandomPlebsLoc3.y = float(rand() % (700 / 9 * 8) + 30);

	m_Reset = false;
	m_GameOverbool = false;

	for (int i{}; i <= 2; i++)
	{
		m_BulletsDown[i] = Rectf(3000.0f, 3000.0f, 6.0f, 6.0f);
		m_BulletsUp[i] = Rectf(3000.0f, 3000.0f, 6.0f, 6.0f);
		m_BulletsRight[i] = Rectf(3000.0f, 3000.0f, 6.0f, 6.0f);
		m_BulletsLeft[i] = Rectf(3000.0f, 3000.0f, 6.0f, 6.0f);
	}
}

void Game::Cleanup( )
{
	delete m_Background;
	delete m_EvilWizard;
	delete m_PlebsAliveT;
	delete m_PlebsDeadT;
	delete m_PollenAmmo;
	delete m_GameOver;
	delete m_Score;
	delete m_ScorePrint;
}

void Game::Update( float elapsedSec )
{

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	const bool Rbutton{ bool(pStates[SDL_SCANCODE_R]) };
	const bool Enterbutton{ bool(pStates[SDL_SCANCODE_P]) };
	if (m_GameStarted)
	{
		if (m_Reset)
		{
			m_Loc.x = 1080.0f / 2.0f - m_EvilWizard->GetWidth() / 2.0f;
			m_Loc.y = 720.0f / 2.0f - m_EvilWizard->GetHeight() / 2.0f;
			m_SourceRect.left = 0.0f;
			m_SourceRect.bottom = 0.0f;
			m_SourceRect.width = m_EvilWizard->GetWidth();
			m_SourceRect.height = m_EvilWizard->GetHeight();
			m_DestRect.left = m_Loc.x;
			m_DestRect.bottom = m_Loc.y;
			m_DestRect.width = m_EvilWizard->GetWidth() / 3 * 2;
			m_DestRect.height = m_EvilWizard->GetHeight() / 3 * 2;

			m_RandomPlebsLoc.x = float(rand() % (930 / 9 * 8) + 30);
			m_RandomPlebsLoc.y = float(rand() % (600 / 9 * 8) + 30);
			m_RandomPlebsLoc2.x = float(rand() % (930 / 9 * 8) + 30);
			m_RandomPlebsLoc2.y = float(rand() % (600 / 9 * 8) + 30);
			m_RandomPlebsLoc3.x = float(rand() % (930 / 9 * 8) + 30);
			m_RandomPlebsLoc3.y = float(rand() % (600 / 9 * 8) + 30);

			for (int i{}; i <= 2; i++)
			{
				m_BulletsDown[i] = Rectf(3000.0f, 3000.0f, 6.0f, 6.0f);
				m_BulletsUp[i] = Rectf(3000.0f, 3000.0f, 6.0f, 6.0f);
				m_BulletsRight[i] = Rectf(3000.0f, 3000.0f, 6.0f, 6.0f);
				m_BulletsLeft[i] = Rectf(3000.0f, 3000.0f, 6.0f, 6.0f);
			}

			m_Reset = false;
			m_GameOverbool = false;
			m_Points = 0;
			m_PollenMeter = 100;
			m_NewPowerCtr = 0;
			m_Counter = 0;
			m_InfPllnCntr = 0;
			m_DblSpdCntr = 0;
			m_Shootcounter = 0;
			m_CurrentPowerUp = powerUp::none;

			m_GameStarted = false;
		}

		m_NewPowerCtr += elapsedSec;

		m_Counter += elapsedSec;

		m_InfPllnCntr += elapsedSec;

		m_DblSpdCntr += elapsedSec;

		m_Shootcounter += elapsedSec;

		for (int i{}; i <= 2; i++)
		{
			if (HitByBullet(m_BulletsDown[i]))
			{
				m_PollenMeter -= 10.0f;
				m_BulletsDown[i].bottom = 3000.0f;
			}
			if (HitByBullet(m_BulletsUp[i]))
			{
				m_PollenMeter -= 10.0f;
				m_BulletsUp[i].bottom = 3000.0f;
			}
			if (HitByBullet(m_BulletsLeft[i]))
			{
				m_PollenMeter -= 10.0f;
				m_BulletsLeft[i].bottom = 3000.0f;
			}
			if (HitByBullet(m_BulletsRight[i]))
			{
				m_PollenMeter -= 10.0f;
				m_BulletsRight[i].bottom = 3000.0f;
			}
		}

		if (m_Shootcounter >= 4 - m_Points / 1000.0f)
		{
			m_BulletsRight[0].left = m_RandomPlebsDest.left + m_RandomPlebsDest.width / 2;
			m_BulletsRight[1].left = m_RandomPlebsDest2.left + m_RandomPlebsDest.width / 2;
			m_BulletsRight[2].left = m_RandomPlebsDest3.left + m_RandomPlebsDest.width / 2;
			m_BulletsRight[0].bottom = m_RandomPlebsDest.bottom + m_RandomPlebsDest.height / 2;
			m_BulletsRight[1].bottom = m_RandomPlebsDest2.bottom + m_RandomPlebsDest.height / 2;
			m_BulletsRight[2].bottom = m_RandomPlebsDest3.bottom + m_RandomPlebsDest.height / 2;

			m_BulletsLeft[0].left = m_RandomPlebsDest.left + m_RandomPlebsDest.width / 2;
			m_BulletsLeft[1].left = m_RandomPlebsDest2.left + m_RandomPlebsDest.width / 2;
			m_BulletsLeft[2].left = m_RandomPlebsDest3.left + m_RandomPlebsDest.width / 2;
			m_BulletsLeft[0].bottom = m_RandomPlebsDest.bottom + m_RandomPlebsDest.height / 2;
			m_BulletsLeft[1].bottom = m_RandomPlebsDest2.bottom + m_RandomPlebsDest.height / 2;
			m_BulletsLeft[2].bottom = m_RandomPlebsDest3.bottom + m_RandomPlebsDest.height / 2;

			m_BulletsUp[0].bottom = m_RandomPlebsDest.bottom + m_RandomPlebsDest.height / 2;
			m_BulletsUp[1].bottom = m_RandomPlebsDest2.bottom + m_RandomPlebsDest.height / 2;
			m_BulletsUp[2].bottom = m_RandomPlebsDest3.bottom + m_RandomPlebsDest.height / 2;
			m_BulletsUp[0].left = m_RandomPlebsDest.left + m_RandomPlebsDest.width / 2;
			m_BulletsUp[1].left = m_RandomPlebsDest2.left + m_RandomPlebsDest.width / 2;
			m_BulletsUp[2].left = m_RandomPlebsDest3.left + m_RandomPlebsDest.width / 2;

			m_BulletsDown[0].bottom = m_RandomPlebsDest.bottom + m_RandomPlebsDest.height / 2;
			m_BulletsDown[1].bottom = m_RandomPlebsDest2.bottom + m_RandomPlebsDest.height / 2;
			m_BulletsDown[2].bottom = m_RandomPlebsDest3.bottom + m_RandomPlebsDest.height / 2;
			m_BulletsDown[0].left = m_RandomPlebsDest.left + m_RandomPlebsDest.width / 2;
			m_BulletsDown[1].left = m_RandomPlebsDest2.left + m_RandomPlebsDest.width / 2;
			m_BulletsDown[2].left = m_RandomPlebsDest3.left + m_RandomPlebsDest.width / 2;

			m_Shootcounter = 0;
		}

		for (int i{}; i <= 2; i++)
		{
			m_BulletsDown[i].bottom--;
		}

		for (int i{}; i <= 2; i++)
		{
			m_BulletsLeft[i].left--;
		}

		for (int i{}; i <= 2; i++)
		{
			m_BulletsRight[i].left++;
		}

		for (int i{}; i <= 2; i++)
		{
			m_BulletsUp[i].bottom++;
		}

		if (m_NewPowerCtr >= 10 && !m_PowerUpSpawned)
		{
			int random = rand() % 2;

			switch (random)
			{
			case(0):
				m_CurrentPowerUp = powerUp::speed;
				break;
			case(1):
				m_CurrentPowerUp = powerUp::pollen;
				break;
			case(2):
				m_CurrentPowerUp = powerUp::points;
				break;
			}
			m_PowerUpSpawned = true;
			m_CurrentPowerUpLoc.x = float(rand() % (930 / 9 * 8) + 30);
			m_CurrentPowerUpLoc.y = float(rand() % (700 / 9 * 8) + 30);
		}
		if (m_DblSpeed) m_SPEEEEEEED = 400;
		else if (m_Counter >= 1 && !m_DblSpeed)
		{
			m_SPEEEEEEED = 200;
			m_Counter = 0;
		}

		if (m_InfPllnCntr >= 3)
		{
			m_InfPollen = false;
		}

		if (m_DblSpdCntr >= 3)
		{
			m_DblSpeed = false;
		}

		if (m_DblSpeed)
		{
			m_SPEEEEEEED = 400;
		}
		if (!m_GameOverbool) {
			Move(elapsedSec);
			m_DestRect.left = m_Loc.x;
			m_DestRect.bottom = m_Loc.y;


			m_RandomPlebsDest.width = m_PlebsAliveT->GetWidth();
			m_RandomPlebsDest.height = m_PlebsAliveT->GetHeight();

			m_RandomPlebsDest3.width = m_PlebsAliveT->GetWidth();
			m_RandomPlebsDest3.height = m_PlebsAliveT->GetHeight();

			m_RandomPlebsDest2.width = m_PlebsAliveT->GetWidth();
			m_RandomPlebsDest2.height = m_PlebsAliveT->GetHeight();

			m_RandomPlebsSrc.bottom = 0.0f;
			m_RandomPlebsSrc.left = 0.0f;
			m_RandomPlebsSrc.width = m_PlebsAliveT->GetWidth();
			m_RandomPlebsSrc.height = m_PlebsAliveT->GetHeight();

			m_RandomPlebsDest.left = m_RandomPlebsLoc.x;
			m_RandomPlebsDest.bottom = m_RandomPlebsLoc.y;

			m_RandomPlebsDest2.left = m_RandomPlebsLoc2.x;
			m_RandomPlebsDest2.bottom = m_RandomPlebsLoc2.y;

			m_RandomPlebsDest3.left = m_RandomPlebsLoc3.x;
			m_RandomPlebsDest3.bottom = m_RandomPlebsLoc3.y;

			InfectPlebs();

			if (!m_InfPollen)
			{
				m_PollenMeter -= 0.05f;
			}

			m_ScoreCounter = std::to_string(m_Points);

			delete m_Score;
			m_Score = new Texture(m_ScoreCounter, Font, Color4f(1.0f, 0.0f, 0.0f, 1.0f));
		}
		

		if (PowerUpInRange(m_CurrentPowerUpLoc))
		{
			switch (m_CurrentPowerUp)
			{
			case powerUp::speed:
				m_DblSpeed = true;
				m_DblSpdCntr = 0;
				m_NewPowerCtr = 0;
				m_PowerUpSpawned = false;
				m_CurrentPowerUp = powerUp::none;
				break;
			case powerUp::pollen:
				m_InfPollen = true;
				m_InfPllnCntr = 0;
				m_NewPowerCtr = 0;
				m_PowerUpSpawned = false;
				m_CurrentPowerUp = powerUp::none;
				break;
			case powerUp::points:
				m_Points += 200;
				m_NewPowerCtr = 0;
				m_PowerUpSpawned = false;
				m_CurrentPowerUp = powerUp::none;
				break;

			}
		}
		if (m_DestRect.bottom <= 22)
			m_DestRect.bottom = 23;
		if (m_DestRect.bottom + m_DestRect.height >= 702)
			m_DestRect.bottom = 701 - m_DestRect.height;
		if (m_DestRect.left <= 23)
			m_DestRect.left = 22;
		if (m_DestRect.left + m_DestRect.width >= 1052)
			m_DestRect.left = 1051 - m_DestRect.width;

		if (m_GameOverbool && Rbutton)
		{
			m_Reset = true;
		}
	}
	else 
	{
		if (Enterbutton) m_GameStarted = true;
	}
}

void Game::InfectPlebs()
{
	const int SPEED{ 200 };
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	const bool fire{ bool(pStates[SDL_SCANCODE_SPACE]) };

	if (fire && !m_InfPollen)
	{
		m_PollenMeter -= 0.1f;
	}
	if (fire)
	{
		if (PlebsInRange(m_RandomPlebsDest2))
		{
			m_Points += 100;
			m_RandomPlebsLoc2.x = float(rand() % 980 + 30);
			m_RandomPlebsLoc2.y = float(rand() % 600 + 30);
			if (m_PollenMeter <= 90.0f && m_PollenMeter > 0.0f) m_PollenMeter += 10.0f;
			else m_PollenMeter = 100.0f;
			m_SPEEEEEEED = 250;
			m_Counter = 0;
		}
	}
	if (fire)
	{
		if (PlebsInRange(m_RandomPlebsDest3))
		{
			m_Points += 100;
			m_RandomPlebsLoc3.x = float(rand() % 980 + 30);
			m_RandomPlebsLoc3.y = float(rand() % 600 + 30);
			if (m_PollenMeter <= 90.0f && m_PollenMeter > 0.0f) m_PollenMeter += 10.0f;
			else m_PollenMeter = 100.0f;
			m_SPEEEEEEED = 250;
			m_Counter = 0;
		}
	}
	if (fire)
	{
		if (PlebsInRange(m_RandomPlebsDest))
		{
			m_Points += 100;
			m_RandomPlebsLoc.x = float(rand() % 980 + 30);
			m_RandomPlebsLoc.y = float(rand() % 600 + 30);
			if (m_PollenMeter <= 90.0f && m_PollenMeter > 0.0f) m_PollenMeter += 10.0f;
			else m_PollenMeter = 100.0f;
			m_SPEEEEEEED = 250;
			m_Counter = 0;
		}
	}
	if (m_PollenMeter <= 0.0f) m_GameOverbool = true;
}

bool Game::PlebsInRange(Rectf PlebsDest)
{
	if (utils::IsPointInCircle(Point2f(PlebsDest.left, PlebsDest.bottom),
		Circlef(Point2f(m_DestRect.left + m_DestRect.width / 2, m_DestRect.bottom + m_DestRect.height / 2), 150.0f)))
		if (utils::IsPointInCircle(Point2f(PlebsDest.left + PlebsDest.width, PlebsDest.bottom),
			Circlef(Point2f(m_DestRect.left + m_DestRect.width / 2, m_DestRect.bottom + m_DestRect.height / 2), 150.0f)))
			if (utils::IsPointInCircle(Point2f(PlebsDest.left, PlebsDest.bottom + PlebsDest.height),
				Circlef(Point2f(m_DestRect.left + m_DestRect.width / 2, m_DestRect.bottom + m_DestRect.height / 2), 150.0f)))
				if (utils::IsPointInCircle(Point2f(PlebsDest.left + PlebsDest.width, PlebsDest.bottom + PlebsDest.height),
					Circlef(Point2f(m_DestRect.left + m_DestRect.width / 2, m_DestRect.bottom + m_DestRect.height / 2), 150.0f))) return true;
}

bool Game::PowerUpInRange(Point2f powerUp)
{
	if (utils::IsPointInRect(powerUp, m_DestRect))
	{
		m_NewPowerCtr = 0;
		return true;
	}
}
void Game::Draw( ) const
{
	if (m_GameStarted)
	{
		utils::SetColor(Color4f(1.0f, 1.0f, 1.0f, 1.0f));
		if (!m_GameOverbool)
		{
			ClearBackground();
			m_Background->Draw();
			m_EvilWizard->Draw(m_DestRect, m_SourceRect);

			m_PlebsAliveT->Draw(m_RandomPlebsDest, m_RandomPlebsSrc);
			m_PlebsAliveT->Draw(m_RandomPlebsDest2, m_RandomPlebsSrc);
			m_PlebsAliveT->Draw(m_RandomPlebsDest3, m_RandomPlebsSrc);


			utils::FillRect(Rectf(425.0f, 0.0f, 200.0f, 50.0f));
			m_Score->Draw(Rectf(550.0f, 0.0f, 50.0f, 50.0f));
			m_ScorePrint->Draw(Rectf(430.0f, 0.0f, 100.0f, 50.0f));

			const int SPEED{ 200 };
			const Uint8* pStates = SDL_GetKeyboardState(nullptr);

			const bool fire{ bool(pStates[SDL_SCANCODE_SPACE]) };

			if (fire)
			{

				for (int i{ 1 }; i <= 150; i++)
				{
					utils::SetColor(Color4f(1.0f, 1.0f, 1.0f, 1.0f / (i / 20.0f)));
					utils::DrawEllipse(Point2f(m_DestRect.left + m_DestRect.width / 2, m_DestRect.bottom + m_DestRect.height / 2), i, i, 1.0f);

				}
			}
			m_EvilWizard->Draw(m_DestRect, m_SourceRect);

			utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
			utils::FillRect(Rectf(20.0f, 650.0f, m_PollenMeter * 2, 20.0f));
			utils::SetColor(Color4f(1.0f, 1.0f, 1.0f, 1.0f));
			utils::DrawRect(Rectf(20.0f, 650.0f, 200.0f, 20.0f));
			m_PollenAmmo->Draw(Rectf(20.0f, 675.0f, m_PollenAmmo->GetWidth() / 3, m_PollenAmmo->GetHeight() / 3),
				Rectf(0.0f, 0.0f, m_PollenAmmo->GetWidth(), m_PollenAmmo->GetHeight()));

			for (int i{}; i <= 2; i++)
			{
				utils::SetColor(Color4f(0.5f, 0.5f, 0.0f, 1.0f));
				utils::FillRect(m_BulletsDown[i]);
			}

			for (int i{}; i <= 2; i++)
			{
				utils::SetColor(Color4f(0.5f, 0.5f, 0.0f, 1.0f));
				utils::FillRect(m_BulletsLeft[i]);
			}

			for (int i{}; i <= 2; i++)
			{
				utils::SetColor(Color4f(0.5f, 0.5f, 0.0f, 1.0f));
				utils::FillRect(m_BulletsRight[i]);
			}

			for (int i{}; i <= 2; i++)
			{
				utils::SetColor(Color4f(0.5f, 0.5f, 0.0f, 1.0f));
				utils::FillRect(m_BulletsUp[i]);
			}
			switch (m_CurrentPowerUp)
			{
			case powerUp::speed:
				utils::SetColor(Color4f(0.0f, 1.0f, 0.0f, 1.0f));
				utils::FillRect(Rectf(m_CurrentPowerUpLoc.x - 4, m_CurrentPowerUpLoc.y - 4, 8, 8));
				break;
			case powerUp::pollen:
				utils::SetColor(Color4f(1.0f, 0.0f, 0.0f, 1.0f));
				utils::FillRect(Rectf(m_CurrentPowerUpLoc.x - 4, m_CurrentPowerUpLoc.y - 4, 8, 8));
				break;
			case powerUp::points:
				utils::SetColor(Color4f(0.0f, 0.0f, 0.0f, 1.0f));
				utils::FillRect(Rectf(m_CurrentPowerUpLoc.x - 4, m_CurrentPowerUpLoc.y - 4, 8, 8));
				break;

			}
		}
		else
		{

			m_GameOver->Draw();
			m_Score->Draw(Rectf(575.0f, 50.0f, 360.0f, 125.0f));
		}
	}
	else
	{
		m_StartScreen->Draw();
	}
}

void Game::Move(float elapsedSec)
{
	const int SPEED{ m_SPEEEEEEED };
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	// read the key values

	const bool isLeft{ bool(pStates[SDL_SCANCODE_LEFT]) };
	const bool isRight{ bool(pStates[SDL_SCANCODE_RIGHT]) };
	const bool isUp{ bool(pStates[SDL_SCANCODE_UP]) };
	const bool isDown{ bool(pStates[SDL_SCANCODE_DOWN]) };

	// update position
	if (isLeft)        m_Loc.x -= SPEED * elapsedSec;
	if (isRight)    m_Loc.x += SPEED * elapsedSec;
	if (isUp)        m_Loc.y += SPEED * elapsedSec;
	if (isDown)        m_Loc.y -= SPEED * elapsedSec;
}

bool Game::HitByBullet(Rectf bullet)
{
	return utils::IsPointInRect(Point2f(bullet.left, bullet.bottom), m_DestRect);
}

void Game::UpdatePlebs()
{

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

