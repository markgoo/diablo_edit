
// Diablo Edit2.h: Diablo Edit2 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

#include <vector>
#include <unordered_map>
#include "ItemDataStruct.h"

CString CSFormat(LPCTSTR lpszFormat, ...);

class CProperty
{
	std::vector<std::pair<int, int>> fields_;
	int bitsSum_ = 0;
public:
	CProperty() {}
	CProperty(std::vector<std::pair<int, int>> fields);
	int Bits() const { return bitsSum_; }
	std::vector<int> Parse(DWORD value) const;
};

// CDiabloEdit2App:
// 有关此类的实现，请参阅 Diablo Edit2.cpp
//

class CDiabloEdit2App : public CWinApp
{
public:
	CDiabloEdit2App() noexcept;

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
// 自定义成员
public:
	static const UINT CLASS_SKILL_NAME_SIZE = 30;			//每种角色技能数量
	static const UINT CLASS_SKILL_TAB_SIZE = 3;				//每种角色技能树数量
	static const UINT CLASS_NAME_SIZE = 7;					//角色数量
	static const int CLASS_SKILL_INDEX[CLASS_NAME_SIZE][CLASS_SKILL_NAME_SIZE];	//每种角色每个技能索引偏移
	INT m_nLangIndex = 0;			//当前语言索引
	// Functions
	const CString & AppPath() const { return m_sAppPath; }
	INT LangCount() const { return m_saLanguage.size(); }
	CString PorpertyDescription(WORD id, DWORD value) const;	//根据属性id和参数value,得到属性的描述字符串
	const CString & LangTitle(UINT index) const {
		ASSERT(index < m_saLanguage.size());
		return m_saLanguage[index][0];
	}
	const CString & MsgWarning() const { return Msg(5); }
	const CString & MsgError() const { return Msg(6); }
	const CString & MsgUnknown() const { return Msg(15); }
	const CString & MsgNoTitle() const { return Msg(12); }
	const CString & Msg(UINT index) const { return String(SectionToIndex(OTHER_MSG, index)); }
	const CString & OtherUI(UINT index) const { return String(SectionToIndex(OTHER_UI, index)); }
	const CString & ItemSuspendUI(UINT index) const { return String(SectionToIndex(ITEM_SUSPEND_UI, index)); }
	const CString & PrefixSuffixUI(UINT index) const { return String(SectionToIndex(PREFX_SUFFIX_UI, index)); }
	const CString & CharItemsUI(UINT index) const { return String(SectionToIndex(CHAR_ITEMS_UI, index)); }
	const CString & CharBasicInfoUI(UINT index) const { return String(SectionToIndex(CHAR_BASIC_INFO_UI, index)); }
	const CString & MsgBoxInfo(UINT index) const { return String(SectionToIndex(MSG_BOX_INFO, index)); }
	const CString & ItemQualityName(UINT index) const { return String(SectionToIndex(ITEM_QUALITY_NAME, index)); }
	const CString & DifficultyName(UINT index) const { return String(SectionToIndex(DIFFICULTY_NAME, index)); }
	const CString & WayPointName(UINT index) const { return String(SectionToIndex(WAY_POINT_NAME, index)); }
	const CString & QuestName(UINT index) const { return String(SectionToIndex(QUEST_NAME, index)); }
	const CString & NormalSkillName(UINT index) const { return String(SectionToIndex(NORMAL_SKILL_NAME, index)); }
	std::pair<CString, int> ClassSkillName(UINT skill_id) const;			//根据绝对技能索引(0-280)得到技能名字，以及角色id
	const CString & ClassSkillName(UINT index, UINT class_id) const {		//根据角色id和技能相对索引(0-29)，得到技能名字
		ASSERT(index < CLASS_SKILL_NAME_SIZE && class_id < CLASS_NAME_SIZE);
		return String(SectionToIndex(CLASS_SKILL_NAME, class_id * CLASS_SKILL_NAME_SIZE + index));
	}
	const CString & ClassSkillTabName(UINT tab, UINT class_id) const { //根据角色id和技能树索引,得到技能树名字
		ASSERT(tab < CLASS_SKILL_TAB_SIZE && class_id < CLASS_NAME_SIZE);
		return String(SectionToIndex(CLASS_SKILL_TAB_NAME, class_id * CLASS_SKILL_TAB_SIZE + tab));
	}
	const CString & TimeName(UINT index) const { return String(SectionToIndex(TIME_NAME, index)); }
	const CString & ClassName(UINT index) const { return String(SectionToIndex(CLASS_NAME, index)); }
	const CString & ItemName(UINT index) const { return String(SectionToIndex(ITEM_NAME, index)); }
	const CString & PropertyName(UINT index) const { return String(SectionToIndex(PROPERTY_NAME, index)); }
	const CString & MonsterName(UINT index) const { return String(SectionToIndex(MONSTER_NAME, index)); }
	const CString & MagicPrefix(UINT index) const { return String(SectionToIndex(MAGIC_PREFIX, index)); }
	const CString & MagicSuffix(UINT index) const { return String(SectionToIndex(MAGIC_SUFFIX, index)); }
	const CString & RareCraftedName(UINT index) const { return String(SectionToIndex(RARE_CRAFTED_NAME, index)); }
	const CString & UniqueName(UINT index) const { return String(SectionToIndex(UNIQUE_NAME, index)); }
	UINT ItemQualityNameSize() const { return SectionSize(ITEM_QUALITY_NAME); }
	UINT DifficultyNameSize() const { return SectionSize(DIFFICULTY_NAME); }
	UINT MagicPrefixSize() const { return SectionSize(MAGIC_PREFIX); }
	UINT MagicSuffixSize() const { return SectionSize(MAGIC_SUFFIX); }
	UINT RareCraftedNameSize() const { return SectionSize(RARE_CRAFTED_NAME); }
	UINT UniqueNameSize() const { return SectionSize(UNIQUE_NAME); }

