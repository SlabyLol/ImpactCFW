/*-----------------------------------------------------------------
 Copyright (C) 2005 - 2013
	Michael "Chishm" Chisholm
	Dave "WinterMute" Murphy
	Claudio "sverx"
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
-------------------------------------------------------------------
 Not Copyright (ɔ) 2019 - 2020
    FlameKat53
    Pk11
    RocketRobz
    StackZ
------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <fat.h>
#include "common/nds_loader_arm9.h"
#include "common/inifile.h"
//---------------------------------------------------------------------------------
void stop (void) {
//---------------------------------------------------------------------------------
	while (1) {
		swiWaitForVBlank();
	}
}

//---------------------------------------------------------------------------------
void bootApp (std::string bruh) {
//---------------------------------------------------------------------------------
	if((access(bruh.c_str(), F_OK) == 0)) {
		const char *argarray[] = {bruh.c_str()};
		int err = runNdsFile(argarray[0], 1, argarray, false);
		iprintf("oof: Error %i\n", err);
		stop();
	} else {
		printf("oof: %s not found", bruh.c_str());
		stop();
	}
}

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------
	std::string bootA = "/_nds/Relaunch/extras/bootA.nds";
	std::string bootB = "/_nds/Relaunch/extras/bootB.nds";
	std::string bootX = "/_nds/Relaunch/extras/bootX.nds";
	std::string bootY = "/_nds/Relaunch/extras/bootY.nds";
	std::string bootR = "/_nds/Relaunch/extras/bootR.nds";
	std::string bootL = "/_nds/Relaunch/extras/bootL.nds";
	std::string bootDown = "/_nds/Relaunch/extras/bootDown.nds";
	std::string bootUp = "/_nds/Relaunch/extras/bootUp.nds";
	std::string bootLeft = "/_nds/Relaunch/extras/bootLeft.nds";
	std::string bootRight = "/_nds/Relaunch/extras/bootRight.nds";
	std::string bootStart = "/_nds/Relaunch/extras/bootStart.nds";
	std::string bootSelect = "/_nds/Relaunch/extras/bootSelect.nds";
	std::string bootTouch = "/_nds/Relaunch/extras/bootTouch.nds";
	std::string bootDefault = "/boot.nds";

	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
	vramSetBankH(VRAM_H_SUB_BG);
	consoleInit(NULL, 1, BgType_Text4bpp, BgSize_T_256x256, 15, 0, false, true);

	if (!fatInitDefault()) {
		iprintf ("fatInitDefault failed!\n");
		stop();
	}

	CIniFile ini("/_nds/Relaunch/Relaunch.ini");
	
	bootA = ini.GetString("IMPACTCFW", "BOOT_A_PATH", bootA);
	bootB = ini.GetString("IMPACTCFW", "BOOT_B_PATH", bootB);
	bootX = ini.GetString("IMPACTCFW", "BOOT_X_PATH", bootX);
	bootY = ini.GetString("IMPACTCFW", "BOOT_Y_PATH", bootY);
	bootR = ini.GetString("IMPACTCFW", "BOOT_R_PATH", bootR);
	bootL = ini.GetString("IMPACTCFW", "BOOT_L_PATH", bootL);
	bootDown = ini.GetString("IMPACTCFW", "BOOT_DOWN_PATH", bootDown);
	bootUp = ini.GetString("IMPACTCFW", "BOOT_UP_PATH", bootUp);
	bootLeft = ini.GetString("IMPACTCFW", "BOOT_LEFT_PATH", bootLeft);
	bootRight = ini.GetString("IMPACTCFW", "BOOT_RIGHT_PATH", bootRight);
	bootStart = ini.GetString("IMPACTCFW", "BOOT_START_PATH", bootStart);
	bootSelect = ini.GetString("IMPACTCFW", "BOOT_SELECT_PATH", bootSelect);
	bootTouch = ini.GetString("IMPACTCFW", "BOOT_TOUCH_PATH", bootTouch);
	bootDefault = ini.GetString("IMPACTCFW", "BOOT_DEFAULT_PATH", bootDefault);

	ini.SetString("IMPACTCFW", "BOOT_A_PATH", bootA);
	ini.SetString("IMPACTCFW", "BOOT_B_PATH", bootB);
	ini.SetString("IMPACTCFW", "BOOT_X_PATH", bootX);
	ini.SetString("IMPACTCFW", "BOOT_Y_PATH", bootY);
	ini.SetString("IMPACTCFW", "BOOT_R_PATH", bootR);
	ini.SetString("IMPACTCFW", "BOOT_L_PATH", bootL);
	ini.SetString("IMPACTCFW", "BOOT_DOWN_PATH", bootDown);
	ini.SetString("IMPACTCFW", "BOOT_UP_PATH", bootUp);
	ini.SetString("IMPACTCFW", "BOOT_LEFT_PATH", bootLeft);
	ini.SetString("IMPACTCFW", "BOOT_RIGHT_PATH", bootRight);
	ini.SetString("IMPACTCFW", "BOOT_START_PATH", bootStart);
	ini.SetString("IMPACTCFW", "BOOT_SELECT_PATH", bootSelect);
	ini.SetString("IMPACTCFW", "BOOT_TOUCH_PATH", bootTouch);
	ini.SetString("IMPACTCFW", "BOOT_DEFAULT_PATH", bootDefault);

	mkdir("/_nds/",0777);
	mkdir("/_nds/ImpactCFW/",0777);
	mkdir("/_nds/ImpactCFW/extras",0777);
	ini.SaveIniFile("/_nds/ImpactCFW/ImpactCFW.ini");

  scanKeys();
	int pressed = keysHeld();

	if ((pressed & (KEY_A | KEY_B)) == (KEY_A | KEY_B)) { // menu
		if((access("_nds/ImpactCFW/menu.bin", F_OK) == 0)) {
			runNdsFile("_nds/ImpactCFW/menu.bin", 0, NULL, false);
		} else {
			printf("Error:\nmenu.bin wasn't found!");
			stop();
		}
	} else if ((pressed & (KEY_A | KEY_X)) == (KEY_A | KEY_X)) { // menu alt
		if((access("_nds/ImpactCFW/menu.bin", F_OK) == 0)) {
			runNdsFile("_nds/ImpactCFW/menu.bin", 0, NULL, false);
		} else {
			printf("Error:\nmenu.bin wasn't found!");
			stop();
		}
	} else if (pressed & KEY_A) {
		bootApp(bootA);
	} else if (pressed & KEY_B) {
		bootApp(bootB);
	} else if (pressed & KEY_X) {
		bootApp(bootX);
	} else if (pressed & KEY_Y) {
		bootApp(bootY);
	} else if (pressed & KEY_R) {
		bootApp(bootR);
	} else if (pressed & KEY_L) {
		bootApp(bootL);
	} else if (pressed & KEY_RIGHT) {
		bootApp(bootRight);
	} else if (pressed & KEY_LEFT) {
		bootApp(bootLeft);
	} else if (pressed & KEY_DOWN) {
		bootApp(bootDown);
	} else if (pressed & KEY_UP) {
		bootApp(bootUp);
	} else if (pressed & KEY_START) {
		bootApp(bootStart);
	} else if (pressed & KEY_SELECT) {
		bootApp(bootSelect);
	} else if (pressed & KEY_TOUCH) {
		bootApp(bootTouch);
	} else {
		bootApp(bootDefault);
	}
}
