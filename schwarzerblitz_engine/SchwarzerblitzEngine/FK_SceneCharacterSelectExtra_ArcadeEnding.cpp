#include "FK_SceneCharacterSelectExtra_ArcadeEnding.h"
#include "FK_Database.h"
#include <fstream>
#include <iostream>
#include <algorithm>

namespace fk_engine {

	FK_SceneCharacterSelectExtra_ArcadeEnding::FK_SceneCharacterSelectExtra_ArcadeEnding() : FK_SceneCharacterSelectExtra() {

	};

	FK_Scene::FK_SceneExtraType FK_SceneCharacterSelectExtra_ArcadeEnding::getExtraSceneType() {
		return FK_Scene::FK_SceneExtraType::ExtraArcadeEndingGallery;
	}

	/* get cutscene if it is unlocked */
	FK_StoryEvent FK_SceneCharacterSelectExtra_ArcadeEnding::getCutsceneToPlay()
	{
		FK_StoryEvent cutscene;
		auto playerOutfit = FK_SceneCharacterSelectArcade::getPlayerOutfit();
		std::string charactersPath = FK_SceneCharacterSelectArcade::charactersDirectory;
		std::string playerPath = FK_SceneCharacterSelectArcade::getPlayerPath();
		/*std::string endingFilePath =
			charactersPath + playerPath + playerOutfit.outfitDirectory +
			fk_constants::FK_CharacterArcadeFolder + fk_constants::FK_CharacterArcadeEndingFileName;
		std::ifstream inputFile(endingFilePath.c_str());
		std::string relativePath = playerPath + playerOutfit.outfitDirectory;
		if (!inputFile) {
			inputFile.clear();
			inputFile.close();
			endingFilePath =
				charactersPath + playerPath +
				fk_constants::FK_CharacterArcadeFolder + fk_constants::FK_CharacterArcadeEndingFileName;
			relativePath = playerPath;
			inputFile = std::ifstream(endingFilePath.c_str());
		}
		if (!inputFile) {
			return cutscene;
		}
		else {
			inputFile.close();
			inputFile.clear();
			cutscene.setup(fk_constants::FK_CharacterArcadeEndingFileName,
				charactersPath + relativePath + fk_constants::FK_CharacterArcadeFolder, relativePath);
			cutscene.playCredits = false;
			cutscene.allowMenu = true;
			cutscene.saveStoryCompletion = false;
			cutscene.saveWhenSkipped = false;
			cutscene.fadeWhenEnding = true;
		}*/
		u32 extraEndingInput = player1input->getPressedButtons();
		if (!player1IsActive) {
			extraEndingInput = player2input->getPressedButtons();
		}
		extraEndingInput &= FK_Input_Buttons::Trigger_Button;
		// play extra ending if Trigger input is pressed before the scene
		bool validEndingFile = false;
		std::string endingFilePath;
		std::string relativePath;
		std::string arcadeEndingConfigFileName;
		if (extraEndingInput != 0) {
			endingFilePath =
				charactersPath + playerPath + playerOutfit.outfitDirectory +
				fk_constants::FK_CharacterArcadeFolder + fk_constants::FK_CharacterArcadeAlternateEndingFileName;
			std::ifstream inputFile(endingFilePath.c_str());
			relativePath = playerPath + playerOutfit.outfitDirectory;
			if (!inputFile) {
				inputFile.clear();
				inputFile.close();
				endingFilePath =
					charactersPath + playerPath +
					fk_constants::FK_CharacterArcadeFolder + fk_constants::FK_CharacterArcadeAlternateEndingFileName;
				relativePath = playerPath;
				inputFile = std::ifstream(endingFilePath.c_str());
			}
			if (inputFile.good()) {
				validEndingFile = true;
				arcadeEndingConfigFileName = fk_constants::FK_CharacterArcadeAlternateEndingFileName;
			}
		}
		if (!validEndingFile) {
			endingFilePath =
				charactersPath + playerPath + playerOutfit.outfitDirectory +
				fk_constants::FK_CharacterArcadeFolder + fk_constants::FK_CharacterArcadeEndingFileName;
			std::ifstream inputFile(endingFilePath.c_str());
			relativePath = playerPath + playerOutfit.outfitDirectory;
			if (!inputFile) {
				inputFile.clear();
				inputFile.close();
				endingFilePath =
					charactersPath + playerPath +
					fk_constants::FK_CharacterArcadeFolder + fk_constants::FK_CharacterArcadeEndingFileName;
				relativePath = playerPath;
				inputFile = std::ifstream(endingFilePath.c_str());
			}
			if (inputFile.good()) {
				validEndingFile = true;
				arcadeEndingConfigFileName = fk_constants::FK_CharacterArcadeEndingFileName;
			}
		}
		if (!validEndingFile) {
			return cutscene;
		}
		else {
			cutscene.setup(arcadeEndingConfigFileName,
				charactersPath + relativePath + fk_constants::FK_CharacterArcadeFolder, relativePath);
			cutscene.playCredits = false;
			cutscene.allowMenu = true;
			cutscene.saveStoryCompletion = false;
			cutscene.saveWhenSkipped = false;
			cutscene.fadeWhenEnding = true;
		}
		return cutscene;
	}

	/* check if ending is available to play */
	bool FK_SceneCharacterSelectExtra_ArcadeEnding::checkIfEndingIsAvailable(std::string& characterPath) {
		std::string charactersPath = FK_SceneCharacterSelectArcade::charactersDirectory;
		std::string endingFilePath =
			charactersPath + characterPath +
			fk_constants::FK_CharacterArcadeFolder + fk_constants::FK_CharacterArcadeEndingFileName;
		std::ifstream inputFile(endingFilePath.c_str());
		if (!inputFile) {
			inputFile.clear();
			inputFile.close();
			return false;
		}
		return true;
	}

