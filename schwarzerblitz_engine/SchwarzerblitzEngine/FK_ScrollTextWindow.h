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

#ifndef FK_SCROLLTEXT_WINDOW_CLASS
#define FK_SCROLLTEXT_WINDOW_CLASS

#include <irrlicht.h>
#include "FK_Window.h"
#include<vector>

using namespace irr;

namespace fk_engine {
	class FK_ScrollTextWindow : public FK_Window {
	private:
		const u32 DialogueOffsetX = 10;
		const u32 DialogueOffsetY = 10;
		const f32 ScrollSpeedPerSecond = 60.f;
	public:
		FK_ScrollTextWindow(IrrlichtDevice *new_device, core::rect<s32> newFrame,
			std::string new_skinName, std::string new_path,
			f32 scaleFactor,
			std::vector<std::string> textLines);
		void reset(f32 scaleFactor, std::vector<std::string> textLines);
		void resetTextPosition();
		virtual void update(u32 pressedButtons, u32 delta_t_ms);
		void drawText(f32 scaleX = 1.0f, f32 scaleY = 1.0f);
		void drawArrows(f32 scaleX = 1.0f, f32 scaleY = 1.0f);
		void draw(core::dimension2d<u32> screenSize, f32 scaleX = 1.0f, f32 scaleY = 1.0f, bool drawArrow_flag = true);
	private:
		void processTextLines(std::vector<std::string> textLines, f32 scaleFactor);
	private:
		IrrlichtDevice *device;
		video::IVideoDriver *driver;
		video::ITexture* mugshotTexture;
		video::ITexture* arrowTextureDown;
		video::ITexture* arrowTextureUp;
		std::vector <std::wstring> windowText;
		gui::IGUIFont* font;
		u32 textWidth;
		s32 currentLineX;
		s32 currentLineY;
		u32 currentLineIndex;
		u32 timeElapsed;
		f32 textPosition;
		bool lineBefore;
		bool lineAfter;
	};
}

#endif
