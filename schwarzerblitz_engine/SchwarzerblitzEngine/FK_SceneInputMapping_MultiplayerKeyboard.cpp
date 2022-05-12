/*
	*** Schwarzerblitz 3D Fighting Game Engine  ***

	=================== Source Code ===================
	Copyright (C) 2016-2022 Andrea Demetrio

	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation and/or
	   other materials provided with the distribution.
	3. Neither the name of the copyright holder nor the names of its contributors may be
	   used to endorse or promote products derived from  this software without specific
	   prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
	OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
	AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
	CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
	IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
	THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


	=============== Additional Components ==============
	Please refer to the license/irrlicht/ and license/SFML/ folder for the license
	indications concerning those components. The irrlicht-schwarzerlicht engine and
	the SFML code and binaries are subject to their own licenses, see the relevant
	folders for more information.

	=============== Assets and resources ================
	Unless specificed otherwise in the Credits file, the assets and resources
	bundled with this engine are to be considered "all rights reserved" and
	cannot be redistributed without the owner's consent. This includes but it is
	not limited to the characters concepts / designs, the 3D models, the music,
	the sound effects, 2D and 3D illustrations, stages, icons, menu art.

	Tutorial Man, Evil Tutor, and Random:
	Copyright (C) 2016-2022 Andrea Demetrio - all rights reserved
*/

#include"FK_SceneInputMapping_MultiplayerKeyboard.h"
#include"ExternalAddons.h"
#include<Windows.h>
#include<iostream>

namespace fk_engine{
	FK_SceneInputMapping_MultiplayerKeyboard::FK_SceneInputMapping_MultiplayerKeyboard() : FK_SceneInputMapping(){

	};
	FK_SceneInputMapping_MultiplayerKeyboard::FK_SceneInputMapping_MultiplayerKeyboard(IrrlichtDevice *newDevice, core::array<SJoystickInfo> joypadInfo,
		FK_Options *newOptions) : FK_SceneInputMapping_MultiplayerKeyboard(){
		setup(newDevice, joypadInfo, newOptions);
	};
	void FK_SceneInputMapping_MultiplayerKeyboard::setup(IrrlichtDevice *newDevice, core::array<SJoystickInfo> joypadInfo,
		FK_Options* newOptions){
		FK_SceneInputMapping::setup(newDevice, joypadInfo, newOptions);
		modifiedInputMap = {
			std::map<FK_Input_Buttons, u32>(inputMapper->getKeyboardMap(1)),
			std::map<FK_Input_Buttons, u32>(inputMapper->getKeyboardMap(2)),
		};
	};

	void FK_SceneInputMapping_MultiplayerKeyboard::saveSettings(){
		inputMapper->setKeyboardInputMap(1, modifiedInputMap[0]);
		inputMapper->setKeyboardInputMap(2, modifiedInputMap[1]);
		// save correct joypad settings, if needed
		if (!joystickInfo.empty()) {
			std::map<FK_Input_Buttons, u32> joypad1Map = std::map<FK_Input_Buttons, u32>(inputMapper->getJoypadMap(1));
			// translate modified input maps
			u32 buttonMask = (u32)(FK_Input_Buttons::Any_NonDirectionButton | FK_Input_Buttons::Any_MenuButton | FK_Input_Buttons::Any_SystemButton);
			std::string joypadName = std::string(joystickInfo[0].Name.c_str());
			for (auto iter = joypad1Map.begin(); iter != joypad1Map.end(); ++iter) {
				if ((iter->first & buttonMask) != 0) {
					joypad1Map[iter->first] = inputMapper->getTranslatedButtonFromJoypadMap(
						joypadName, (FK_JoypadInputNative)iter->second);
				}
			}
			inputMapper->setJoypadInputMap(1, joypad1Map);
			if (joystickInfo.size() > 1) {
				joypadName = std::string(joystickInfo[1].Name.c_str());
				joypad1Map = std::map<FK_Input_Buttons, u32>(inputMapper->getJoypadMap(2));
				for (auto iter = joypad1Map.begin(); iter != joypad1Map.end(); ++iter) {
					if ((iter->first & buttonMask) != 0) {
						joypad1Map[iter->first] = inputMapper->getTranslatedButtonFromJoypadMap(
							joypadName, (FK_JoypadInputNative)iter->second);
					}
				}
			}
			inputMapper->setJoypadInputMap(2, joypad1Map);
		}
		inputMapper->saveMapToFile(configurationFilesPath + fk_constants::FK_InputMapFileName);
	};

