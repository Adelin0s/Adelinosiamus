#include "PythonrootlibManager.h"
#include "Python27/Python.h"
#ifdef _DEBUG
	#pragma comment (lib, "rootlib_d.lib")
#else
	#pragma comment (lib, "rootlib.lib")
#endif

struct rootlib_SMethodDef
{
	const char* func_name;
	void (*func)();
};

PyMODINIT_FUNC initcolorInfo();
PyMODINIT_FUNC initconsoleModule();
PyMODINIT_FUNC initconstInfo();
PyMODINIT_FUNC initdebugInfo();
PyMODINIT_FUNC initdragon_soul_refine_settings();
PyMODINIT_FUNC initemotion();
PyMODINIT_FUNC initexception();
PyMODINIT_FUNC initgame();
PyMODINIT_FUNC initinterfaceModule();
PyMODINIT_FUNC initintroCreate();
PyMODINIT_FUNC initintroEmpire();
PyMODINIT_FUNC initintroLoading();
PyMODINIT_FUNC initintroLogin();
PyMODINIT_FUNC initintroLogo();
PyMODINIT_FUNC initintroSelect();
PyMODINIT_FUNC initlocaleInfo();
PyMODINIT_FUNC initmouseModule();
PyMODINIT_FUNC initmusicInfo();
PyMODINIT_FUNC initnetworkModule();
PyMODINIT_FUNC initnew_introcreate();
PyMODINIT_FUNC initnew_introselect();
PyMODINIT_FUNC initplayerSettingModule();
PyMODINIT_FUNC initPrototype();
PyMODINIT_FUNC initRootLibCythonizer();
PyMODINIT_FUNC initserverCommandParser();
PyMODINIT_FUNC initserverInfo();
PyMODINIT_FUNC initstringCommander();
PyMODINIT_FUNC initsystem();
PyMODINIT_FUNC inittest_affect();
PyMODINIT_FUNC initui();
PyMODINIT_FUNC inituiacce();
PyMODINIT_FUNC inituiAffectShower();
PyMODINIT_FUNC inituiAttachMetin();
PyMODINIT_FUNC inituiAttr67Add();
PyMODINIT_FUNC inituiAutoban();
PyMODINIT_FUNC inituibattlepass();
PyMODINIT_FUNC inituibiyolog();
PyMODINIT_FUNC inituiCandidate();
PyMODINIT_FUNC inituichangename();
PyMODINIT_FUNC inituiCharacter();
PyMODINIT_FUNC inituicharacterdetails();
PyMODINIT_FUNC inituiChat();
PyMODINIT_FUNC inituiCommon();
PyMODINIT_FUNC inituiCube();
PyMODINIT_FUNC inituicuberenewal();
PyMODINIT_FUNC inituiDragonSoul();
PyMODINIT_FUNC inituidungeontimer();
PyMODINIT_FUNC inituidungeontrack();
PyMODINIT_FUNC inituiEquipmentDialog();
PyMODINIT_FUNC inituieventcalendar();
PyMODINIT_FUNC inituiEx();
PyMODINIT_FUNC inituiExchange();
PyMODINIT_FUNC inituifishinggame();
PyMODINIT_FUNC inituiGameButton();
PyMODINIT_FUNC inituiGameOption();
PyMODINIT_FUNC inituigameoptionnew();
PyMODINIT_FUNC inituigemshop();
PyMODINIT_FUNC inituiGuild();
PyMODINIT_FUNC inituiHelp();
PyMODINIT_FUNC inituiInventory();
PyMODINIT_FUNC inituiitemcombination();
PyMODINIT_FUNC inituiMapNameShower();
PyMODINIT_FUNC inituiMessenger();
PyMODINIT_FUNC inituiMiniMap();
PyMODINIT_FUNC inituimission();
PyMODINIT_FUNC inituiMoveChannel();
PyMODINIT_FUNC inituiofflineshop();
PyMODINIT_FUNC inituiofflineshopbuilder();
PyMODINIT_FUNC inituiOption();
PyMODINIT_FUNC inituiParty();
PyMODINIT_FUNC inituipetsystem();
PyMODINIT_FUNC inituiPhaseCurtain();
PyMODINIT_FUNC inituipickitem();
PyMODINIT_FUNC inituiPickMoney();
PyMODINIT_FUNC inituiPlayerGauge();
PyMODINIT_FUNC inituiPointReset();
PyMODINIT_FUNC inituiPrivateShopBuilder();
PyMODINIT_FUNC inituiprivateshopsearch();
PyMODINIT_FUNC inituiQuest();
PyMODINIT_FUNC inituirank();
PyMODINIT_FUNC inituiRefine();
PyMODINIT_FUNC inituiRestart();
PyMODINIT_FUNC inituireward();
PyMODINIT_FUNC inituiSafebox();
PyMODINIT_FUNC inituisashskin();
PyMODINIT_FUNC inituiScriptLocale();
PyMODINIT_FUNC inituiselectitem();
PyMODINIT_FUNC inituiselectitemex();
PyMODINIT_FUNC inituiSelectMusic();
PyMODINIT_FUNC inituiShop();
PyMODINIT_FUNC inituishoprender();
PyMODINIT_FUNC inituiskillcolor();
PyMODINIT_FUNC inituispecialinventory();
PyMODINIT_FUNC inituiswitchbot();
PyMODINIT_FUNC inituiSystem();
PyMODINIT_FUNC inituiSystemOption();
PyMODINIT_FUNC inituiTarget();
PyMODINIT_FUNC inituiTaskBar();
PyMODINIT_FUNC inituiTip();
PyMODINIT_FUNC inituiToolTip();
PyMODINIT_FUNC inituiUploadMark();
PyMODINIT_FUNC inituiWarpShower();
PyMODINIT_FUNC inituiWeb();
PyMODINIT_FUNC inituiwheeloffortune();
PyMODINIT_FUNC inituiWhisper();
PyMODINIT_FUNC inituiwiki();
PyMODINIT_FUNC initutils();
PyMODINIT_FUNC initwikiui();

