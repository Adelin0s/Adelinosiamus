#pragma once

// Client version ////////////////////////////////////////////////////////
#define APP_CLIENT_VERSION 1000011

//#define LIVE_SERVER
#if defined(LIVE_SERVER)
	#define __USE_CYTHON__
	#define CHECK_AUTOPATCHER
	#if defined(CHECK_AUTOPATCHER)
		#define PATCHER_ARG "--ghf3Nqww5N8D4qB62s3vk5by"
	#endif
#endif
// End of client version ////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// ### Default Ymir Macros ###
#define LOCALE_SERVICE_EUROPE               // New Locale Service
#define ENABLE_COSTUME_SYSTEM               // Costume System
#define ENABLE_ENERGY_SYSTEM                // Energy Old System
#define ENABLE_DRAGON_SOUL_SYSTEM           // DSS 
#define ENABLE_NEW_EQUIPMENT_SYSTEM         // New Equipment Slots
// ### Default Ymir Macros ###
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// ### New From LocaleInc ###
//#define ENABLE_PACK_GET_CHECK             // Check Pack
#define ENABLE_CANSEEHIDDENTHING_FOR_GM     // You can see invisible things as GM
#define ENABLE_PLAYER_PER_ACCOUNT5          // 5 characters per account
#define ENABLE_LEVEL_IN_TRADE               // Level in trade
#define ENABLE_DICE_SYSTEM                  // Dice system
#define ENABLE_EXTEND_INVEN_SYSTEM          // Extend inventory to 4pages
#define ENABLE_LVL115_ARMOR_EFFECT          // New Lv115 armor effects
#define ENABLE_SLOT_WINDOW_EX               // New Slow window
#define ENABLE_TEXT_LEVEL_REFRESH           // New Text Level Refresh
#define ENABLE_USE_COSTUME_ATTR             // Costume Attributes
#define ENABLE_DISCORD_RPC                  // Discord RPC Information
#define ENABLE_PET_SYSTEM_EX                // New Pet System items
#define ENABLE_LOCALE_EX                    // New Locale funcs
#define ENABLE_NO_DSS_QUALIFICATION         // No DSS Qualifiucation
#define ENABLE_NO_SELL_PRICE_DIVIDED_BY_5   // New recalculation for prices
#define ENABLE_PENDANT_SYSTEM               // Talisman system
#define ENABLE_ELEMENT_ADD					// New Talisman Icon
#define ENABLE_GLOVE_SYSTEM                 // Glove System
#define ENABLE_MOVE_CHANNEL                 // Change channel
#define ENABLE_QUIVER_SYSTEM                // New Quiver System
#define ENABLE_4TH_AFF_SKILL_DESC           // 4th Aff Skill description

#define WJ_SHOW_MOB_INFO                    // Show Mob Info State
#ifdef WJ_SHOW_MOB_INFO
#define ENABLE_SHOW_MOBAIFLAG               // Show Mob Aggresive State
#define ENABLE_SHOW_MOBLEVEL                // Show Mob Level
#endif
// ### New From LocaleInc ###
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// ### From GameLib ###
#define ENABLE_WOLFMAN_CHARACTER			// Enable Wolfman
#ifdef ENABLE_WOLFMAN_CHARACTER				
#define DISABLE_WOLFMAN_ON_CREATE			// Disable wolfman creation
#endif
#define ENABLE_MAGIC_REDUCTION_SYSTEM		// New Magic Reduction Recalculation
#define ENABLE_MOUNT_COSTUME_SYSTEM         // Mount Costume System
#define ENABLE_WEAPON_COSTUME_SYSTEM        // Weapon Costume System
// ### From GameLib ###
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// ### New System Defines - Extended Version ###

#define ENABLE_ACCE_COSTUME_SYSTEM          // Shoulder Sash System
#define ENABLE_OBJ_SCALLING                 // Object Size Scalling
// #define USE_ACCE_ABSORB_WITH_NO_NEGATIVE_BONUS   // No Negative Bonus on Absortion

// if you want use SetMouseWheelScrollEvent or you want use mouse wheel to move the scrollbar
#define ENABLE_MOUSEWHEEL_EVENT             // New mousewheel event

// it shows emojis in the textlines
#define ENABLE_EMOJI_SYSTEM                 // Emoji functions

// effects while hidden won't show up
#define __ENABLE_STEALTH_FIX__              // Stealth Ninja fix