	void FK_SceneInputMapping_MultiplayerKeyboard::initialize(){
		FK_SceneInputMapping::initialize();
		playerIndex = 0;
	}

	// draw item
	void FK_SceneInputMapping_MultiplayerKeyboard::drawItem(u32 itemIndex){

		// draw KEY DESCRIPTION
		std::string unassignedKeyString = "N/A";
		std::string keyIdentifier = menuOptionsStrings[itemIndex];
		std::string assignedKey1;
		std::string assignedKey2;
		s32 fixedOffsetY = 64;
		s32 baseOffsetY = fixedOffsetY;
		s32 fixedSpacingY = 18;
		u32 tempIndex = itemIndex;

		// add offset
		if (menuIndex > 5){
			fixedOffsetY -= (fixedSpacingY * (menuIndex - 5));
			s32 thresholdValue = (menuOptionsStrings.size()) * fixedSpacingY + baseOffsetY + 40;
			thresholdValue = screenSize.Height / scale_factorY - thresholdValue;
			if (fixedOffsetY < thresholdValue){
				fixedOffsetY = thresholdValue;
			}
		}

		if (itemIndex >= directionButtons.size() + menuButtons.size()){
			tempIndex -= directionButtons.size() + menuButtons.size();
			if (modifiedInputMap[0][gameButtons[tempIndex]] != KEY_KEY_CODES_COUNT){
				assignedKey1 = acceptedKeys[(EKEY_CODE)modifiedInputMap[0][gameButtons[tempIndex]]];
			}
			else{
				assignedKey1 = unassignedKeyString;
			}
			if (modifiedInputMap[1][gameButtons[tempIndex]] != KEY_KEY_CODES_COUNT){
				assignedKey2 = acceptedKeys[(EKEY_CODE)modifiedInputMap[1][gameButtons[tempIndex]]];
			}
			else{
				assignedKey2 = unassignedKeyString;
			}
			fixedOffsetY += 40;
		}
		else if (itemIndex >= directionButtons.size()){
			tempIndex -= directionButtons.size();
			if (modifiedInputMap[0][menuButtons[tempIndex]] != KEY_KEY_CODES_COUNT){
				assignedKey1 = acceptedKeys[(EKEY_CODE)modifiedInputMap[0][menuButtons[tempIndex]]];
			}
			else{
				assignedKey1 = unassignedKeyString;
			}
			if (modifiedInputMap[1][menuButtons[tempIndex]] != KEY_KEY_CODES_COUNT){
				assignedKey2 = acceptedKeys[(EKEY_CODE)modifiedInputMap[1][menuButtons[tempIndex]]];
			}
			else{
				assignedKey2 = unassignedKeyString;
			}
			fixedOffsetY += 20;
		}
		else{
			if (modifiedInputMap[0][directionButtons[tempIndex]] != 0){
				assignedKey1 = acceptedKeys[(EKEY_CODE)modifiedInputMap[0][directionButtons[tempIndex]]];
			}
			else{
				assignedKey1 = unassignedKeyString;
			}
			if (modifiedInputMap[1][directionButtons[tempIndex]] != 0){
				assignedKey2 = acceptedKeys[(EKEY_CODE)modifiedInputMap[1][directionButtons[tempIndex]]];
			}
			else{
				assignedKey2 = unassignedKeyString;
			}
		}

		// don't draw if outside of screen
		s32 tempY = fixedOffsetY + itemIndex * fixedSpacingY;
		if (tempY < baseOffsetY){
			return;
		}
		if (tempY > screenSize.Height / scale_factorY - (baseOffsetY + fixedSpacingY)){
			return;
		}

		s32 fixedOffsetX = 32;
		s32 selectedItemAdditionalOffsetX = 15;

		irr::video::SColor itemColor = irr::video::SColor(255, 255, 255, 255);
		std::wstring itemString(keyIdentifier.begin(), keyIdentifier.end());
		s32 sentenceWidth = submenufont->getDimension(itemString.c_str()).Width;
		s32 sentenceHeight = submenufont->getDimension(itemString.c_str()).Height;
		s32 sentenceX = fixedOffsetX;
		if (itemIndex == menuIndex){
			sentenceX += selectedItemAdditionalOffsetX;
			itemColor = irr::video::SColor(255, 200, 200, 20);
		}
		s32 sentenceY = fixedOffsetY + itemIndex * fixedSpacingY; // distance from the top of the screen
		core::rect<s32> destinationRect = core::rect<s32>(sentenceX * scale_factorX,
			sentenceY * scale_factorY,
			sentenceX * scale_factorX + sentenceWidth,
			sentenceHeight + sentenceY * scale_factorY);
		fk_addons::drawBorderedText(submenufont, itemString, destinationRect,
			itemColor, irr::video::SColor(128, 0, 0, 0));

		// draw KEY (Player 1)

		s32 selectedItemXL = 0;
		s32 selectedItemXR = 0;
		s32 selectedItemY = 0;
		s32 selectedItemDimension = 0;
		fixedOffsetX = 192;
		/* get width and height of the string*/
		itemColor = irr::video::SColor(255, 20, 225, 120);
		itemString = std::wstring(assignedKey1.begin(), assignedKey1.end());
		sentenceWidth = submenufont->getDimension(itemString.c_str()).Width;
		sentenceHeight = submenufont->getDimension(itemString.c_str()).Height;
		sentenceX = fixedOffsetX; // distance from screen center
		sentenceY = fixedOffsetY + itemIndex * fixedSpacingY; // distance from the top of the screen
		if (itemIndex == menuIndex && playerIndex == 0){
			//sentenceX += selectedItemAdditionalOffsetX;
			itemColor = getSelectedKeyColor();
			selectedItemXL = screenSize.Width - (sentenceX * scale_factorX + sentenceWidth);
			selectedItemXR = screenSize.Width - sentenceX * scale_factorX;
			selectedItemY = (sentenceY + 5) * scale_factorY;
			selectedItemDimension = sentenceHeight * 3 / 4;
		}
		destinationRect = core::rect<s32>(
			screenSize.Width - (sentenceX * scale_factorX + sentenceWidth),
			sentenceY * scale_factorY,
			screenSize.Width - sentenceX * scale_factorX,
			sentenceHeight + sentenceY * scale_factorY);
		fk_addons::drawBorderedText(submenufont, itemString, destinationRect,
			itemColor, irr::video::SColor(128, 0, 0, 0));

		//draw KEY(Player2)

		fixedOffsetX = 32;
		/* get width and height of the string*/
		itemColor = irr::video::SColor(255, 20, 225, 120);
		itemString = std::wstring(assignedKey2.begin(), assignedKey2.end());
		sentenceWidth = submenufont->getDimension(itemString.c_str()).Width;
		sentenceHeight = submenufont->getDimension(itemString.c_str()).Height;
		sentenceX = fixedOffsetX; // distance from screen center
		sentenceY = fixedOffsetY + itemIndex * fixedSpacingY; // distance from the top of the screen
		if (itemIndex == menuIndex && playerIndex == 1){
			//sentenceX += selectedItemAdditionalOffsetX;
			itemColor = getSelectedKeyColor();
			selectedItemXL = screenSize.Width - (sentenceX * scale_factorX + sentenceWidth);
			selectedItemXR = screenSize.Width - sentenceX * scale_factorX;
			selectedItemY = (sentenceY + 5) * scale_factorY;
			selectedItemDimension = sentenceHeight * 3 / 4;
		}
		destinationRect = core::rect<s32>(
			screenSize.Width - (sentenceX * scale_factorX + sentenceWidth),
			sentenceY * scale_factorY,
			screenSize.Width - sentenceX * scale_factorX,
			sentenceHeight + sentenceY * scale_factorY);
		fk_addons::drawBorderedText(submenufont, itemString, destinationRect,
			itemColor, irr::video::SColor(128, 0, 0, 0));
	}

