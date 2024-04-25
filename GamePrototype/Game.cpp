#include "pch.h"
#include "Game.h"
#include "Texture.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	m_Background = new Texture("Background.png");
	m_EvilWizard = new Texture("EvilWizard.png");
	m_PlebsAliveT = new Texture("Plebs_Alive.png");
	m_PlebsDeadT = new Texture("Plebs_Dead.png");
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
			m_RandomPlebsLoc.x = float(rand() % 500);
			m_RandomPlebsLoc.y = float(rand() % 980);
			m_Points += 100;
		}

	m_RandomPlebsDest.left = m_RandomPlebsLoc.x;
	m_RandomPlebsDest.bottom = m_RandomPlebsLoc.y;

}

void Game::Draw( ) const
{
	ClearBackground( );
	m_Background->Draw();
	m_EvilWizard->Draw(m_DestRect, m_SourceRect);

	m_PlebsAliveT->Draw(m_RandomPlebsDest, m_RandomPlebsSrc);

}

void Game::UpdatePlebs()
{

}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
	{
		m_Loc.x -= 10;
	}
	break;
	case SDLK_RIGHT:
	{
		m_Loc.x += 10;
	}
	break;
	case SDLK_UP:
	{
		m_Loc.y += 10;
	}
	break;
	case SDLK_DOWN:
	{
		m_Loc.y -= 10;
	}
	break;
	}
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