// circle dots in minimap instead of squares
#define ENABLE_MINIMAP_WHITEMARK_CIRCLE     // New Whitemark circle

// for debug: print received packets
//#define ENABLE_PRINT_RECV_PACKET_DEBUG   // Print Packet Debug

// ### New System Defines - Extended Version ###
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// ### Hex Defines - New Zenaris Version ###

#define ENABLE_ENTITY_PRELOADING			// Load Entity Information from Server ( Prevent Frame Spikes )
#define ENABLE_LOADING_PERFORMANCE			// Client loading performance ( Boost Loading Time )
//#define __VERTEX_BUFFER_PERFORMANCE__		// Vertex Buffer ( Boost Frames Per Second )
#define __TEXT_PERFORMANCE__				// Boosts the Text Performance
#define __TEXT_BOOST__						// Outline render boost

#define ENABLE_OFFLINESHOP_SYSTEM			// Define the Offlineshop System
#ifdef ENABLE_OFFLINESHOP_SYSTEM
	#define ENABLE_SHOP_SEARCH_SYSTEM		// Define Search Shop System
#endif

#define WJ_MULTI_TEXTLINE					// Multiple lines of text on the same script
#define ENABLE_DETAILS_UI					// Page Info for Bonuses in Character Window
#define ENABLE_WIKI							// Wikipedia System
#define ENABLE_RENDER_TARGET				// Render Target Objects
#define ENABLE_NEW_GAMEOPTION				// New Game Option Settings and new Button funcs
#define _USE_CPP_RTL_FLIP					// Define for C++ variant for Right To Left Flip
#define __VERSION__							// Check client version for players

#define ENABLE_MULTI_FARM_BLOCK				// Multi Farm Block for multiple characters
#define __RENEWAL_BRAVE_CAPE__				// Automatic Bravery Cape
#define ENABLE_DUNGEON_BOSS_ICON_IN_MAP		// Boss Position and Respawn Info on atlas
#define RENEWAL_PICKUP_AFFECT				// Auto Pick Up Premium Feature
#define RENEWAL_MISSION_BOOKS				// Renewal Mission Book System
#define ENABLE_EVENT_MANAGER				// Event Handler
#define ENABLE_REWARD_SYSTEM				// Reward For New Players
#define ENABLE_BATTLE_PASS					// Battle Pass 
#define ENABLE_WHEEL_OF_FORTUNE				// Wheel Of Fortune with item
#define ENABLE_BIYOLOG						// Biolog System
#define ENABLE_RENEWAL_AFFECT_SHOWER		// New Categories for the Affects

#define ENABLE_DS_GRADE_MYTH				// New Mythic Alchemy
#define ENABLE_DS_SET						// New bonuses when the wheel is complete

#define ENABLE_VIEW_TARGET_PLAYER_HP		// Player HP
#define ENABLE_VIEW_TARGET_DECIMAL_HP		// Decimal HP

#define ENABLE_CUBE_RENEWAL_WORLDARD		// Offical Cube System
#define ENABLE_POISON_GAUGE_EFFECT			// Poison Effect for Target Bar
#define ENABLE_SEND_TARGET_INFO				// Info about drops on the Target Menu

#define ENABLE_SWITCHBOT					// Switchbot
#define ENABLE_FIX_PICKITEM					// Fix Pickup Item Distance
#define ENABLE_QUEST_RENEWAL				// Quest Page Renewal
#define ENABLE_FOV_OPTION					// Fov System + Slider + Fov on Minimap

#define ENABLE_REFINE_RENEWAL				// New Refine Keep Window
#define ENABLE_REFINE_MSG_ADD				// Fail message
#define __BL_PARTY_POSITION__				// Party Position for each Member

#define ENABLE_ITEM_APPLY4					// 4 attributes on the item
#define ENABLE_NEW_PET_SYSTEM				// New Pet System
#define __BUFFI_SUPPORT__					// Enable New Buffi System
#define ENABLE_SPECIAL_COSTUME_ATTR			// Enchant for Costumes
#define __RENEWAL_CRYSTAL__					// New Energy Crystal
#define __PERMA_ACCESSORY__					// Perma buff for accessories

#define ENABLE_NEW_BLEND_AFFECT				// New Blends
#define ENABLE_EXTENDED_BLEND_AFFECT		// Extended Blend System
#define __TIME_STACKEBLE__					// Item Time Stackable
#define __BL_67_ATTR__						// 6 7 bonuses