	const CItemDataStruct * ItemData(DWORD typeID) const {	//如果没有,返回0
		std::unordered_map<DWORD, CItemDataStruct>::const_iterator wh = m_mapItemData.find(typeID);
		return wh == m_mapItemData.end() ? 0 : &wh->second;
	}
	const CProperty & PropertyData(UINT index) const {
		ASSERT(index < m_vProperty.size());
		return m_vProperty[index];
	}
private:
	CString m_sAppPath;			//程序运行的目录
	std::vector<std::vector<CString>> m_saLanguage;		//语言数据
	std::vector<UINT> m_aLangBases;
	enum LangSection {
		UNIQUE_NAME = 1,		//暗金装备名字
		RARE_CRAFTED_NAME,		//Rare和Crafted装备名字
		MAGIC_SUFFIX,			//魔法后缀
		MAGIC_PREFIX,			//魔法前缀
		MONSTER_NAME,			//怪物名称
		PROPERTY_NAME,			//属性名称
		ITEM_NAME,				//物品名称
		CLASS_NAME,				//角色名字
		TIME_NAME,				//时刻名字
		CLASS_SKILL_TAB_NAME,	//角色技能树名字（不是技能名）
		CLASS_SKILL_NAME,		//角色技能名字
		NORMAL_SKILL_NAME,		//通用技能名字
		QUEST_NAME,				//任务名字
		WAY_POINT_NAME,			//小站名字
		DIFFICULTY_NAME,		//游戏难度
		ITEM_QUALITY_NAME,		//物品质量名字
		MSG_BOX_INFO,			//对话框消息
		CHAR_BASIC_INFO_UI,		//角色基本信息UI
		CHAR_ITEMS_UI,			//角色装备信息UI
		PREFX_SUFFIX_UI,		//物品前后缀窗口UI
		ITEM_SUSPEND_UI,		//物品属性悬浮窗口UI
		OTHER_UI,				//其他窗口UI
		OTHER_MSG,				//其他
	};
	std::unordered_map<DWORD, CItemDataStruct>	m_mapItemData;	//物品额外信息,以TypeID作为关键字
	std::vector<CProperty> m_vProperty;                     //属性数据
	//Functions
	BOOL ReadLangRes(void);		//从语言资源文件里读取语言数据
	BOOL ReadItemRes(void);		//从物品资源文件里读取额外物品数据
	BOOL ReadPropRes(void);		//从属性资源文件里读取属性数据
	const CString & String(UINT index) const {
		ASSERT(index < m_saLanguage[m_nLangIndex].size());
		//ASSERT(!m_saLanguage[m_nLangIndex][index].IsEmpty());
		return m_saLanguage[m_nLangIndex][index];
	}
	UINT SectionSize(LangSection section) const {
		ASSERT(m_aLangBases[section - 1] >= m_aLangBases[section]);
		return m_aLangBases[section - 1] - m_aLangBases[section];
	}
	UINT SectionToIndex(LangSection section, UINT index) const {
		ASSERT(index < SectionSize(section));
		return index + m_aLangBases[section];
	}
};

extern CDiabloEdit2App theApp;