rootlib_SMethodDef rootlib_init_methods[] =
{
	{ "colorInfo", initcolorInfo },
	{ "consoleModule", initconsoleModule },
	{ "constInfo", initconstInfo },
	{ "debugInfo", initdebugInfo },
	{ "dragon_soul_refine_settings", initdragon_soul_refine_settings },
	{ "emotion", initemotion },
	{ "exception", initexception },
	{ "game", initgame },
	{ "interfaceModule", initinterfaceModule },
	{ "introCreate", initintroCreate },
	{ "introEmpire", initintroEmpire },
	{ "introLoading", initintroLoading },
	{ "introLogin", initintroLogin },
	{ "introLogo", initintroLogo },
	{ "introSelect", initintroSelect },
	{ "localeInfo", initlocaleInfo },
	{ "mouseModule", initmouseModule },
	{ "musicInfo", initmusicInfo },
	{ "networkModule", initnetworkModule },
	{ "new_introcreate", initnew_introcreate },
	{ "new_introselect", initnew_introselect },
	{ "playerSettingModule", initplayerSettingModule },
	{ "Prototype", initPrototype },
	{ "RootLibCythonizer", initRootLibCythonizer },
	{ "serverCommandParser", initserverCommandParser },
	{ "serverInfo", initserverInfo },
	{ "stringCommander", initstringCommander },
	{ "system", initsystem },
	{ "test_affect", inittest_affect },
	{ "ui", initui },
	{ "uiacce", inituiacce },
	{ "uiAffectShower", inituiAffectShower },
	{ "uiAttachMetin", inituiAttachMetin },
	{ "uiAttr67Add", inituiAttr67Add },
	{ "uiAutoban", inituiAutoban },
	{ "uibattlepass", inituibattlepass },
	{ "uibiyolog", inituibiyolog },
	{ "uiCandidate", inituiCandidate },
	{ "uichangename", inituichangename },
	{ "uiCharacter", inituiCharacter },
	{ "uicharacterdetails", inituicharacterdetails },
	{ "uiChat", inituiChat },
	{ "uiCommon", inituiCommon },
	{ "uiCube", inituiCube },
	{ "uicuberenewal", inituicuberenewal },
	{ "uiDragonSoul", inituiDragonSoul },
	{ "uidungeontimer", inituidungeontimer },
	{ "uidungeontrack", inituidungeontrack },
	{ "uiEquipmentDialog", inituiEquipmentDialog },
	{ "uieventcalendar", inituieventcalendar },
	{ "uiEx", inituiEx },
	{ "uiExchange", inituiExchange },
	{ "uifishinggame", inituifishinggame },
	{ "uiGameButton", inituiGameButton },
	{ "uiGameOption", inituiGameOption },
	{ "uigameoptionnew", inituigameoptionnew },
	{ "uigemshop", inituigemshop },
	{ "uiGuild", inituiGuild },
	{ "uiHelp", inituiHelp },
	{ "uiInventory", inituiInventory },
	{ "uiitemcombination", inituiitemcombination },
	{ "uiMapNameShower", inituiMapNameShower },
	{ "uiMessenger", inituiMessenger },
	{ "uiMiniMap", inituiMiniMap },
	{ "uimission", inituimission },
	{ "uiMoveChannel", inituiMoveChannel },
	{ "uiofflineshop", inituiofflineshop },
	{ "uiofflineshopbuilder", inituiofflineshopbuilder },
	{ "uiOption", inituiOption },
	{ "uiParty", inituiParty },
	{ "uipetsystem", inituipetsystem },
	{ "uiPhaseCurtain", inituiPhaseCurtain },
	{ "uipickitem", inituipickitem },
	{ "uiPickMoney", inituiPickMoney },
	{ "uiPlayerGauge", inituiPlayerGauge },
	{ "uiPointReset", inituiPointReset },
	{ "uiPrivateShopBuilder", inituiPrivateShopBuilder },
	{ "uiprivateshopsearch", inituiprivateshopsearch },
	{ "uiQuest", inituiQuest },
	{ "uirank", inituirank },
	{ "uiRefine", inituiRefine },
	{ "uiRestart", inituiRestart },
	{ "uireward", inituireward },
	{ "uiSafebox", inituiSafebox },
	{ "uisashskin", inituisashskin },
	{ "uiScriptLocale", inituiScriptLocale },
	{ "uiselectitem", inituiselectitem },
	{ "uiselectitemex", inituiselectitemex },
	{ "uiSelectMusic", inituiSelectMusic },
	{ "uiShop", inituiShop },
	{ "uishoprender", inituishoprender },
	{ "uiskillcolor", inituiskillcolor },
	{ "uispecialinventory", inituispecialinventory },
	{ "uiswitchbot", inituiswitchbot },
	{ "uiSystem", inituiSystem },
	{ "uiSystemOption", inituiSystemOption },
	{ "uiTarget", inituiTarget },
	{ "uiTaskBar", inituiTaskBar },
	{ "uiTip", inituiTip },
	{ "uiToolTip", inituiToolTip },
	{ "uiUploadMark", inituiUploadMark },
	{ "uiWarpShower", inituiWarpShower },
	{ "uiWeb", inituiWeb },
	{ "uiwheeloffortune", inituiwheeloffortune },
	{ "uiWhisper", inituiWhisper },
	{ "uiwiki", inituiwiki },
	{ "utils", initutils },
	{ "wikiui", initwikiui },
	{ NULL, NULL },
};

