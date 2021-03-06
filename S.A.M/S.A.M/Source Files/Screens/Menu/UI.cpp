#include "../../../Header Files/Screens/Menu/UI.h" 

UI::UI(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext, int ScreenHeight, int ScreenWidth, Input* input, Stats* stats) : Screen(Device, DeviceContext, ScreenHeight, ScreenWidth, input)
{
	m_font = make_unique<SpriteFont>(Device, L"Resources/moonhouse.spritefont");
	m_states = make_unique<CommonStates>(Device);
	m_stats = stats;
	m_input = input;

	CreateWICTextureFromFile(Device, L"Resources/Sprites/Bullet1.png", nullptr, m_bSprite1.ReleaseAndGetAddressOf());
	m_shotBinding[SHOT1].m_color = Colors::Crimson;
	m_shotBinding[SHOT1].m_origin = DirectX::SimpleMath::Vector2(97, 305);
	m_shotBinding[SHOT1].m_position = DirectX::SimpleMath::Vector2(20 * (float(m_screenWidth) / float(1058)), m_screenHeight - 150 * (float(m_screenWidth) / float(1440)));

	CreateWICTextureFromFile(Device, L"Resources/Sprites/Bullet2.png", nullptr, m_bSprite2.ReleaseAndGetAddressOf());
	m_shotBinding[SHOT2].m_color = Colors::Crimson;
	m_shotBinding[SHOT2].m_origin = DirectX::SimpleMath::Vector2(154, 147);
	m_shotBinding[SHOT2].m_position = DirectX::SimpleMath::Vector2(80 * (float(m_screenWidth) / float(1058)), m_screenHeight - 150 * (float(m_screenWidth) / float(1440)));

	CreateWICTextureFromFile(Device, L"Resources/Sprites/Bullet3.png", nullptr, m_bSprite3.ReleaseAndGetAddressOf());
	m_shotBinding[SHOT3].m_color = Colors::Crimson;
	m_shotBinding[SHOT3].m_origin = DirectX::SimpleMath::Vector2(283, 235);
	m_shotBinding[SHOT3].m_position = DirectX::SimpleMath::Vector2(150 * (float(m_screenWidth) / float(1058)), m_screenHeight - 150 * (float(m_screenWidth) / float(1440)));

	CreateWICTextureFromFile(Device, L"Resources/Sprites/Bullet4.png", nullptr, m_bSprite4.ReleaseAndGetAddressOf());
	m_shotBinding[SHOT4].m_color = Colors::Crimson;
	m_shotBinding[SHOT4].m_origin = DirectX::SimpleMath::Vector2(96, 254);
	m_shotBinding[SHOT4].m_position = DirectX::SimpleMath::Vector2(185 * (float(m_screenWidth) / float(1058)), m_screenHeight - 150 * (float(m_screenWidth) / float(1440)));


	HRESULT HR = CreateWICTextureFromFile(Device, L"Resources/Sprites/ComboMeter.png", nullptr, m_comboMeter.ReleaseAndGetAddressOf());
	m_spriteCombo.m_origin = DirectX::SimpleMath::Vector2(30, 160); //50 width and 300 height from png!
	m_spriteCombo.m_position = DirectX::SimpleMath::Vector2(m_screenWidth * 17 / 18, m_screenHeight / 2);

	HR = CreateWICTextureFromFile(Device, L"Resources/Sprites/ComboBar.png", nullptr, m_comboBar.ReleaseAndGetAddressOf());
	m_spriteBar.m_origin = DirectX::SimpleMath::Vector2(20,2.5f);// from png file! pixel size is double
	m_spriteBar.m_position = DirectX::SimpleMath::Vector2(m_screenWidth * 17 / 18, m_screenHeight / 2);

	
}

UI::~UI() 
{
	m_score.erase();
	m_livesLeft.erase();
	m_bSprite1.Reset();
	m_bSprite2.Reset();
	m_bSprite3.Reset();
}

void UI::Update(double time)
{
	BulletType _bullet = m_input->CheckBullet();

	m_shotBinding[SHOT1].m_color = Colors::White;
	m_shotBinding[SHOT2].m_color = Colors::White;
	m_shotBinding[SHOT3].m_color = Colors::White;
	m_shotBinding[SHOT4].m_color = Colors::White;

	switch (_bullet)
	{
	case INPUT_DEFAULT_BULLET:
		break;
	case INPUT_BULLET2:
		m_shotBinding[SHOT1].m_color = Colors::Green;
		break;
	case INPUT_BULLET3:
		m_shotBinding[SHOT2].m_color = Colors::Cyan;
		break;
	case INPUT_BULLET4:
		m_shotBinding[SHOT3].m_color = Colors::Blue;
		break;
	case INPUT_BULLET5:
		m_shotBinding[SHOT4].m_color = Colors::HotPink;
		break;
	default:
		break;
	}


	// top pos �r y = m_spriteCombo.m_position.y+135.f;
	//Sen �r det bara att f� den till att variera mellan dessa v�rden!
	// min Pos �r y = m_spriteCombo.m_position.y - 135.f;
	//Typ
	m_spriteBar.m_position.y = (m_screenHeight / 2) + cos(m_stats->GetPrecentage())*147.5f; 
	m_score = to_wstring(m_stats->GetScore());
	m_livesLeft = to_wstring(m_stats->GetLives());
	m_combo = to_wstring(m_stats->GetCombo());
}