	void FK_SceneInputMapping_MultiplayerKeyboard::drawTitle(){
		s32 x = screenSize.Width / 2;
		s32 y = screenSize.Height / 20;
		std::wstring itemString = L"Keyboard Settings (multiplayer)";
		s32 sentenceWidth = font->getDimension(itemString.c_str()).Width;
		s32 sentenceHeight = font->getDimension(itemString.c_str()).Height;
		x -= sentenceWidth / 2;
		y -= sentenceHeight / 2;
		core::rect<s32> destinationRect = core::rect<s32>(x,
			y,
			x + sentenceWidth,
			y + scale_factorY);
		fk_addons::drawBorderedText(font, itemString, destinationRect,
			irr::video::SColor(255, 255, 255, 255), irr::video::SColor(128, 0, 0, 0));
	}

	// draw tags
	void FK_SceneInputMapping_MultiplayerKeyboard::drawPlayerTags(){
		// draw tag (Player1)
		f32 phase = (f32)(now % 500) / 500 * 2.0f * 3.1415926f;
		/* get width and height of the string*/
		video::SColor itemColor(255, 200, 200, 200);
		if (playerIndex == 0) {
			u32 blinkAddon = std::round(60 * std::cos(phase));
			itemColor = irr::video::SColor(255, 220, 160 + blinkAddon, 60 + blinkAddon);
		}
		std::wstring itemString = L"Player 1";
		u32 sentenceWidth = submenufont->getDimension(itemString.c_str()).Width;
		u32 sentenceHeight = submenufont->getDimension(itemString.c_str()).Height;
		s32 sentenceX = 192; // distance from screen center
		s32 sentenceY = 36;
		core::rect<s32> destinationRect(
			screenSize.Width - (sentenceX * scale_factorX + sentenceWidth),
			sentenceY * scale_factorY,
			screenSize.Width - sentenceX * scale_factorX,
			sentenceHeight + sentenceY * scale_factorY);
		fk_addons::drawBorderedText(submenufont, itemString, destinationRect,
			itemColor, irr::video::SColor(128, 0, 0, 0));

		//draw tag (Player2)

		/* get width and height of the string*/
		itemString = L"Player 2";
		itemColor = irr::video::SColor(255, 200, 200, 200);
		if (playerIndex == 1) {
			u32 blinkAddon = std::round(60 * std::cos(phase));
			itemColor = irr::video::SColor(255, 220, 160 + blinkAddon, 60 + blinkAddon);
		}
		sentenceWidth = submenufont->getDimension(itemString.c_str()).Width;
		sentenceHeight = submenufont->getDimension(itemString.c_str()).Height;
		sentenceX = 32; // distance from screen center
		destinationRect = core::rect<s32>(
			screenSize.Width - (sentenceX * scale_factorX + sentenceWidth),
			sentenceY * scale_factorY,
			screenSize.Width - sentenceX * scale_factorX,
			sentenceHeight + sentenceY * scale_factorY);
		fk_addons::drawBorderedText(submenufont, itemString, destinationRect,
			itemColor, irr::video::SColor(128, 0, 0, 0));
	}

