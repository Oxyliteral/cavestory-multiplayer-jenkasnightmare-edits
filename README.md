# cavestory-multiplayer-jenkasnightmare-edits

Edits for autumn-mnya's Jenka's Nightmare for Cave Story Multiplayer. Download, and overwrite autumn's jenkasnightmare folder with this jenkasnightmare folder.

Specific edits currently include:

**jenkasnightmare.dll**

*: Snake reloads every 60 frames, 20 with afterburner. Machine gun reloads faster with turbocharge. Spur charges twice as fast with the Ursa Minor (Polar Star capsule new game plus item).

**head.tsc**

*: Edits a certain event to set the correct flag, preventing the game from sometimes starting you from the beginning without loading a save when dying. (Also makes it so the game always loads a save when clicking retry, as loading with no save file just starts from a new game, so it is not an issue, and prevents certain sequence breaks (saving without flag setting)

**Stage/JN079.pxcm**

*: Config added to door, press down to interact and bring up menus for new game plus purposes (can add/remove every weapon, add/remove all life capsules, add/remove certain items with new game plus usage), or start a true new game.

**mod.pxmod**

*: New game starting location set to new game plus prefab house (for use with above edit). To start a true new game, interact with the door. Additionally, weapons/bullets have been synced to JN. This is most noticeable with the Snake, which has a range increase and different damage values.

Based off of CSM's CaveModBase (v1.0.5) found at https://cavestorymultiplayer.com/modding/

Additional references found at:

https://github.com/ClayHanson/CaveStory-Multiplayer-Public/

https://cavestorymultiplayer.com/modding/docs/index.html