	/* load single character outfit list */
	void FK_SceneCharacterSelectExtra_ArcadeEnding::loadSingleCharacterOutfitList(
		u32 characterId, FK_Character* character) {
		u32 selectionId = availableEndingsIndexMap[characterId];
		u32 maxNumberOfOutfits = character->getNumberOfOutfits();
		for (u32 i = 0; i < maxNumberOfOutfits; ++i) {
			FK_Character::FK_CharacterOutfit outfit = character->getOutfit(i);
			std::string charaPath = characterPaths[selectionId];
			std::string key = charaPath + outfit.outfitDirectory;
			if (i == 0) {
				bool unlockedEnding = std::find(storyEpisodesCleared.begin(), storyEpisodesCleared.end(), charaPath) !=
					storyEpisodesCleared.end();
				unlockedEnding |= unlockAllFlag;
				characterAvailableCostumes[characterId].push_back(std::pair<u32, bool>(i, unlockedEnding));
			} else if (checkIfEndingIsAvailable(key)) {
				bool unlockedEnding = std::find(storyEpisodesCleared.begin(), storyEpisodesCleared.end(), key) !=
					storyEpisodesCleared.end();
				unlockedEnding |= unlockAllFlag;
				characterAvailableCostumes[characterId].push_back(std::pair<u32, bool>(i, unlockedEnding));
			}
		}
	}

	/* load character files */
	void FK_SceneCharacterSelectExtra_ArcadeEnding::loadCharacterList() {
		availableEndingsIndexMap.clear();
		u32 availabilityIndex = 0;
		drawLoadingScreen(0);
		dummyCharacterDirectory = "chara_dummy";
		if (!checkIfEndingIsAvailable(dummyCharacterDirectory + "\\")) {
			if (std::find(unlockedCharacters.begin(), unlockedCharacters.end(), dummyCharacterDirectory) != unlockedCharacters.end()) {
				unlockedCharacters.erase(
					std::find(unlockedCharacters.begin(), unlockedCharacters.end(), dummyCharacterDirectory)
				);
			}
		}
		dummyCharacterDirectory += "\\";
		std::string characterFileName = charactersDirectory + fk_constants::FK_CharacterRosterFileName;
		std::ifstream characterFile(characterFileName.c_str());
		u32 characterId = 0;
		u32 characterIdArcadeOpponent = 0;
		std::string charaPath = std::string();
		std::vector<std::string> availableCharacterArray;

		for each (auto unlockable in storyEpisodesCleared) {
			u32 nameIndex = std::find(unlockable.begin(), unlockable.end(), '\\') - unlockable.begin();
			std::string charaName = unlockable.substr(0, nameIndex);
			if (!charaName.empty()) {
				availableCharacterArray.push_back(charaName);
			}
		}

		while (!characterFile.eof() && characterFile >> charaPath) {
			std::string key = charaPath;
			charaPath += "\\";
			int availabilityIdentifier;
			characterFile >> availabilityIdentifier;
			if (availabilityIdentifier == CharacterUnlockKeys::Character_AvailableFromStart ||
				availabilityIdentifier == CharacterUnlockKeys::Character_UnlockableAndShown ||
				availabilityIdentifier == CharacterUnlockKeys::Character_Unlockable_NoArcadeOpponent) {
				if (!checkIfEndingIsAvailable(charaPath)) {
					continue;
				}
				characterPaths.push_back(charaPath);
				availableEndingsIndexMap[characterId] = availabilityIndex;
				availabilityIndex += 1;
				if (unlockAllFlag || std::find(
					availableCharacterArray.begin(),
					availableCharacterArray.end(), key) !=
					availableCharacterArray.end()) {
					availableCharacters.push_back(characterId);
				}
				characterId += 1;

			}
			else if (availabilityIdentifier == CharacterUnlockKeys::Character_Hidden ||
				availabilityIdentifier == CharacterUnlockKeys::Character_Unlockable_Hidden_NoArcadeOpponent) {
				if (!checkIfEndingIsAvailable(charaPath)) {
					continue;
				}
				if (unlockAllFlag || std::find(
					availableCharacterArray.begin(),
					availableCharacterArray.end(), key) !=
					availableCharacterArray.end()) {
					availableCharacters.push_back(characterId);
					characterPaths.push_back(charaPath);
					availableEndingsIndexMap[characterId] = availabilityIndex;
					availabilityIndex += 1;
					characterId += 1;
				}
			}
		};
		characterFile.close();
		availableCharacters.push_back(characterId);
		/*f32 totalProgress = (f32)characterPaths.size() + 1;
		f32 currentProgress = 0;
		for each(std::string chara_path in characterPaths) {
			std::string temp;
			loadSingleCharacterFile(charactersDirectory + chara_path, temp);
			std::wstring wtemp = fk_addons::convertNameToNonASCIIWstring(temp);
			characterNames.push_back(wtemp);
			currentProgress += 1.f;
			drawLoadingScreen(100.f * currentProgress / totalProgress);
		}
		std::string temp;
		loadSingleCharacterFile(charactersDirectory + dummyCharacterDirectory, temp);
		std::wstring wtemp = fk_addons::convertNameToNonASCIIWstring(temp);
		characterNames.push_back(wtemp);
		drawLoadingScreen(100.f);*/
		finalizeCharacterList();
	};
}