	// draw all
	void FK_SceneInputMapping_MultiplayerKeyboard::drawAll(bool showBackground){
		if (showBackground) {
			drawBackground();
		}
		drawItems();
		drawCaptions();
		drawArrows();
		drawPlayerTags();
		drawTitle();
	}

	// toggle player
	void FK_SceneInputMapping_MultiplayerKeyboard::togglePlayer(){
		soundManager->playSound("cursor", 100.0 * gameOptions->getSFXVolume());
		playerIndex = !playerIndex;
	}

	void FK_SceneInputMapping_MultiplayerKeyboard::swapSameInputButtons(FK_Input_Buttons lastModifiedButton, u32 oldKeyCode){
		u32 inputKey = modifiedInputMap[playerIndex][lastModifiedButton];
		std::cout << acceptedKeys[(EKEY_CODE)oldKeyCode] << " " << lastModifiedButton << std::endl;
		if (isDirection(lastModifiedButton)){
			for each (auto key in modifiedInputMap[playerIndex]){
				if (key.second == inputKey && key.first != lastModifiedButton){
					modifiedInputMap[playerIndex][key.first] = oldKeyCode;
				}
			}
			for each (auto key in modifiedInputMap[!playerIndex]){
				if (key.second == inputKey){
					modifiedInputMap[!playerIndex][key.first] = oldKeyCode;
				}
			}
		}
		else if (isMenuButton(lastModifiedButton)){
			for each (auto key in menuButtons){
				if (modifiedInputMap[playerIndex][key] == inputKey  && key != lastModifiedButton){
					modifiedInputMap[playerIndex][key] = oldKeyCode;
					return;
				}
			}
			for each (auto key in directionButtons){
				if (modifiedInputMap[playerIndex][key] == inputKey && key != lastModifiedButton){
					modifiedInputMap[playerIndex][key] = oldKeyCode;
					return;
				}
			}

			for each (auto key in menuButtons){
				if (modifiedInputMap[!playerIndex][key] == inputKey){
					modifiedInputMap[!playerIndex][key] = oldKeyCode;
					togglePlayer();
					return;
				}
			}
			for each (auto key in directionButtons){
				if (modifiedInputMap[!playerIndex][key] == inputKey){
					modifiedInputMap[!playerIndex][key] = oldKeyCode;
					togglePlayer();
					return;
				}
			}
		}
		else if (isGameButton(lastModifiedButton)){
			for each (auto key in gameButtons){
				if (modifiedInputMap[playerIndex][key] == inputKey && key != lastModifiedButton){
					modifiedInputMap[playerIndex][key] = oldKeyCode;
					return;
				}
			}
			for each (auto key in directionButtons){
				if (modifiedInputMap[playerIndex][key] == inputKey && key != lastModifiedButton){
					modifiedInputMap[playerIndex][key] = oldKeyCode;
					return;
				}
			}
			for each (auto key in gameButtons){
				if (modifiedInputMap[!playerIndex][key] == inputKey){
					modifiedInputMap[!playerIndex][key] = oldKeyCode;
					return;
				}
			}
			for each (auto key in directionButtons){
				if (modifiedInputMap[!playerIndex][key] == inputKey){
					modifiedInputMap[!playerIndex][key] = oldKeyCode;
					return;
				}
			}
		}
	}

