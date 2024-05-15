#include "pch.h"
#include "Game.h"
#include "Texture.h"
#include "utils.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	m_Background = new Texture("Background.png");
	m_EvilWizard = new Texture("EvilWizard.png");
	m_PlebsAliveT = new Texture("Plebs_Alive.png");
	m_PlebsDeadT = new Texture("Plebs_Dead.png");
	m_PollenAmmo = new Texture("PollenCount.png");
	m_GameOver = new Texture("GameOver.png");
	m_Loc.x = window.width / 2.0f - m_EvilWizard->GetWidth() / 2.0f;
	m_Loc.y = window.height / 2.0f - m_EvilWizard->GetHeight() / 2.0f;
	m_SourceRect.left = 0.0f;
	m_SourceRect.bottom = 0.0f;
	m_SourceRect.width = m_EvilWizard->GetWidth();
	m_SourceRect.height = m_EvilWizard->GetHeight();
	m_DestRect.left = m_Loc.x;
	m_DestRect.bottom = m_Loc.y;
	m_DestRect.width = m_EvilWizard->GetWidth() / 3 * 2;
	m_DestRect.height = m_EvilWizard->GetHeight() / 3 * 2;
	m_RandomPlebsLoc.x = float(rand() / (720 / 9 * 8));
	m_RandomPlebsLoc.y = float(rand() / (1080 / 9 * 8));
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	Move(elapsedSec);
	m_DestRect.left = m_Loc.x;
	m_DestRect.bottom = m_Loc.y;


	m_RandomPlebsDest.width = m_PlebsAliveT->GetWidth();
	m_RandomPlebsDest.height = m_PlebsAliveT->GetHeight();

	m_RandomPlebsSrc.bottom = 0.0f;
	m_RandomPlebsSrc.left = 0.0f;
	m_RandomPlebsSrc.width = m_PlebsAliveT->GetWidth();
	m_RandomPlebsSrc.height = m_PlebsAliveT->GetHeight();

	if (m_RandomPlebsDest.left + m_RandomPlebsDest.width / 3.0f < m_DestRect.left && 
		m_DestRect.left < m_RandomPlebsDest.left + ( 2.0f * m_RandomPlebsDest.width / 3.0f))

		if (m_RandomPlebsDest.bottom + m_RandomPlebsDest.height / 3.0f < m_DestRect.bottom && 
			m_DestRect.bottom < m_RandomPlebsDest.bottom + (2.0f * m_RandomPlebsDest.height / 3.0f))
		{
			m_RandomPlebsLoc.x = float(rand() % 1000);
			m_RandomPlebsLoc.y = float(rand() % 500);
			m_Points += 100;
		}

	m_RandomPlebsDest.left = m_RandomPlebsLoc.x;
	m_RandomPlebsDest.bottom = m_RandomPlebsLoc.y;

	InfectPlebs();

	m_PollenMeter -= 0.05f;

}

void Game::InfectPlebs()
{
	const int SPEED{ 200 };
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	const bool fire{ bool(pStates[SDL_SCANCODE_SPACE]) };

	if (fire)
	{
		m_PollenMeter -= 0.1f;
		if (PlebsInRange())
		{
			m_Points += 100;
			m_RandomPlebsLoc.x = float(rand() % 1000);
			m_RandomPlebsLoc.y = float(rand() % 500);
			if (m_PollenMeter <= 90.0f && m_PollenMeter > 0.0f) m_PollenMeter += 10.0f;
			else m_PollenMeter = 100.0f;
		}
	}
	if (m_PollenMeter <= 0.0f) m_GameOverbool = true;
}

bool Game::PlebsInRange()
{
	if (utils::IsPointInCircle(Point2f(m_RandomPlebsDest.left, m_RandomPlebsDest.bottom),
		Circlef(Point2f(m_DestRect.left + m_DestRect.width / 2, m_DestRect.bottom + m_DestRect.height / 2), 150.0f)))
		if (utils::IsPointInCircle(Point2f(m_RandomPlebsDest.left + m_RandomPlebsDest.width, m_RandomPlebsDest.bottom),
			Circlef(Point2f(m_DestRect.left + m_DestRect.width / 2, m_DestRect.bottom + m_DestRect.height / 2), 150.0f)))
			if (utils::IsPointInCircle(Point2f(m_RandomPlebsDest.left, m_RandomPlebsDest.bottom + m_RandomPlebsDest.height),
				Circlef(Point2f(m_DestRect.left + m_DestRect.width / 2, m_DestRect.bottom + m_DestRect.height / 2), 150.0f)))
				if (utils::IsPointInCircle(Point2f(m_RandomPlebsDest.left + m_RandomPlebsDest.width, m_RandomPlebsDest.bottom + m_RandomPlebsDest.height),
					Circlef(Point2f(m_DestRect.left + m_DestRect.width / 2, m_DestRect.bottom + m_DestRect.height / 2), 150.0f))) return true;
}
void Game::Draw( ) const
{
	if (!m_GameOverbool)
	{
		ClearBackground();
		m_Background->Draw();
		m_EvilWizard->Draw(m_DestRect, m_SourceRect);

		m_PlebsAliveT->Draw(m_RandomPlebsDest, m_RandomPlebsSrc);

		
		utils::FillRect(Rectf(425.0f, 0.0f, 200.0f, 50.0f));

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
	}
	else m_GameOver->Draw(Rectf(0.0f, 0.0f, m_GameOver->GetWidth(), m_GameOver->GetHeight()), Rectf(0.0f, 0.0f, m_GameOver->GetWidth(), m_GameOver->GetHeight()));
}

void Game::Move(float elapsedSec)
{
	const int SPEED{ 200 };
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