#define TEXT_LAG_IMPROVEMENT				// Improvements for text performance
#define __RENEWAL_INTERFACE_RENDER__		// New Interface Render
#define ENABLE_PERFORMANCE					// New performance mode
#define ENABLE_NEW_OPTIMIZATION				// New optimization
#define EMOTICON_FIX						// Fix emoticon icons

#define ENABLE_GEM_SYSTEM					// New Gem System

// Damage effect types
#define ENABLE_EFFECT_DAMAGE_CRITICAL_AND_PENETRATE
#define ENABLE_EFFECT_TARGET_CRITICAL_AND_PENETRATE
#define ENABLE_EFFECT_DAMAGE_CRITICAL
#define ENABLE_EFFECT_TARGET_CRITICAL
#define ENABLE_EFFECT_DAMAGE_PENETRATE
#define ENABLE_EFFECT_TARGET_PENETRATE
#define ENABLE_EFFECT_DAMAGE_POISON
#define ENABLE_EFFECT_DAMAGE_FIRE
#define ENABLE_EFFECT_DAMAGE_BLEEDING

#define ENABLE_CONFIG_MODULE				// New Configuration Module (File Settings)
#define __BL_EVENT_STONE_SHAPE_CHANGE__		// Stone shape based on event
#define ENABLE_SPECIAL_INVENTORY_SYSTEM		// Special Inventory System

#define __DUNGEON_INFO__					// New dungeon manager
#define __PENDANT__							// New pendants
#define ENABLE_SWAP_SLOT_SYSTEM				// Swap Item Slot
#if defined(ENABLE_SWAP_SLOT_SYSTEM)
#	define ENABLE_SWAP_SLOT_DIFFUSE_COLOR	// Diffuse Color Swap Slot
#endif
#define ENABLE_SORT_INVENTORY				// Sort Inventory Items
#define ITEM_CHECKINOUT_UPDATE				// Check Items
#define __BACK_DUNGEON__					// Back in dungeon
#define __BL_MOVE_COSTUME_ATTR__			// Move Costume Attributes
#define ENABLE_HIDE_COSTUME_SYSTEM			// Hide costumes from inventory


#define ENABLE_RENEWAL_SHOPEX				// New Shop functions with pges
#define ENABLE_CHATTING_WINDOW_RENEWAL		// New chat interface and functions
#define WJ_ENABLE_TRADABLE_ICON				// Tradable icons
#define ENABLE_678TH_SKILL					// New boost and ward skills

#define ENABLE_RENDER_STATE_FIX				// Fix for render state.
#define  __ENABLE_SHAMAN_ATTACK_FIX__		// Fix for shaman attack
#define ENABLE_NEW_EXCHANGE_WINDOW			// New exchange functions.
#define ENABLE_BADGE_NOTIFICATION_MANAGER	// New notifications for the game.
#define ENABLE_NPC_WEAR_ITEM				// Preview function for NPCs.
#define ENABLE_ULTIMATE_REGEN				// New regen with info on atlas.

#define __RENEWAL_NOTICE__					// New notice aspect.
#define ENABLE_TELEPORT_MINIMAP_GM			// GMs can teleport via click on atlas.
#define __BL_ENABLE_PICKUP_ITEM_EFFECT__	// Pickup item effect in inventory.
#define LINK_IN_CHAT						// Link in chat.
#define __MAINTENANCE__						// New maintenance mode.
#define KEEP_DRAGON_BEAN					// Keep dragon beans in the refinement window.

#define ENABLE_MESSENGER_BLOCK				// Messenger Block System.
#define ENABLE_MESSENGER_LOCK_FIX			// Messenger List Lock Fix.
#define ENABLE_MESSENGER_GM					// Messenger GM List.

#define ENABLE_DS_CHANGE_ATTR				// Change DSS bonus.

#define ENABLE_SHOPEX_RENEWAL				// New shop functions.
#if defined(ENABLE_SHOPEX_RENEWAL)
#	define ENABLE_SHOPEX_TAB4				// Now you can use up to 4 pages for the shops.
#endif
#define RENEWAL_DEAD_PACKET					// New timer for dead event.
#define BL_SORT_LASTPLAYTIME				// Sort characters by last play time.
#define ENABLE_IMPROVED_LOGOUT_POINTS		// Improved logout points.
#define ENABLE_SAVE_LAST_WINDOW_POSITION	// Save last window position.
#define __SASH_SKIN__						// New sash skins.
#define ENABLE_SHIP_DEFENSE					// Ship Defense (Hydra Dungeon)
#define ENABLE_GUILD_TOKEN_AUTH				// Fix for guild exploit.