void UI::Render(int offset)
{
	SimpleMath::Vector2 _scorePos, _livesPos, _comboPos, _offsetCountPos;
	_scorePos.x = m_screenWidth /2;
	_scorePos.y = 40.f * (float(m_screenHeight) / float(1440));
	_livesPos.x = 100 * (float(m_screenWidth) / float(1058));
	_livesPos.y = m_screenHeight - 40 * (float(m_screenHeight) / float(1440));
	_comboPos.x = m_screenWidth - 150 * (float(m_screenWidth) / float(1058)), _comboPos.y = m_screenHeight - 40 * (float(m_screenHeight) / float(1440));
	_offsetCountPos.x = m_screenWidth / 2, _offsetCountPos.y = m_screenHeight / 2;

	DirectX::SimpleMath::Vector3 _scale;
	_scale.x = float(m_screenWidth) / float(1058), _scale.y = (float(m_screenHeight) / float(1440)), _scale.z = (float(m_screenHeight) / float(1440));

	wstring _tempHighScore = L"Score: " + m_score;
	wstring _tempLives = L"Lives: " + m_livesLeft;
	wstring _tempCombo = L"Combo: " + m_combo;
	wstring _tempOffset;
	if ((offset - m_stats->GetBeat() + 1) > 10)
	{
		_tempOffset = L"Take a chill pill";
	}
	else if ((offset - m_stats->GetBeat() + 1) > 0)
	{
		_tempOffset = L"Beats until start: " + to_wstring(offset - m_stats->GetBeat());
	}
	else if ((offset - m_stats->GetBeat() + 1) > -4)
	{
		_tempOffset = L"Go Go Go";
	}
	m_spriteBatch->Begin(SpriteSortMode_Deferred,m_states->NonPremultiplied());
	if (offset - m_stats->GetBeat() >= -4)
	{
		m_font->DrawString(m_spriteBatch.get(), _tempOffset.c_str(), _offsetCountPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempOffset.c_str()) / 2.f, _scale);
	}
	m_beats = L"Beats: " +to_wstring(m_stats->GetBeat());

	m_font->DrawString(m_spriteBatch.get(), _tempHighScore.c_str(),_scorePos, Colors::Crimson, 0.f, m_font->MeasureString(_tempHighScore.c_str()) / 2.f, _scale);
	m_font->DrawString(m_spriteBatch.get(), _tempLives.c_str(), _livesPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempLives.c_str()) / 2.f, _scale);
	m_font->DrawString(m_spriteBatch.get(), _tempCombo.c_str(), _comboPos, Colors::Crimson, 0.f, m_font->MeasureString(_tempCombo.c_str()) / 2.f, _scale);

	//Used for counting beats when adding new song
	//m_font->DrawString(m_spriteBatch.get(), m_beats.c_str(), SimpleMath::Vector2(m_screenWidth/2, m_screenHeight / 2), Colors::Aquamarine, 0.f, m_font->MeasureString(m_beats.c_str()) / 2.f, _scale);
	m_spriteBatch->Draw(m_bSprite1.Get(), m_shotBinding[SHOT1].m_position, nullptr, m_shotBinding[SHOT1].m_color, 0.f, m_shotBinding[SHOT1].m_origin, 0.1f * (float(m_screenHeight) / float(980)));
	m_spriteBatch->Draw(m_bSprite2.Get(), m_shotBinding[SHOT2].m_position, nullptr, m_shotBinding[SHOT2].m_color, 0.f, m_shotBinding[SHOT2].m_origin, 0.2f * (float(m_screenHeight) / float(980)));
	m_spriteBatch->Draw(m_bSprite3.Get(), m_shotBinding[SHOT3].m_position, nullptr, m_shotBinding[SHOT3].m_color, 0.f, m_shotBinding[SHOT3].m_origin, 0.05f * (float(m_screenHeight) / float(980)));
	m_spriteBatch->Draw(m_bSprite4.Get(), m_shotBinding[SHOT4].m_position, nullptr, m_shotBinding[SHOT4].m_color, 0.f, m_shotBinding[SHOT4].m_origin, 0.1f * (float(m_screenHeight) / float(980)));
	m_spriteBatch->Draw(m_comboMeter.Get(), m_spriteCombo.m_position, nullptr, Colors::White, 0.0f, m_spriteCombo.m_origin);
	m_spriteBatch->Draw(m_comboBar.Get(), m_spriteBar.m_position, nullptr, Colors::White, 0.0f, m_spriteBar.m_origin);
	m_spriteBatch->End();
	


}