static PyObject* rootlib_isExist(PyObject *self, PyObject *args)
{
	char* func_name;

	if(!PyArg_ParseTuple(args, "s", &func_name))
		return NULL;

	for (int i = 0; NULL != rootlib_init_methods[i].func_name;i++)
	{
		if (0 == _stricmp(rootlib_init_methods[i].func_name, func_name))
		{
			return Py_BuildValue("i", 1);
		}
	}
	return Py_BuildValue("i", 0);
}

static PyObject* rootlib_moduleImport(PyObject *self, PyObject *args)
{
	char* func_name;

	if(!PyArg_ParseTuple(args, "s", &func_name))
		return NULL;

	for (int i = 0; NULL != rootlib_init_methods[i].func_name;i++)
	{
		if (0 == _stricmp(rootlib_init_methods[i].func_name, func_name))
		{
			rootlib_init_methods[i].func();
			if (PyErr_Occurred())
				return NULL;
			PyObject* m = PyDict_GetItemString(PyImport_GetModuleDict(), rootlib_init_methods[i].func_name);
			if (m == NULL) {
				PyErr_SetString(PyExc_SystemError,
					"dynamic module not initialized properly");
				return NULL;
			}
			Py_INCREF(m);
			return Py_BuildValue("S", m);
		}
	}
	return NULL;
}

static PyObject* rootlib_getList(PyObject *self, PyObject *args)
{
	int iTupleSize = 0;
	while (NULL != rootlib_init_methods[iTupleSize].func_name) {iTupleSize++;}

	PyObject* retTuple = PyTuple_New(iTupleSize);
	for (int i = 0; NULL != rootlib_init_methods[i].func_name; i++)
	{
		PyObject* retSubString = PyString_FromString(rootlib_init_methods[i].func_name);
		PyTuple_SetItem(retTuple, i, retSubString);
	}
	return retTuple;
}

void initrootlibManager()
{
	static struct PyMethodDef methods[] =
	{
		{"isExist", rootlib_isExist, METH_VARARGS},
		{"moduleImport", rootlib_moduleImport, METH_VARARGS},
		{"getList", rootlib_getList, METH_VARARGS},
		{NULL, NULL},
	};

	PyObject* m;
	m = Py_InitModule("rootlib", methods);
}
