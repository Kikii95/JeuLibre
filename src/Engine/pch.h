#pragma once
#ifdef _DEBUG

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define LMB sf::Mouse::Button::Left
#define RMB sf::Mouse::Button::Right

#define KEY_ESCAPE sf::Keyboard::Key::Escape
#define KEY_ENTER  sf::Keyboard::Key::Enter
#define KEY_SPACE  sf::Keyboard::Key::Space

#define KEY_UP     sf::Keyboard::Key::Up
#define KEY_DOWN   sf::Keyboard::Key::Down
#define KEY_LEFT   sf::Keyboard::Key::Left
#define KEY_RIGHT  sf::Keyboard::Key::Right

#define KEY_A sf::Keyboard::Key::A
#define KEY_B sf::Keyboard::Key::B
#define KEY_C sf::Keyboard::Key::C
#define KEY_D sf::Keyboard::Key::D
#define KEY_E sf::Keyboard::Key::E
#define KEY_F sf::Keyboard::Key::F
#define KEY_G sf::Keyboard::Key::G
#define KEY_H sf::Keyboard::Key::H
#define KEY_I sf::Keyboard::Key::I
#define KEY_J sf::Keyboard::Key::J
#define KEY_K sf::Keyboard::Key::K
#define KEY_L sf::Keyboard::Key::L
#define KEY_M sf::Keyboard::Key::M
#define KEY_N sf::Keyboard::Key::N
#define KEY_O sf::Keyboard::Key::O
#define KEY_P sf::Keyboard::Key::P
#define KEY_Q sf::Keyboard::Key::Q
#define KEY_R sf::Keyboard::Key::R
#define KEY_S sf::Keyboard::Key::S
#define KEY_T sf::Keyboard::Key::T
#define KEY_U sf::Keyboard::Key::U
#define KEY_V sf::Keyboard::Key::V
#define KEY_W sf::Keyboard::Key::W
#define KEY_X sf::Keyboard::Key::X
#define KEY_Y sf::Keyboard::Key::Y
#define KEY_Z sf::Keyboard::Key::Z

#define KEY_1 sf::Keyboard::Key::Num1
#define KEY_2 sf::Keyboard::Key::Num2
#define KEY_3 sf::Keyboard::Key::Num3
#define KEY_4 sf::Keyboard::Key::Num4
#define KEY_5 sf::Keyboard::Key::Num5
#define KEY_6 sf::Keyboard::Key::Num6
#define KEY_7 sf::Keyboard::Key::Num7
#define KEY_8 sf::Keyboard::Key::Num8
#define KEY_9 sf::Keyboard::Key::Num9
#define KEY_0 sf::Keyboard::Key::Num0

#include <cmath>
#include <cstdlib>
#include <functional>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility> 
#include <vector>



#include "ActionDatabase.h"
#include "ActionDefinition.h"
#include "EffectDatabase.h"
#include "EffectDefinition.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "EntityManager.h"
#include "GameEngine.h"
#include "GameLogicManager.h"
#include "GameTimer.h"
#include "HexDirection.h"
#include "Input.h"
#include "ItemDatabase.h"
#include "ItemDefinition.h"
#include "ItemInstance.h"
#include "Logs.h"
#include "LootDatabase.h"
#include "Scene.h"
#include "SceneManager.h"
#include "StatsDatabase.h"
#include "StatsDefinition.h"
#include "SpawnerDatabase.h"
#include "SpawnerDefinition.h"
#include "ToolBox.h"
#include "ToolBoxVisual.h"
#include "ToolBoxAssets.h"
#include "TileDatabase.h"
#include "TileDefinition.h"
#include "TileMapLoader.h"

#include "ComponentRender.h"

#include "Component.h"
#include "ComponentAI.h"
#include "ComponentAudio.h"
#include "ComponentBuffDebuff.h"
#include "ComponentCamera.h"
#include "ComponentClickable.h"
#include "ComponentCollider.h"
#include "ComponentCombat.h"
#include "ComponentCrewMember.h"
#include "ComponentDecay.h"
#include "ComponentDialogue.h"
#include "ComponentDifficulty.h"
#include "ComponentEvent.h"
#include "ComponentEquipment.h"
#include "ComponentFaction.h"
#include "ComponentFogOfWar.h"
#include "ComponentFont.h"
#include "ComponentHealth.h"
#include "ComponentInput.h"
#include "ComponentItem.h"
#include "ComponentInventory.h"
#include "ComponentLoot.h"
#include "ComponentMerchant.h"
#include "ComponentMoney.h"
#include "ComponentNavire.h"
#include "ComponentPause.h"
#include "ComponentPhysics.h"
#include "ComponentProjectile.h"
#include "ComponentQuest.h"
#include "ComponentReputation.h"
#include "ComponentState.h"
#include "ComponentStats.h"
#include "ComponentTag.h"
#include "ComponentTransform.h"
#include "ComponentTurnOrder.h"
#include "ComponentWeapon.h"
#include "ComponentZoneSpawner.h"


#include "System.h"
#include "SystemInput.h"
#include "SystemAction.h"
#include "SystemAI.h"
#include "SystemBuffDebuff.h"
#include "SystemCamera.h"
#include "SystemClickable.h"
#include "SystemCollision.h"
#include "SystemCombat.h"
#include "SystemCrewManagement.h"
#include "SystemDialogue.h"
#include "SystemDifficulty.h"
#include "SystemEvent.h"
#include "SystemEquipment.h"
#include "SystemFaction.h"
#include "SystemFogOfWar.h"
#include "SystemHealth.h"
#include "SystemInventory.h"
#include "SystemItem.h"
#include "SystemLoot.h"
#include "SystemManager.h"
#include "SystemMerchant.h"
#include "SystemMoney.h"
#include "SystemNavire.h"
#include "SystemPause.h"
#include "SystemPhysics.h"
#include "SystemProjectile.h"
#include "SystemQuest.h"
#include "SystemRender.h"
#include "SystemReputation.h"
#include "SystemState.h"
#include "SystemStats.h"
#include "SystemSpawner.h"
#include "SystemTurnOrder.h"
#include "SystemText.h"
#include "SystemWarmup.h"



#include "json.hpp"

#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DEBUG_NEW
#endif
