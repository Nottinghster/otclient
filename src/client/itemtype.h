/*
 * Copyright (c) 2010-2025 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#ifdef FRAMEWORK_EDITOR
#include <framework/core/declarations.h>
#include <framework/luaengine/luaobject.h>

enum ItemTypeAttr : uint8_t
{
    ItemTypeAttrServerId = 16,
    ItemTypeAttrClientId = 17,
    ItemTypeAttrName = 18,   // deprecated
    ItemTypeAttrDesc = 19,   // deprecated
    ItemTypeAttrSpeed = 20,
    ItemTypeAttrSlot = 21,   // deprecated
    ItemTypeAttrMaxItems = 22,   // deprecated
    ItemTypeAttrWeight = 23,   // deprecated
    ItemTypeAttrWeapon = 24,   // deprecated
    ItemTypeAttrAmmunition = 25,   // deprecated
    ItemTypeAttrArmor = 26,   // deprecated
    ItemTypeAttrMagicLevel = 27,   // deprecated
    ItemTypeAttrMagicField = 28,   // deprecated
    ItemTypeAttrWritable = 29,   // deprecated
    ItemTypeAttrRotateTo = 30,   // deprecated
    ItemTypeAttrDecay = 31,   // deprecated
    ItemTypeAttrSpriteHash = 32,
    ItemTypeAttrMinimapColor = 33,
    ItemTypeAttr07 = 34,
    ItemTypeAttr08 = 35,
    ItemTypeAttrLight = 36,
    ItemTypeAttrDecay2 = 37,   // deprecated
    ItemTypeAttrWeapon2 = 38,   // deprecated
    ItemTypeAttrAmmunition2 = 39,   // deprecated
    ItemTypeAttrArmor2 = 40,   // deprecated
    ItemTypeAttrWritable2 = 41,   // deprecated
    ItemTypeAttrLight2 = 42,
    ItemTypeAttrTopOrder = 43,
    ItemTypeAttrWrtiable3 = 44,   // deprecated
    ItemTypeAttrWareId = 45,
    ItemTypeAttrLast = 46
};

enum ItemCategory : uint8_t
{
    ItemCategoryInvalid = 0,
    ItemCategoryGround = 1,
    ItemCategoryContainer = 2,
    ItemCategoryWeapon = 3,
    ItemCategoryAmmunition = 4,
    ItemCategoryArmor = 5,
    ItemCategoryCharges = 6,
    ItemCategoryTeleport = 7,
    ItemCategoryMagicField = 8,
    ItemCategoryWritable = 9,
    ItemCategoryKey = 10,
    ItemCategorySplash = 11,
    ItemCategoryFluid = 12,
    ItemCategoryDoor = 13,
    ItemCategoryDeprecated = 14
};

enum ClientVersion
{
    ClientVersion750 = 1,
    ClientVersion755 = 2,
    ClientVersion760 = 3,
    ClientVersion770 = 3,
    ClientVersion780 = 4,
    ClientVersion790 = 5,
    ClientVersion792 = 6,
    ClientVersion800 = 7,
    ClientVersion810 = 8,
    ClientVersion811 = 9,
    ClientVersion820 = 10,
    ClientVersion830 = 11,
    ClientVersion840 = 12,
    ClientVersion841 = 13,
    ClientVersion842 = 14,
    ClientVersion850 = 15,
    ClientVersion854_OLD = 16,
    ClientVersion854 = 17,
    ClientVersion855 = 18,
    ClientVersion860_OLD = 19,
    ClientVersion860 = 20,
    ClientVersion861 = 21,
    ClientVersion862 = 22,
    ClientVersion870 = 23,
    ClientVersion871 = 24,
    ClientVersion872 = 25,
    ClientVersion873 = 26,
    ClientVersion900 = 27,
    ClientVersion910 = 28,
    ClientVersion920 = 29,
    ClientVersion940 = 30,
    ClientVersion944_V1 = 31,
    ClientVersion944_V2 = 32,
    ClientVersion944_V3 = 33,
    ClientVersion944_V4 = 34,
    ClientVersion946 = 35,
    ClientVersion950 = 36,
    ClientVersion952 = 37,
    ClientVersion953 = 38,
    ClientVersion954 = 39,
    ClientVersion960 = 40,
    ClientVersion961 = 41
};

class ItemType : public LuaObject
{
public:
    void unserialize(const BinaryTreePtr& node);

    void setServerId(uint16_t serverId) { m_serverId = serverId; }
    uint16_t getServerId() { return m_serverId; }

    void setClientId(uint16_t clientId) { m_clientId = clientId; }
    uint16_t getClientId() { return m_clientId; }

    void setCategory(ItemCategory category) { m_category = category; }
    ItemCategory getCategory() { return m_category; }

    void setName(const std::string& name) { m_name = name; }
    std::string getName() { return m_name; }

    void setDesc(const std::string& desc) { m_desc = desc; }
    std::string getDesc() { return m_desc; }

    bool isNull() { return m_null; }
    bool isWritable() { return m_writable; }

private:
    ItemCategory m_category{ ItemCategoryInvalid };
    bool m_null{ true };
    bool m_writable{ false };

    uint16_t m_serverId{ 0 };
    uint16_t m_clientId{ 0 };
    std::string m_name;
    std::string m_desc;
};
#endif
