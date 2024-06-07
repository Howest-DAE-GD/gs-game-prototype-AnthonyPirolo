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
	bool PowerUpInRange(Point2f powerUp);
	bool HitByBullet(Rectf bullet);
	void checkCollision(Rectf& DestRect);

	enum class powerUp
	{
		speed, pollen, points, none
	};

	powerUp m_CurrentPowerUp;
private:

	Texture* m_Background{};
	Texture* m_EvilWizard{};
	Texture* m_PlebsAliveT{};
	Texture* m_PlebsDeadT{};
	Texture* m_PollenAmmo{};
	Texture* m_GameOver{};
	Texture* m_Score{};
	Texture* m_StartScreen{};

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

	Point2f m_CurrentPowerUpLoc{};

	int m_Points{ 0 };

	std::string m_ScoreString{ "Score:" };
	Texture* m_ScorePrint;
	std::string m_ScoreCounter{  };
	TTF_Font* Font;

	int m_SPEEEEEEED{ 200 };
	float m_Counter{};
	bool m_DblSpeed{ false };
	bool m_InfPollen{ false };
	float m_DblSpdCntr{};
	float m_InfPllnCntr{};
	float m_NewPowerCtr{};
	bool m_PowerUpSpawned{false};

	float m_Shootcounter{};
	Rectf m_BulletsUp[3];
	Rectf m_BulletsDown[3];
	Rectf m_BulletsRight[3];
	Rectf m_BulletsLeft[3];

	bool m_Reset{ false };
	bool m_GameStarted{ false };
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};