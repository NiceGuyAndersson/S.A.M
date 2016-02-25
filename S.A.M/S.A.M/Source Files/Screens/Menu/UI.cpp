#include "../../../Header Files/Screens/Menu/UI.h" 

UI::UI(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");
	m_stats = stats;
}

UI::~UI() 
{
	m_score.erase();
	m_livesLeft.erase();
}

void UI::Update(double time)
{

	m_score = to_wstring(m_stats->GetScore());
	m_livesLeft = to_wstring(m_stats->GetLives());
	m_combo = to_wstring(m_stats->GetCombo());
}

void UI::Render(int offset)
{
	SimpleMath::Vector2 _scorePos, _livesPos, _comboPos, _offsetCountPos;
	_scorePos.x = m_screenWidth /2;
	_scorePos.y = 40;
	_livesPos.x = 100;
	_livesPos.y = m_screenHeight - 40;
	_comboPos.x = m_screenWidth - 150, _comboPos.y = m_screenHeight - 40;
	_offsetCountPos.x = m_screenWidth / 2, _offsetCountPos.y = m_screenHeight / 2;

	wstring _tempHighScore = L"High Score: " + m_score;
	wstring _tempLives = L"Lives: " + m_livesLeft;
	wstring _tempCombo = L"Combo: " + m_combo;
	wstring _tempOffset;
	if (offset > 0)
	{
		_tempOffset = L"Beats until start: " + to_wstring(offset);
	}
	else if (offset > 3)
	{
		_tempOffset = L"Go Go Go";
	}
	m_spriteBatch->Begin();
	if (offset >= -3)
	{
		m_font->DrawString(m_spriteBatch.get(), _tempOffset.c_str(), _offsetCountPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempOffset.c_str()) / 2.f);
	}
	m_font->DrawString(m_spriteBatch.get(), _tempHighScore.c_str(),_scorePos, Colors::Crimson, 0.f, m_font->MeasureString(_tempHighScore.c_str()) / 2.f);
	m_font->DrawString(m_spriteBatch.get(), _tempLives.c_str(), _livesPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempLives.c_str()) / 2.f);
	m_font->DrawString(m_spriteBatch.get(), _tempCombo.c_str(), _comboPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempCombo.c_str()) / 2.f);
	m_spriteBatch->End();

}

