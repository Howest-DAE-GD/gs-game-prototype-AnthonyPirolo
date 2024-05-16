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
	bool PlebsInRange(Rectf plebsDest);
	float m_PollenMeter{ 100.0f };

private:

	Texture* m_Background{};
	Texture* m_EvilWizard{};
	Texture* m_PlebsAliveT{};
	Texture* m_PlebsDeadT{};
	Texture* m_PollenAmmo{};
	Texture* m_GameOver{};
	Texture* m_Score{};

	Point2f m_Loc{};

	Rectf m_SourceRect{};
	Rectf m_DestRect{};

	Point2f m_RandomPlebsLoc{};
	Rectf m_RandomPlebsDest;

	Rectf m_RandomPlebsSrc;

	Point2f m_RandomPlebsLoc2{};
	Rectf m_RandomPlebsDest2;

	Point2f m_RandomPlebsLoc3{};
	Rectf m_RandomPlebsDest3;

	bool m_Plebskilled{};
	bool m_GameOverbool{ false };


	int m_Points{ 0 };

	std::string m_ScoreString{ "Score:" };
	Texture* m_ScorePrint;
	std::string m_ScoreCounter{  };
	TTF_Font* Font;
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};