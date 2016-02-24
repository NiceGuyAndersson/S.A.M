#include "../../../Header Files/Screens/Menu/HighscoreMenu.h" 

HighScoreMenu::HighScoreMenu(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats, std::string scorepath) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_stats = stats;
	m_scorePath = scorepath;
	m_stats->LoadScore(scorepath);

	m_highscore = m_stats->GetHighScores();	//receives 10

	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");

}

void HighScoreMenu::Update(double time)
{
	//Don't do anything here
}

void HighScoreMenu::Render()
{	
	
	m_spriteBatch->Begin();
	for (int i = 0; i < 10; i++)
	{
		DirectX::XMVECTOR _nameOrigin = m_font->MeasureString(wstring(m_highscore[i].first.begin(), m_highscore[i].first.end()).c_str());
		_nameOrigin = DirectX::XMVectorSetIntY(_nameOrigin, 0);
		
		m_font->DrawString(
			m_spriteBatch.get(),
			wstring(m_highscore[i].first.begin(), m_highscore[i].first.end()).c_str(),
			SimpleMath::Vector2(m_screenWidth / 2, m_screenHeight / 4 + i * m_screenHeight / 20),
			Colors::Yellow,
			0.f,
			_nameOrigin,
			SimpleMath::Vector3(1.0-i*0.05)
			);
		m_font->DrawString(
			m_spriteBatch.get(),
			to_wstring(m_highscore[i].second).c_str(),
			SimpleMath::Vector2(m_screenWidth / 2, m_screenHeight / 4 + i * m_screenHeight / 20),
			Colors::Yellow,
			0.f,
			SimpleMath::Vector2(0.f),
			SimpleMath::Vector3(1.0-i*0.05)
			);
	}
	m_spriteBatch->End();
}