	// assign new input
	void FK_SceneInputMapping_MultiplayerKeyboard::assignNewInput(FK_Input_Buttons buttonToReplace, u32 newKeyCode){
		if (modifiedInputMap[playerIndex][buttonToReplace] != newKeyCode){
			u32 oldKeyCode = modifiedInputMap[playerIndex][buttonToReplace];
			modifiedInputMap[playerIndex][buttonToReplace] = newKeyCode;
			swapSameInputButtons(buttonToReplace, oldKeyCode);
		}
		else if (isOptionalButton(buttonToReplace)){
			modifiedInputMap[playerIndex][buttonToReplace] = KEY_KEY_CODES_COUNT;
		}
	}

	// update input
	void FK_SceneInputMapping_MultiplayerKeyboard::updateInput(){
		u32 lastInputTimePlayer1 = lastInputTime;
		u32 lastInputTimePlayer2 = lastInputTime;
		u32 inputThreshold = 200;
		// check input for player 1
		if (now - lastInputTimePlayer1 > inputThreshold){
			if (joystickInfo.size() > 0){
				player1input->update(now, inputReceiver->JoypadStatus(0),false);
			}
			else{
				player1input->update(now, inputReceiver->KeyboardStatus(),false);
			}
			u32 directionPlayer1 = player1input->getLastDirection();
			u32 lastButtonPlayer1 = player1input->getPressedButtons() & FK_Input_Buttons::Any_MenuButton;
			if (lastButtonPlayer1 == FK_Input_Buttons::Confirmation_Button){
				saveAndExit();
				lastInputTime = now;
				return;
			}
			if (lastButtonPlayer1 == FK_Input_Buttons::Cancel_Button){
				std::vector < std::map<FK_Input_Buttons, u32>> originalInputMap = {
					std::map<FK_Input_Buttons, u32>(inputMapper->getKeyboardMap(1)),
					std::map<FK_Input_Buttons, u32>(inputMapper->getKeyboardMap(2)),
				};
				bool needsSaving = false;
				for (auto key : originalInputMap[0]) {
					if (originalInputMap[0][key.first] !=
						modifiedInputMap[0][key.first]) {
						needsSaving = true;
						break;
					}
				}
				for (auto key : originalInputMap[1]) {
					if (originalInputMap[1][key.first] !=
						modifiedInputMap[1][key.first]) {
						needsSaving = true;
						break;
					}
				}
				if (needsSaving) {
					activateExitMenu();
				}
				else {
					exitScene(true);
				}
				return;
			}
			else{
				if (directionPlayer1 == FK_Input_Buttons::Down_Direction){
					increaseMenuIndex();
					lastInputTime = now;
				}
				else if (directionPlayer1 == FK_Input_Buttons::Up_Direction){
					decreaseMenuIndex();
					lastInputTime = now;
				}
				else if (directionPlayer1 == FK_Input_Buttons::Left_Direction ||
					directionPlayer1 == FK_Input_Buttons::Right_Direction){
					togglePlayer();
					lastInputTime = now;
				}
				else if(lastButtonPlayer1 == FK_Input_Buttons::ScrollLeft_Button ||
					lastButtonPlayer1 == FK_Input_Buttons::ScrollRight_Button){
					togglePlayer();
					inputReceiver->reset();
					lastInputTime = now;
				}
				else{
					if (lastButtonPlayer1 == FK_Input_Buttons::Selection_Button){
						selectItem();
						lastInputTime = now;
						Sleep(200);
						return;
					}
				}
			}
		}
		// check input for player 2
		if (now - lastInputTimePlayer2 > inputThreshold){
			if (joystickInfo.size() > 1){
				player2input->update(now, inputReceiver->JoypadStatus(1),false);
			}
			else{
				player2input->update(now, inputReceiver->KeyboardStatus(),false);
			}
			u32 directionPlayer2 = player2input->getLastDirection();
			u32 lastButtonPlayer2 = player2input->getPressedButtons() & FK_Input_Buttons::Any_MenuButton;
			if (lastButtonPlayer2 == FK_Input_Buttons::Confirmation_Button){
				saveAndExit();
				lastInputTime = now;
				return;
			}
			if (lastButtonPlayer2 == FK_Input_Buttons::Cancel_Button){
				lastInputTime = now;
				std::vector < std::map<FK_Input_Buttons, u32>> originalInputMap = {
					std::map<FK_Input_Buttons, u32>(inputMapper->getKeyboardMap(1)),
					std::map<FK_Input_Buttons, u32>(inputMapper->getKeyboardMap(2)),
				};
				bool needsSaving = false;
				for (auto key : originalInputMap[0]) {
					if (originalInputMap[0][key.first] !=
						modifiedInputMap[0][key.first]) {
						needsSaving = true;
						break;
					}
				}
				for (auto key : originalInputMap[1]) {
					if (originalInputMap[1][key.first] !=
						modifiedInputMap[1][key.first]) {
						needsSaving = true;
						break;
					}
				}
				if (needsSaving) {
					activateExitMenu();
				}
				else {
					exitScene(false);
				}
				return;
			}
			else{
				if (directionPlayer2 == FK_Input_Buttons::Down_Direction){
					increaseMenuIndex();
					lastInputTime = now;
				}
				else if (directionPlayer2 == FK_Input_Buttons::Up_Direction){
					decreaseMenuIndex();
					lastInputTime = now;
				}
				else if (directionPlayer2 == FK_Input_Buttons::Left_Direction ||
					directionPlayer2 == FK_Input_Buttons::Right_Direction){
					togglePlayer();
					lastInputTime = now;
				}
				else{
					if (lastButtonPlayer2 == FK_Input_Buttons::Selection_Button){
						selectItem();
						lastInputTime = now;
						Sleep(200);
						return;
					}
				}
			}
		}
	}
}