//#define ENABLE_SEQUENCE_SYSTEM
#define CEF_BROWSER							// Chromium Embedded Framework Browser 
#define ENABLE_CHEST_OPEN_RENEWAL			// Open multiple chests at once.
#define ENABLE_CHAT_LOG_FIX					// Chat-log window fix
#define SAVE_WHISPER						// Save whisper even if offline.
#define ENABLE_QUEST_WIDTH_EXPANSION		// New quest size.
#define BL_OFFLINE_MESSAGE					// Offline private messages
#define ENABLE_TAB_NEXT_TARGET				// Tab Targeting
#define METINSTONES_QUEUE					// Metinstones queue system
#define __SAVE_BLOCK_ATTR__
#define __LOBBY_MAP_VISIBILITY__
#define ENABLE_MINI_GAME_OKEY

// ### Hex Defines - New Zenaris Version ###	
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// ### Jettyx Defines - New Zenaris Version ###

#define DIRECTX9								// Define DirectX9 Update
/* DIRECTX SELECT*/
#ifdef DIRECTX9
#define D3DLIGHT8					D3DLIGHT9
#define D3DMATERIAL8				D3DMATERIAL9
#define IDirect3DVertexBuffer8		IDirect3DVertexBuffer9
#define LPDIRECT3DTEXTURE8			LPDIRECT3DTEXTURE9
#define LPDIRECT3DSURFACE8			LPDIRECT3DSURFACE9
#define D3DVIEWPORT8				D3DVIEWPORT9
#define LPDIRECT3DDEVICE8			LPDIRECT3DDEVICE9
#define LPDIRECT3DVERTEXBUFFER8		LPDIRECT3DVERTEXBUFFER9
#define LPDIRECT3DINDEXBUFFER8		LPDIRECT3DINDEXBUFFER9
#define DXLOCKTYPE					(void**)
#define D3DVERTEXELEMENT8			D3DVERTEXELEMENT9
#define LPDIRECT3DBASETEXTURE8		LPDIRECT3DBASETEXTURE9
#define LPDIRECT3DPIXELSHADER8		LPDIRECT3DPIXELSHADER9
#define D3DADAPTER_IDENTIFIER8		D3DADAPTER_IDENTIFIER9
#define IDirect3D8					IDirect3D9
#define IDirect3DDevice8			IDirect3DDevice9
#define D3DCAPS8					D3DCAPS9
#define LPDIRECT3D8					LPDIRECT3D9
#define D3DCAPS2_CANRENDERWINDOWED	DDCAPS2_CANRENDERWINDOWED
#define IDirect3DTexture8			IDirect3DTexture9
#define Direct3DCreate8				Direct3DCreate9
#define IDirect3DSurface8			IDirect3DSurface9
#else
#define DXLOCKTYPE					(BYTE**)
#endif

#define JETTYX_TRANSPARENCY_BUILDING_FIX
#define JTX_SPECULAR
#define JTX_EXTENDED_COLLISIONS
#define JTX_ENABLE_GRAPHICS_OPTIONS
#define JTX_UNLOAD_GRASS
#define JTX_DISTANCE_SETTINGS
#define ENABLE_GRAPHIC_ON_OFF
#define ENABLE_ENVIRONMENT_EFFECT_OPTION // Environment Effect Options
#define JTX_INDOOR_LIGHT

#define ENABLE_FIX_MOBS_LAG
#if defined(ENABLE_FIX_MOBS_LAG)
	// -> The define ENABLE_FIX_MOBS_LAG have problems in device reseting.
	// -> With this new define all this problems are fixed.
#define FIX_MOBS_LAG_FIX
#endif

#define IMPROVE_ENTITY_FREEZE
#define JTX_BLOOD
#define ENABLE_SAFEZONE_STOP_COLLISION
#define JTX_FIX_CAN_ATTACK
//#define JTX_FIX_WIKIFRUSTUM
//#define JTX_FPS
#define JTX_ENTIRE_TERRAIN_RENDER				// Randare in cache full map, fix freeze schimbare chunk

// ### Jettyx Defines - New Zenaris Version ###
//////////////////////////////////////////////////////////////////////////
//martysama0134's 7f12f88f86c76f82974cba65d7406ac8
