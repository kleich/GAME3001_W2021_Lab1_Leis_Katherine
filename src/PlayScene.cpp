#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Create target (blue circle)
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pTarget);

	// Create spaceship
	m_pSpaceShip = new SpaceShip();
	m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, 100.0f);
	m_pSpaceShip->setEnabled(false); // Stops the ship from updating & drawing
	m_pSpaceShip->setDestination(m_pTarget->getTransform()->position); //
	addChild(m_pSpaceShip);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	// Enables the ship
	if(ImGui::Button("Start"))
	{
		m_pSpaceShip->setEnabled(true);
		m_pSpaceShip->setRotation(-(m_pSpaceShip->getTransform()->position.x), -(m_pTarget->getTransform()->position.x), m_pSpaceShip->getTransform()->position.y, m_pTarget->getTransform()->position.y);
	}

	ImGui::SameLine(); // Puts the buttons on the same line
	
	// Resets spaceship location & disables it 
	if(ImGui::Button("Reset Ship"))
	{
		m_pSpaceShip->getTransform()->position = glm::vec2(100.0f, 100.0f);
		m_pSpaceShip->setEnabled(false);
	}
	
	ImGui::SameLine(); // Puts the buttons on the same line

	// Moves the target & has the ship re-target
	if(ImGui::Button("Move Target"))
	{
		m_pTarget->getTransform()->position = glm::vec2(rand() % 800, rand() % 600);
		m_pSpaceShip->setRotation(-(m_pSpaceShip->getTransform()->position.x), -(m_pTarget->getTransform()->position.x), m_pSpaceShip->getTransform()->position.y, m_pTarget->getTransform()->position.y);
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
	}
	
	ImGui::SameLine(); // Puts the buttons on the same line

	// Rotate the ship based on slider value
	//static float angleInRadians = 0.0f; // static float angleInRadians = m_pSpaceShip->getRotation();
	//if(ImGui::SliderAngle("Orientation Angle", &angleInRadians))
	//{
	//	m_pSpaceShip->setRotation(angleInRadians * Util::Rad2Deg);
	//}

	ImGui::Separator();

	// Speed of the ship
	static float shipSpeed = 10.0f;
	if(ImGui::SliderFloat("Ship Speed", &shipSpeed, 0.0f, 100.0f))
	{
		m_pSpaceShip->setMaxSpeed(shipSpeed);
	}
		
	ImGui::Separator();

	// Move the target based on slider value
	static float targetPosition[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y };
	if(ImGui::SliderFloat2("Target Slider", targetPosition, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(targetPosition[0], targetPosition[1]);
		m_pSpaceShip->setDestination(m_pTarget->getTransform()->position);
		m_pSpaceShip->setRotation(-(m_pSpaceShip->getTransform()->position.x), -(m_pTarget->getTransform()->position.x), m_pSpaceShip->getTransform()->position.y, m_pTarget->getTransform()->position.y);
	}


	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
