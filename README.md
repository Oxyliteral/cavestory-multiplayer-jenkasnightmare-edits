# cavestory-multiplayer-jenkasnightmare-edits

Edits for autumn-mnya's Jenka's Nightmare for Cave Story Multiplayer.

**COMPILED FOR STABLE RELEASE v0.1.1.17b with ModBase v1.0.5**

Compatibility for other stable releases and/or unstable preview builds not guaranteed. Please check the branches tabs for other versions.

**Downloading**

You can download the repo by clicking the green [<> Code] Button, then clicking download zip. Download CSMP, download v1.0.1 of autumn's jenkasnightmare, put it into the CSMP directory, then place the jenkasnightmare folder from this repo into the CSMP directory, and it should prompt you to overwrite the files.

**Character Skin**

Due to CSMP's way of handling character models, at a few certain points in the game, your model will not display as intended, and will instead use the mimigma mask spritesheet, or instead glitch out in the case of the secret item. You may still use your custom character skin, but be aware there may be graphical issues.

To fix this, I have made a custom skin for Jenka's Nightmare, which should show the intended models. It should go in your data/Players folder, not your jenkasnightmare folder, as CSMP does not correctly register skins in modded folders.

Specific edits currently include:

**jenkasnightmare.dll**

*: Snake reloads every 60 frames, 20 with afterburner. Machine gun reloads faster with turbocharge. Spur charges twice as fast with the Ursa Minor (Polar Star capsule new game plus item).

*: Event skipper comes up during events, press/hold <Map> key to skip, or <Inventory> key to hide the popup. It skips text, <NOD, <CLR, and <FAC. It can skip other TSC like <WAI, but I'm pretty sure <WAI is tied to some animations, therefore doing so may break the game, so I left that function out. In multiplayer, ONLY THE HOST may use the event skipper.

*: New TSC commands <UIA and <UIR to set equip flags for using items in inventory. <USE was used previously for this, but it seems to be hardcoded for some items, so they did not work for certain items in multiplayer.

*: Edits player drawing code so the secret item now uses third sprite layer on the sprite sheet.

**head.tsc**

*: Edits a certain event to set the correct flag, preventing the game from sometimes starting you from the beginning without loading a save when dying. (Also makes it so the game always loads a save when clicking retry, as loading with no save file just starts from a new game, so it is not an issue, and prevents certain sequence breaks (saving without flag setting)

**mod.pxmod**

*: New game starting location set to new game plus prefab house (for use with above edit). To start a true new game, interact with the door.

*: Weapons/bullets have been synced to JN. This is most noticeable with the Snake, which has a range increase and different damage values.

*: Save slot count set to 99

**Npc/NpcRegu**

*: Original spritesheet is used instead, this fixes the sky dragon sprite.

**Stage/095 (Throne Room)**

*: <CMP TSC added to save point. Certain blocks were not being edited correctly in multiplayer, so the save point now does it as a backup.

**Stage/079 (A Familiar House)** (New Game+ house)

*: Config added to door, press down to interact and bring up menus for new game plus purposes (can add/remove every weapon, add/remove all life capsules, add/remove certain items with new game plus usage), or start a true new game.

**Stage/062 (Hermit Gunsmith)**

*: Added branch for Polar Star capsule if you also have Spur capsule.

**Stage/032 (Sanctuary)**

*: Added <YNJ option to hidden return point.

**Stage/017 (Pipeworks E), 18 (Pipeworks S)**

*: Fixed endless clogging of pipes in multiplayer.

**ArmsItem.tsc**

*: Certain items now use <UIA and <UIR along with <USE.

**Following have text wrap/overflow fixes:**

*: ArmsItem, 22 (Grasstown), 40 (Workshop), 65 (Abandoned Facility)

Based off of CSM's CaveModBase found at https://cavestorymultiplayer.com/modding/

Additional references found at:

https://github.com/ClayHanson/CaveStory-Multiplayer-Public/

https://cavestorymultiplayer.com/modding/docs/index.html
