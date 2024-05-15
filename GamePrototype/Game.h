#pragma once
#include "BaseGame.h"

class Texture;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

	void UpdatePlebs();

	void Move(float elapsedSec);
	void InfectPlebs();
	bool PlebsInRange();
	float m_PollenMeter{ 100.0f };

private:

	Texture* m_Background{};
	Texture* m_EvilWizard{};
	Texture* m_PlebsAliveT{};
	Texture* m_PlebsDeadT{};
	Texture* m_PollenAmmo{};

	Point2f m_Loc{};

	Rectf m_SourceRect{};
	Rectf m_DestRect{};

	bool m_PlebsAlive{ true };
	bool m_PlebsSpawnedIn{ false };

	Point2f m_RandomPlebsLoc{};
	Rectf m_RandomPlebsSrc;
	Rectf m_RandomPlebsDest;

	bool m_Plebskilled{};



	int m_Points{ 0 };
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};