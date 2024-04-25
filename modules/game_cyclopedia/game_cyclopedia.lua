local contentContainer = nil
local buttonSelection = nil
local items = nil
local bestiary = nil
local charms = nil
local map = nil
local houses = nil
local character = nil
local CyclopediaButton = nil
local bosstiary = nil
local bossSlot = nil

function toggle()
    if not controllerCyclopedia.ui then
        return
    end
    if controllerCyclopedia.ui:isVisible() then
        return hide()
    end
    show()
end

controllerCyclopedia = Controller:new()
controllerCyclopedia:setUI('game_cyclopedia')
function controllerCyclopedia:onInit()
    CyclopediaButton = modules.game_mainpanel.addToggleButton('CyclopediaButton', tr('Cyclopedia'),
        '/images/options/cooldowns', toggle, false, 7)
    CyclopediaButton:setOn(false)
    contentContainer = controllerCyclopedia.ui:recursiveGetChildById('contentContainer')
    buttonSelection = controllerCyclopedia.ui:recursiveGetChildById('buttonSelection')
    items = buttonSelection:recursiveGetChildById('items')
    bestiary = buttonSelection:recursiveGetChildById('bestiary')
    charms = buttonSelection:recursiveGetChildById('charms')
    map = buttonSelection:recursiveGetChildById('map')
    houses = buttonSelection:recursiveGetChildById('houses')
    character = buttonSelection:recursiveGetChildById('character')
    bosstiary = buttonSelection:recursiveGetChildById('bosstiary')
    bossSlot = buttonSelection:recursiveGetChildById('bossSlot')

    --[[    note: 
     if not g_game.getFeature(GameCyclopedia) then
        return CyclopediaButton:hide()
    end 
]]
end

function controllerCyclopedia:onGameStart()

end

function controllerCyclopedia:onGameEnd()

    hide()
end

function controllerCyclopedia:onTerminate()
    local widgets = {CyclopediaButton, contentContainer, buttonSelection, items, bestiary, charms, map, houses,
                     character, bosstiary, bossSlot}

    for i = 1, #widgets do
        local widget = widgets[i]
        if widget then
            widget:destroy()
            widgets[i] = nil
        end
    end

end

function hide()
    if not controllerCyclopedia.ui then
        return
    end
    controllerCyclopedia.ui:hide()
end

function show()
    if not controllerCyclopedia.ui or not CyclopediaButton then
        return
    end

    controllerCyclopedia.ui:show()
    controllerCyclopedia.ui:raise()
    controllerCyclopedia.ui:focus()
end


function SelectWindow(type)
    local windowTypes = {
        items = {obj = items,func = showItems},
        bestiary = {obj = bestiary,func = showBestiary},
        charms = {obj = charms,func = showCharms},
        map = {obj = map,func = showMap},
        houses = {obj = houses,func = showHouse}, 
        character = {obj = character,func = showCharacter},
        bosstiary = {obj = bosstiary,func = showBosstiary},
        bossSlot = {obj = bossSlot,func = showBossSlot}
    }

    if previousType then
        previousType.obj:enable()
        previousType.obj:setOn(false)
    end
    contentContainer:destroyChildren()

    local window = windowTypes[type]
    if window then
        window.obj:setOn(true)
        window.obj:disable()
        previousType = window
        if window.func then
            window.func(contentContainer)
        end
    end
end

function showItems()
    local test = g_ui.createWidget("Label", contentContainer)
    test:addAnchor(AnchorLeft, 'parent', AnchorLeft)
    test:addAnchor(AnchorTop, 'parent', AnchorTop)
    test:setText("showItems")
end

function showBestiary()
    local test = g_ui.createWidget("Label", contentContainer)
    test:addAnchor(AnchorLeft, 'parent', AnchorLeft)
    test:addAnchor(AnchorTop, 'parent', AnchorTop)
    test:setText("showBestiary")
end

function showCharms()
    local test = g_ui.createWidget("Label", contentContainer)
    test:addAnchor(AnchorLeft, 'parent', AnchorLeft)
    test:addAnchor(AnchorTop, 'parent', AnchorTop)
    test:setText("showCharms")
end

function showMap()
    local test = g_ui.createWidget("Label", contentContainer)
    test:addAnchor(AnchorLeft, 'parent', AnchorLeft)
    test:addAnchor(AnchorTop, 'parent', AnchorTop)
    test:setText("showMap")
end

function showHouse()
    local test = g_ui.createWidget("Label", contentContainer)
    test:addAnchor(AnchorLeft, 'parent', AnchorLeft)
    test:addAnchor(AnchorTop, 'parent', AnchorTop)
    test:setText("showHouse")
end

function showCharacter()

    local test = g_ui.createWidget("Label", contentContainer)
    test:addAnchor(AnchorLeft, 'parent', AnchorLeft)
    test:addAnchor(AnchorTop, 'parent', AnchorTop)
    test:setText("showCharacter")
end

function showBossSlot()
    local test = g_ui.createWidget("Label", contentContainer)
    test:addAnchor(AnchorLeft, 'parent', AnchorLeft)
    test:addAnchor(AnchorTop, 'parent', AnchorTop)
    test:setText("showBossSlot")
end

function showBosstiary()
    local test = g_ui.createWidget("Label", contentContainer)
    test:addAnchor(AnchorLeft, 'parent', AnchorLeft)
    test:addAnchor(AnchorTop, 'parent', AnchorTop)
    test:setText("showBosstiary")
end

